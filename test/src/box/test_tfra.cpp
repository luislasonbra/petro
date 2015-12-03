// Copyright Steinwurf ApS 2015.
// All Rights Reserved

#include <petro/box/tfra.hpp>
#include <petro/box/box.hpp>

#include <gtest/gtest.h>

#include <memory>

TEST(box_test_tfra, construct)
{
    std::weak_ptr<petro::box::box> parent;
    petro::box::tfra b(parent);
    EXPECT_EQ("tfra", b.type());
}
