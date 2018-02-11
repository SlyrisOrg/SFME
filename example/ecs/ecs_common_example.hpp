//
// Created by milerius on 11/02/18.
//

#pragma once

#include <SFME/ecs/ecs.hpp>

namespace sfme::example
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

namespace sfme::example::system
{
    class PreUpdate : public sfme::ecs::System<PreUpdate>
    {
    public:
        reflect_class(PreUpdate);

        PreUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System<PreUpdate>(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        static constexpr sfme::ecs::SystemType getSystemType() noexcept
        {
            return sfme::ecs::SystemType::PreUpdate;
        }

        ~PreUpdate() noexcept override = default;

    private:
        [[maybe_unused]] EntityManager &_ettMgr;
    };

    class PostUpdate : public sfme::ecs::System<PostUpdate>
    {
    public:
        reflect_class(PostUpdate);

        PostUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System<PostUpdate>(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        static constexpr sfme::ecs::SystemType getSystemType() noexcept
        {
            return sfme::ecs::SystemType::PostUpdate;
        }

        ~PostUpdate() noexcept override = default;

    private:
        [[maybe_unused]] EntityManager &_ettMgr;
    };
    
    class Logic : public sfme::ecs::System<Logic>
    {
    public:
        reflect_class(Logic);

        Logic(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System<Logic>(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        static constexpr sfme::ecs::SystemType getSystemType() noexcept
        {
            return sfme::ecs::SystemType::LogicUpdate;
        }

        ~Logic() noexcept override = default;

    private:
        [[maybe_unused]] EntityManager &_ettMgr;
    };

    class WithUserData : public sfme::ecs::System<WithUserData>
    {
    public:
        reflect_class(WithUserData);

        WithUserData(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr, int i, int j) noexcept :
            System<WithUserData>(evtMgr),
            _ettMgr(ettMgr)
        {
            std::cout << i << " " << j << std::endl;
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        static constexpr sfme::ecs::SystemType getSystemType() noexcept
        {
            return sfme::ecs::SystemType::LogicUpdate;
        }

        ~WithUserData() noexcept override = default;

    private:
        [[maybe_unused]] EntityManager &_ettMgr;
    };
}