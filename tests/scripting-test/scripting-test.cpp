//
// Created by sztergbaum roman on 2/17/2018.
//

#include <gtest/gtest.h>
#include "scripting_world_test.hpp"

namespace sfme::example
{
    class Game : public sfme::World<GameTraits>, public testing::Test
    {
    private:
        void createEntities() noexcept
        {
            auto id = _ettMgr.createEntity();
            auto &player = _ettMgr.getEntity(id);
            player.addComponent<components::Script>("player.lua", "player", "playerTable");
            player.addComponent<components::PV>(100);
        }

    protected:
        void SetUp() override
        {
            fs::copy(fs::current_path().parent_path() / fs::path("tests/scripting-test/lua_scripts"),
                     fs::current_path() / fs::path("lua_scripts"), fs::copy_options::overwrite_existing | fs::copy_options::recursive);
            _sysMgr.loadSystems<system::PreUpdate, system::Logical>();
            _scriptingEngine.registerSystems<sfme::example::SystemList>();
            createEntities();
            _scriptingEngine.loadEntitiesScript<components::Script>();
        }

        void TearDown() override
        {
        }
    };

    TEST_F(Game, FunctionCall)
    {
        _ettMgr.for_each<components::Script, components::PV>([this](Entity &ett) {
            auto &tableName = ett.getComponent<components::Script>().tableName;
            _scriptingEngine.executeScopedFunction(tableName, "onUpdate");
        });
    }
}
