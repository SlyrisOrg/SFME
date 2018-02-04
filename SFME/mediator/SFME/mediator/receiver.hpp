//
// Created by milerius on 03/02/18.
//

#pragma once

#include <core/utils/NonCopyable.hpp>

namespace sfme::mediator
{
    struct BaseReceiver : private utils::NonCopyable
    {
    };

    template <typename Derived>
    struct Receiver : public BaseReceiver
    {
    };
}

