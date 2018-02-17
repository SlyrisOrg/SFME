//
// Created by doom on 11/02/18.
// Also maintained by milerius
//

#pragma once

#include <tuple>
#include <memory>
#include <unordered_map>
#include <core/algorithm/erase_if.hpp>
#include <SFME/ecs/details/entity.hpp>

namespace sfme::ecs
{
    template <typename ComponentsList, template <typename> typename ComponentsAlloc = std::allocator>
    class EntityManager
    {
    public:
        using Entity = details::Entity<ComponentsList, ComponentsAlloc>;
        using EntityID = typename Entity::ID;
        using AllocatorsTuple = typename Entity::AllocatorsTuple;

    private:
        EntityID _nextID() noexcept
        {
            static EntityID curID{0};

            return curID++;
        }

    public:
        EntityID createEntity() noexcept
        {
            return createEntity(_nextID());
        }

        EntityID createEntity(EntityID id) noexcept
        {
            auto pair = _entities.emplace(id, Entity(id, _allocators));

            return pair.first->first;
        }

        Entity &operator[](EntityID id) noexcept
        {
            return _entities.at(id);
        }

        const Entity &operator[](EntityID id) const noexcept
        {
            return _entities.at(id);
        }

        template <typename ...Types, typename PredT>
        void for_each(PredT &&pred) noexcept(noexcept(pred(std::declval<Entity &>())))
        {
            for (auto &pair : _entities) {
                auto &entity = pair.second;
                if (entity.template hasComponents<Types...>()) {
                    pred(entity);
                }
            }
        }

        void sweepEntities() noexcept
        {
            algo::erase_if(_entities, [](auto &&pair) { return pair.second.isMarked(); });
        }

        void clear() noexcept
        {
            _entities.clear();
        }

        size_t nbEntities() const noexcept
        {
            return _entities.size();
        }

    private:
        std::unordered_map<EntityID, Entity> _entities;
        AllocatorsTuple _allocators;
    };
}
