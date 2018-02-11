//
// Created by milerius on 11/02/18.
//

#pragma once

#include <core/meta/List.hpp>
#include <SFME/ecs/ecs.hpp>

namespace sfme::testing
{
    namespace components
    {
        struct Box
        {
        };
    }

    using Components = meta::TypeList<components::Box>;
    using EntityManager = sfme::ecs::EntityManager<Components>;
    using Entity = EntityManager::Entity;
}