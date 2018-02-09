//
// Created by milerius on 09/02/18.
//

#pragma once

namespace sfme::ecs
{
    enum class SystemType
    {
        PreUpdate = 0,
        LogicUpdate = 1,
        PostUpdate = 2
    };
}
