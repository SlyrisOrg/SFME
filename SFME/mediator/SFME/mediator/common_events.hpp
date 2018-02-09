//
// Created by milerius on 09/02/18.
//

#pragma once

#include <SFME/mediator/base_event.hpp>
#include <core/reflection/Reflection.hpp>

namespace sfme::mediator::evt
{
    struct GameStarted : public sfme::mediator::BaseEvent
    {
        GameStarted() noexcept
        {
        };

        reflect_class(GameStarted);
    };
}
