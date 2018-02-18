//
// Created by sztergbaum roman on 2/17/2018.
//

#include <gtest/gtest.h>
#include "scripting_world_test.hpp"

namespace sfme::example
{
    class Game : public sfme::World<GameTraits>, public testing::Test
    {
    protected:
        void SetUp() override
        {
            _scriptingEngine.registerSystems<sfme::example::SystemList>();
        }

        void TearDown() override
        {
        }
    };
}

TEST(Scripting, Basic)
{
}