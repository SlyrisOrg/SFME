//
// Created by milerius on 09/02/18.
//

#pragma once

#include <chrono>

namespace sfme::timer
{
    using namespace std::chrono_literals;

    constexpr std::chrono::nanoseconds _60fps{16666666ns};
    constexpr std::chrono::nanoseconds _120fps{8333333ns};
    constexpr std::chrono::nanoseconds _144fps{6944444ns};
}