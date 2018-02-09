//
// Created by milerius on 09/02/18.
//

#pragma once

#include <chrono>
#include <iostream>
#include <SFME/timer/fps.hpp>

namespace sfme::timer
{
    class TimeStep
    {
    public:
        void start() noexcept
        {
            _start = clock::now();
        }

        void startFrame() noexcept
        {
            auto deltaTime = clock::now() - _start;
            _start = clock::now();
            _lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
        }

        bool isUpdateRequired() const noexcept
        {
            return (_lag >= _timestep);
        }

        void performUpdate() noexcept
        {
            _lag -= _timestep;
        };

        float getInterpolation() const noexcept
        {
            return static_cast<float>(_lag.count()) / _timestep.count();
        }

    private:
        using clock = std::chrono::steady_clock;
        std::chrono::nanoseconds _lag{0ns};
        std::chrono::nanoseconds _timestep{_60fps};
        clock::time_point _start;
    };
}
