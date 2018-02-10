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
    }

    static constexpr sfme::ecs::SystemType getSystemType() noexcept
    {
        return sfme::ecs::SystemType::PreUpdate;
    }

    ~TestSystem() noexcept override = default;
};

struct LogicalSystem : public sfme::ecs::System<LogicalSystem>
{
    reflect_class(LogicalSystem);

    LogicalSystem(sfme::mediator::EventManager &evtMgr) noexcept : System<LogicalSystem>(evtMgr)
    {
    }

    void update() noexcept override
    {
    }

    static constexpr sfme::ecs::SystemType getSystemType() noexcept
    {
        return sfme::ecs::SystemType::LogicUpdate;
    }

    ~LogicalSystem() noexcept override = default;
};

struct PostSystem : public sfme::ecs::System<PostSystem>
{
    reflect_class(PostSystem);

    PostSystem(sfme::mediator::EventManager &evtMgr) noexcept : System<PostSystem>(evtMgr)
    {
    }

    void update() noexcept override
    {
    }

    static constexpr sfme::ecs::SystemType getSystemType() noexcept
    {
        return sfme::ecs::SystemType::PostUpdate;
    }

    ~PostSystem() noexcept override = default;
};

struct SecondTestSystem : public sfme::ecs::System<SecondTestSystem>
{
    reflect_class(SecondTestSystem);

    SecondTestSystem(sfme::mediator::EventManager &evtMgr) noexcept : System<SecondTestSystem>(evtMgr)
    {
    }

    void update() noexcept override
    {
    }

    static constexpr sfme::ecs::SystemType getSystemType() noexcept
    {
        return sfme::ecs::SystemType::PreUpdate;
    }

    ~SecondTestSystem() noexcept override = default;
};

TEST(ECS, AddSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    auto res = sysMgr.createSystem<TestSystem>();
    ASSERT_TRUE(sysMgr.hasSystem<TestSystem>());
    ASSERT_EQ(1, sysMgr.size());
    res.update();
}

TEST(ECS, AddMultipleSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.loadSystems<TestSystem, SecondTestSystem>();
    ASSERT_EQ(2, sysMgr.size());
    evtMgr.emit<sfme::mediator::evt::GameStarted>();
    sysMgr.update();
}

TEST(ECS, TestAllKindOfSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.loadSystems<TestSystem, SecondTestSystem, LogicalSystem, PostSystem>();
    ASSERT_EQ(4, sysMgr.size());
    evtMgr.emit<sfme::mediator::evt::GameStarted>();
    int i = 0;
    while (i < 10000) {
        sysMgr.update();
        i++;
    }
}

TEST(ECS, GetSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.createSystem<TestSystem>();
    ASSERT_EQ(1, sysMgr.size());
    sysMgr.getSystem<TestSystem>().update();
}

