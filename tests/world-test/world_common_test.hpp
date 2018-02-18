//
// Created by sztergbaum roman on 2/17/2018.
//

#pragma once

#include <core/meta/List.hpp>
#include <core/reflection/Reflection.hpp>

namespace sfme::example
{
    namespace components
    {
        struct Box
        {
            reflect_class(Box);

            int getX() const noexcept
            {
                return _x;
            }

            int getY() const noexcept
            {
                return _y;
            }

            static constexpr auto reflectedFunctions() noexcept
            {
                return meta::makeMap(reflect_function(&Box::getX), reflect_function(&Box::getY));
            }

            static constexpr auto reflectedMembers() noexcept
            {
                return meta::makeMap();
            }
        private:
            int _x{0};
            int _y{0};
        };
    }

    using Components = meta::TypeList<components::Box>;
    using GameTraits = sfme::world::Traits<Components, sfme::scripting::ScriptingLua>;
}