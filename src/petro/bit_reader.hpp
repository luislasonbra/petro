// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#pragma once

#include <cstdint>
#include <cassert>
#include <vector>

namespace petro
{
    /// Bit reader for reading packed bits.
    /// The reading is done in most significant byte first, most significant
    /// bit first order. Example:
    ///
    /// 5 bits: 2 (00010)
    /// 4 bits: 4 (0100)
    /// 4 bits: 2 (0010)
    /// 3 bits: 0 (000)
    ///
    /// Byte 1: 00010010
    /// Byte 2: 00010000
    ///
    /// 00010010 00010000
    /// [ 2 ][ 4 ][2 ][0]
    ///
    class bit_reader
    {

    public:

        bit_reader(uint8_t* data, uint64_t bits):
            m_data(data),
            m_bits(bits),
            m_bit_offset(0)
        { }

        bit_reader(std::vector<uint8_t>& data):
            m_data(data.data()),
            m_bits(data.size() * 8),
            m_bit_offset(0)
        { }

        uint8_t read_next_bit()
        {
            assert(m_bit_offset < m_bits);
            auto byte = m_bit_offset / 8;
            auto position = 7 - (m_bit_offset % 8);
            m_bit_offset += 1;
            return (m_data[byte] >> position) & 0x1;
        }

        void skip(uint64_t bits)
        {
            m_bit_offset += bits;
            assert(m_bit_offset < m_bits);
        }

        uint8_t read_1_bit()
        {
            return read_bits(1);
        }

        uint8_t read_2_bits()
        {
            return read_bits(2);
        }
        uint8_t read_3_bits()
        {
            return read_bits(3);
        }
        uint8_t read_4_bits()
        {
            return read_bits(4);
        }
        uint8_t read_5_bits()
        {
            return read_bits(5);
        }
        uint8_t read_6_bits()
        {
            return read_bits(6);
        }
        uint8_t read_7_bits()
        {
            return read_bits(7);
        }
        uint8_t read_8_bits()
        {
            return read_bits(8);
        }
        uint32_t read_bits(uint32_t bits)
        {
            assert(bits <= 32);
            uint8_t result = 0;
            for (uint32_t i = 0; i < bits; i++)
            {
                result |= (read_next_bit() << (bits - i - 1));
            }
            return result;
        }

        uint32_t read_exponential_golomb_code()
        {
            uint32_t i = 0;
            while ((read_1_bit() == 0) && (i < 32U))
            {
                i++;
            }
            uint32_t result = read_bits(i);
            result += (1 << i) - 1;
            return result;
        }

        int64_t read_se()
        {
            int64_t result = read_exponential_golomb_code();
            if (result & 0x01)
            {
                return (result + 1) / 2;
            }
            else
            {
                return -(result / 2);
            }
        }

        uint64_t size() const
        {
            return m_bits;
        }

        uint64_t offset() const
        {
            return m_bit_offset;
        }


    private:

        uint8_t* m_data;
        uint64_t m_bits;
        uint64_t m_bit_offset;
    };
}
