#pragma once

#include <core/utils/Enums.hpp>

namespace sfme::input::mouse
{
	ENUM(Button,
		Left,       ///< The left mouse button
		Right,      ///< The right mouse button
		Middle,     ///< The middle (wheel) mouse button
		XButton1,   ///< The first extra mouse button
		XButton2   ///< The second extra mouse button
		);

	ENUM(Wheel,
		VerticalWheel,  ///< The vertical mouse wheel
		HorizontalWheel ///< The horizontal mouse wheel
	    );
}
