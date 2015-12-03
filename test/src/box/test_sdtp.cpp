// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/sdtp.hpp>
#include <petro/box/box.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_sdtp, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::sdtp b(parent);
    EXPECT_EQ("sdtp", b.type());
}
