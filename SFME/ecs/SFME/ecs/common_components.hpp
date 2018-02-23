//
// Created by sztergbaum roman on 2/22/2018.
//

#pragma once

#include <utility>
#include <core/reflection/Reflection.hpp>
#include <core/meta/Meta.hpp>

namespace sfme::ecs::components
{
    struct UserLayer1
    {
        reflect_class(UserLayer1);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer2
    {
        reflect_class(UserLayer2);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer3
    {
        reflect_class(UserLayer3);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer4
    {
        reflect_class(UserLayer4);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer5
    {
        reflect_class(UserLayer5);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer6
    {
        reflect_class(UserLayer6);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer7
    {
        reflect_class(UserLayer7);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct UserLayer8
    {
        reflect_class(UserLayer8);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }
    };

    struct Script
    {
        Script(std::string _scriptName, std::string _selfName, std::string _tableName = "") noexcept :
            scriptName(std::move(_scriptName)),
            selfName(std::move(_selfName)),
            tableName(std::move(_tableName))
        {
        }

        reflect_class(Script);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap(reflect_member(&Script::scriptName),
                                 reflect_member(&Script::selfName),
                                 reflect_member(&Script::tableName));
        }

        std::string scriptName;
        std::string selfName;
        std::string tableName;
    };

    using CommonComponents = meta::TypeList<UserLayer1, UserLayer2, UserLayer3, UserLayer4, UserLayer5, UserLayer6, UserLayer7, UserLayer8, Script>;
}