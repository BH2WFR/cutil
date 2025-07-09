#include <iostream>


#include <cutil/all.h>
#include <gtest/gtest.h>

TEST(Console, Console){
	std::cout << FLYellow "Hello World!" CReset << std::endl;
	EXPECT_EQ(0b10101011, cutil::set_bit_by_idx((uint8_t)0b10101010, 0));
}

// TEST(Bit2, simple)
// {
// 	EXPECT_EQ(0b10000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
// 	EXPECT_EQ(0b00000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
// 	EXPECT_EQ(0b10000010, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
// 	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b00000010, cutil::get_bit_by_idx((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(0b00100010, cutil::get_bit_by_idx((uint8_t)0b10101010, {0, 1, 2, 5, 6}));
// 	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
// 	EXPECT_EQ(false, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
// 	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
// 	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(true, cutil::check_bit_by_idx((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(true, cutil::check_bit_by_idx((uint8_t)0b10101010, {0, 1, 2, 5, 6}));
// 	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, {0, 2, 4}));
// 	static_assert(0b00000000 == cutil::get_bit_by_idx((uint8_t)0b10101010, 0), "");
// 	static_assert(true == cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000), "");
	
	
// 	uint8_t byte = 0b10101010;
// 	EXPECT_EQ(0b10101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
// 	EXPECT_EQ(0b11101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
// 	EXPECT_EQ(0b11101011, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
// 	EXPECT_EQ(0b10101011, cutil::set_bit_by_idx((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b10101110, cutil::set_bit_by_idx((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 3));
// 	EXPECT_EQ(0b10011011, cutil::set_bit_by_idx((uint8_t)0b10000001, {1, 3, 4}));
// 	static_assert(0b10101010 == cutil::set_bit_by_idx((uint8_t)0b10101010, 3), "");
	
	
// 	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
// 	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
// 	EXPECT_EQ(0b10101000, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
// 	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b10101000, cutil::clear_bit_by_idx((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(0b10100010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 3));
// 	EXPECT_EQ(0b10001000, cutil::clear_bit_by_idx((uint8_t)0b10101010, {0, 1, 4, 5}));
	
	
// 	EXPECT_EQ(0b00101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
// 	EXPECT_EQ(0b01101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
// 	EXPECT_EQ(0b11101001, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
// 	EXPECT_EQ(0b10101011, cutil::flip_bit_by_idx((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b10101000, cutil::flip_bit_by_idx((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b10101110, cutil::flip_bit_by_idx((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(0b10100010, cutil::flip_bit_by_idx((uint8_t)0b10101010, 3));
// 	EXPECT_EQ(0b10000001, cutil::flip_bit_by_idx((uint8_t)0b10101010, {0, 1, 3, 5}));
// 	static_assert(0b10100010 == cutil::flip_bit_by_idx((uint8_t)0b10101010, 3), "");
	
// }

// TEST(Bit2, rotate)
// {
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b01010101, cutil::rotate_bit_left((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 2));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 10));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_left((uint8_t)0b10101010, 10));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, -2));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, -10));
// 	static_assert(0b10101010 == cutil::rotate_bit_left((uint8_t)0b10101010, 10), "");
	
	
// 	EXPECT_EQ(0b00100100, cutil::rotate_bit_left((uint8_t)0b00100100, 0));
// 	EXPECT_EQ(0b01001000, cutil::rotate_bit_left((uint8_t)0b00100100, 1));
// 	EXPECT_EQ(0b10010000, cutil::rotate_bit_left((uint8_t)0b00100100, 2));
// 	EXPECT_EQ(0b00100001, cutil::rotate_bit_left((uint8_t)0b00100100, 3));
// 	EXPECT_EQ(0b01000010, cutil::rotate_bit_left((uint8_t)0b00100100, 4));
// 	constexpr auto zzzz = cutil::rotate_bit_left((uint8_t)0b00100100, -1);
// 	constexpr auto zzz2 = cutil::rotate_bit_right((uint8_t)0b00100100, 1);
	
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 0));
// 	EXPECT_EQ(0b01010101, cutil::rotate_bit_right((uint8_t)0b10101010, 1));
// 	EXPECT_EQ(0b10101010, cutil::rotate_bit_right((uint8_t)0b10101010, 2));
	
	
// 	EXPECT_EQ(0b00100100, cutil::rotate_bit_right((uint8_t)0b00100100, 0));
// 	EXPECT_EQ(0b00010010, cutil::rotate_bit_right((uint8_t)0b00100100, 1));
// 	EXPECT_EQ(0b00001001, cutil::rotate_bit_right((uint8_t)0b00100100, 2));
// 	EXPECT_EQ(0b10000100, cutil::rotate_bit_right((uint8_t)0b00100100, 3));
// 	EXPECT_EQ(0b01000010, cutil::rotate_bit_right((uint8_t)0b00100100, 4));
	
	
// 	EXPECT_EQ(0b10010010, cutil::insert_bit_left((uint8_t)0b00100100, true));
// 	EXPECT_EQ(0b00010010, cutil::insert_bit_left((uint8_t)0b00100100, false));
// 	EXPECT_EQ(0b01001001, cutil::insert_bit_right((uint8_t)0b00100100, true));
// 	EXPECT_EQ(0b01001000, cutil::insert_bit_right((uint8_t)0b00100100, false));
	
	

// }
