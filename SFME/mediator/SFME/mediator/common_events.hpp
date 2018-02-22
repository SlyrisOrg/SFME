//
// Created by milerius on 09/02/18.
//

#pragma once

#include <core/reflection/Reflection.hpp>
#include <SFME/input/input.hpp>
#include <SFME/mediator/base_event.hpp>

namespace sfme::mediator::evt
{
    struct GameStarted : public sfme::mediator::BaseEvent
    {
        GameStarted() noexcept
        {
        };

        reflect_class(GameStarted);
    };

    struct GameShutdown : public sfme::mediator::BaseEvent
    {
        GameShutdown() noexcept
        {

        };

        reflect_class(GameShutdown);
    };

    struct KeyPressed : public sfme::mediator::BaseEvent
    {
        explicit KeyPressed(sfme::input::keyboard::TKey _key) noexcept : key(_key)
        {
            showEvents(KeyPressed::className());
        }

        reflect_class(KeyPressed);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap(reflect_member(&KeyPressed::key));
        }

        sfme::input::keyboard::TKey key;
    };
}
