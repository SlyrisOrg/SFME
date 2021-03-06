//
// Created by milerius on 03/02/18.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <SFME/mediator/receiver.hpp>
#include <SFME/mediator/details/type_traits.hpp>
#include <SFME/mediator/details/event_callback_wrapper.hpp>
#include <SFME/mediator/details/type_id.hpp>

namespace sfme::mediator
{
    class EventManager
    {
    public:
        template <typename TEvent, typename TReceiver>
        void subscribe(TReceiver &receiver) noexcept
        {
            static_assert(details::is_mediator_event<TEvent>, "The template parameter must be derived from BaseEvent");
            const details::EventTypeID eventTypeID = details::getEventTypeID<TEvent>();
            const BaseReceiver &baseReceiver = receiver;
            auto receiverFunctor = [&receiver](const auto &ev) noexcept { receiver.receive(ev); };
            auto callbackPtr = std::make_unique<details::EventCallbackWrapper<TEvent>>(receiverFunctor);
            _receiversRegistry.emplace(eventTypeID, ReceiverData{&baseReceiver, std::move(callbackPtr)});
        };

        template <typename TEvent, typename ... Args>
        void emit(Args &&... args) noexcept
        {
            static_assert(details::is_mediator_event<TEvent>, "The template parameter must be derived from BaseEvent");
            TEvent event(std::forward<Args>(args)...);
            const details::EventTypeID eventTypeID = details::getEventTypeID<TEvent>();
            auto &&receivers = _receiversRegistry.equal_range(eventTypeID);
            std::for_each(receivers.first, receivers.second, [&event](const auto &receiverEntry) noexcept {
                (*receiverEntry.second.callback)(&event);
            });
        };

        bool isRegister(const BaseReceiver &receiver) const noexcept
        {
            return std::any_of(begin(_receiversRegistry), end(_receiversRegistry),
                               [&receiver](const auto &receiverEntry) {
                                   return receiverEntry.second.receiver == &receiver;
                               });
        }

    private:
        using CallbackPtr = std::unique_ptr<details::BaseEventCallbackWrapper>;
        struct ReceiverData
        {
            const BaseReceiver *receiver;
            CallbackPtr callback;
        };
        using ReceiversMap = std::unordered_multimap<details::EventTypeID, ReceiverData>;
        ReceiversMap _receiversRegistry;
    };
}
