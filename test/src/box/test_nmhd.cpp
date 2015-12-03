// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/nmhd.hpp>
#include <petro/box/box.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_nmhd, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::nmhd b(parent);
    EXPECT_EQ("nmhd", b.type());
}
