//
// Created by milerius on 03/02/18.
//

#pragma once

#include <cstddef>

namespace sfme::mediator::details
{
    using EventTypeID = std::size_t;

    static inline EventTypeID generateTypeId() noexcept
    {
        static EventTypeID cur{0};

        return cur++;
    }

    template <typename T>
    static inline EventTypeID getEventTypeID() noexcept
    {
        static EventTypeID id{generateTypeId()};

        return id;
    }
}
