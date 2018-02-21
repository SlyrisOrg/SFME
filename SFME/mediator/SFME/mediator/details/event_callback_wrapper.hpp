//
// Created by milerius on 03/02/18.
//

#pragma once

#include <SFME/mediator/base_event.hpp>
#include <functional>

namespace sfme::mediator::details
{
    /**
     * @brief The event manager works with type-erasure, in order to stock different template type.
     */
    struct BaseEventCallbackWrapper
    {
        virtual ~BaseEventCallbackWrapper() noexcept = default;
        virtual void operator()(const sfme::mediator::BaseEvent *event) const noexcept = 0;
    };

    template <typename TEvent>
    class EventCallbackWrapper final : public BaseEventCallbackWrapper
    {
    public:
        explicit EventCallbackWrapper(const std::function<void(const TEvent &)> &callback) noexcept : _callback(
            callback)
        {
        }

        void operator()(const sfme::mediator::BaseEvent *event) const noexcept final
        {
            _callback(*(static_cast<const TEvent *>(event)));
        }

    private:
        std::function<void(const TEvent &)> _callback;
    };
}
