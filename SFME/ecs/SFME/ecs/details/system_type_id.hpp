//
// Created by milerius on 10/02/18.
//

#pragma once

#include <cstddef>
#include <typeindex>
#include <type_traits>

namespace sfme::ecs
{
    using typeID = std::size_t;
}

namespace sfme::ecs::details
{
    template <typename Type>
    static typeID generateID() noexcept
    {
        static const auto id = std::hash<std::type_index>()(std::type_index(typeid(std::decay_t<Type>)));
        return id;
    }
}
