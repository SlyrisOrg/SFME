
#include <gtest/gtest.h>
#include <SFME/mediator/mediator.hpp>

static std::streambuf *cerrBufBackup;

static void captureCerr(std::ostream &replacement) noexcept
{
    cerrBufBackup = std::cerr.rdbuf();
    std::cerr.rdbuf(replacement.rdbuf());
}

static void releaseCerr() noexcept
{
    std::cerr.rdbuf(cerrBufBackup);
}

struct FooEvents : sfme::mediator::InsideEvents
{
    FooEvents() noexcept
    {
        showEvents("FooEvents");
    }

    static constexpr std::string_view className() noexcept
    {
        using namespace std::string_view_literals;
        return "FooEvents"sv;
    }

    std::string str{"Good"};
};

struct BarEvents : sfme::mediator::InsideEvents
{
    BarEvents() noexcept
    {
        showEvents("BarEvents");
    }

    static constexpr std::string_view className() noexcept
    {
        using namespace std::string_view_literals;
        return "BarEvents"sv;
    }
};

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
    void receive([[maybe_unused]] const EventType& evt) noexcept
    {
        std::cout << EventType::className() << std::endl;
    }

private:
    sfme::mediator::EventManager &_evtMgr;
};

TEST(Mediator, Subscribe)
{
    sfme::mediator::EventManager manager;
    Foo subjectFoo(manager);
    NotRegister subjectBar;
    ASSERT_FALSE(manager.isRegister(subjectBar));
    ASSERT_TRUE(manager.isRegister(subjectFoo));
}

TEST(Mediator, Emit)
{
    sfme::mediator::EventManager manager;
    Foo subjectFoo(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<FooEvents>();
    releaseCerr();
}

TEST(Mediator, EmitToMultipleSubscriber)
{
    sfme::mediator::EventManager manager;
    Foo subjectFoo(manager);
    SecondSubject secondSub(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<FooEvents>();
    releaseCerr();
}

TEST(Mediator, TypeTraits)
{
    static_assert(std::is_base_of_v<sfme::mediator::InsideEvents, FooEvents>, "must be true");
    static_assert(std::is_base_of_v<sfme::mediator::InsideEvents, BarEvents>, "must be true");
    static_assert(!std::is_base_of_v<sfme::mediator::InsideEvents, Foo>, "must be false");
}

TEST(Mediator, AllEvents)
{
    sfme::mediator::EventManager manager;
    AllEvents subject(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<FooEvents>();
    manager.emit<BarEvents>();
    releaseCerr();
}