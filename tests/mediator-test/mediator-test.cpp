
#include <gtest/gtest.h>
#include <SFME/mediator/mediator.hpp>
#include "events.hpp"
#include "receivers.hpp"

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

TEST(Mediator, Subscribe)
{
    sfme::mediator::EventManager manager;
    sfme::testing::Foo subjectFoo(manager);
    sfme::testing::NotRegister subjectBar;
    ASSERT_FALSE(manager.isRegister(subjectBar));
    ASSERT_TRUE(manager.isRegister(subjectFoo));
}

TEST(Mediator, Emit)
{
    sfme::mediator::EventManager manager;
    sfme::testing::Foo subjectFoo(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<sfme::testing::FooEvents>();
    releaseCerr();
}

TEST(Mediator, EmitToMultipleSubscriber)
{
    sfme::mediator::EventManager manager;
    sfme::testing::Foo subjectFoo(manager);
    sfme::testing::SecondSubject secondSub(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<sfme::testing::FooEvents>();
    releaseCerr();
}

TEST(Mediator, TypeTraits)
{
    static_assert(std::is_base_of_v<sfme::mediator::InsideEvents, sfme::testing::FooEvents>, "must be true");
    static_assert(std::is_base_of_v<sfme::mediator::InsideEvents, sfme::testing::BarEvents>, "must be true");
    static_assert(!std::is_base_of_v<sfme::mediator::InsideEvents, sfme::testing::Foo>, "must be false");
}

TEST(Mediator, AllEvents)
{
    sfme::mediator::EventManager manager;
    sfme::testing::AllEvents subject(manager);
    std::stringstream ss;
    captureCerr(ss);
    manager.emit<sfme::testing::FooEvents>();
    manager.emit<sfme::testing::BarEvents>();
    releaseCerr();
}