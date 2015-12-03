// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/moov.hpp>
#include <petro/box/box.hpp>
#include <petro/parser.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_moov, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::moov<petro::parser<>> b(parent);
    EXPECT_EQ("moov", b.type());
}
