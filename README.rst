flags
=====

A simple type-safe flag template library in C++

usage
=====

Define a flags type and flag values::

	#include "type_safe_flags.hpp"

	using flags::operator ""_bit;
	using colour_flags_t = flags::bitfield_flag<std::uint8_t, struct color_flag_tag>;

	constexpr colour_flags_t red   = 0_bit;
	constexpr colour_flags_t green = 1_bit;
	constexpr colour_flags_t blue  = 2_bit;
	constexpr colour_flags_t alpha = 3_bit;

Use flags::

	colour_flags_t f = ...;
	if (flags & red) {
		...
	}
	std::cout << f << "\n";

	void fun(colour_flags_t);

	fun(red | green);
	fun({}); // zero, no flag set

