#include <iostream>


#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <stack>
#include <queue>
#include <algorithm>


#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#endif

#include <fmt/core.h>
#include <fmt/format.h>

#ifdef CUTIL_CPP20_SUPPORTED // C++20 required
	#include <format>
#endif
// #define CUTIL_ANSI_ESCAPE_UNSUPPORTED	1
#include <cutil/all.h>

#include <gtest/gtest.h>

#ifdef CUTIL_CPP17_SUPPORTED
	#include <execution>
#endif

#include <cutil_externals/span.hpp>

int main(int argc, char* argv[])
{
	cutil::console::set_locale_utf8();
	cutil::console::set_chcp_encoding(cutil::console::Encodings::UTF8);
	cutil::console::enable_virtual_terminal();
	cutil::console::set_title("cutil Test");
	// cutil::console::set_size(70, 50);
	// cutil::console::flush_input_buffer();
	cutil::console::clear();
	cutil::console::print_argv(argc, argv);
	// cutil::console::set_cursor_pos(0, 0);
	cutil::console::move_cursor_next_line(3);
	std::cout << FLGreen "Hello" FLMagenta " World!" CRst "  -> UTF-8 Test: 中文 한글 🤣\n";
	fmt::println(FLCyan "     Test For cutil librarys" CRst);
	// std::getchar();
	// std::cout << FLRed "ERROR\	n" CReset;
	constexpr uint64_t ver = CUTIL_PTR_SIZE;
	
	std::atexit([]{
		fmt::println(FLYellow "EXIT! cpp lang={}" CRst, CUTIL_CPP_LANG);
		// cutil::console::pause();
	});
	testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	if(ret != 0){
		fmt::println(FLRed "Tests failed with code {}" CRst, ret);
	}else{
		fmt::println(FLGreen "All tests passed!" CRst);
	}
	return ret;
}

int test_macros_enum(CUTIL_ENUM(var_, int, 3)){
	return var_0 + var_1 + var_2;
}

TEST(Basic, macros)
{
	EXPECT_EQ(CUTIL_MULTICAT(1, 23, 4), 1234);
	EXPECT_EQ(CUTIL_MULTICAT(1, 23, 4, 56), 123456);
	
	std::vector<int> vec {};
	#define TEST_BASIC_APPEND(x) vec.push_back(x)
	CUTIL_SEQ_FOREACH(TEST_BASIC_APPEND, 1, 2, 3, 4, 5);
	EXPECT_EQ(vec, (std::vector<int>{1, 2, 3, 4, 5}));
	vec.clear();
	
	#define TEST_BASIC_REPEAT(x) vec.push_back(x)
	CUTIL_REPEAT(5, TEST_BASIC_REPEAT, 1);
	EXPECT_EQ(vec, (std::vector<int>{1, 1, 1, 1, 1}));
	vec.clear();
	
	EXPECT_EQ(6, test_macros_enum(1, 2, 3));
	
	
	CUTIL_FOR(i, 5){
		vec.push_back(i);
	}
	EXPECT_EQ(vec, (std::vector<int>{0, 1, 2, 3, 4}));
	vec.clear();
	
	CUTIL_FOR_TYPE(int, i, 5){
		vec.push_back(i);
	}
	EXPECT_EQ(vec, (std::vector<int>{0, 1, 2, 3, 4}));
	vec.clear();
	
	CUTIL_FOR(i, 2, 5){
		vec.push_back(i);
	}
	EXPECT_EQ(vec, (std::vector<int>{2, 3, 4}));
	vec.clear();
	
	CUTIL_FOR_TYPE(int, i, 2, 5){
		vec.push_back(i);
	}
	EXPECT_EQ(vec, (std::vector<int>{2, 3, 4}));
	vec.clear();
	
	int num {4};
	switch(num){
		CUTIL_CASE(1):
			EXPECT_EQ(1, 2);
			break;
		CUTIL_CASE(2, 3, 4):
			EXPECT_EQ(1, 1);
			break;
		CUTIL_CASE(5, 6, 7, 8, 9, 10):
			EXPECT_EQ(1, 2);
			break;
	}
}

TEST(Compare, equal_any)
{
	int a = 2;
	int b = 1;
	EXPECT_EQ(true,  cutil::equal_any(1, 1));
	EXPECT_EQ(false, cutil::equal_any(1, a));
	EXPECT_EQ(true,  cutil::equal_any(1, 1, a));
	EXPECT_EQ(false, cutil::equal_any(b, 2, 3));
	EXPECT_EQ(true,  cutil::equal_any(1, 2, 1));
	EXPECT_EQ(true,  cutil::equal_any(b, 1, 1));
	EXPECT_EQ(true,  cutil::equal_any(1, 1, a, 3));
	EXPECT_EQ(true,  cutil::equal_any(1, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_any(b, 2, 3, 4));
	static_assert(true == cutil::equal_any(1, 2, 3, 1), "");
	
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2, 3));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 2, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 1, 2, 3));
	EXPECT_EQ(true,  CUTIL_EQUAL_ANY(1, 2, 3, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ANY(1, 2, 3, 4));
	
}
TEST(Compare, equal_all)
{
	int a = 2;
	int b = 1;
	EXPECT_EQ(true,  cutil::equal_all(1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, a));
	EXPECT_EQ(false, cutil::equal_all(b, 1, a));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 1));
	EXPECT_EQ(true,  cutil::equal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 1, a, 3));
	EXPECT_EQ(false, cutil::equal_all(b, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_all(1, 2, 3, 4));
	EXPECT_EQ(false, cutil::equal_all(1, a, 1, 1));
	EXPECT_EQ(true,  cutil::equal_all(b, 1, 1, 1));
	static_assert(false == cutil::equal_all(1, 2, 3, 4), "");
	
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 1, 2));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 3, 4));
	EXPECT_EQ(false, CUTIL_EQUAL_ALL(1, 2, 1, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_ALL(1, 1, 1, 1));
	
	EXPECT_EQ(true,  cutil::equal_mutually(1, 1));
	EXPECT_EQ(false, cutil::equal_mutually(1, a));
	EXPECT_EQ(false, cutil::equal_mutually(b, 1, a));
	EXPECT_EQ(false, cutil::equal_mutually(1, 2, 3));
	EXPECT_EQ(false, cutil::equal_mutually(1, 2, 1));
	EXPECT_EQ(true,  cutil::equal_mutually(1, 1, 1));
	EXPECT_EQ(false, cutil::equal_mutually(1, 1, a, 3));
	EXPECT_EQ(false, cutil::equal_mutually(b, 2, 3, 1));
	EXPECT_EQ(false, cutil::equal_mutually(1, 2, 3, 4));
	EXPECT_EQ(false, cutil::equal_mutually(1, a, 1, 1));
	EXPECT_EQ(true,  cutil::equal_mutually(b, 1, 1, 1));
	
	EXPECT_EQ(true,  CUTIL_EQUAL_MUTUALLY(1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, a));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(b, 1, a));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, 2, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, 2, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_MUTUALLY(1, 1, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, 1, a, 3));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(b, 2, 3, 1));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, 2, 3, 4));
	EXPECT_EQ(false, CUTIL_EQUAL_MUTUALLY(1, a, 1, 1));
	EXPECT_EQ(true,  CUTIL_EQUAL_MUTUALLY(b, 1, 1, 1));
}
TEST(Compare, unequal_any)
{
	int a = 2;
	int b = 1;
	EXPECT_EQ(false, cutil::unequal_any(1, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2));
	EXPECT_EQ(true,  cutil::unequal_any(1, 1, 2));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_any(1, 1, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 1, 2, 3));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3, 1));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 3, 4));
	EXPECT_EQ(true,  cutil::unequal_any(1, 2, 1, 1));
	EXPECT_EQ(false, cutil::unequal_any(1, 1, 1, 1));
	static_assert(false == cutil::unequal_any(1, 1, 1, 1), "");
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 1, 2, 3));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 3, 4));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ANY(1, 2, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ANY(1, 1, 1, 1));
	
}
TEST(Compare, unequal_all)
{
	EXPECT_EQ(false, cutil::unequal_all(1, 1));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 1));
	EXPECT_EQ(false, cutil::unequal_all(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_all(1, 2, 3, 1));
	EXPECT_EQ(true,  cutil::unequal_all(1, 2, 3, 4));
	EXPECT_EQ(true, cutil::unequal_all(1, 2, 2, 2));
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 2));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_ALL(1, 2, 3, 1));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 3, 4));
	EXPECT_EQ(true,  CUTIL_UNEQUAL_ALL(1, 2, 2, 2));
}
TEST(Compare, unequal_mutually)
{
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 2));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 1));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 1));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 1, 2, 3));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 3, 1));
	EXPECT_EQ(true, cutil::unequal_mutually(1, 2, 3, 4));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 2, 4));
	EXPECT_EQ(false, cutil::unequal_mutually(1, 2, 3, 3));
	
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 2));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 1));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 1, 2, 3));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 1));
	EXPECT_EQ(true, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 4));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 2, 4));
	EXPECT_EQ(false, CUTIL_UNEQUAL_MUTUALLY(1, 2, 3, 3));
	
}

TEST(Compare, others)
{
	int a1 = 9;
	EXPECT_EQ(false, cutil::increasing(1, 1));
	EXPECT_EQ(true,  cutil::increasing(1, 2));
	EXPECT_EQ(false, cutil::increasing(1, 1, 2));
	EXPECT_EQ(false, cutil::increasing(1, 2, 2));
	EXPECT_EQ(true,  cutil::increasing(1, 2, 3));
	EXPECT_EQ(false, cutil::increasing(3, 2, 1));
	EXPECT_EQ(false, cutil::increasing(1, 2, 1, 4));
	EXPECT_EQ(false, cutil::increasing(1, 2, 2, 4));
	EXPECT_EQ(false, cutil::increasing(1, 2, 2, 5, 3));
	EXPECT_EQ(false, cutil::increasing(1, 2, 2, 5, 9));
	EXPECT_EQ(true,  cutil::increasing(1, 3, 5, 7, 9));
	EXPECT_EQ(true,  cutil::increasing(1, 3, 5, 7, a1));
	static_assert(true == cutil::increasing(1, 3, 5, 7, 9), "");
	
	EXPECT_EQ(false, CUTIL_INCREASING(1, 1));
	EXPECT_EQ(true,  CUTIL_INCREASING(1, 2));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 1, 2));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 2, 2));
	EXPECT_EQ(true,  CUTIL_INCREASING(1, 2, 3));
	EXPECT_EQ(false, CUTIL_INCREASING(3, 2, 1));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 2, 1, 4));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 2, 2, 4));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 2, 2, 5, 3));
	EXPECT_EQ(false, CUTIL_INCREASING(1, 2, 2, 5, 9));
	EXPECT_EQ(true,  CUTIL_INCREASING(1, 3, 5, 7, 9));
	EXPECT_EQ(true,  CUTIL_INCREASING(1, 3, 5, 7, a1));
	
	EXPECT_EQ(true,  cutil::increasing_equal(1, 1));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 2));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 1, 2));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 2, 2));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 2, 3));
	EXPECT_EQ(false, cutil::increasing_equal(3, 2, 1));
	EXPECT_EQ(false, cutil::increasing_equal(1, 2, 1, 4));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 2, 2, 4));
	EXPECT_EQ(false, cutil::increasing_equal(1, 2, 2, 5, 3));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 2, 2, 5, 9));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 3, 5, 7, 9));
	EXPECT_EQ(true,  cutil::increasing_equal(1, 3, 5, 7, a1));
	
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 1));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 2));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 1, 2));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 2, 2));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 2, 3));
	EXPECT_EQ(false, CUTIL_INCREASING_EQUAL(3, 2, 1));
	EXPECT_EQ(false, CUTIL_INCREASING_EQUAL(1, 2, 1, 4));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 2, 2, 4));
	EXPECT_EQ(false, CUTIL_INCREASING_EQUAL(1, 2, 2, 5, 3));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 2, 2, 5, 9));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 3, 5, 7, 9));
	EXPECT_EQ(true,  CUTIL_INCREASING_EQUAL(1, 3, 5, 7, a1));
	
	EXPECT_EQ(false, cutil::decreasing(1, 1));
	EXPECT_EQ(true,  cutil::decreasing(2, 1));
	EXPECT_EQ(false, cutil::decreasing(2, 1, 1));
	EXPECT_EQ(false, cutil::decreasing(3, 2, 2));
	EXPECT_EQ(true,  cutil::decreasing(3, 2, 1));
	EXPECT_EQ(false, cutil::decreasing(1, 2, 3));
	EXPECT_EQ(false, cutil::decreasing(3, 2, 2));
	EXPECT_EQ(false, cutil::decreasing(3, 3, 2));
	EXPECT_EQ(false, cutil::decreasing(4, 2, 2, 1));
	EXPECT_EQ(false, cutil::decreasing(1, 4, 2, 1));
	EXPECT_EQ(true,  cutil::decreasing(a1, 7, 6, 5, 3, 1));
	EXPECT_EQ(false, cutil::decreasing(9, 7, 6, 6, 3, 1));
	EXPECT_EQ(false, cutil::decreasing(a1, 7, 6, 5, 6, 1));
	
	EXPECT_EQ(false, CUTIL_DECREASING(1, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING(2, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(2, 1, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(3, 2, 2));
	EXPECT_EQ(true,  CUTIL_DECREASING(3, 2, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(1, 2, 3));
	EXPECT_EQ(false, CUTIL_DECREASING(3, 2, 2));
	EXPECT_EQ(false, CUTIL_DECREASING(3, 3, 2));
	EXPECT_EQ(false, CUTIL_DECREASING(4, 2, 2, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(1, 4, 2, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING(a1, 7, 6, 5, 3, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(9, 7, 6, 6, 3, 1));
	EXPECT_EQ(false, CUTIL_DECREASING(a1, 7, 6, 5, 6, 1));
	
	EXPECT_EQ(true,  cutil::decreasing_equal(1, 1));
	EXPECT_EQ(true,  cutil::decreasing_equal(2, 1));
	EXPECT_EQ(true,  cutil::decreasing_equal(2, 1, 1));
	EXPECT_EQ(true,  cutil::decreasing_equal(3, 2, 2));
	EXPECT_EQ(true,  cutil::decreasing_equal(3, 2, 1));
	EXPECT_EQ(false, cutil::decreasing_equal(1, 2, 3));
	EXPECT_EQ(true,  cutil::decreasing_equal(3, 3, 2));
	EXPECT_EQ(true,  cutil::decreasing_equal(4, 2, 2, 1));
	EXPECT_EQ(false, cutil::decreasing_equal(1, 4, 2, 1));
	EXPECT_EQ(true,  cutil::decreasing_equal(a1, 7, 6, 5, 3, 1));
	EXPECT_EQ(true,  cutil::decreasing_equal(9, 7, 6, 6, 3, 1));
	EXPECT_EQ(false, cutil::decreasing_equal(a1, 7, 6, 5, 6, 1));
	
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(1, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(2, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(2, 1, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(3, 2, 2));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(3, 2, 1));
	EXPECT_EQ(false, CUTIL_DECREASING_EQUAL(1, 2, 3));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(3, 3, 2));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(4, 2, 2, 1));
	EXPECT_EQ(false, CUTIL_DECREASING_EQUAL(1, 4, 2, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(a1, 7, 6, 5, 3, 1));
	EXPECT_EQ(true,  CUTIL_DECREASING_EQUAL(9, 7, 6, 6, 3, 1));
	EXPECT_EQ(false, CUTIL_DECREASING_EQUAL(a1, 7, 6, 5, 6, 1));
	
	CUTIL_DECREASING_EQUAL(a1, 7, 6, 5, 6, 1);
	
}

TEST(Range, contains)
{
	const std::vector<int> v1 = {1, 2, 3, 4, 5};
	std::map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
	std::set<int> s1 = {1, 2, 3, 4, 5};
	std::unordered_map<int, int> um1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
	std::unordered_set<int> us1 = {1, 2, 3, 4, 5};
	std::array<int, 5> a1 = {1, 2, 3, 4, 5};
	std::deque<int> d1 = {1, 2, 3, 4, 5};
	std::list<int> l1 = {1, 2, 3, 4, 5};
	std::forward_list<int> fl1 = {1, 2, 3, 4, 5};
	// std::stack<int> st1;
	// st1.push(1); st1.push(2); st1.push(3); st1.push(4); st1.push(5);
	// std::queue<int> q1;
	// std::priority_queue<int> pq1;
	// q1.push(1); q1.push(2); q1.push(3); q1.push(4); q1.push(5);
	
	EXPECT_EQ(true, cutil::contains(v1, 2));
	EXPECT_EQ(false, cutil::contains(v1, 0));
#ifndef CUTIL_COMPILER_GCC
	EXPECT_EQ(true, cutil::contains(m1, std::pair<int, int>(2, 2)));
	EXPECT_EQ(false, cutil::contains(m1, std::pair<int, int>(2, 3)));
#endif
	EXPECT_EQ(true, cutil::contains(s1, 2));
	EXPECT_EQ(false, cutil::contains(s1, 0));
#ifndef CUTIL_COMPILER_GCC
	EXPECT_EQ(true, cutil::contains(um1, std::pair<int, int>(2, 2)));
	EXPECT_EQ(false, cutil::contains(um1, std::pair<int, int>(2, 3)));
#endif
	EXPECT_EQ(true, cutil::contains(us1, 3));
	EXPECT_EQ(false, cutil::contains(us1, 0));
	EXPECT_EQ(true, cutil::contains(a1, 2));
	EXPECT_EQ(false, cutil::contains(a1, 0));
	EXPECT_EQ(true, cutil::contains(d1, 2));
	EXPECT_EQ(false, cutil::contains(d1, 0));
	EXPECT_EQ(true, cutil::contains(l1, 2));
	EXPECT_EQ(false, cutil::contains(l1, 0));
	EXPECT_EQ(true, cutil::contains(fl1, 2));
	EXPECT_EQ(false, cutil::contains(fl1, 0));
	
	EXPECT_EQ(true, cutil::contains_if(v1, [](int i){return i == 2;}));
	EXPECT_EQ(false, cutil::contains_if(v1, [](int i){return i == 0;}));
	
#ifdef CUTIL_CPP17_SUPPORTED
	EXPECT_EQ(true, cutil::contains(std::execution::seq, v1, 2));
	EXPECT_EQ(false, cutil::contains(std::execution::seq, v1, 0));
#endif
	
	
	std::vector<int> e1 = {1, 2, 2, 4, 2, 5, 4};
	int e1_1 = 2;
	EXPECT_EQ(3, cutil::erase_vector(e1, e1_1));
	EXPECT_EQ(std::vector<int>({1, 4, 5, 4}), e1);
	EXPECT_EQ(2, cutil::erase_vector(e1, 4));
	EXPECT_EQ(std::vector<int>({1, 5}), e1);
	EXPECT_EQ(0, cutil::erase_vector(e1, 6));
	EXPECT_EQ(std::vector<int>({1, 5}), e1);
	e1.clear();
	EXPECT_EQ(0, cutil::erase_vector(e1, 6));
	EXPECT_EQ(std::vector<int>(), e1);
	// EXPECT_EQ(true, cutil::contains(st1, 2));
	// EXPECT_EQ(false, cutil::contains(st1, 0));
	// EXPECT_EQ(true, cutil::contains(q1, 2));
	// EXPECT_EQ(false, cutil::contains(q1, 0));
	
	std::deque<int> e2 = {1, 2, 2, 4, 2, 5, 4};
	EXPECT_EQ(3, cutil::erase_vector(e2, 2));
	EXPECT_EQ(std::deque<int>({1, 4, 5, 4}), e2);
	EXPECT_EQ(2, cutil::erase_vector(e2, 4));
	EXPECT_EQ(std::deque<int>({1, 5}), e2);
	EXPECT_EQ(0, cutil::erase_vector(e2, 6));
	EXPECT_EQ(std::deque<int>({1, 5}), e2);
	e2.clear();
	EXPECT_EQ(0, cutil::erase_vector(e2, 6));
	EXPECT_EQ(std::deque<int>(), e2);
	
	std::vector<int> e3 = {1, 2, 2, 4, 2, 5, 4};
	EXPECT_EQ(3, cutil::erase_if_vector(e3, [](int i){return i == 2;}));
	EXPECT_EQ(std::vector<int>({1, 4, 5, 4}), e3);
}

TEST(Bit, simple)
{
	EXPECT_EQ(0b10000000, cutil::get_bit_by_mask((uint32_t)0b10101010, (uint32_t)0b10000000));
	EXPECT_EQ(0b10000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
	EXPECT_EQ(0b10000010, cutil::get_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b00000010, cutil::get_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b00000000, cutil::get_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b00100010, cutil::get_bit_by_idx((uint8_t)0b10101010, {0, 1, 2, 5, 6}));
	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(false, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000000));
	EXPECT_EQ(true, cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000011));
	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(true, cutil::check_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(true, cutil::check_bit_by_idx((uint8_t)0b10101010, {0, 1, 2, 5, 6}));
	EXPECT_EQ(false, cutil::check_bit_by_idx((uint8_t)0b10101010, {0, 2, 4}));
	static_assert(0b00000000 == cutil::get_bit_by_idx((uint8_t)0b10101010, 0), "");
	static_assert(true == cutil::check_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000), "");
	
	EXPECT_EQ(0b10000000, CUTIL_BIT_GET_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_MASK(0b10101010, 0b01000000));
	EXPECT_EQ(0b10000010, CUTIL_BIT_GET_MASK(0b10101010, 0b11000011));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_IDX(0b10101010, 0));
	EXPECT_EQ(0b00000010, CUTIL_BIT_GET_IDX(0b10101010, 1));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_IDX(0b10101010, 2));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_MASK(0b10101010, 0b01000000));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_MASK(0b10101010, 0b11000011));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_IDX(0b10101010, 0));
	EXPECT_EQ(1, CUTIL_BIT_CHECK_IDX(0b10101010, 1));
	EXPECT_EQ(0, CUTIL_BIT_CHECK_IDX(0b10101010, 2));
	
	uint8_t byte = 0b10101010;
	EXPECT_EQ(0b10101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b11101010, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b11101011, cutil::set_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101011, cutil::set_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::set_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10101010, cutil::set_bit_by_idx((uint8_t)0b10101010, 3));
	EXPECT_EQ(0b10011011, cutil::set_bit_by_idx((uint8_t)0b10000001, {1, 3, 4}));
	static_assert(0b10101010 == cutil::set_bit_by_idx((uint8_t)0b10101010, 3), "");
	
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b11101010, CUTIL_BIT_SET_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101011, CUTIL_BIT_SET_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, CUTIL_BIT_SET_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101110, CUTIL_BIT_SET_IDX(0b10101010, 2));
	EXPECT_EQ(0b10101010, CUTIL_BIT_SET_IDX(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b00101010, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::clear_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::clear_bit_by_idx((uint8_t)0b10101010, 3));
	EXPECT_EQ(0b10001000, cutil::clear_bit_by_idx((uint8_t)0b10101010, {0, 1, 4, 5}));
	
	EXPECT_EQ(0b00101010, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b00101010, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b10101000, CUTIL_BIT_CLEAR_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101010, CUTIL_BIT_CLEAR_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101000, CUTIL_BIT_CLEAR_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_CLEAR_IDX(0b10101010, 2));
	EXPECT_EQ(0b10100010, CUTIL_BIT_CLEAR_IDX(0b10101010, 3));
	
	EXPECT_EQ(0b00101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b10000000));
	EXPECT_EQ(0b01101010, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b11000000));
	EXPECT_EQ(0b11101001, cutil::flip_bit_by_mask((uint8_t)0b10101010, (uint8_t)0b01000011));
	EXPECT_EQ(0b10101011, cutil::flip_bit_by_idx((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b10101000, cutil::flip_bit_by_idx((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101110, cutil::flip_bit_by_idx((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10100010, cutil::flip_bit_by_idx((uint8_t)0b10101010, 3));
	EXPECT_EQ(0b10000001, cutil::flip_bit_by_idx((uint8_t)0b10101010, {0, 1, 3, 5}));
	static_assert(0b10100010 == cutil::flip_bit_by_idx((uint8_t)0b10101010, 3), "");
	
	EXPECT_EQ(0b00101010, CUTIL_BIT_FLIP_MASK(0b10101010, 0b10000000));
	EXPECT_EQ(0b01101010, CUTIL_BIT_FLIP_MASK(0b10101010, 0b11000000));
	EXPECT_EQ(0b11101001, CUTIL_BIT_FLIP_MASK(0b10101010, 0b01000011));
	EXPECT_EQ(0b10101011, CUTIL_BIT_FLIP_IDX(0b10101010, 0));
	EXPECT_EQ(0b10101000, CUTIL_BIT_FLIP_IDX(0b10101010, 1));
	EXPECT_EQ(0b10101110, CUTIL_BIT_FLIP_IDX(0b10101010, 2));
	EXPECT_EQ(0b10100010, CUTIL_BIT_FLIP_IDX(0b10101010, 3));
}

TEST(Bit, rotate)
{
	EXPECT_EQ(0b00010010001101000101011001111000, cutil::rotl((uint32_t)0x12345678, 0));
	EXPECT_EQ(0b00100100011010001010110011110000, cutil::rotl((uint32_t)0x12345678, 1));
	EXPECT_EQ(0b01001000110100010101100111100000, cutil::rotl((uint32_t)0x12345678, 2));
	EXPECT_EQ(0b10010001101000101011001111000000, cutil::rotl((uint32_t)0x12345678, 3));
	EXPECT_EQ(0b00100011010001010110011110000001, cutil::rotl((uint32_t)0x12345678, 4));
	EXPECT_EQ(0b00001001000110100010101100111100, cutil::rotl((uint32_t)0x12345678, -1));
	EXPECT_EQ(0b00000100100011010001010110011110, cutil::rotl((uint32_t)0x12345678, -2));
	EXPECT_EQ(0b00000010010001101000101011001111, cutil::rotl((uint32_t)0x12345678, -3));
	EXPECT_EQ(0b10000001001000110100010101100111, cutil::rotl((uint32_t)0x12345678, -4));
	
	EXPECT_EQ(0b00010010001101000101011001111000, cutil::rotr((uint32_t)0x12345678, 0));
	EXPECT_EQ(0b00001001000110100010101100111100, cutil::rotr((uint32_t)0x12345678, 1));
	EXPECT_EQ(0b00000100100011010001010110011110, cutil::rotr((uint32_t)0x12345678, 2));
	EXPECT_EQ(0b00000010010001101000101011001111, cutil::rotr((uint32_t)0x12345678, 3));
	EXPECT_EQ(0b10000001001000110100010101100111, cutil::rotr((uint32_t)0x12345678, 4));
	EXPECT_EQ(0b00100100011010001010110011110000, cutil::rotr((uint32_t)0x12345678, -1));
	EXPECT_EQ(0b01001000110100010101100111100000, cutil::rotr((uint32_t)0x12345678, -2));
	EXPECT_EQ(0b10010001101000101011001111000000, cutil::rotr((uint32_t)0x12345678, -3));
	EXPECT_EQ(0b00100011010001010110011110000001, cutil::rotr((uint32_t)0x12345678, -4));
	
	
	EXPECT_EQ(0b10101010, cutil::rotl((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotl((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotl((uint8_t)0b10101010, 2));
	EXPECT_EQ(0b10101010, cutil::rotl((uint8_t)0b10101010, 10));
	EXPECT_EQ(0b10101010, cutil::rotl((uint8_t)0b10101010, 10));
	EXPECT_EQ(0b10101010, cutil::rotr((uint8_t)0b10101010, -2));
	EXPECT_EQ(0b10101010, cutil::rotr((uint8_t)0b10101010, -10));
	static_assert(0b10101010 == cutil::rotl((uint8_t)0b10101010, 10), "");
	
	// EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotl((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b01001000, cutil::rotl((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b10010000, cutil::rotl((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b00100001, cutil::rotl((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotl((uint8_t)0b00100100, 4));
	constexpr auto zzzz = cutil::rotl((uint8_t)0b00100100, -1);
	constexpr auto zzz2 = cutil::rotr((uint8_t)0b00100100, 1);
	// EXPECT_EQ(0b00100100, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b01001000, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b10010000, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b00100001, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, CUTIL_BIT_ROTATE_LEFT((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b10101010, cutil::rotr((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, cutil::rotr((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, cutil::rotr((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 0));
	EXPECT_EQ(0b01010101, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 1));
	EXPECT_EQ(0b10101010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b10101010, 2));
	
	EXPECT_EQ(0b00100100, cutil::rotr((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b00010010, cutil::rotr((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b00001001, cutil::rotr((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b10000100, cutil::rotr((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, cutil::rotr((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b00100100, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 0));
	EXPECT_EQ(0b00010010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 1));
	EXPECT_EQ(0b00001001, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 2));
	EXPECT_EQ(0b10000100, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 3));
	EXPECT_EQ(0b01000010, CUTIL_BIT_ROTATE_RIGHT((uint8_t)0b00100100, 4));
	
	EXPECT_EQ(0b10010010, cutil::insert_bit_left((uint8_t)0b00100100, true));
	EXPECT_EQ(0b00010010, cutil::insert_bit_left((uint8_t)0b00100100, false));
	EXPECT_EQ(0b01001001, cutil::insert_bit_right((uint8_t)0b00100100, true));
	EXPECT_EQ(0b01001000, cutil::insert_bit_right((uint8_t)0b00100100, false));
	
	EXPECT_EQ(0b10010010, CUTIL_BIT_INSERT_LEFT((uint8_t)0b00100100, true));
	EXPECT_EQ(0b00010010, CUTIL_BIT_INSERT_LEFT((uint8_t)0b00100100, false));
	EXPECT_EQ(0b01001001, CUTIL_BIT_INSERT_RIGHT((uint8_t)0b00100100, true));
	EXPECT_EQ(0b01001000, CUTIL_BIT_INSERT_RIGHT((uint8_t)0b00100100, false));
	

}



TEST(Bit, Others)
{
	EXPECT_EQ(0b00000001, cutil::get_lsb((uint8_t)0b00100101));
	EXPECT_EQ(0b00000000, cutil::get_lsb((uint8_t)0b00100100));
	EXPECT_EQ(0b00000001, cutil::get_lsb((uint8_t)0b00000001));
	EXPECT_EQ(0b00000000, cutil::get_lsb((uint8_t)0b00000000));
	EXPECT_EQ(0b00000000, cutil::get_msb((uint8_t)0b00100101));
	EXPECT_EQ(0b10000000, cutil::get_msb((uint8_t)0b10100101));
	static_assert(0b10000000 == cutil::get_msb((uint8_t)0b10100101), "");
	
	EXPECT_EQ(0b00000001, CUTIL_BIT_GET_LSB((uint8_t)0b00100101));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_LSB((uint8_t)0b00100100));
	EXPECT_EQ(0b00000001, CUTIL_BIT_GET_LSB((uint8_t)0b00000001));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_LSB((uint8_t)0b00000000));
	EXPECT_EQ(0b00000000, CUTIL_BIT_GET_MSB((uint8_t)0b00100101));
	EXPECT_EQ(0b10000000, CUTIL_BIT_GET_MSB((uint8_t)0b10100101));
	
	
	
	EXPECT_EQ(false, cutil::has_single_bit(0u));
	EXPECT_EQ(true, cutil::has_single_bit(1u));
	EXPECT_EQ(true, cutil::has_single_bit(2u));
	EXPECT_EQ(false, cutil::has_single_bit(3u));
	EXPECT_EQ(true, cutil::has_single_bit(4u));
	EXPECT_EQ(false, cutil::has_single_bit(6u));
	EXPECT_EQ(true, cutil::has_single_bit(8u));
	
	
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(0u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(1u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(2u));
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(3u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(4u));
	EXPECT_EQ(false, CUTIL_HAS_SINGLE_BIT(6u));
	EXPECT_EQ(true, CUTIL_HAS_SINGLE_BIT(8u));
	
	// countr_zero
	EXPECT_EQ(8,  cutil::countr_zero((uint8_t)0b00000000));
	EXPECT_EQ(7,  cutil::countr_zero((uint8_t)0b10000000));
	EXPECT_EQ(6,  cutil::countr_zero((uint8_t)0b11000000));
	EXPECT_EQ(5,  cutil::countr_zero((uint8_t)0b10100000));
	EXPECT_EQ(4,  cutil::countr_zero((uint8_t)0b11110000));
	EXPECT_EQ(3,  cutil::countr_zero((uint8_t)0b01111000));
	EXPECT_EQ(2,  cutil::countr_zero((uint8_t)0b10111100));
	EXPECT_EQ(1,  cutil::countr_zero((uint8_t)0b11011110));
	EXPECT_EQ(0,  cutil::countr_zero((uint8_t)0b11100011));
	EXPECT_EQ(0,  cutil::countr_zero((uint8_t)0b01010111));
	EXPECT_EQ(0,  cutil::countr_zero((uint8_t)0b00000001));
	EXPECT_EQ(16, cutil::countr_zero((uint16_t)0b0000000000000000));
	EXPECT_EQ(15, cutil::countr_zero((uint16_t)0b1000000000000000));
	EXPECT_EQ(14, cutil::countr_zero((uint16_t)0b1100000000000000));
	EXPECT_EQ(13, cutil::countr_zero((uint16_t)0b1010000000000000));
	EXPECT_EQ(2,  cutil::countr_zero((uint16_t)0b1111000000000100));
	EXPECT_EQ(1,  cutil::countr_zero((uint16_t)0b0111100000000010));
	EXPECT_EQ(0,  cutil::countr_zero((uint16_t)0b1011110000000001));
	EXPECT_EQ(32, cutil::countr_zero((uint32_t)0b00000000000000000000000000000000));
	EXPECT_EQ(31, cutil::countr_zero((uint32_t)0b10000000000000000000000000000000));
	EXPECT_EQ(30, cutil::countr_zero((uint32_t)0b11000000000000000000000000000000));
	EXPECT_EQ(29, cutil::countr_zero((uint32_t)0b10100000000000000000000000000000));
	
	// countr_one tests
	EXPECT_EQ(0, cutil::countr_one((uint8_t)0b00000000));
	EXPECT_EQ(1, cutil::countr_one((uint8_t)0b00000001));
	EXPECT_EQ(2, cutil::countr_one((uint8_t)0b00000011));
	EXPECT_EQ(3, cutil::countr_one((uint8_t)0b00000111));
	EXPECT_EQ(4, cutil::countr_one((uint8_t)0b00001111));
	EXPECT_EQ(5, cutil::countr_one((uint8_t)0b00011111));
	EXPECT_EQ(6, cutil::countr_one((uint8_t)0b00111111));
	EXPECT_EQ(7, cutil::countr_one((uint8_t)0b01111111));
	EXPECT_EQ(8, cutil::countr_one((uint8_t)0b11111111));
	EXPECT_EQ(0, cutil::countr_one((uint8_t)0b11111110));
	EXPECT_EQ(0, cutil::countr_one((uint8_t)0b10101010));
	EXPECT_EQ(2, cutil::countr_one((uint8_t)0b10101011));

	EXPECT_EQ(0, cutil::countr_one((uint16_t)0b0000000000000000));
	EXPECT_EQ(5, cutil::countr_one((uint16_t)0b1010101000011111));
	EXPECT_EQ(6, cutil::countr_one((uint16_t)0b111110000111111));
	EXPECT_EQ(16, cutil::countr_one((uint16_t)0b1111111111111111));

	EXPECT_EQ(0, cutil::countr_one((uint32_t)0b00000000000000000000000000000000));
	EXPECT_EQ(12, cutil::countr_one((uint32_t)0b10101010101010101010111111111111));
	EXPECT_EQ(32, cutil::countr_one((uint32_t)0b11111111111111111111111111111111));

	// countl_zero tests
	EXPECT_EQ(8, cutil::countl_zero((uint8_t)0b00000000));
	EXPECT_EQ(7, cutil::countl_zero((uint8_t)0b00000001));
	EXPECT_EQ(5, cutil::countl_zero((uint8_t)0b00000100));
	EXPECT_EQ(2, cutil::countl_zero((uint8_t)0b00101000));
	EXPECT_EQ(0, cutil::countl_zero((uint8_t)0b10010000));
	EXPECT_EQ(0, cutil::countl_zero((uint8_t)0b10100000));
	EXPECT_EQ(1, cutil::countl_zero((uint8_t)0b01000000));
	EXPECT_EQ(0, cutil::countl_zero((uint8_t)0b10000100));
	EXPECT_EQ(0, cutil::countl_zero((uint8_t)0b11111111));
	EXPECT_EQ(0, cutil::countl_zero((uint8_t)0b10101010));
	EXPECT_EQ(1, cutil::countl_zero((uint8_t)0b01010101));

	EXPECT_EQ(16, cutil::countl_zero((uint16_t)0b0000000000000000));
	EXPECT_EQ(8, cutil::countl_zero((uint16_t)0b0000000011111111));
	EXPECT_EQ(4, cutil::countl_zero((uint16_t)0b0000111100000000));
	EXPECT_EQ(0, cutil::countl_zero((uint16_t)0b1111111111111111));

	EXPECT_EQ(32, cutil::countl_zero((uint32_t)0b00000000000000000000000000000000));
	EXPECT_EQ(16, cutil::countl_zero((uint32_t)0b00000000000000001111111111111111));
	EXPECT_EQ(0, cutil::countl_zero((uint32_t)0b11111111111111111111111111111111));

	static_assert(8 == cutil::countl_zero((uint8_t)0b00000000), "");
	static_assert(0 == cutil::countl_zero((uint8_t)0b11111111), "");
	static_assert(0 == cutil::countr_one((uint8_t)0b00000000), "");
	static_assert(8 == cutil::countr_one((uint8_t)0b11111111), "");
	
	
	// countl_one
	EXPECT_EQ(0,  cutil::countl_one((uint8_t)0b00000000));
	EXPECT_EQ(1,  cutil::countl_one((uint8_t)0b10000000));
	EXPECT_EQ(2,  cutil::countl_one((uint8_t)0b11000100));
	EXPECT_EQ(3,  cutil::countl_one((uint8_t)0b11100010));
	EXPECT_EQ(4,  cutil::countl_one((uint8_t)0b11110001));
	EXPECT_EQ(5,  cutil::countl_one((uint8_t)0b11111000));
	EXPECT_EQ(6,  cutil::countl_one((uint8_t)0b11111100));
	EXPECT_EQ(7,  cutil::countl_one((uint8_t)0b11111110));
	EXPECT_EQ(8,  cutil::countl_one((uint8_t)0b11111111));
	EXPECT_EQ(0,  cutil::countl_one((uint16_t)0b0000000000000000));
	EXPECT_EQ(1,  cutil::countl_one((uint16_t)0b1000000000000000));
	EXPECT_EQ(2,  cutil::countl_one((uint16_t)0b1100000000000000));
	EXPECT_EQ(3,  cutil::countl_one((uint16_t)0b1110000010010000));
	EXPECT_EQ(14, cutil::countl_one((uint16_t)0b1111111111111101));
	EXPECT_EQ(16, cutil::countl_one((uint16_t)0b1111111111111111));
	
	// bit_width
	EXPECT_EQ(0,  cutil::bit_width((uint8_t)0b00000000));
	EXPECT_EQ(1,  cutil::bit_width((uint8_t)0b00000001));
	EXPECT_EQ(2,  cutil::bit_width((uint8_t)0b00000010));
	EXPECT_EQ(3,  cutil::bit_width((uint8_t)0b00000101));
	EXPECT_EQ(4,  cutil::bit_width((uint8_t)0b00001000));
	EXPECT_EQ(5,  cutil::bit_width((uint8_t)0b00011101));
	EXPECT_EQ(6,  cutil::bit_width((uint8_t)0b00101001));
	EXPECT_EQ(7,  cutil::bit_width((uint8_t)0b01010000));
	EXPECT_EQ(8,  cutil::bit_width((uint8_t)0b10000111));
	EXPECT_EQ(0,   cutil::bit_width((uint32_t)0b00000000'00000000'00000000'00000000));
	EXPECT_EQ(4,   cutil::bit_width((uint32_t)0b00000000'00000000'00000000'00001000));
	EXPECT_EQ(5,   cutil::bit_width((uint32_t)0b00000000'00000000'00000000'00011000));
	EXPECT_EQ(31,  cutil::bit_width((uint32_t)0b01000000'00100000'00000100'00001101));
	
	// bit_ceil
	EXPECT_EQ(1,  cutil::bit_ceil((uint8_t)0b00000000));
	EXPECT_EQ(1,  cutil::bit_ceil((uint8_t)0b00000001));
	EXPECT_EQ(2,  cutil::bit_ceil((uint8_t)0b00000010));
	EXPECT_EQ(8,  cutil::bit_ceil((uint8_t)0b00000101));
	EXPECT_EQ(8,  cutil::bit_ceil((uint8_t)0b00001000));
	EXPECT_EQ(32, cutil::bit_ceil((uint8_t)0b00011101));
	EXPECT_EQ(64, cutil::bit_ceil((uint8_t)0b00101001));
	EXPECT_EQ(128, cutil::bit_ceil((uint8_t)0b01010000));
	EXPECT_EQ(1,   cutil::bit_ceil((uint32_t)0b00000000'00000000'00000000'00000000));
	EXPECT_EQ(16,  cutil::bit_ceil((uint32_t)0b00000000'00000000'00000000'00001010));
	EXPECT_EQ(16,  cutil::bit_ceil((uint32_t)0b00000000'00000000'00000000'00010000));
	EXPECT_EQ(32,  cutil::bit_ceil((uint32_t)0b00000000'00000000'00000000'00011000));
	EXPECT_EQ(0x8000'0000,  cutil::bit_ceil((uint32_t)0b01000000'00100000'00000100'00001101));
	
	// bit_floor
	EXPECT_EQ(0,  cutil::bit_floor((uint8_t)0b00000000));
	EXPECT_EQ(1,  cutil::bit_floor((uint8_t)0b00000001));
	EXPECT_EQ(2,  cutil::bit_floor((uint8_t)0b00000010));
	EXPECT_EQ(4,  cutil::bit_floor((uint8_t)0b00000101));
	EXPECT_EQ(8,  cutil::bit_floor((uint8_t)0b00001000));
	EXPECT_EQ(16, cutil::bit_floor((uint8_t)0b00011101));
	EXPECT_EQ(32, cutil::bit_floor((uint8_t)0b00101001));
	EXPECT_EQ(32, cutil::bit_floor((uint8_t)0b00100000));
	EXPECT_EQ(64, cutil::bit_floor((uint8_t)0b01010000));
	EXPECT_EQ(128, cutil::bit_floor((uint8_t)0b10000111));
	EXPECT_EQ(0,   cutil::bit_floor((uint32_t)0b00000000'00000000'00000000'00000000));
	EXPECT_EQ(1,   cutil::bit_floor((uint32_t)0b00000000'00000000'00000000'00000001));
	EXPECT_EQ(2,   cutil::bit_floor((uint32_t)0b00000000'00000000'00000000'00000010));
	EXPECT_EQ(4,   cutil::bit_floor((uint32_t)0b00000000'00000000'00000000'00000101));
	EXPECT_EQ(8,   cutil::bit_floor((uint32_t)0b00000000'00000000'00000000'00001000));
	EXPECT_EQ(0x4000'0000,  cutil::bit_floor((uint32_t)0b01000000'00100000'00000100'00001101));
	
	// popcnt
	EXPECT_EQ(0,  cutil::popcnt((uint8_t)0b00000000));
	EXPECT_EQ(1,  cutil::popcnt((uint8_t)0b00000001));
	EXPECT_EQ(2,  cutil::popcnt((uint8_t)0b00000011));
	EXPECT_EQ(3,  cutil::popcnt((uint8_t)0b00000111));
	EXPECT_EQ(4,  cutil::popcnt((uint8_t)0b00001111));
	EXPECT_EQ(5,  cutil::popcnt((uint8_t)0b00011111));
	EXPECT_EQ(6,  cutil::popcnt((uint8_t)0b00111111));
	EXPECT_EQ(7,  cutil::popcnt((uint8_t)0b01111111));
	EXPECT_EQ(8,  cutil::popcnt((uint8_t)0b11111111));
	EXPECT_EQ(0,  cutil::popcnt((uint16_t)0b0000000000000000));
	EXPECT_EQ(1,  cutil::popcnt((uint16_t)0b0000000000000001));
	EXPECT_EQ(2,  cutil::popcnt((uint16_t)0b0000000000000011));
	EXPECT_EQ(3,  cutil::popcnt((uint16_t)0b0000000000000111));
	EXPECT_EQ(4,  cutil::popcnt((uint16_t)0b0000000000001111));
	EXPECT_EQ(5,  cutil::popcnt((uint16_t)0b0000000000011111));
	EXPECT_EQ(6,  cutil::popcnt((uint16_t)0b0000000000111111));
	EXPECT_EQ(7,  cutil::popcnt((uint16_t)0b0000000001111111));
	EXPECT_EQ(8,  cutil::popcnt((uint16_t)0b0000000011111111));
	EXPECT_EQ(9,  cutil::popcnt((uint16_t)0b0000000111111111));
	EXPECT_EQ(10, cutil::popcnt((uint16_t)0b1000001111011111));
	EXPECT_EQ(10, cutil::popcnt((uint16_t)0b0001011111011110));
	EXPECT_EQ(12, cutil::popcnt((uint16_t)0b0000111111111111));
	EXPECT_EQ(13, cutil::popcnt((uint16_t)0b0001111111111111));
	EXPECT_EQ(14, cutil::popcnt((uint16_t)0b0011111111111111));
	EXPECT_EQ(13, cutil::popcnt((uint16_t)0b0111111011111011));
	EXPECT_EQ(16, cutil::popcnt((uint16_t)0b1111111111111111));
	
	// byteswap
	EXPECT_EQ(0x12345678, cutil::byteswap((uint32_t)0x78563412));
	EXPECT_EQ(0x1234, cutil::byteswap((uint16_t)0x3412));
	EXPECT_EQ(0x78563412,cutil::byteswap((uint32_t)0x12345678));
	EXPECT_EQ(0x12345678ABCDEF01, cutil::byteswap((uint64_t)0x01EFCDAB78563412));
	
}

TEST(Math, range)
{
	EXPECT_EQ(100, CUTIL_MAX(100, 50));
	EXPECT_EQ(50, CUTIL_MIN(100, 50));
	EXPECT_EQ(100, CUTIL_MAX(50, 100));
	EXPECT_EQ(50, CUTIL_MIN(50, 100));
	
	EXPECT_EQ(100, CUTIL_ABS(100));
	EXPECT_EQ(100, CUTIL_ABS(-100));
	EXPECT_EQ(100, CUTIL_ABS(100.0));
	EXPECT_EQ(100, CUTIL_ABS(-100.0));
	
	EXPECT_EQ(15, cutil::clamp(15, 10, 20));
	EXPECT_EQ(17, cutil::clamp(15, 17, 20));
	EXPECT_EQ(13, cutil::clamp(15, 10, 13));
	EXPECT_EQ(15.0, cutil::clamp(15.0, 10.0, 20.0));
	EXPECT_EQ(17.0, cutil::clamp(15.0, 17.0, 20.0));
	EXPECT_EQ(13.0, cutil::clamp(15.0, 10.0, 13.0));
	static_assert(13.0 == cutil::clamp(15.0, 10.0, 13.0), "");
	EXPECT_EQ(15, cutil::clamp(15, 10, 20, std::less<int>()));
	EXPECT_EQ(17, cutil::clamp(15, 17, 20, std::less<int>()));
	EXPECT_EQ(13, cutil::clamp(15, 10, 13, std::less<int>()));
	EXPECT_EQ(15.0, cutil::clamp(15.0, 10.0, 20.0, std::less<double>()));
	EXPECT_EQ(17.0, cutil::clamp(15.0, 17.0, 20.0, std::less<double>()));
	EXPECT_EQ(13.0, cutil::clamp(15.0, 10.0, 13.0, std::less<double>()));
	static_assert(13.0 == cutil::clamp(15.0, 10.0, 13.0, std::less<double>()), "");
	EXPECT_EQ(15, CUTIL_CLAMP(15, 10, 20));
	EXPECT_EQ(17, CUTIL_CLAMP(15, 17, 20));
	EXPECT_EQ(13, CUTIL_CLAMP(15, 10, 13));
	EXPECT_EQ(15.0, CUTIL_CLAMP(15.0, 10.0, 20.0));
	EXPECT_EQ(17.0, CUTIL_CLAMP(15.0, 17.0, 20.0));
	EXPECT_EQ(13.0, CUTIL_CLAMP(15.0, 10.0, 13.0));
	
	{
		int a = 15;
		cutil::limit(a, 10, 20);
		EXPECT_EQ(15, a);
		a = 15;
		cutil::limit(a, 17, 20);
		EXPECT_EQ(17, a);
		a = 15;
		cutil::limit(a, 10, 13);
		EXPECT_EQ(13, a);
		a = 15;
		CUTIL_LIMIT(a, 10, 20);
		EXPECT_EQ(15, a);
		a = 15;
		CUTIL_LIMIT(a, 17, 20);
		EXPECT_EQ(17, a);
		a = 15;
		CUTIL_LIMIT(a, 10, 13);
		EXPECT_EQ(13, a);
	}
	
	EXPECT_EQ(true,  cutil::num_in_interval(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_interval(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_interval(15.0, 10.0, 13.0));
	EXPECT_EQ(true,  cutil::num_in_interval(10.0, 10.0, 20.0));
	EXPECT_EQ(true,  cutil::num_in_interval(20.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(15.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_INTERVAL(15.0, 17.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_INTERVAL(15.0, 10.0, 13.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(10.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_INTERVAL(20.0, 10.0, 20.0));
	
	EXPECT_EQ(true,  cutil::num_in_open_interval(15.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(15.0, 17.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(15.0, 10.0, 13.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(10.0, 10.0, 20.0));
	EXPECT_EQ(false, cutil::num_in_open_interval(20.0, 10.0, 20.0));
	EXPECT_EQ(true,  CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 17.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(15.0, 10.0, 13.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(10.0, 10.0, 20.0));
	EXPECT_EQ(false, CUTIL_NUM_IN_OPEN_INTERVAL(20.0, 10.0, 20.0));
	
#if CUTIL_CPP17_SUPPORTED
	double min = 10.0;
	double max = 20.0;
	EXPECT_EQ(true,  (cutil::num_in_interval<true, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<true, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, true>(10.0, min, max)));
	EXPECT_EQ(true,  (cutil::num_in_interval<false, true>(20.0, min, max)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, false>(10.0, 10.0, 20.0)));
	EXPECT_EQ(false, (cutil::num_in_interval<false, false>(20.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_interval<true, true>(10.0, 10.0, 20.0)));
	EXPECT_EQ(true,  (cutil::num_in_interval<true, true>(20.0, 10.0, 20.0)));
#endif
}


TEST(Math, increase)
{
	using numType_t = int16_t;
	using floatType_t = float;
	std::vector<numType_t> aNums;
	std::vector<floatType_t> aFloats;
	aNums.reserve(10);
	auto test = [&](numType_t initial, size_t times, std::function<void(numType_t&)> f){
		numType_t num = initial;
		aNums.clear();
		for(size_t i = 0; i < times; i++){
			f(num);
			aNums.push_back(num);
		}
	};
	auto testf = [&](numType_t initial, size_t times, std::function<void(floatType_t&)> f){
		floatType_t num = initial;
		aFloats.clear();
		for(size_t i = 0; i < times; i++){
			f(num);
			aFloats.push_back(num);
		}
	};
	
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 104, 104, 104, 104, 104, 104, 104, 104}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit_clamp(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 105, 105, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	test(100, 10, [](numType_t& num){cutil::increase_under_limit_clamp(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit(num, 105, 1);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit(num, 105);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit(num, 105, 2);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{102, 104, 104, 104, 104, 104, 104, 104, 104, 104}));
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit_clamp(num, 105, 2);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{102, 104, 105, 105, 105, 105, 105, 105, 105, 105}));
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit(num, 106, 2);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	testf(100, 10, [](floatType_t& num){cutil::increase_under_limit_clamp(num, 106, 2);});
	EXPECT_EQ(aFloats, (std::vector<floatType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT(num, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 102, 103, 104, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 104, 104, 104, 104, 104, 104, 104, 104}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT_CLAMP(num, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 105, 105, 105, 105, 105, 105, 105, 105}));
	test(100, 10, [](numType_t& num){CUTIL_INCREASE_UNDER_LIMIT_CLAMP(num, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{102, 104, 106, 106, 106, 106, 106, 106, 106, 106}));
	
	
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 101, 101, 101, 101, 101, 101, 101, 101}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit_clamp(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 100, 100, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	test(105, 10, [](numType_t& num){cutil::decrease_above_limit_clamp(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT(num, 100, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 103, 102, 101, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 101, 101, 101, 101, 101, 101, 101, 101}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT_CLAMP(num, 100, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 100, 100, 100, 100, 100, 100, 100, 100}));
	test(105, 10, [](numType_t& num){CUTIL_DECREASE_ABOVE_LIMIT_CLAMP(num, 99, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 101, 99, 99, 99, 99, 99, 99, 99, 99}));
	
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 104, 105, 100, 101, 102, 103, 104, 105, 100}));
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 100, 102, 104, 100, 102, 104, 100, 102, 104}));
	test(102, 10, [](numType_t& num){cutil::increase_rolling(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 106, 100, 102, 104, 106, 100, 102, 104, 106}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 105);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 100, 105, 104, 103, 102, 101, 100, 105, 104}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 105, 103, 101, 105, 103, 101, 105, 103, 101}));
	test(102, 10, [](numType_t& num){cutil::decrease_rolling(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 106, 104, 102, 100, 106, 104, 102, 100, 106}));
	
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{103, 104, 105, 100, 101, 102, 103, 104, 105, 100}));
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 100, 102, 104, 100, 102, 104, 100, 102, 104}));
	test(102, 10, [](numType_t& num){CUTIL_INCREASE_ROLLING(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{104, 106, 100, 102, 104, 106, 100, 102, 104, 106}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 105, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{101, 100, 105, 104, 103, 102, 101, 100, 105, 104}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 105, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 105, 103, 101, 105, 103, 101, 105, 103, 101}));
	test(102, 10, [](numType_t& num){CUTIL_DECREASE_ROLLING(num, 100, 106, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{100, 106, 104, 102, 100, 106, 104, 102, 100, 106}));
	
	
	test(32763, 6, [](numType_t& num){cutil::increase_no_overflow(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32765, 32766, 32767, 32767, 32767}));
	test(32762, 6, [](numType_t& num){cutil::increase_no_overflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32766, 32766, 32766, 32766, 32766}));
	test(32761, 6, [](numType_t& num){cutil::increase_no_overflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32763, 32765, 32767, 32767, 32767, 32767}));
	
	test(32763, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32765, 32766, 32767, 32767, 32767}));
	test(32762, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32764, 32766, 32766, 32766, 32766, 32766}));
	test(32761, 6, [](numType_t& num){CUTIL_INCREASE_NO_OVERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{32763, 32765, 32767, 32767, 32767, 32767}));
	
	
	test(-32763, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32765, -32766, -32767, -32768, -32768}));
	test(-32762, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32766, -32768, -32768, -32768, -32768}));
	test(-32761, 6, [](numType_t& num){cutil::decrease_no_underflow(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32763, -32765, -32767, -32767, -32767, -32767}));
	
	test(-32763, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 1);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32765, -32766, -32767, -32768, -32768}));
	test(-32762, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32764, -32766, -32768, -32768, -32768, -32768}));
	test(-32761, 6, [](numType_t& num){CUTIL_DECREASE_NO_UNDERFLOW(num, 2);});
	EXPECT_EQ(aNums, (std::vector<numType_t>{-32763, -32765, -32767, -32767, -32767, -32767}));
	
	
}
TEST(Math, inf_nan)
{
	EXPECT_EQ(false, cutil::isnan(0.0));
	EXPECT_EQ(false, cutil::isnan(1.0));
	EXPECT_EQ(false, cutil::isnan(-1.0));
	EXPECT_EQ(false, cutil::isnan(0.0f));
	EXPECT_EQ(false, cutil::isnan(1.0f));
	EXPECT_EQ(false, cutil::isnan(-1.0f));
	EXPECT_EQ(true, cutil::isnan(std::numeric_limits<double>::quiet_NaN()));
	EXPECT_EQ(true, cutil::isnan(std::numeric_limits<float>::quiet_NaN()));
	EXPECT_EQ(true, cutil::isnan(std::numeric_limits<double>::signaling_NaN()));
	EXPECT_EQ(true, cutil::isnan(std::numeric_limits<float>::signaling_NaN()));
	EXPECT_EQ(true, cutil::isinf(std::numeric_limits<double>::infinity()));
	EXPECT_EQ(true, cutil::isinf(std::numeric_limits<float>::infinity()));
	EXPECT_EQ(true, cutil::isinf(-std::numeric_limits<double>::infinity()));
	EXPECT_EQ(true, cutil::isinf(-std::numeric_limits<float>::infinity()));
	
}
TEST(Math, abs){
	constexpr auto abs1 = cutil::abs((int)-1);
	constexpr auto abs2 = cutil::abs((uint32_t)-1);
	constexpr auto abs3 = cutil::abs((int8_t)-1);
	constexpr auto abs4 = cutil::abs((uint8_t)-1);
	constexpr auto abs5 = cutil::abs((int64_t)-1);
	constexpr auto abs6 = cutil::abs((int16_t)-1);
	constexpr auto abs7 = cutil::abs((double)-1);
	constexpr auto abs8 = cutil::abs((float)-1);
	constexpr auto abs9 = cutil::abs((size_t)-1);
	constexpr auto abs10 = cutil::abs((double)1);
	constexpr auto abs11 = cutil::abs((int64_t)1);
	static_assert(abs1 == 1, "");
	static_assert(abs2 == 4294967295U, "");
	static_assert(abs3 == 1, "");
	static_assert(abs4 == 255U, "");
	static_assert(abs5 == 1, "");
	static_assert(abs6 == 1, "");
	static_assert(abs7 == 1.0, "");
	static_assert(abs8 == 1.0f, "");
	static_assert(abs9 == 18446744073709551615ul, "");
	static_assert(abs10 == 1.0, "");
	static_assert(abs11 == 1, "");
	EXPECT_EQ(abs1, 1);
	EXPECT_EQ(abs2, 4294967295U);
	EXPECT_EQ(abs3, 1);
	EXPECT_EQ(abs4, 255U);
	EXPECT_EQ(abs5, 1);
	EXPECT_EQ(abs6, 1);
	EXPECT_EQ(abs7, 1.0);
	EXPECT_EQ(abs8, 1.0f);
	EXPECT_EQ(abs9, 18446744073709551615ul);
	EXPECT_EQ(abs10, 1.0);
	EXPECT_EQ(abs11, 1);
}
TEST(Math, lerp){
	EXPECT_EQ(true, (cutil::fequal_ulp(15.0, cutil::math::lerp(10, 20, 0.5))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(17.5, cutil::math::lerp(10, 20, 0.75))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(12.5, cutil::math::lerp(10, 20, 0.25))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(10.0, cutil::math::lerp(10, 20, 0.0))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(20.0, cutil::math::lerp(10, 20, 1.0))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(20.0, cutil::math::lerp(10, 20, 1.0))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(5.0, cutil::math::lerp(10, 20, -0.5))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(25.0, cutil::math::lerp(10, 20, 1.5))) );
	EXPECT_EQ(true, (cutil::fequal_ulp(10.0, cutil::math::lerp(10, 10, 0.5))) );
	// static_assert(true == cutil::fequal_ulp(10.0, cutil::math::lerp(10, 10, 0.5)), "");
	
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(15.0, CUTIL_LERP(10, 20 ,0.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(17.5, CUTIL_LERP(10, 20 ,0.75), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(12.5, CUTIL_LERP(10, 20 ,0.25), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(10.0, CUTIL_LERP(10, 20 ,0.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(20.0, CUTIL_LERP(10, 20 ,1.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(20.0, CUTIL_LERP(10, 20 ,1.0), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(5.0, CUTIL_LERP(10, 20 ,-0.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(25.0, CUTIL_LERP(10, 20 ,1.5), 1e-14)));
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(10.0, CUTIL_LERP(10, 10 ,0.5), 1e-14)));
	
#ifdef CUTIL_CPP20_SUPPORTED
	EXPECT_EQ(true, (cutil::fequal_eps(15.0, std::lerp(10, 20, 0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(17.5, std::lerp(10, 20, 0.75), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(12.5, std::lerp(10, 20, 0.25), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(10.0, std::lerp(10, 20, 0.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(20.0, std::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(20.0, std::lerp(10, 20, 1.0), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(5.0, std::lerp(10, 20, -0.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(25.0, std::lerp(10, 20, 1.5), 1e-14)) );
	EXPECT_EQ(true, (cutil::fequal_eps(10.0, std::lerp(10, 10, 0.5), 1e-14)) );
#endif
}
TEST(Math, floatingNumbers){

	
	EXPECT_EQ(true,  cutil::fequal_eps(0.00001, 0.00002, 0.0001));
	EXPECT_EQ(false, cutil::fequal_eps(0.00001, 0.00002, 0.0000001));
	EXPECT_EQ(true,  cutil::fequal_eps(0.0000000000001f, 0.0000000000002f));
	EXPECT_EQ(false, cutil::fequal_eps(0.0000000000001, 0.0000000000002));
	EXPECT_EQ(false, cutil::fequal_eps(cutil::Numbers<double>::nan, 0.0));
	EXPECT_EQ(false, cutil::fequal_eps(cutil::Numbers<double>::nan, cutil::Numbers<double>::nan));
	EXPECT_EQ(false, cutil::fequal_eps(cutil::Numbers<double>::inf, 0.0));
	EXPECT_EQ(false, cutil::fequal_eps(cutil::Numbers<double>::neg_inf, 0.0));
	EXPECT_EQ(false, cutil::fequal_eps(cutil::Numbers<double>::neg_inf, cutil::Numbers<double>::inf));
	EXPECT_EQ(true, cutil::fequal_eps(cutil::Numbers<double>::neg_inf, cutil::Numbers<double>::neg_inf));
	
	
	double a = cutil::deg2rad(32.0);
	double b = std::asin(std::acos(std::atan(std::tan(std::cos(std::sin(a))))));
	EXPECT_EQ(false, a == b);
	EXPECT_EQ(true, cutil::fequal_eps(a, b));
	EXPECT_EQ(true, cutil::fequal_ulp(a, b, 3));
	
	a *= 1e20;
	b *= 1e20;
	EXPECT_EQ(false, a == b);
	EXPECT_EQ(false, cutil::fequal_eps(a, b));
	EXPECT_EQ(true, cutil::fequal_ulp(a, b, 3));
	
	a *= -1;
	EXPECT_EQ(false, cutil::fequal_ulp(a, b, 3));
	
	EXPECT_EQ(false, cutil::fequal_ulp(1.0, 2.0, 3));
	EXPECT_EQ(false, cutil::fequal_ulp(0.0001, 0.0002, 3));
	EXPECT_EQ(false, cutil::fequal_ulp(0.0001L, 0.0002L, 3));
	
	EXPECT_EQ(true, cutil::fequal_zero(0.000000001f));
	EXPECT_EQ(false, cutil::fequal_zero(0.001f));
	
	EXPECT_EQ(true, CUTIL_EQUAL_EPS(0.00001, 0.00002, 0.0001));
	EXPECT_EQ(false, CUTIL_EQUAL_EPS(0.00001, 0.00002, 0.0000001));
	EXPECT_EQ(true, CUTIL_EQUAL_EPS_F(0.0000000000001, 0.0000000000002));
	EXPECT_EQ(false, CUTIL_EQUAL_EPS_D(0.0000000000001, 0.0000000000002));
	
	EXPECT_EQ(true, (cutil::fequal_eps(cutil::numbers::pi_third, cutil::math::deg2rad(60.0))));
	EXPECT_EQ(false, (cutil::numbers::pi_third == cutil::math::deg2rad(60.0)));
	static_assert(true == cutil::fequal_eps(cutil::numbers::pi_third, cutil::math::deg2rad(60.0)), "");

	EXPECT_EQ(true, (cutil::fequal_eps(60.0, cutil::math::rad2deg(cutil::numbers::pi_third), 1e-14)));
	EXPECT_EQ(false, (60.0 == cutil::math::rad2deg(cutil::Numbers<double>::pi_third)));
	static_assert(true == cutil::fequal_eps(60.0, cutil::math::rad2deg(cutil::numbers::pi_third), 1e-14), "");
	
	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(CUTIL_PI_THIRD, CUTIL_DEG_TO_RAD(60.0), 1e-14)));
	EXPECT_EQ(false, (CUTIL_PI_THIRD == CUTIL_DEG_TO_RAD(60.0)));

	EXPECT_EQ(true, (CUTIL_EQUAL_EPS(60.0, CUTIL_RAD_TO_DEG(CUTIL_PI_THIRD), 1e-14)));
	EXPECT_EQ(false, (60.0 == CUTIL_RAD_TO_DEG(CUTIL_PI_THIRD)));
	


}
TEST(Math, IntegerCompare){
	static_assert(cutil::cmp_less(-1, 1U), "");
	EXPECT_EQ(true, cutil::cmp_less(-1, 1U));
	static_assert(cutil::cmp_less(1, 2), "");
	EXPECT_EQ(true, cutil::cmp_less_equal(-1, 1u));
	EXPECT_EQ(false, cutil::cmp_greater(-1, 1u));
	EXPECT_EQ(false, cutil::cmp_greater_equal(-1, 1u));
	
	EXPECT_EQ(true, cutil::cmp_not_equal(-1, 0xFFFFFFFFu));
	
}
TEST(Math, midpoint){
	EXPECT_EQ(cutil::math::midpoint(6.0, 9.0), 7.5);
	EXPECT_EQ(cutil::math::midpoint(6, 9), 7);
	EXPECT_EQ(cutil::math::midpoint(6, 10), 8);
	EXPECT_EQ(CUTIL_MIDPOINT(6, 9), 7);
	static_assert(cutil::math::midpoint(6, 9) == 7, "");
	
	std::array<int, 10> arr;
	std::iota(arr.begin(), arr.end(), 0);
	int* p2 = &arr[2];
	int* p4 = &arr[4];
	int* p5 = &arr[5];
	int* p6 = &arr[6];
	EXPECT_EQ(cutil::math::midpoint(p2, p5), &arr[3]);
	EXPECT_EQ(cutil::math::midpoint(p2, p6), p4);
}
TEST(Math, others)
{


	EXPECT_EQ(2, (cutil::math::gcd(6, 10)) );
	EXPECT_EQ(2, (cutil::math::gcd(10, 6)) );
	EXPECT_EQ(2, (cutil::math::gcd(6, -10)) );
	EXPECT_EQ(2, (cutil::math::gcd(-6, -10)) );
	EXPECT_EQ(2, (cutil::math::gcd(-6, 10)) );
	EXPECT_EQ(24, (cutil::math::gcd(0, 24)) );
	EXPECT_EQ(24, (cutil::math::gcd(0, -24)) );
	EXPECT_EQ(2, (cutil::math::gcd(6u, 10u)) );

	static_assert(cutil::math::lcm(6, 10) == 30, "");
	static_assert(cutil::math::gcd(-6, 10) == 2, "");
	EXPECT_EQ(cutil::math::lcm(6, 10), 30);
	EXPECT_EQ(cutil::math::lcm(10, 6), 30);
	EXPECT_EQ(cutil::math::lcm(6, -10), 30);
	EXPECT_EQ(cutil::math::lcm(-6, -10), 30);
	EXPECT_EQ(cutil::math::lcm(-6, 10), 30);
	
	


	// constexpr auto zzzz = cutil::pow<30>(2lu);
	EXPECT_EQ(cutil::math::pow(2, 0), 1);
	EXPECT_EQ(cutil::math::pow(2, 1), 2);
	EXPECT_EQ(cutil::math::pow(2, 2), 4);
	EXPECT_EQ(cutil::math::pow(2, 3), 8);
	EXPECT_EQ(cutil::math::pow(2, 4), 16);
	EXPECT_EQ(cutil::math::pow(3, 1), 3);
	EXPECT_EQ(cutil::math::pow(3, 2), 9);
	EXPECT_EQ(cutil::math::pow(3, 3), 27);
	EXPECT_EQ(cutil::math::pow<1>(3), 3);
	EXPECT_EQ(cutil::math::pow<2>(3), 9);
	EXPECT_EQ(cutil::math::pow<3>(3), 27);
	EXPECT_EQ(cutil::math::fequal_eps(cutil::math::pow<1>(33.3), 33.3), true);
	EXPECT_EQ(cutil::math::fequal_eps(cutil::math::pow<2>(33.3), 33.3*33.3), true);
	EXPECT_EQ(cutil::math::fequal_eps(cutil::math::pow<3>(33.3), 33.3*33.3*33.3), true);
	EXPECT_EQ(cutil::math::pow(-2.5, 1), -2.5);
	EXPECT_EQ(cutil::math::pow(-2.5, 2), 6.25);
	
	EXPECT_EQ(cutil::math::pow(0, 0), 1);
	EXPECT_EQ(cutil::math::pow(0, 1), 0);
	EXPECT_EQ(cutil::math::pow(0, 2), 0);
	EXPECT_EQ(cutil::math::pow<0>(0), 1);
	EXPECT_EQ(cutil::math::pow<1>(0), 0);
	EXPECT_EQ(cutil::math::pow<2>(0), 0);
	
	static_assert(cutil::math::pow(3, 2) == 9, "");
	static_assert(cutil::math::pow<2>(3) == 9, "");
	static_assert(cutil::math::pow<2>(-2.5) == 6.25, "");
	static_assert(cutil::math::factorial(3) == 6, "");
	
	uint64_t z = 2;
	EXPECT_EQ(cutil::math::pow(z++, 2), 4);
	EXPECT_EQ(cutil::math::pow(z++, 2), 9);
	EXPECT_EQ(cutil::math::pow(z++, 2), 16);
	z = 2;
	EXPECT_EQ(cutil::math::pow<2>(z++), 4);
	EXPECT_EQ(cutil::math::pow<2>(z++), 9);
	EXPECT_EQ(cutil::math::pow<2>(z++), 16);
	
	EXPECT_EQ(cutil::math::factorial(1), 1);
	EXPECT_EQ(cutil::math::factorial(2), 2);
	EXPECT_EQ(cutil::math::factorial(3), 6);
	EXPECT_EQ(cutil::math::factorial(4), 24);
	EXPECT_EQ(cutil::math::factorial(5), 120);
	EXPECT_EQ(cutil::math::factorial<1>(), 1);
	EXPECT_EQ(cutil::math::factorial<2>(), 2);
	EXPECT_EQ(cutil::math::factorial<3>(), 6);
	EXPECT_EQ(cutil::math::factorial<4>(), 24);
	EXPECT_EQ(cutil::math::factorial<5>(), 120);
	
	
	EXPECT_EQ(cutil::math::get_digit<0>(1234), 4);
	EXPECT_EQ(cutil::math::get_digit<1>(1234), 3);
	EXPECT_EQ(cutil::math::get_digit<2>(1234), 2);
	EXPECT_EQ(cutil::math::get_digit<3>(1234), 1);
	EXPECT_EQ(cutil::math::get_digit<4>(1234), 0);
	EXPECT_EQ(cutil::math::get_digit<5>(1234), 0);
	
	EXPECT_EQ(cutil::math::get_digit(1234, 0), 4);
	EXPECT_EQ(cutil::math::get_digit(1234, 1), 3);
	EXPECT_EQ(cutil::math::get_digit(1234, 2), 2);
	EXPECT_EQ(cutil::math::get_digit(1234, 3), 1);
	EXPECT_EQ(cutil::math::get_digit(1234, 4), 0);
	EXPECT_EQ(cutil::math::get_digit(1234, 5), 0);
	
	EXPECT_EQ(cutil::math::get_digit< -6>(1234.5678), 0);
	EXPECT_EQ(cutil::math::get_digit< -5>(1234.5678), 0);
	EXPECT_EQ(cutil::math::get_digit< -4>(1234.5678), 8);
	EXPECT_EQ(cutil::math::get_digit< -3>(1234.5678), 7);
	EXPECT_EQ(cutil::math::get_digit< -2>(1234.5678), 6);
	EXPECT_EQ(cutil::math::get_digit< -1>(1234.5678), 5);
	EXPECT_EQ(cutil::math::get_digit<0>(1234.5678), 4);
	EXPECT_EQ(cutil::math::get_digit<1>(1234.5678), 3);
	EXPECT_EQ(cutil::math::get_digit<2>(1234.5678), 2);
	EXPECT_EQ(cutil::math::get_digit<3>(1234.5678), 1);
	EXPECT_EQ(cutil::math::get_digit<4>(1234.5678), 0);
	EXPECT_EQ(cutil::math::get_digit<5>(1234.5678), 0);
	
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -6), 0);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -5), 0);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -4), 8);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -3), 7);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -2), 6);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, -1), 5);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 0), 4);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 1), 3);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 2), 2);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 3), 1);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 4), 0);
	EXPECT_EQ(cutil::math::get_digit(1234.5678, 5), 0);
	
	
	
	
}

TEST(Memory, Basic)
{
	uint16_t num = 0x1234;
	EXPECT_EQ(0x34, cutil::get_word_low(num));
	EXPECT_EQ(0x12, cutil::get_word_high(num));
	
	EXPECT_EQ(0x1234, cutil::read_memory<uint16_t>(&num));
	cutil::write_memory(&num, (uint16_t)0x5678);
	EXPECT_EQ(0x5678, num);
	
}
TEST(Memory, Bitwise)
{
	uint32_t i = 0x12345678;
	std::array<float, 15> f;
	std::fill(f.begin(), f.end(), 0.0f);
	cutil::bitwise_memcpy(f[0], i);
	cutil::bitwise_memcpy(f[1], 0x12345678);
	CUTIL_BITWISE_MEMCPY(&f[2], &i);
	CUTIL_BITWISE_ASSIGN(f[3], i);
	f[4] = CUTIL_BITWISE_CAST(float, i);
	f[5] = cutil::bit_cast<float>(i);
	f[6] = cutil::bit_cast<float>(0x40490FDB);
	EXPECT_EQ(cutil::fequal_eps(f[6], 3.1415927f), true);
	
	
	
#ifdef CUTIL_CPP20_SUPPORTED
	f[13] = std::bit_cast<float>(i);
	f[14] = std::bit_cast<float>(0x12345678);
	constexpr float f5 = cutil::bit_cast<float>(0x12345678);
	EXPECT_EQ(f5, f[5]);
#endif

	EXPECT_EQ(f[0], f[1]);
	EXPECT_EQ(f[0], f[2]);
	EXPECT_EQ(f[0], f[3]);
	EXPECT_EQ(f[0], f[4]);
	EXPECT_EQ(f[0], f[5]);
	
#ifdef CUTIL_CPP20_SUPPORTED
	EXPECT_EQ(f[0], f[13]);
	EXPECT_EQ(f[0], f[14]);
#endif
}



TEST(Memory, Field)
{
	struct MyStruct {
		uint8_t 	a;	// 0    (+0)
		uint8_t 	b;	// 1      |--(+1)
		uint32_t 	c;	// 4    (+4)
		uint8_t 	d;	// 8    (+4)
		uint8_t 	e;	// 9      |--(+1)
		uint8_t 	f;	// 10     |--(+1)
		uint64_t 	g;	// 16   (+8)
		uint32_t 	h;	// 24   (+8)
	};
	int a;
	int b;
	int* c;
	int* d;
	auto zzz = &a - &b;
	
	EXPECT_EQ(0, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, a));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, b));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, c));
	EXPECT_EQ(8, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, d));
	EXPECT_EQ(9, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, e));
	EXPECT_EQ(10, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, f));
	EXPECT_EQ(16, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, g));
	EXPECT_EQ(24, CUTIL_STRUCT_FIELD_OFFSET(MyStruct, h));
	
	EXPECT_EQ(0, cutil::get_member_offset(&MyStruct::a));
	EXPECT_EQ(1, cutil::get_member_offset(&MyStruct::b));
	EXPECT_EQ(4, cutil::get_member_offset(&MyStruct::c));
	EXPECT_EQ(8, cutil::get_member_offset(&MyStruct::d));
	EXPECT_EQ(9, cutil::get_member_offset(&MyStruct::e));
	EXPECT_EQ(10, cutil::get_member_offset(&MyStruct::f));
	EXPECT_EQ(16, cutil::get_member_offset(&MyStruct::g));
	EXPECT_EQ(24, cutil::get_member_offset(&MyStruct::h));
	
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, a));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, b));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_SIZE(MyStruct, c));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, d));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, e));
	EXPECT_EQ(1, CUTIL_STRUCT_FIELD_SIZE(MyStruct, f));
	EXPECT_EQ(8, CUTIL_STRUCT_FIELD_SIZE(MyStruct, g));
	EXPECT_EQ(4, CUTIL_STRUCT_FIELD_SIZE(MyStruct, h));
	
	
	
	MyStruct s;
	EXPECT_EQ(8, CUTIL_PTR_OFFSET(&s.h, &s.g));
	EXPECT_EQ(8, cutil::get_ptr_offset(&s.h, &s.g));
	EXPECT_EQ(&s, CUTIL_STRUCT_FIELD_CONTAINER(MyStruct, b, &s.b));
	
}
TEST(Span, Span)
{
	std::vector<uint32_t> v(10);
	std::iota(v.begin(), v.end(), 0);
	
	cutil::span<uint32_t> s(v);
	EXPECT_EQ(10, s.size());
	EXPECT_EQ(0, s[0]);
	EXPECT_EQ(9, s[9]);
	EXPECT_EQ(0, s.front());
	EXPECT_EQ(9, s.back());
	
}
TEST(Others, Others)
{
	int* p = new int[10];
	int* q = new int(13);
	int* r = cutil::malloc_type<int>(15);
	int modified = 10;
	int modified1 = 20;
	
	auto release2 = cutil::make_scope_guard([&](){
		EXPECT_EQ(11, modified);
		EXPECT_EQ(20, modified1);
	}); // execute finally
	
	auto release3 = cutil::make_scope_guard([&](){
		modified1 = 21;
	});
	release3.dismiss(); // dismissed, not be executed
	
	auto release = cutil::make_scope_guard([&](){
		cutil::free_ptr(r);
    	cutil::delete_array(p);
		cutil::delete_ptr(q);
		modified = 11;
	}); // execute first

}
TEST(Type, Cast)
{
	class Base {
	public:
		virtual ~Base() = default;
		virtual std::string f() const {return "Base";}
		std::string g() const {return "Base";}
	};
	class A : public Base {
	public:
		std::string f() const override {return "A";}
		std::string g() const {return "A";}
	};
	class B : public Base {
	public:
		std::string f() const override {return "B";}
		std::string g() const {return "B";}
	};
	
	std::unique_ptr<Base> a = std::make_unique<A>();
	std::unique_ptr<Base> b = std::make_unique<B>();
	auto a1 = cutil::safe_cast<A*>(a.get());
	auto b1 = cutil::safe_cast<const B*>(const_cast<const Base*>(b.get()));
	// auto b2 = cutil::safe_cast<A*>(b.get());	// assert failed!
	// auto b4 = cutil::safe_cast<B*>(const_cast<const Base*>(b.get())); // ERROR
	// auto b5 = cutil::safe_cast<const B*>(const_cast<const Base*>(b.get())); // ERROR
	
	
	EXPECT_EQ("A", a->f());
	EXPECT_EQ("B", b->f());
	EXPECT_EQ("A", a1->f());
	EXPECT_EQ("B", b1->f());
	EXPECT_EQ("Base", a->g());
	EXPECT_EQ("Base", b->g());
	EXPECT_EQ("A", a1->g());
	EXPECT_EQ("B", b1->g());
	
	EXPECT_EQ(true,  (cutil::internal::is_pointer_both_same_attributes<const B*, const B*>::value));
	EXPECT_EQ(true,  (cutil::internal::is_pointer_both_same_attributes<B*, B*>::value));
	EXPECT_EQ(false, (cutil::internal::is_pointer_both_same_attributes<const B*, B*>::value));
	EXPECT_EQ(false, (cutil::internal::is_pointer_both_same_attributes<B*, const B*>::value));
	EXPECT_EQ(true,  (cutil::internal::is_pointer_both_same_attributes<volatile B*, volatile B*>::value));
	EXPECT_EQ(false, (cutil::internal::is_pointer_both_same_attributes<volatile B*, B*>::value));
	
#ifdef CUTIL_CPP17_SUPPORTED
	auto f1 = [](){};
	auto f2 = [](int i){};
	static_assert(std::is_invocable_v<decltype(f1)>);
	static_assert(std::is_invocable_v<decltype(f2), int>);
	static_assert(! std::is_invocable_v<decltype(f2)>);
#endif
}

TEST(Enum, Enum)
{
	enum class MyEnum : uint8_t {
		Zero = 0,
		Bit0 = 1 << 0,
		Bit1 = 1 << 1,
		Bit2 = 1 << 2,
		Bit3 = 1 << 3,
		Bit4 = 1 << 4,
		Bit5 = 1 << 5,
		Bit6 = 1 << 6,
		Bit7 = 1 << 7,
		All = Bit0 | Bit1 | Bit2 | Bit3 | Bit4 | Bit5 | Bit6 | Bit7
	};
	auto num = cutil::enum_int(MyEnum::Bit2);
	static_assert(std::is_same<decltype(num), uint8_t>::value, "");
	EXPECT_EQ(0x04, num);
	
	using namespace cutil::enum_bitwise;
	MyEnum test1 = MyEnum::Bit0 | MyEnum::Bit1;
	EXPECT_EQ(test1, static_cast<MyEnum>(0b0000'0011));
	
	MyEnum test2 = MyEnum::Bit7 | MyEnum::Bit3 | MyEnum::Bit4;
	EXPECT_EQ(test2, static_cast<MyEnum>(0b1001'1000));
	
	MyEnum test3 = MyEnum::Bit2 & MyEnum::Bit3;
	EXPECT_EQ(test3, MyEnum::Zero);
	
	MyEnum test4 = test2 & MyEnum::Bit3;
	EXPECT_EQ(test4, MyEnum::Bit3);
	
	MyEnum test5 = ~MyEnum::Bit5;
	EXPECT_EQ(test5, static_cast<MyEnum>(0b1101'1111));
	
	MyEnum test6 = test2 ^ test4;
	EXPECT_EQ(test6, static_cast<MyEnum>(0b1001'0000));
	
	test6 |= MyEnum::Bit0;
	EXPECT_EQ(test6, static_cast<MyEnum>(0b1001'0001));
	
	test6 &= MyEnum::Bit0;
	EXPECT_EQ(test6, MyEnum::Bit0);
	
	test6 &= MyEnum::Bit1;
	EXPECT_EQ(test6, MyEnum::Zero);
	
	test1 ^= MyEnum::Bit0;
	EXPECT_EQ(test1, MyEnum::Bit1);
}

TEST(Convert, Overload)
{
	class ConvertTestClass{
	public:
		int func() 						{return 0;}
		int func(int i) 				{return 1;}
		int func(double i)				{return 2;}
		int func(int i, double d) 		{return 3;}
		int func() 						const {return 4;} 	// with const/non-const overload
		int func(int i) 				const {return 5;}
		int func(double i) 				const {return 6;}
		int func(int i, double d) 		const {return 7;}
		static int static_func() 				{return 8;} // non-member function
		static int static_func(int i) 			{return 9;}
		static int static_func(double i) 		{return 10;}
		static int static_func(int i, double d) {return 11;}
		int func2() 					{return 12;} 		// without const/non-const overload
		int func2(int i) 				{return 13;}
		int func2(double i) 			{return 14;}
		int func2(int i, double d) 		{return 15;}
	};
	// using namespace cutil::internal;
	ConvertTestClass c;
	const ConvertTestClass cc;

	EXPECT_EQ(8, cutil::overload<>(&ConvertTestClass::static_func)());
	EXPECT_EQ(9, cutil::overload<int>(&ConvertTestClass::static_func)(1));
	EXPECT_EQ(10, cutil::overload<double>(&ConvertTestClass::static_func)(1.0));
	EXPECT_EQ(11, (cutil::overload<int, double>(&ConvertTestClass::static_func)(1, 1.0)));
	
	EXPECT_EQ(0, (c.*cutil::non_const_overload<>(&ConvertTestClass::func))());
	EXPECT_EQ(1, (c.*cutil::non_const_overload<int>(&ConvertTestClass::func))(1));
	EXPECT_EQ(2, (c.*cutil::non_const_overload<double>(&ConvertTestClass::func))(1.0));
	EXPECT_EQ(3, (c.*cutil::non_const_overload<int, double>(&ConvertTestClass::func))(1, 1.0));
	
	EXPECT_EQ(4, (cc.*cutil::const_overload<>(&ConvertTestClass::func))());
	EXPECT_EQ(5, (cc.*cutil::const_overload<int>(&ConvertTestClass::func))(1));
	EXPECT_EQ(6, (cc.*cutil::const_overload<double>(&ConvertTestClass::func))(1.0));
	EXPECT_EQ(7, (cc.*cutil::const_overload<int, double>(&ConvertTestClass::func))(1, 1.0));
	
	EXPECT_EQ(12, (c.*cutil::overload<>(&ConvertTestClass::func2))());
	EXPECT_EQ(13, (c.*cutil::overload<int>(&ConvertTestClass::func2))(1));
	EXPECT_EQ(14, (c.*cutil::overload<double>(&ConvertTestClass::func2))(1.0));
	EXPECT_EQ(15, (c.*cutil::overload<int, double>(&ConvertTestClass::func2))(1, 1.0));
	
}
