// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/url.hpp>
#include <petro/box/box.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_url, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::url b(parent);
    EXPECT_EQ("url ", b.type());
}