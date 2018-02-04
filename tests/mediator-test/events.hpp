//
// Created by milerius on 04/02/18.
//

#pragma once

#include <SFME/mediator/base_event.hpp>

namespace sfme::testing
{
    struct FooEvents : sfme::mediator::BaseEvent
    {
        FooEvents() noexcept
        {
            showEvents("FooEvents");
        }

        static constexpr std::string_view className() noexcept
        {
            using namespace std::string_view_literals;
            return "FooEvents"sv;
        }

        std::string str{"Good"};
    };

    struct BarEvents : sfme::mediator::BaseEvent
    {
        BarEvents() noexcept
        {
            showEvents("BarEvents");
        }

        static constexpr std::string_view className() noexcept
        {
            using namespace std::string_view_literals;
            return "BarEvents"sv;
        }
    };
}

