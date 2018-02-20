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
            return _createEntity(_nextID());
        }

    private:
        EntityID _createEntity(EntityID id) noexcept
        {
            auto pair = _entities.emplace(id, Entity(id, _allocators));

            return pair.first->first;
        }

    public:
        Entity &operator[](EntityID id) noexcept
        {
            return _entities.at(id);
        }

        const Entity &operator[](EntityID id) const noexcept
        {
            return _entities.at(id);
        }

        Entity &getEntity(EntityID id) noexcept
        {
            return operator[](id);
        }

        const Entity &getEntityConst(EntityID id) const noexcept
        {
            return operator[](id);
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

        template <typename ComponentType>
        std::vector<Entity *> getEntitiesWithComponent() noexcept
        {
            std::vector<Entity *> entities;
            for (auto & [id, entity] : _entities) {
                static_cast<void>(id);
                if (entity.template hasComponent<ComponentType>())
                    entities.push_back(&entity);
            }
            return entities;
        }

		template<typename ...Args>
		std::vector<Entity *> getEntitiesWithComponents(Args&& ...args) noexcept
        {
			std::vector<Entity *> entities;
			for (auto &[id, entity] : _entities)
			{
				static_cast<void>(id);
				if (entity.hasComponents(std::forward<Args>(args)...))
				{
					entities.push_back(&entity);
				}
			}
			return entities;
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

    public:
        reflect_class(EntityManager)

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&EntityManager::nbEntities),
                                 reflect_function(&EntityManager::clear),
                                 reflect_function(&EntityManager::sweepEntities),
                                 reflect_function(&EntityManager::getEntity),
                                 reflect_function(&EntityManager::getEntityConst),
                                 reflect_function(&EntityManager::createEntity));
        }

    private:
        std::unordered_map<EntityID, Entity> _entities;
        AllocatorsTuple _allocators;
    };
}
