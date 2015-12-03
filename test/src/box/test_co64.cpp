// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/co64.hpp>
#include <petro/box/box.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_co64, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::co64 b(parent);
    EXPECT_EQ("co64", b.type());
}
