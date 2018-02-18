//
// Created by sztergbaum roman on 2/18/2018.
//

#pragma once

#include <SFME/scripting/scripting.hpp>
#include <SFME/scripting/scripting_lua.hpp>
#include <SFME/world/details/world_traits.hpp>

namespace sfme::example::components
{
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

    struct PV
    {
        reflect_class(PV);

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap();
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap(reflect_member(&PV::pv));
        }

        explicit PV(unsigned int _pv) noexcept : pv(_pv)
        {

        }

        unsigned int pv;
    };
}

namespace sfme::example
{
    using Components = meta::TypeList<components::PV, components::Script>;
    using GameTraits = sfme::world::Traits<Components, sfme::scripting::LuaSystem>;
    using EntityManager = GameTraits::TEntityManager;
    using Entity = GameTraits::TEntity;
    using ScriptingSystem = scripting::ScriptedSystem<GameTraits>;
}

namespace sfme::example::system
{
    struct Logical : public sfme::ecs::LogicUpdateSystem<Logical>
    {
        reflect_class(Logical);

        Logical(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        ~Logical() noexcept override = default;

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&Logical::update));
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

        EntityManager &_ettMgr;
    };

    struct PreUpdate : public sfme::ecs::PreUpdateSystem<PreUpdate>
    {
        reflect_class(PreUpdate);

        PreUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        ~PreUpdate() noexcept override = default;

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&PreUpdate::update));
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

        EntityManager &_ettMgr;
    };

    struct PostUpdate : public sfme::ecs::PostUpdateSystem<PostUpdate>
    {
        reflect_class(PostUpdate);

        PostUpdate(sfme::mediator::EventManager &evtMgr, EntityManager &ettMgr) noexcept :
            System(evtMgr),
            _ettMgr(ettMgr)
        {
        }

        void update() noexcept override
        {
            std::cout << __FUNCTION__ << std::endl;
        }

        ~PostUpdate() noexcept override = default;

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&PostUpdate::update));
        }

        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap();
        }

        EntityManager &_ettMgr;
    };
}

namespace sfme::example
{
    using SystemList = meta::TypeList<system::Logical, system::PreUpdate, system::PostUpdate, sfme::scripting::ScriptedSystem<GameTraits>>;
}