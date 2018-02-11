//
// Created by milerius on 10/02/18.
//

#pragma once

#include <type_traits>
#include <core/reflection/Reflection.hpp>
#include <SFME/ecs/system_base.hpp>

namespace sfme::ecs::details
{
    template <typename System>
    static constexpr bool is_system_v = std::is_base_of_v<BaseSystem, System> &&
    refl::has_reflectible_class_name_v<System> && System::getSystemType() < SystemType::Size;
}