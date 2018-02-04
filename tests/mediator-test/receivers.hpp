//
// Created by milerius on 04/02/18.
//

#pragma once

#include <gtest/gtest.h>
#include <SFME/mediator/mediator.hpp>
#include "events.hpp"

namespace sfme::testing
{
    class SecondSubject : public sfme::mediator::Receiver<SecondSubject>
    {
    public:
        SecondSubject(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<FooEvents>(*this);
        }

    public:
        void receive(const FooEvents &evt) noexcept
        {
            using namespace std::string_literals;
            ASSERT_EQ("Good"s, evt.str);
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
    };

    class Foo : public sfme::mediator::Receiver<Foo>
    {
    public:
        Foo(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<FooEvents>(*this);
        }

    public:
        void receive(const FooEvents &evt) noexcept
        {
            using namespace std::string_literals;
            ASSERT_EQ("Good"s, evt.str);
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
    };

    class NotRegister : public sfme::mediator::Receiver<NotRegister>
    {
    };

    class AllEvents : public sfme::mediator::Receiver<AllEvents>
    {
    public:
        AllEvents(sfme::mediator::EventManager &evtMgr) noexcept : _evtMgr(evtMgr)
        {
            _evtMgr.subscribe<FooEvents>(*this);
            _evtMgr.subscribe<BarEvents>(*this);
        }

    public:
        template <typename EventType>
        void receive([[maybe_unused]] const EventType &evt) noexcept
        {
            using Type = decltype(EventType::className());
            ::testing::StaticAssertTypeEq<Type, std::string_view>();
        }

    private:
        sfme::mediator::EventManager &_evtMgr;
    };
}