//
// Created by milerius on 09/02/18.
//

#pragma once

#include <SFME/mediator/base_event.hpp>

namespace sfme::mediator::evt
{
    struct GameStarted : public sfme::mediator::BaseEvent
    {
        //TODO: make it reflectible
        GameStarted() noexcept
        {

        };
    };
}
