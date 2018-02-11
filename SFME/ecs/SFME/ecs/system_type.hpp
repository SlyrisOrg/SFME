//
// Created by milerius on 09/02/18.
//

#pragma once

namespace sfme::ecs
{
    enum SystemType
    {
        PreUpdate = 0,
        LogicUpdate = 1,
        PostUpdate = 2,
        Size = 3,
    };

    using TPreUpdate = utils::NamedType<SystemType, struct PreUpdateTag>;
    using TLogicUpdate = utils::NamedType<SystemType, struct TLogicUpdateTag>;
    using TPostUpdate = utils::NamedType<SystemType, struct TPostUpdateTag>;
}
