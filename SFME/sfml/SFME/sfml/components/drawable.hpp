//
// Created by sztergbaum roman on 2/23/2018.
//

#pragma once

#include <SFML/Graphics/Sprite.hpp>

namespace sfme::sfml::components
{
    struct Sprite
    {
        reflect_class(Sprite);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

        sf::Sprite sprite;
    };
}