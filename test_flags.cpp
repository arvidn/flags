#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "type_safe_flags.hpp"
#include <sstream>
#include <cstdint>

using flags::operator ""_bit;

template <typename UnderlyingType, typename Tag>
std::string print(flags::bitfield_flag<UnderlyingType, Tag> v)
{
	std::stringstream s;
	s << v;
	return s.str();
}

using flags_t = flags::bitfield_flag<std::uint8_t, struct TestTag>;

TEST_CASE("print", "flags")
{
	using flags_t = flags::bitfield_flag<std::uint8_t, struct TestTag>;

	constexpr flags_t test_0 = 0_bit;
	constexpr flags_t test_1 = 1_bit;
	constexpr flags_t test_7 = 7_bit;

	CHECK(print(test_0) == "1");
	CHECK(print(test_1) == "2");
	CHECK(print(test_7) == "128");
}

TEST_CASE("static_cast", "flags")
{
	constexpr flags_t test_0 = 0_bit;
	constexpr flags_t test_1 = 1_bit;
	constexpr flags_t test_7 = 7_bit;

	CHECK(static_cast<std::uint8_t>(test_0) == 1);
	CHECK(static_cast<std::uint8_t>(test_1) == 2);
	CHECK(static_cast<std::uint8_t>(test_7) == 128);
}

TEST_CASE("AND", "flags")
{
	constexpr flags_t test_0{0};
	constexpr flags_t test_1{1};

	CHECK(static_cast<std::uint8_t>(test_0 & test_0) == 0);
	CHECK(static_cast<std::uint8_t>(test_0 & test_1) == 0);
	CHECK(static_cast<std::uint8_t>(test_1 & test_0) == 0);
	CHECK(static_cast<std::uint8_t>(test_1 & test_1) == 1);

	CHECK(static_cast<std::uint8_t>(flags_t{0} &= test_0) == 0);
	CHECK(static_cast<std::uint8_t>(flags_t{0} &= test_1) == 0);
	CHECK(static_cast<std::uint8_t>(flags_t{1} &= test_0) == 0);
	CHECK(static_cast<std::uint8_t>(flags_t{1} &= test_1) == 1);
}

TEST_CASE("OR", "flags")
{
	constexpr flags_t test_0{0};
	constexpr flags_t test_1{1};

	CHECK(static_cast<std::uint8_t>(test_0 | test_0) == 0);
	CHECK(static_cast<std::uint8_t>(test_0 | test_1) == 1);
	CHECK(static_cast<std::uint8_t>(test_1 | test_0) == 1);
	CHECK(static_cast<std::uint8_t>(test_1 | test_1) == 1);

	CHECK(static_cast<std::uint8_t>(flags_t{0} |= test_0) == 0);
	CHECK(static_cast<std::uint8_t>(flags_t{0} |= test_1) == 1);
	CHECK(static_cast<std::uint8_t>(flags_t{1} |= test_0) == 1);
	CHECK(static_cast<std::uint8_t>(flags_t{1} |= test_1) == 1);
}

TEST_CASE("XOR", "flags")
{
	constexpr flags_t test_0{0};
	constexpr flags_t test_1{1};

	CHECK(static_cast<std::uint8_t>(test_0 ^ test_0) == 0);
	CHECK(static_cast<std::uint8_t>(test_0 ^ test_1) == 1);
	CHECK(static_cast<std::uint8_t>(test_1 ^ test_0) == 1);
	CHECK(static_cast<std::uint8_t>(test_1 ^ test_1) == 0);

	CHECK(static_cast<std::uint8_t>(flags_t{0} ^= test_0) == 0);
	CHECK(static_cast<std::uint8_t>(flags_t{0} ^= test_1) == 1);
	CHECK(static_cast<std::uint8_t>(flags_t{1} ^= test_0) == 1);
	CHECK(static_cast<std::uint8_t>(flags_t{1} ^= test_1) == 0);
}

TEST_CASE("NOT", "flags")
{
	constexpr flags_t test_0{0};
	constexpr flags_t test_1{1};

	CHECK(static_cast<std::uint8_t>(~test_0) == 0b11111111);
	CHECK(static_cast<std::uint8_t>(~test_1) == 0b11111110);
}

TEST_CASE("compare", "flags")
{
	constexpr flags_t test_0{0};
	constexpr flags_t test_1{1};

	CHECK(test_0 == test_0);
	CHECK(test_1 == test_1);
	CHECK(test_1 != test_0);
	CHECK(test_0 != test_1);
}

