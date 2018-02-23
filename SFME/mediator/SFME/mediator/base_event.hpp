//
// Created by milerius on 03/02/18.
//

#pragma once

#include <SFME/mediator/config.hpp>
#include <string_view>

namespace sfme::mediator
{
    struct BaseEvent
    {
    protected:
        void showEvents(std::string_view eventName) const noexcept
        {
            _log(logging::Debug) << "Events " << eventName << " triggered." << std::endl;
        }

        logging::Logger _log{"event-logger", logging::Debug};
    };
}
