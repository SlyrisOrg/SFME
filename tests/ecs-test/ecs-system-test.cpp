//
// Created by milerius on 08/02/18.
//

#include <gtest/gtest.h>
#include <SFME/ecs/ecs.hpp>
#include <typeindex>
#include "common_ecs_test.hpp"
#include "ecs_plugin_foo.hpp"

struct TestSystem : public sfme::ecs::PreUpdateSystem<TestSystem>
{
    reflect_class(TestSystem);

    TestSystem(sfme::mediator::EventManager &evtMgr, sfme::testing::EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    void update() noexcept override
    {
    }

    ~TestSystem() noexcept override = default;

    sfme::testing::EntityManager &_ettMgr;
};

struct LogicalSystem : public sfme::ecs::LogicUpdateSystem<LogicalSystem>
{
    reflect_class(LogicalSystem);

    LogicalSystem(sfme::mediator::EventManager &evtMgr, sfme::testing::EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    void update() noexcept override
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    ~LogicalSystem() noexcept override = default;

    sfme::testing::EntityManager &_ettMgr;
};

struct PostSystem : public sfme::ecs::PostUpdateSystem<PostSystem>
{
    reflect_class(PostSystem);

    PostSystem(sfme::mediator::EventManager &evtMgr, sfme::testing::EntityManager &ettMgr) noexcept :
        System(evtMgr),
        _ettMgr(ettMgr)
    {
    }

    void update() noexcept override
    {
    }

    ~PostSystem() noexcept override = default;
    sfme::testing::EntityManager &_ettMgr;
};

struct SecondTestSystem : public sfme::ecs::PreUpdateSystem<SecondTestSystem>
{
    reflect_class(SecondTestSystem);

    SecondTestSystem(sfme::mediator::EventManager &evtMgr, sfme::testing::EntityManager &ettMgr) noexcept
        : System(evtMgr),
          _ettMgr(ettMgr)
    {
    }

    void update() noexcept override
    {
    }

    ~SecondTestSystem() noexcept override = default;
    sfme::testing::EntityManager &_ettMgr;
};

class TestingSystem : public sfme::ecs::World<sfme::testing::Components>, public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

class TestingSystemPlugins : public sfme::ecs::World<sfme::testing::Components>, public ::testing::Test
{
protected:
    void SetUp() override
    {
        ASSERT_TRUE(_sysMgr.loadPlugin("ecs-plugin-foo"));
    }

    void TearDown() override
    {
    }
};

class TestingSystemMultiplePlugins : public sfme::ecs::World<sfme::testing::Components>, public ::testing::Test
{
protected:
    void SetUp() override
    {
        ASSERT_TRUE(_sysMgr.loadPlugins());
    }

    void TearDown() override
    {
    }
};

TEST_F(TestingSystem, AddSystem)
{
    _sysMgr.createSystem<TestSystem>();
    auto res = _sysMgr.createSystem<TestSystem>();
    ASSERT_TRUE(_sysMgr.hasSystem<TestSystem>());
    ASSERT_EQ(1, _sysMgr.size());
    res.update();
}

TEST_F(TestingSystem, AddMultipleSystem)
{
    _sysMgr.loadSystems<TestSystem, SecondTestSystem>();
    ASSERT_EQ(2, _sysMgr.size());
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
}

TEST_F(TestingSystem, TestAllKindOfSystem)
{
    _sysMgr.loadSystems<TestSystem, SecondTestSystem, LogicalSystem, PostSystem>();
    ASSERT_EQ(4, _sysMgr.size());
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    int i = 0;
    while (i < 100000) {
        _sysMgr.update();
        i++;
    }
}

TEST_F(TestingSystem, GetSystem)
{
    _sysMgr.createSystem<TestSystem>();
    ASSERT_EQ(1, _sysMgr.size());
    _sysMgr.getSystem<TestSystem>().update();
}

TEST_F(TestingSystem, HasSystem)
{
    _sysMgr.createSystem<SecondTestSystem>();
    ASSERT_TRUE(_sysMgr.hasSystem<SecondTestSystem>());
    ASSERT_FALSE(_sysMgr.hasSystem<TestSystem>());
}

TEST_F(TestingSystem, HasSystems)
{
    _sysMgr.loadSystems<PostSystem, LogicalSystem, SecondTestSystem>();
    ASSERT_TRUE(_sysMgr.hasSystems<SecondTestSystem>());
    bool res = _sysMgr.hasSystems<SecondTestSystem, LogicalSystem>();
    ASSERT_TRUE(res);
    res = _sysMgr.hasSystems<SecondTestSystem, TestSystem>();
    ASSERT_FALSE(res);
    res = _sysMgr.hasSystems<TestSystem>();
    ASSERT_FALSE(res);
}

TEST_F(TestingSystem, Size)
{
    _sysMgr.createSystem<SecondTestSystem>();
    ASSERT_EQ(1, _sysMgr.size());
    _sysMgr.createSystem<TestSystem>();
    ASSERT_EQ(2, _sysMgr.size());
}

TEST_F(TestingSystem, SizePerType)
{
    _sysMgr.createSystem<SecondTestSystem>();
    ASSERT_NE(1, _sysMgr.size(sfme::ecs::SystemType::PostUpdate));
    ASSERT_EQ(1, _sysMgr.size(sfme::ecs::SystemType::PreUpdate));
    _sysMgr.createSystem<TestSystem>();
    ASSERT_EQ(2, _sysMgr.size(sfme::ecs::SystemType::PreUpdate));
    ASSERT_NE(2, _sysMgr.size(sfme::ecs::SystemType::LogicUpdate));
}

TEST_F(TestingSystem, RemoveSystem)
{
    _sysMgr.loadSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(4, _sysMgr.size());
    _sysMgr.markSystem<PostSystem>();
    ASSERT_TRUE(_sysMgr.getSystem<PostSystem>().isMarked());
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
    ASSERT_EQ(3, _sysMgr.size());
}

TEST_F(TestingSystem, DisableSingleSystem)
{
    _sysMgr.loadSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(3, _sysMgr.update());
    ASSERT_TRUE(_sysMgr.disableSystem<PostSystem>());
    ASSERT_EQ(2, _sysMgr.update());
}

TEST_F(TestingSystem, EnableSingleSystem)
{
    _sysMgr.loadSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(3, _sysMgr.update());
    ASSERT_TRUE(_sysMgr.disableSystem<PostSystem>());
    ASSERT_EQ(2, _sysMgr.update());
    ASSERT_TRUE(_sysMgr.enableSystem<PostSystem>());
    ASSERT_EQ(3, _sysMgr.update());
}

TEST_F(TestingSystem, DisableMultipleSystems)
{
    _sysMgr.loadSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(3, _sysMgr.update());
    bool res = _sysMgr.disableSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_TRUE(res);
    ASSERT_EQ(0, _sysMgr.update());
}

TEST_F(TestingSystem, EnableMultipleSystems)
{
    _sysMgr.loadSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(3, _sysMgr.update());
    bool res = _sysMgr.disableSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_TRUE(res);
    ASSERT_EQ(0, _sysMgr.update());
    res = _sysMgr.enableSystems<PostSystem, SecondTestSystem, TestSystem>();
    ASSERT_TRUE(res);
    ASSERT_EQ(3, _sysMgr.update());
}

TEST_F(TestingSystem, RemoveSystemDuplicata)
{
    _sysMgr.loadSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(4, _sysMgr.size());
    ASSERT_TRUE(_sysMgr.markSystem<PostSystem>());
    ASSERT_TRUE(_sysMgr.getSystem<PostSystem>().isMarked());
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
    ASSERT_FALSE(_sysMgr.markSystem<PostSystem>());
    _sysMgr.update();
    ASSERT_EQ(3, _sysMgr.size());
}

TEST_F(TestingSystem, AddThenRemoveThenAdd)
{
    _sysMgr.loadSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(4, _sysMgr.size());
    ASSERT_TRUE(_sysMgr.markSystem<PostSystem>());
    ASSERT_TRUE(_sysMgr.markSystem<LogicalSystem>());
    ASSERT_TRUE(_sysMgr.getSystem<PostSystem>().isMarked());
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
    ASSERT_EQ(2, _sysMgr.size());
    _sysMgr.loadSystems<LogicalSystem, PostSystem>();
    ASSERT_EQ(4, _sysMgr.size());
}

TEST_F(TestingSystem, MarkSystems)
{
    _sysMgr.loadSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(4, _sysMgr.size());
    bool res = _sysMgr.markSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_TRUE(res);
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
    ASSERT_EQ(0, _sysMgr.size());
}

TEST_F(TestingSystem, MarkSystemsFold)
{
    _sysMgr.loadSystems<LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(3, _sysMgr.size());
    bool res = _sysMgr.markSystems<PostSystem, LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_FALSE(res);
    _evtMgr.emit<sfme::mediator::evt::GameStarted>();
    _sysMgr.update();
    ASSERT_EQ(3, _sysMgr.size());
    res = _sysMgr.markSystems<LogicalSystem, SecondTestSystem, TestSystem, PostSystem>();
    ASSERT_FALSE(res);
    _sysMgr.update();
    ASSERT_EQ(3, _sysMgr.size());
}

TEST_F(TestingSystem, GetSystems)
{
    _sysMgr.loadSystems<LogicalSystem, SecondTestSystem, TestSystem>();
    const auto &[logical, second, test] = _sysMgr.getSystems<LogicalSystem, SecondTestSystem, TestSystem>();
    ASSERT_EQ(std::decay_t<decltype(logical)>::getSystemType(), sfme::ecs::SystemType::LogicUpdate);
    ASSERT_EQ(std::decay_t<decltype(second)>::getSystemType(), sfme::ecs::SystemType::PreUpdate);
    ASSERT_EQ(std::decay_t<decltype(test)>::getSystemType(), sfme::ecs::SystemType::PreUpdate);
}

TEST_F(TestingSystemPlugins, GetSystem)
{
    ASSERT_EQ(1, _sysMgr.size());
    _sysMgr.getSystem<sfme::testing::plugins::FooSystem>().update();
}

TEST_F(TestingSystemPlugins, GetSystems)
{
    _sysMgr.createSystem<LogicalSystem>();
    ASSERT_EQ(2, _sysMgr.size());
    const auto &[logical, foo] = _sysMgr.getSystems<LogicalSystem, sfme::testing::plugins::FooSystem>();
    ASSERT_EQ(std::decay_t<decltype(logical)>::getSystemType(), sfme::ecs::SystemType::LogicUpdate);
    ASSERT_EQ(std::decay_t<decltype(foo)>::getSystemType(), sfme::ecs::SystemType::PreUpdate);
}

TEST_F(TestingSystemPlugins, RemovePlugedSystem)
{
    ASSERT_EQ(1, _sysMgr.size());
    ASSERT_EQ(1, _sysMgr.nbPlugins());
    _sysMgr.getSystem<sfme::testing::plugins::FooSystem>().mark();
    ASSERT_TRUE(_sysMgr.markSystem<sfme::testing::plugins::FooSystem>());
    ASSERT_EQ(0, _sysMgr.nbPlugins());
    ASSERT_EQ(1, _sysMgr.update());
    ASSERT_EQ(0, _sysMgr.size());
    ASSERT_EQ(0, _sysMgr.update());
}

TEST_F(TestingSystemMultiplePlugins, Basics)
{
    ASSERT_EQ(2, _sysMgr.size());
    ASSERT_EQ(2, _sysMgr.nbPlugins());
}