// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#pragma once

#include <cstdint>
#include <string>

#include "box.hpp"
#include "../byte_stream.hpp"

namespace petro
{
namespace box
{
    /// container for the media information in a track
    template<class Parser>
    class mdia : public box
    {

    public:

        static const std::string TYPE;

    public:
        mdia():
            box(mdia::TYPE)
        { }

        void read(uint32_t size, byte_stream& bs, box* parent)
        {
            box::read(size, bs, parent);
            Parser p;
            p.read(this, bs.data(), m_remaining_bytes);
            bs.skip(m_remaining_bytes);
        }
    };

    template<class Parser>
    const std::string mdia<Parser>::TYPE = "mdia";
}
}

