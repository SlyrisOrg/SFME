//
// Created by milerius on 08/02/18.
//

#include <gtest/gtest.h>
#include <SFME/ecs/ecs.hpp>
#include <typeindex>

struct TestSystem : public sfme::ecs::System<TestSystem>
{
    reflect_class(TestSystem);

    TestSystem(sfme::mediator::EventManager &evtMgr) noexcept : System<TestSystem>(evtMgr)
    {
    }

    void update() noexcept override
    {
        std::cout << getType() << std::endl;
    }

    ~TestSystem() noexcept override = default;
};

struct SecondTestSystem : public sfme::ecs::System<SecondTestSystem>
{
    reflect_class(SecondTestSystem);

    SecondTestSystem(sfme::mediator::EventManager &evtMgr) noexcept : System<SecondTestSystem>(evtMgr)
    {
    }

    void update() noexcept override
    {
        std::cout << getType() << std::endl;
    }

    ~SecondTestSystem() noexcept override = default;
};

TEST(ECS, AddSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    auto res = sysMgr.createSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate);
    res.update();
}

TEST(ECS, AddMultipleSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.loadSystems<TestSystem, SecondTestSystem>(sfme::ecs::SystemType::PreUpdate);
    evtMgr.emit<sfme::mediator::evt::GameStarted>();
    sysMgr.update();
}

TEST(ECS, GetSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.createSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate);
    sysMgr.getSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate).update();
}

