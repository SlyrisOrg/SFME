//
// Created by milerius on 04/02/18.
//

#pragma once

#include <type_traits>

namespace sfme::mediator::details
{
    template <typename T>
    constexpr bool is_mediator_event = std::is_base_of_v<BaseEvent, T>;
}
