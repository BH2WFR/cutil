/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		15 JUN 2025
  License:		MIT License
* You can include this header in header files.
* C++14 or later is required.
*/

#ifndef CUTIL_CPP_BITS_HPP__
#define CUTIL_CPP_BITS_HPP__
#include <cutil/base.h>
#include <cutil/cpp_base.hpp>

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif

#include <algorithm>
#include <iterator>
#include <cassert>
#include <cmath>
#include <numeric>
#include <limits>
#include <functional>
#ifdef CUTIL_CPP20_SUPPORTED
	#include <bit>
#endif


_CUTIL_NAMESPACE_BEGIN


namespace internal {
	
	
	
	
} // namespace internal


//======================= Bit Operations ============================
inline namespace bit { // inline
	//* get bits filtered by mask, `(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & bit_mask);
	}
	//* set bits specified by mask, `(num | mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_mask(T num, T bit_mask) noexcept {
		return (num | bit_mask);
	}
	//* clear bits specified by mask, `(num & ~mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_mask(T num, T bit_mask) noexcept {
		return (num & (~bit_mask));
	}
	//* flip bits specified by mask, `(num ^ mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_mask(T num, T bit_mask) noexcept {
		return (num ^ bit_mask);
	}
	//* check if bits filtered by mask are zero or not, `(bool)(num & mask)`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_mask(T num, T bit_mask) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_mask(num, bit_mask));
	}
	
	//* get the bit filtered by nth bit, `(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::get_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::get_bit_by_mask(num, mask);
	}
	
	//* set the bit specified by nth bit, `(num | (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::set_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T set_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::set_bit_by_mask(num, mask);
	}
	
	//* clear the bit specified by nth bit, `(num & ~(1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::clear_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clear_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::clear_bit_by_mask(num, mask);
	}
	
	//* flip the bit specified by nth bit, `(num ^ (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_idx(T num, size_t bit_idx) noexcept {
		return cutil::bit::flip_bit_by_mask(num, static_cast<T>(static_cast<T>(1u) << (bit_idx % std::numeric_limits<T>::digits)));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T flip_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		T mask = static_cast<T>(0);
		for(auto idx : bit_idx) {
			mask |= (static_cast<T>(1u) << (idx % std::numeric_limits<T>::digits));
		}
		return cutil::bit::flip_bit_by_mask(num, mask);
	}
	
	//* check if the bit filtered by nth bit is zero or not, `(bool)(num & (1<<bit_idx))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_idx(T num, size_t bit_idx) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_idx(num, bit_idx));
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool check_bit_by_idx(T num, std::initializer_list<size_t> bit_idx) noexcept {
		return static_cast<bool>(cutil::bit::get_bit_by_idx(num, bit_idx));
	}
	
	//* insert bit to the left, then shift others to right. `(bit >> 1) | (inserted << (bitSize - 1))`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T insert_bit_left(T num, bool inserted = true) noexcept {
		return (num >> 1) | (static_cast<T>(inserted) << (std::numeric_limits<T>::digits - 1));
	}
	
	//* insert bit to the right, then shift others to left. `(bit << 1) | inserted`
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T insert_bit_right(T num, bool inserted = true) noexcept {
		return (num << 1) | static_cast<T>(inserted);
	}
	
	//* get lsb (least significant bit, the rightmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_lsb(T num) noexcept {
		return (num & 1);
	}
	
	//* get msb (most significant bit, the leftmost bit)
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T get_msb(T num) noexcept {
		return (num & (1u << (std::numeric_limits<T>::digits - 1)));
	}
/*
	uint16_t num {0};
	// operate bit by index, starts at 0. use them in a separate line, and returns nothing
	num = cutil::bit::set_bit_by_idx(num, 1);   // equals to {num = num |  (1u << 0));}
	num = cutil::bit::clear_bit_by_idx(num, 2); // equals to {num = num & ~(1u << 2));}
	num = cutil::bit::flip_bit_by_idx(num, 3);  // equals to {num = num ^  (1u << 3));}
	num = cutil::bit::set_bit_by_idx(num, {0, 1, 3});   // initializer_list available
	num = cutil::bit::clear_bit_by_idx(num, {0, 1, 3}); // initializer_list available
	num = cutil::bit::flip_bit_by_idx(num, {0, 1, 3});  // initializer_list available
	if(cutil::bit::get_bit_by_idx(num, 0) != 0x0000){ // reading bit, if bit is 1, returns `(1<<bitIdx)`, NOT `1`
		printf("%x\n", num);
	}
	if(cutil::bit::check_bit_by_idx(num, 0) == true){ // reading bit, if bit is 1, returns `true`
		printf("%x\n", num);
	}
	
	// operate bit by mask
	num = cutil::bit::set_bit_by_mask(num, 0x2B00);   // equals to {num = num |  0x2B00;}
	num = cutil::bit::clear_bit_by_mask(num, 0x2B00); // equals to {num = num & ~0x2B00;}
	num = cutil::bit::flip_bit_by_mask(num, 0x1100);  // equals to {num = num ^  0x1100;}
	if(cutil::bit::get_bit_by_mask(num, 0x0022) != 0x0000){
		printf("%x\n", num);
	}
	if(cutil::bit::check_bit_by_mask(num, 0x0022) == true){ // reading bit, if bit is 1, returns `true`
		printf("%x\n", num);
	}
	
	// insert bit.
	uint16_t var2 {0b0001'0010'0011'0100};
	var2 = cutil::bit::insert_bit_left(var2, true);	  -> 0b1000'1001'0001'1010
	var2 = cutil::bit::insert_bit_right(var2, false); -> 0b0001'0010'0011'0100
*/
/*
	
	// rotate bits. use them in a separate line, and returns nothing
	uint16_t var {0b0001'0010'0011'0100};
	var = cutil::bit::rotate_bit_left(var, 1);	-> 0b0010'0100'0110'1000
	var = cutil::bit::rotate_bit_right(var, 1);	-> 0b0001'0010'0011'0100
	var = cutil::bit::rotate_bit_left(var, 4);	-> 0b0010'0100'0110'1000
	fmt::println("var={:#016b}", var);
	
	// get msb and lsb (leftmost and rightmost bit)
	var = cutil::bit::get_msb(0xFFFF); // get msb -> 0x8000
	var = cutil::bit::get_lsb(0xFFFF); // get lsb -> 0x0001
	
	// check if the number is power of 2 ({1, 2, 4, 8...})
	bool out = cutil::bit::has_single_bit(num));
	
*/

	//* get low byte and high byte of a word (16-bit unsigned integer)
	//  regardless of the endianness, the low byte is always the rightmost byte
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	uint8_t get_word_low(uint16_t word) {
		return (uint8_t)(word & 0xFF);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	uint8_t get_word_high(uint16_t word) {
		return (uint8_t)(word >> 8u);
	}
	_CUTIL_FUNC_STATIC inline
	void set_word_low(uint16_t& word, uint8_t val) {
		word = ((word & 0xFF00) | val);
	}
	_CUTIL_FUNC_STATIC inline
	void set_word_high(uint16_t& word, uint8_t val) {
		word = ((word & 0x00FF) | ((uint16_t)val << 8u));
	}
/*
	uint16_t v {0x1234};
	std::cout << cutil::memory::get_word_high(0x1234); // -> 12
	std::cout << cutil::memory::get_word_low(0x1234);  // -> 34
	cutil::memory::set_word_high(v, 0x56); // -> 0x5634
*/


//=================== C++20 <bit> implementation ===================

	//* rotate bit left by step, `((num << step) | (num >> (N - step)))`
	//  use std::rotl() since C++20
	//  if /O2 is enabled, this will be optimized to a single instruction on x86 and ARM
	//  also, you can use `_rotl()` `_rotl64()` in MSVC
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotate_bit_left(T num, int step = 1) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::rotl(num, static_cast<int>(step)); // x86 and ARM have CPU instructions for this
		}
	#endif
		constexpr auto digits = std::numeric_limits<T>::digits;
		step = step % digits; // ensure step is within range
		if(step > 0){
			return ((num << step) | (num >> (digits - step)));
		}else if(step < 0){
			return ((num >> -step) | (num << (digits + step))); // rotate left if step is negative
		}
		return num; // step == 0, no rotation needed
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotl(T num, int step = 1) noexcept {
		return cutil::bit::rotate_bit_left(num, step);
	}
	
	//* rotate bit right by step, `((num >> step) | (num << (N - step)))`
	//  use std::rotr() since C++20
	//  if /O2 is enabled, this will be optimized to a single instruction on x86 and ARM
	//  also, you can use `_rotr()` `_rotr64()` in MSVC
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotate_bit_right(T num, int step = 1) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::rotr(num, static_cast<int>(step)); // x86 and ARM have CPU instructions for this
		}
	#endif
		constexpr auto digits = std::numeric_limits<T>::digits;
		step = step % digits; // ensure step is within range
		if(step > 0){
			return ((num >> step) | (num << (digits - step)));
		}else if(step < 0){
			return ((num << -step) | (num >> (digits + step))); // rotate right if step is negative
		}
		return num; // step == 0, no rotation needed
	}
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T rotr(T num, int step = 1) noexcept {
		return cutil::bit::rotate_bit_right(num, step);
	}
	
	
	//* countl_zero, count leading zeros
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int countl_zero(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::countl_zero(num);
		}
	#endif
		constexpr int digits = std::numeric_limits<T>::digits;
		if(num == 0) {
			return digits; // all bits are zero
		}
		int count = 0;
		for(int i = digits; i > 0; --i) {
			if((num & (static_cast<T>(1u) << (i - 1))) == 0) {
				++count; // count leading zero
			}else{
				break; // stop counting when a non-zero bit is found
			}
		}
		return count;
	}
	
	//* countr_zero, count trailing zeros
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int countr_zero(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::countr_zero(num);
		}
	#endif
		constexpr int digits = std::numeric_limits<T>::digits;
		if(num == 0) {
			return digits; // all bits are zero
		}
		int count = 0;
		for(int i = 0; i < digits; ++i) {
			if((num & (static_cast<T>(1u) << i)) == 0) {
				++count; // count trailing zero
			}else{
				break; // stop counting when a non-zero bit is found
			}
		}
		return count;
	}
	
	//* countl_one, count leading ones
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int countl_one(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::countl_one(num);
		}
	#endif
		constexpr int digits = std::numeric_limits<T>::digits;
		if(num == 0) {
			return 0; // no leading ones
		}
		int count = 0;
		for(int i = digits; i > 0; --i) {
			if((num & (static_cast<T>(1u) << (i - 1))) != 0) {
				++count; // count leading one
			}else{
				break; // stop counting when a zero bit is found
			}
		}
		return count;
	}
	
	//* countr_one, count trailing ones
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int countr_one(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::countr_one(num);
		}
	#endif
		constexpr int digits = std::numeric_limits<T>::digits;
		if(num == 0) {
			return 0; // no trailing ones
		}
		int count = 0;
		for(int i = 0; i < digits; ++i) {
			if((num & (static_cast<T>(1u) << i)) != 0) {
				++count; // count trailing one
			}else{
				break; // stop counting when a zero bit is found
			}
		}
		return count;
	}
	
	//* has_single_bit, check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool has_single_bit(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::has_single_bit(num);
		}
	#endif
		return num != 0 && (num & (num - 1)) == 0;
	}
	// check if the number is power of 2 ({1, 2, 4, 8...})
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool is_power_of_2(T num) noexcept {
		return cutil::bit::has_single_bit(num);
	}
	
	//* bit_width, get the number of bits required to represent the number
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int bit_width(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::bit_width(num);
		}
	#endif
		return static_cast<int>(std::numeric_limits<T>::digits - cutil::bit::countl_zero(num));
	}
	
	
	//* bit_ceil, get the smallest power of 2 that is greater than or equal to the number
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T bit_ceil(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::bit_ceil(num);
		}
	#endif
		if(num <= 1u){
			return static_cast<T>(1u);
		}else{
			return static_cast<T>(1u) << (cutil::bit::bit_width(num) - 1 + (num & (num - 1) ? 1 : 0));
		}
	}
	
	//* bit_floor, get the largest power of 2 that is less than or equal to the number
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T bit_floor(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::bit_floor(num);
		}
	#endif
		if(num != 0){
			return (static_cast<T>(1u) << cutil::bit::bit_width(num) - 1);
		}else{
			return 0;
		}
	}
	
	
	//* byteswap, swap the byte order of the number
	#ifdef CUTIL_CPP23_SUPPORTED
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T byteswap(T num) noexcept {
		return std::byteswap(num);
	}
	#else // C++14/17/20
	template<typename T, _CUTIL_CONCEPT((std::is_same<T, uint8_t>::value))> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T byteswap(T num) noexcept {
		return num; // no need to swap for 1 byte
	}
	template<typename T, _CUTIL_CONCEPT((std::is_same<T, uint16_t>::value))> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T byteswap(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		#ifdef CUTIL_COMPILER_MSVC
			if (!std::is_constant_evaluated()) {return _byteswap_ushort(num);} // MSVC specific
		#elif defined(CUTIL_COMPILER_GCC) || defined(CUTIL_COMPILER_CLANG)
			if (!std::is_constant_evaluated()) {return __builtin_bswap16(num);} // GCC/Clang specific
		#endif
	#endif
		return (num >> 8) | (num << 8); // swap bytes for 2 bytes
	}
	template<typename T, _CUTIL_CONCEPT((std::is_same<T, uint32_t>::value))> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T byteswap(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		#ifdef CUTIL_COMPILER_MSVC
			if (!std::is_constant_evaluated()) {return _byteswap_ulong(num);} // MSVC specific
		#elif defined(CUTIL_COMPILER_GCC) || defined(CUTIL_COMPILER_CLANG)
			if (!std::is_constant_evaluated()) {return __builtin_bswap32(num);} // GCC/Clang specific
		#endif
	#endif
		return ((num >> 24) & 0x000000FF) // move byte 3 to byte 0
			 | ((num >> 8)  & 0x0000FF00)  // move byte 2 to byte 1
			 | ((num << 8)  & 0x00FF0000)  // move byte 1 to byte 2
			 | ((num << 24) & 0xFF000000); // move byte 0 to byte 3
	}
	template<typename T, _CUTIL_CONCEPT((std::is_same<T, uint64_t>::value))> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T byteswap(T num) noexcept {

	#ifdef CUTIL_CPP20_SUPPORTED
		#ifdef CUTIL_COMPILER_MSVC
			if (!std::is_constant_evaluated()) {return _byteswap_uint64(num);} // MSVC specific
		#elif defined(CUTIL_COMPILER_GCC) || defined(CUTIL_COMPILER_CLANG)
			if (!std::is_constant_evaluated()) {return __builtin_bswap64(num);} // GCC/Clang specific
		#endif
	#endif
		return ((num >> 56) & 0x00000000000000FF)  // move byte 7 to byte 0
			 | ((num >> 40) & 0x000000000000FF00)  // move byte 6 to byte 1
			 | ((num >> 24) & 0x0000000000FF0000)  // move byte 5 to byte 2
			 | ((num >> 8)  & 0x00000000FF000000)  // move byte 4 to byte 3
			 | ((num << 8)  & 0x000000FF00000000)  // move byte 3 to byte 4
			 | ((num << 24) & 0x0000FF0000000000)  // move byte 2 to byte 5
			 | ((num << 40) & 0x00FF000000000000)  // move byte 1 to byte 6
			 | ((num << 56) & 0xFF00000000000000); // move byte 0 to byte 7
	}
	#endif // C++23
	
	//* popcnt, count the number of set bits (1s) in the number
	template<typename T, _CUTIL_CONCEPT_UNSIGNED(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr int popcnt(T num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::popcount(num);
		}
	#endif
		int count = 0;
		while(num) {
			count += (num & 1); // add the least significant bit
			num >>= 1; // shift right to check the next bit
		}
		return count;
		// num = (num & T(0x5555555555555555UL)) + (num >> 1 & T(0x5555555555555555UL));
		// num = (num & T(0x3333333333333333UL)) + (num >> 2 & T(0x3333333333333333UL));
		// num = (num & T(0x0F0F0F0F0F0F0F0FUL)) + (num >> 4 & T(0x0F0F0F0F0F0F0F0FUL));
		// if(sizeof(num) > 1) {
		// 	num = (num & T(0x00FF00FF00FF00FFUL)) + (num >> 8 & T(0x00FF00FF00FF00FFUL));
		// 	if(sizeof(num) > 2) {
		// 		num = (num & T(0x0000FFFF0000FFFFUL)) + (num >> 16 & T(0x0000FFFF0000FFFFUL));
		// 		if(sizeof(num) > 4) {
		// 		num = (num & T(0x00000000FFFFFFFFUL)) + (num >> 32 & T(0x00000000FFFFFFFFUL));
		// 		}
		// 	}
		// }
		// return num;
	}





} // namespace bit







_CUTIL_NAMESPACE_END
#endif /* CUTIL_CPP_BITS_HPP__ */
