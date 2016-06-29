// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed  under the "BSD License". See the accompanying LICENSE.rst file.

#include "h264_extractor.hpp"

namespace petro
{
    h264_extractor::h264_extractor(std::ifstream& file) :
        m_file(file)
    {
        auto root = std::make_shared<box::root>();
        byte_stream bs(m_file);

        parser<
            box::moov<parser<
                box::trak<parser<
                    box::mdia<parser<
                        box::hdlr,
                            box::minf<parser<
                                box::stbl<parser<
                                    box::stsd,
                                    box::stsc,
                                    box::stco,
                                    box::co64,
                                    box::stsz
                                  >>
                                >>
                              >>
                            >>
                         >>
            > parser;

        parser.read(root, bs);

        //get needed boxes
        auto avc1 = root->get_child("avc1");
        assert(avc1 != nullptr);

        m_avcc = avc1->get_child<box::avcc>();
        assert(m_avcc != nullptr);

        auto trak = avc1->get_parent("trak");
        assert(trak != nullptr);

        auto stco = trak->get_child<box::stco>();
        if (stco != nullptr)
        {

        m_chunk_offsets.resize(stco->entry_count());
        std::copy(
            stco->entries().begin(),
            stco->entries().end(),
            m_chunk_offsets.begin());
        }
        else
        {
            auto co64 = trak->get_child<box::co64>();
            assert(co64 != nullptr);
            m_chunk_offsets.resize(co64->entry_count());
            std::copy(
                co64->entries().begin(),
                co64->entries().end(),
                m_chunk_offsets.begin());
        }

        m_stsc = trak->get_child<box::stsc>();
        assert(m_stsc != nullptr);

        m_stsz = trak->get_child<box::stsz>();
        assert(m_stsz != nullptr);
    }

    const std::shared_ptr<sequence_parameter_set> h264_extractor::sps()
    {
        return m_avcc->sequence_parameter_set(0);
    }

    const std::shared_ptr<picture_parameter_set> h264_extractor::pps()
    {
        return m_avcc->picture_parameter_set(0);
    }


    // Private methods
    bool h264_extractor::has_next_nalu()
    {
        if(m_chunk < m_chunk_offsets.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::vector<char> h264_extractor::next_nalu()
    {

        if(!(m_sample_size > 0))
        {
            m_found_samples++;
            m_sample++;
            m_sample_size = m_stsz->sample_size(m_found_samples);
        }


        if(m_sample = m_stsc->samples_for_chunk(m_chunk))
        {
            m_chunk++;
            m_file.seekg(m_chunk_offsets[m_chunk]);
        }

        m_current_nalu_size = read_nalu_size(m_file, m_avcc->length_size());
        std::cout << "Current nalu size: " << m_current_nalu_size << std::endl;
        m_sample_size -= m_avcc->length_size();
        std::vector<char> temp(m_current_nalu_size);
        m_file.read(temp.data(), m_current_nalu_size);
        m_sample_size -= m_current_nalu_size;
        return temp;
    }

    uint32_t h264_extractor::current_nalu_size()
    {
        return m_current_nalu_size;
    }

    uint32_t h264_extractor::read_nalu_size(
        std::istream& file,
        uint8_t length_size)
    {
        std::vector<uint8_t> data(length_size);
        file.read((char*)data.data(), data.size());

        uint32_t result = 0;
        for (uint8_t i = 0; i < length_size; ++i)
        {
            result |= data[i] << ((length_size - 1) - i) * 8;
        }
        return result;
    }
}
