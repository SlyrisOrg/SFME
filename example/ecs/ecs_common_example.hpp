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
        private:
            int _x{0};
            int _y{0};
        };
    }

    using Components = meta::TypeList<components::Box>;
    using EntityManager = sfme::ecs::EntityManager<Components>;
    using Entity = EntityManager::Entity;
}

namespace sfme::example::system
{
    class PreUpdate : public sfme::ecs::PreUpdateSystem<PreUpdate>
    {
    public:
        reflect_class(PreUpdate);

        PreUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            (void)_ettMgr;
            std::cout << __FUNCTION__ << std::endl;
        }

        ~PreUpdate() noexcept override = default;

    private:
        EntityManager &_ettMgr;
    };

    class PostUpdate : public sfme::ecs::PostUpdateSystem<PostUpdate>
    {
    public:
        reflect_class(PostUpdate);

        PostUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            (void)_ettMgr;
            std::cout << __FUNCTION__ << std::endl;
        }

        ~PostUpdate() noexcept override = default;

    private:
        EntityManager &_ettMgr;
    };
    
    class Logic : public sfme::ecs::LogicUpdateSystem<Logic>
    {
    public:
        reflect_class(Logic);

        Logic(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            (void)_ettMgr;
            std::cout << __FUNCTION__ << std::endl;
        }

        ~Logic() noexcept override = default;

    private:
        EntityManager &_ettMgr;
    };

    class WithUserData : public sfme::ecs::LogicUpdateSystem<WithUserData>
    {
    public:
        reflect_class(WithUserData);

        WithUserData(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr, int i, int j) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
            std::cout << i << " " << j << std::endl;
        }

        void update() noexcept override
        {
            (void)_ettMgr;
            std::cout << __FUNCTION__ << std::endl;
        }

        ~WithUserData() noexcept override = default;

    private:
        EntityManager &_ettMgr;
    };
}