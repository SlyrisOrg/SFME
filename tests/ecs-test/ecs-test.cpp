//
// Created by milerius on 08/02/18.
//

#include <gtest/gtest.h>
#include <SFME/ecs/ecs.hpp>

struct TestSystem : public sfme::ecs::BaseSystem
{
    reflect_class(TestSystem);

    TestSystem(sfme::mediator::EventManager &evtMgr) noexcept : BaseSystem(evtMgr)
    {
    }

    void update() noexcept override
    {
        std::cout << getName() << std::endl;
    }

    const std::string &getName() const noexcept override
    {
        return TestSystem::className();
    }

    ~TestSystem() noexcept override = default;
};

TEST(ECS, AddSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    auto res = sysMgr.createSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate);
    res.update();
}

TEST(ECS, GetSystem)
{
    sfme::mediator::EventManager evtMgr;
    sfme::ecs::SystemManager sysMgr{evtMgr};
    sysMgr.createSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate);
    sysMgr.getSystem<TestSystem>(sfme::ecs::SystemType::LogicUpdate).update();
}