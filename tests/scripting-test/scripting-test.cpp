//
// Created by sztergbaum roman on 2/17/2018.
//

#include <gtest/gtest.h>
#include <SFME/world/world.hpp>
#include "scripting_world_test.hpp"

namespace sfme::example
{
    class ScriptingFixture : public sfme::World<GameTraits>, public testing::Test
    {
    protected:
        void SetUp() override
        {
            fs::copy(fs::current_path().parent_path() / fs::path("tests/scripting-test/lua_scripts"),
                     fs::current_path() / fs::path("lua_scripts"),
                     fs::copy_options::overwrite_existing | fs::copy_options::recursive);
            _sysMgr.loadSystems<system::PreUpdate, system::Logical, system::PostUpdate, scripting::ScriptedSystem<GameTraits>>();
            ScriptingSystem& scriptSystem = _sysMgr.getSystem<ScriptingSystem>();
            scriptSystem.registerSystems<sfme::example::SystemList>(_sysMgr);
            scriptSystem.loadEntitiesScript<components::Script>();
            scriptSystem.loadScript("test.lua");
        }

        void TearDown() override
        {
        }
    };

    TEST_F(ScriptingFixture, ScopedCall)
    {
        ScriptingSystem& scriptSystem = _sysMgr.getSystem<ScriptingSystem>();
        bool res = false;
        res = scriptSystem.executeScopedFunction<bool>("testTable", "onUpdate");
        ASSERT_TRUE(res);
    }

    TEST_F(ScriptingFixture, GlobalCall)
    {
        ScriptingSystem& scriptSystem = _sysMgr.getSystem<ScriptingSystem>();
        bool res = false;
        res = scriptSystem.executeGlobalFunction<bool>("testGlobalFunction", 42);
        ASSERT_TRUE(res);
    }

    TEST_F(ScriptingFixture, EntityManager)
    {
        ScriptingSystem& scriptSystem = _sysMgr.getSystem<ScriptingSystem>();
        using Result = std::tuple<Entity::ID, unsigned int>;
        auto[ettID, res]  = scriptSystem.executeGlobalFunction<Result>("testEntityManager");
        ASSERT_EQ(res, _ettMgr[ettID].getComponent<components::PV>().pv);
        scriptSystem.executeGlobalFunction("testClearEntities");
        ASSERT_EQ(_ettMgr.nbEntities(), 0);
    }

	TEST_F(ScriptingFixture, GetEntityWithSpecificComponents)
    {
		ScriptingSystem& scriptSystem = _sysMgr.getSystem<ScriptingSystem>();
		scriptSystem.executeGlobalFunction("testGetEntityWithSpecificComponents");
    }
}
