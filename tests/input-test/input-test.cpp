//
// Created by milerius on 08/02/18.
//

#include <gtest/gtest.h>
#include <SFME/input/input.hpp>

TEST(Input, Basic)
{
	using namespace std::string_literals;
	ASSERT_EQ("A"s, sfme::input::keyboard::Key::toString(sfme::input::keyboard::Key::A));
	ASSERT_EQ("Left"s, sfme::input::mouse::Button::toString(sfme::input::mouse::Button::Left));
	ASSERT_EQ("HorizontalWheel"s, sfme::input::mouse::Wheel::toString(sfme::input::mouse::Wheel::HorizontalWheel));
}
