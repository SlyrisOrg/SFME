//
// Created by milerius on 10/02/18.
//

#pragma once

#include <type_traits>
#include <core/reflection/Reflection.hpp>
#include <core/meta/List.hpp>
#include <SFME/ecs/system_type.hpp>
#include <SFME/ecs/system_base.hpp>

namespace sfme::ecs::details
{
    using KindSystemList = meta::TypeList<TLogicUpdate, TPreUpdate, TPostUpdate>;

    template <typename ...Types>
    static constexpr bool is_valid_system_v(meta::TypeList<Types...>) noexcept
    {
        return std::disjunction_v<Types...>;
    }

    template <typename System>
    static constexpr bool is_system_v = std::is_base_of_v<BaseSystem, System> &&
    refl::has_reflectible_class_name_v<System> && System::getSystemType() < SystemType::Size;
}