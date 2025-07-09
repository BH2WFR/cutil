#include <fmt/format.h>
#include <fmt/core.h>

#include <cutil/base.h>

#ifdef CUTIL_CPP17_SUPPORTED // C++17 required

#include <cutil/console_utils.h>
#include <cutil/cpp_utils.hpp>

#include <iostream>
#include <string>

#ifdef CUTIL_CPP20_SUPPORTED // C++20 required
	#include <format>
#endif

#include <cutil_externals/magic_enum/magic_enum_all.hpp>
#include <string_view>

#include <gtest/gtest.h>




enum class MyEnum : int16_t{
	var1 = 0,
	var2,
	var3,
	var4,
	var5,
	var6,
	var7,
	var8,
	var9,
	var10,
	var20 = 20,
	Default = var3,
};

enum class MyBits : uint32_t
{
	bit1 = 0x0000'0001,
	bit2 = 0x0000'0002,
	bit3 = 0x0000'0004,
	bit4 = 0x0000'0008,
	bit5 = 0x0000'0010,
	bit6 = 0x0000'0020,
	bit7 = 0x0000'0040,
	bit8 = 0x0000'0080,
	bit9 = 0x0000'0100,
	bit10 = 0x0000'0200,
	bit11 = 0x0000'0400,
	bit12 = 0x0000'0800,
	bit13 = 0x0000'1000,
	bit14 = 0x0000'2000,
	bit15 = 0x0000'4000,
	bit16 = 0x0000'8000,
	bit17 = 0x0001'0000,
	bit18 = 0x0002'0000,
	bit19 = 0x0004'0000,
	bit20 = 0x0008'0000,
	bit21 = 0x0010'0000,
	bit22 = 0x0020'0000,
	bit23 = 0x0040'0000,
	bit24 = 0x0080'0000,
	bit25 = 0x0100'0000,
	bit26 = 0x0200'0000,
	bit27 = 0x0400'0000,
	bit28 = 0x0800'0000,
	bit29 = 0x1000'0000,
	bit30 = 0x2000'0000,
	bit31 = 0x4000'0000,
	bit32 = 0x8000'0000,
};
	
TEST(MagicEnum, MyEnum)
{
	// enum -> std::string_view (constexpr)
	std::string var1str = magic_enum::enum_name(MyEnum::var1).data();
	EXPECT_EQ("var1", var1str);
	std::string var2str = magic_enum::enum_name(MyEnum::var2).data();
	EXPECT_EQ("var2", var2str);
	
	// enum -> number (constexpr)
	constexpr auto var1num = magic_enum::enum_integer(MyEnum::var1);
	EXPECT_EQ(0, var1num);
	constexpr auto var2num = magic_enum::enum_integer(MyEnum::var2);
	EXPECT_EQ(1, var2num);
	constexpr auto var20num = magic_enum::enum_integer(MyEnum::var20);
	EXPECT_EQ(20, var20num);
	static_assert(magic_enum::enum_integer(MyEnum::var1) == 0, "MagicEnum: var1 should be 0");
	static_assert(magic_enum::enum_integer(MyEnum::var2) == 1, "MagicEnum: var2 should be 1");
	static_assert(magic_enum::enum_integer(MyEnum::var20) == 20, "MagicEnum: var20 should be 20");
	
	// string -> enum (constexpr)
	constexpr auto var1enum = magic_enum::enum_cast<MyEnum>("var1");
	EXPECT_TRUE(var1enum.has_value());
	EXPECT_EQ(MyEnum::var1, var1enum.value());
	auto var2enum = magic_enum::enum_cast<MyEnum>("var2");
	EXPECT_TRUE(var2enum.has_value());
	EXPECT_EQ(MyEnum::var2, var2enum.value());
	auto var20enum = magic_enum::enum_cast<MyEnum>("var20");
	EXPECT_TRUE(var20enum.has_value());
	EXPECT_EQ(MyEnum::var20, var20enum.value());
	auto var99enum = magic_enum::enum_cast<MyEnum>("var99");
	EXPECT_FALSE(var99enum.has_value());
	
	
	// integer -> enum (constexpr)
	constexpr auto var1enum2 = magic_enum::enum_cast<MyEnum>(0);
	EXPECT_TRUE(var1enum2.has_value());
	EXPECT_EQ(MyEnum::var1, var1enum2.value());
	constexpr auto var2enum2 = magic_enum::enum_cast<MyEnum>(1);
	EXPECT_TRUE(var2enum2.has_value());
	EXPECT_EQ(MyEnum::var2, var2enum2.value());
	constexpr auto var20enum2 = magic_enum::enum_cast<MyEnum>(20);
	EXPECT_TRUE(var20enum2.has_value());
	EXPECT_EQ(MyEnum::var20, var20enum2.value());
	auto var99enum2 = magic_enum::enum_cast<MyEnum>(99);
	EXPECT_FALSE(var99enum2.has_value());


	// index -> enum
	auto var1enum3 = magic_enum::enum_value<MyEnum, 0>();
	EXPECT_EQ(MyEnum::var1, var1enum3);
	auto var2enum3 = magic_enum::enum_value<MyEnum, 1>();
	EXPECT_EQ(MyEnum::var2, var2enum3);
	
	// get sequence of enum values
	constexpr auto sequence = magic_enum::enum_values<MyEnum>();
	EXPECT_EQ(11, sequence.size());
	EXPECT_EQ(MyEnum::var1, sequence[0]);
	EXPECT_EQ(MyEnum::var2, sequence[1]);
	EXPECT_EQ(MyEnum::var20, sequence[10]);
	
	// numbers of enum elements
	constexpr auto count = magic_enum::enum_count<MyEnum>();
	EXPECT_EQ(11, count);
	
	// enum -> integer
	constexpr auto var1int = magic_enum::enum_integer(MyEnum::var1);
	EXPECT_EQ(0, var1int);
	constexpr auto var2int = magic_enum::enum_integer(MyEnum::var2);
	EXPECT_EQ(1, var2int);
	
	// enum name sequence
	constexpr auto names = magic_enum::enum_names<MyEnum>();
	EXPECT_EQ(11, names.size());
	EXPECT_EQ("var1", names[0]);
	EXPECT_EQ("var2", names[1]);
	EXPECT_EQ("var10", names[9]);
	
	// enum for each
	magic_enum::enum_for_each<MyEnum>([](MyEnum e) {
		switch (e) {
			case MyEnum::var1:
				EXPECT_EQ(MyEnum::var1, e);
				break;
			case MyEnum::var2:
				EXPECT_EQ(MyEnum::var2, e);
				break;
			case MyEnum::var20:
				EXPECT_EQ(MyEnum::var20, e);
				break;
			default:
				break;
		}
	});
	
	// enum type name
	auto enum_type_name = magic_enum::enum_type_name<MyEnum>();
	// fmt::println("Enum type name: {}", enum_type_name.data());
	EXPECT_EQ(strcmp(enum_type_name.data(), "MyEnum"), 0);
	
	// iostream operator<<
	using magic_enum::iostream_operators::operator<<;
	std::cout << "MyEnum::var1: " << MyEnum::var1 << std::endl;
	std::cout << "MyEnum::var2: " << MyEnum::var2 << std::endl;
}

TEST(MagicEnum, MyBits)
{
	// bitwise operator
	using namespace magic_enum::bitwise_operators;
	auto bit1 = MyBits::bit1;
	auto bit2 = MyBits::bit2;
	EXPECT_EQ(bit1 | bit2, MyBits::bit1 | MyBits::bit2);
	EXPECT_EQ(bit1 & bit2, MyBits::bit1 & MyBits::bit2);
	EXPECT_EQ(bit1 ^ bit2, MyBits::bit1 ^ MyBits::bit2);
	EXPECT_EQ(~bit1, ~MyBits::bit1);
	
	std::string bit1str = magic_enum::enum_flags_name(MyBits::bit1).data();
	EXPECT_EQ("bit1", bit1str);
	std::string bit2str = magic_enum::enum_flags_name(MyBits::bit2).data();
	EXPECT_EQ("bit2", bit2str);
	std::string bit1bit2str = magic_enum::enum_flags_name(MyBits::bit1 | MyBits::bit2).data();
	EXPECT_EQ("bit1|bit2", bit1bit2str);
	
	std::string bit31str = magic_enum::enum_flags_name(MyBits::bit31).data();
	EXPECT_EQ("bit31", bit31str);
	std::string bit32str = magic_enum::enum_flags_name(MyBits::bit32).data();
	EXPECT_EQ("bit32", bit32str);
	std::string bit31bit32str = magic_enum::enum_flags_name(MyBits::bit31 | MyBits::bit32).data();
	EXPECT_EQ("bit31|bit32", bit31bit32str);
	
	auto bit31bit32enum = magic_enum::enum_flags_cast<MyBits>(static_cast<uint32_t>(MyBits::bit31) | static_cast<uint32_t>(MyBits::bit32));
	EXPECT_TRUE(bit31bit32enum.has_value());
	EXPECT_EQ(MyBits::bit31 | MyBits::bit32, bit31bit32enum.value());
	
	// string to enum-flags
	auto bit1enum = magic_enum::enum_flags_cast<MyBits>("bit1");
	EXPECT_TRUE(bit1enum.has_value());
	EXPECT_EQ(MyBits::bit1, bit1enum.value());
	auto bit2enum = magic_enum::enum_flags_cast<MyBits>("bit2");
	EXPECT_TRUE(bit2enum.has_value());
	EXPECT_EQ(MyBits::bit2, bit2enum.value());
	auto bit1bit2enum = magic_enum::enum_flags_cast<MyBits>("bit1|bit2");
	EXPECT_TRUE(bit1bit2enum.has_value());
	EXPECT_EQ(MyBits::bit1 | MyBits::bit2, bit1bit2enum.value());
	auto bit31bit32enum2 = magic_enum::enum_flags_cast<MyBits>("bit31|bit32");
	EXPECT_TRUE(bit31bit32enum2.has_value());
	EXPECT_EQ(MyBits::bit31 | MyBits::bit32, bit31bit32enum2.value());
	auto bit99enum = magic_enum::enum_flags_cast<MyBits>("bit99");
	EXPECT_FALSE(bit99enum.has_value());
	
	// enum fuse between MyBits and MyEnum
	auto zzzzz1 = magic_enum::enum_fuse(MyEnum::var1, MyBits::bit1);
	EXPECT_TRUE(zzzzz1.has_value());
	EXPECT_EQ(magic_enum::enum_integer(MyEnum::var1), magic_enum::enum_integer(zzzzz1.value()));
	
	// print enum with fmt
	auto fmt_str = fmt::format("MyEnum::var1: {}, MyBits::bit1: {}", MyEnum::var1, MyBits::bit1);
	EXPECT_EQ(fmt_str, "MyEnum::var1: var1, MyBits::bit1: bit1");
}



#endif // C++17 required
