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
            static_assert(details::is_mediator_event<TEvent>, "The template parameter must be base of InsideEvents");
            const details::EventTypeID familyId = details::getTypeId<TEvent>();
            BaseReceiver &base = receiver;
            auto pair = std::make_pair(&base,
                                       std::make_shared<details::EventCallbackWrapper<TEvent>>(
                                           [&receiver](const auto &ev) noexcept {
                                               receiver.receive(ev);
                                           }));
            _receivers[familyId].emplace_back(std::move(pair));
        };

        template <typename TEvent, typename ... Args>
        void emit(Args &&... args) noexcept
        {
            static_assert(details::is_mediator_event<TEvent>, "The template parameter must be base of InsideEvents");
            TEvent event(std::forward<Args>(args)...);
            const details::EventTypeID familyId = details::getTypeId<TEvent>();

            std::for_each(begin(_receivers[familyId]), end(_receivers[familyId]), [&event](const auto &pr) noexcept {
                //! Otherwise MSVC ambiguous call...
                pr.second->operator()(&event);
            });
        };

        bool isRegister(BaseReceiver &receiver) const noexcept
        {
            for (auto &&receivers : _receivers) {
                for (auto &&vec: receivers.second) {
                    if (vec.first == &receiver)
                        return true;
                }
            }
            return false;
        }

    private:
        using CbPtr = std::shared_ptr<details::BaseEventCallbackWrapper>;
        using ReceiversVector = std::vector<std::pair<BaseReceiver *, CbPtr>>;
        using ReceiversMap = std::unordered_map<details::EventTypeID, ReceiversVector>;
        ReceiversMap _receivers;
    };
}
