/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		10 JUN 2025
  License:		MIT License
* You can include this header in header files.
* C++14 or later is required.
*/
#ifndef CUTIL_CPP_UTILS_H__
#define CUTIL_CPP_UTILS_H__
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

//=================== Comparison Statements =======================
inline namespace compare {
template<typename T> inline constexpr bool equal_any(T&& compared) noexcept {
	return false; // end of recursion
}
template<typename T> inline constexpr bool equal_all(T&& compared) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool unequal_any(T&& compared) noexcept {
	return false; // end of recursion
}
template<typename T> inline constexpr bool unequal_all(T&& compared) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool unequal_mutually(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool equal_mutually(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool increasing(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool increasing_equal(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool decreasing(T&& a1) noexcept {
	return true; // end of recursion
}
template<typename T> inline constexpr bool decreasing_equal(T&& a1) noexcept {
	return true; // end of recursion
}

//* bool statement: `(compared == arg1 || compared == arg2 || compared == arg3 || ...)`
//  if 1st param `compared` is equal to ANY of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_any(T&& compared, U&& a1, E&&... a) noexcept {
	return (std::forward<T>(compared) == std::forward<U>(a1))
			|| cutil::compare::equal_any(std::forward<T>(compared), std::forward<E>(a)...);
}

//* bool statement: `(compared == arg1 && compared == arg2 && compared == arg3 && ...)`
//  if 1st param `compared` is equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_all(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) == std::forward<U>(a1))
			&& cutil::compare::equal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 || compared != arg2 || compared != arg3 || ...)`
//  if 1st param `compared` is NOT equal to ANY of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_any(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			|| cutil::compare::unequal_any(std::forward<T>(compared), std::forward<E>(a)...));
}

//* bool statement: `(compared != arg1 && compared != arg2 && compared != arg3 && ...)`
//  if 1st param `compared` is NOT equal to ALL of the following arguments, return `true`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_all(T&& compared, U&& a1, E&&... a) noexcept {
	return ((std::forward<T>(compared) != std::forward<U>(a1))
			&& cutil::compare::unequal_all(std::forward<T>(compared), std::forward<E>(a)...));
}

//* check if all of the variables are mutually nonequal, not recommended for large amount of arguments
// if you want to compare more arguments, pls use `std::set` or `std::unordered_set` (hashset)
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, !=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool unequal_mutually(T&& a1, U&& a2, E&&... a) noexcept {
	return (cutil::unequal_all(std::forward<T>(a1), std::forward<U>(a2), std::forward<E>(a)...)
			&& cutil::compare::unequal_mutually(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually equal `(a1 == a2 && a2 == a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, ==)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool equal_mutually(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) == std::forward<U>(a2))
			&& cutil::compare::equal_mutually(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually increasing, `(a1 < a2 && a2 < a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, <)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool increasing(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) < std::forward<U>(a2))
			&& cutil::compare::increasing(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually increasing or equal, `(a1 <= a2 && a2 <= a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, <=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool increasing_equal(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) <= std::forward<U>(a2))
			&& cutil::compare::increasing_equal(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually decreasing, `(a1 > a2 && a2 > a3 && ...)`
template<typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, >)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool decreasing(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) > std::forward<U>(a2))
			&& cutil::compare::decreasing(std::forward<T>(a2), std::forward<E>(a)...));
}

//* check if all of the variables are mutually decreasing or equal, `(a1 >= a2 && a2 >= a3 && ...)`
template <typename T, typename U, typename... E, _CUTIL_CONCEPT_COMPARABLE(T, U, >=)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline constexpr bool decreasing_equal(T&& a1, U&& a2, E&&... a) noexcept {
	return ((std::forward<T>(a1) >= std::forward<U>(a2))
			&& cutil::compare::decreasing_equal(std::forward<T>(a2), std::forward<E>(a)...));
}

/* Instruction:
	int var = 10;
	if(cutil::equal_any(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 || var == 4 || var == 6 || var == 8 || var == 10)`
		// equivalent to `if(!CUTIL_UNEQUAL_ALL(var, 2, 4, 6, 8, 10))`
	}
	if(cutil::equal_all(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var == 2 && var == 4 && var == 6 && var == 8 && var == 10)`
		// equivalent to `if(cutil::equal_mutually(var, 2, 4, 6, 8, 10))`
		// equivalent to `if(!cutil::unequal_any(var, 2, 4, 6, 8, 10))`
	}
	
	//*-------------------------------------------
	if(cutil::unequal_all(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 && var != 4 && var != 6 && var != 8 && var != 10)`
		// equivalent to `if(! cutil::equal_any(var, 2, 4, 6, 8, 10))`
	}
	if(cutil::unequal_any(var, 2, 4, 6, 8, 10)){
		// equivalent to `if(var != 2 || var != 4 || var != 6 || var != 8 || var != 10)`
		// equivalent to `if(! cutil::equal_all(var, 2, 4, 6, 8, 10))`
	}
	
	//*----------------------------------------------
	if(cutil::unequal_mutually(a1, a2, a3, a4);){ // is `a1`, `a2`, `a3`, `a4` mutually different?
		// (  ((a1) != (a2) && (a1) != (a3) && (a1) != (a4))
		// && ((a2) != (a3) && (a2) != (a4))
		// && ((a3) != (a4))   )
	}
	
	if(cutil::equal_mutually(a1, a2, a3, a4, a5)){
		// ((a1) == (a2) && (a1) == (a3) && (a1) == (a4) && (a1) == (a5))
		// equivalent to `if(cutil::equal_all(a1, a2, a3, a4, a5))`
	}
	
	//*--------------------------------------
	bool b1 = cutil::increasing(1, 2, 3, 4, 5); // true
	bool b2 = cutil::increasing(1, 2, 3, 3, 5); // false
	bool b3 = cutil::decreasing(5, 4, 3, 2, 1); // true
	bool b4 = cutil::decreasing(5, 4, 3, 3, 1); // false
	bool b5 = cutil::increasing_equal(1, 2, 3, 3, 5); // true
	bool b6 = cutil::decreasing_equal(5, 4, 3, 3, 1); // true
*/
} // namespace compare



//======================== Enum Utils =========================
inline namespace enum_utils {
	
	//* convert enum to its underlying integer type
	template<typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr auto enum_int(T e) noexcept {
		return static_cast<std::underlying_type_t<T>>(e);
	}
} // namespace enum_utils


namespace enum_bitwise { // not inline namespace, must use it explicitly
	
	//* bitwise operators for enum types
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T operator~(T e) noexcept {
		return static_cast<T>(~enum_int(e));
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T operator|(T e1, T e2) noexcept {
		return static_cast<T>(enum_int(e1) | enum_int(e2));
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T operator&(T e1, T e2) noexcept {
		return static_cast<T>(enum_int(e1) & enum_int(e2));
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T operator^(T e1, T e2) noexcept {
		return static_cast<T>(enum_int(e1) ^ enum_int(e2));
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_FUNC_STATIC
	inline constexpr T& operator|=(T& e1, T e2) noexcept {
		return e1 = static_cast<T>(enum_int(e1) | enum_int(e2));;
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_FUNC_STATIC
	inline constexpr T& operator&=(T& e1, T e2) noexcept {
		return e1 = static_cast<T>(enum_int(e1) & enum_int(e2));
	}
	template <typename T, _CUTIL_CONCEPT_IS_ENUM(T)> _CUTIL_FUNC_STATIC
	inline constexpr T& operator^=(T& e1, T e2) noexcept {
		return e1 = static_cast<T>(enum_int(e1) ^ enum_int(e2));
	}
} // namespace enum_bitwise

/*
	Example:
	enum class MyEnum : uint8_t {
		None = 0,
		Flag1 = 1 << 0, // 0b00000001
		Flag2 = 1 << 1, // 0b00000010
		Flag3 = 1 << 2, // 0b00000100
		Flag4 = 1 << 3, // 0b00001000
	};
	
	// convert enum to its underlying integer type
	auto value = cutil::enum_int(MyEnum::Flag1); // uint8_t, 0b00000011
	
	// bitwise operators for enum types
	//  by default, `enum class` is not compatible with bitwise operators, not like `enum`
	using namespace cutil::enum_bitwise; // you must include this namespace to use bitwise operators
	auto flag = MyEnum::Flag1 | MyEnum::Flag2;
	auto flag2 = MyEnum::Flag1 & MyEnum::Flag2;
	auto flag3 = MyEnum::Flag1 ^ MyEnum::Flag2;
	auto flag4 = ~MyEnum::Flag1;
	flag |= MyEnum::Flag2;
	flag &= MyEnum::Flag3;
	flag ^= MyEnum::Flag4;
	

*/



//======================= Type Conversions =========================
inline namespace type {
	//* cast bitwise, uses `memcpy()` before C++20, and uses `std::bit_cast()` in C++20
	// is not constexpr in C++14/17, but constexpr since C++20
	template<typename Out, typename In
		, _CUTIL_CONCEPT(!std::is_reference<Out>::value)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC _CUTIL_CONSTEXPR_CPP20
	inline Out bit_cast(In&& in) noexcept {
		static_assert(!std::is_reference<Out>::value, "Out cannot be a reference type");
		static_assert(sizeof(Out) == sizeof(typename std::remove_reference<In>::type), "Out and In must have same size");
		static_assert(std::is_trivially_copyable<Out>::value, "Out must be a trivially copyable type");
		static_assert(std::is_trivially_copyable<typename std::remove_reference_t<In>>::value, "In must be a trivially copyable type");
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::bit_cast<Out>(in);
	#else
		// return *reinterpret_cast<volatile Out*>(&in); // UB, but works in practice
		typename std::remove_const_t<Out> out;
		memcpy(&out, &in, sizeof(Out)); // copy memory
		return out; // return the casted value
	#endif
	}
	
	//* assign bitwise, `(memcpy(&out, &in, sizeof(T)))`
	template<typename Out, typename In> _CUTIL_FUNC_STATIC
	inline void bitwise_memcpy(Out& out, In&& in) {
		// static_assert(std::is_trivially_copyable_v<Out>, "Out and In must be a trivially copyable type");
		// static_assert(std::is_trivially_copyable_v<std::decay_t<In>>, "In must be a trivially copyable type");
		static_assert(sizeof(Out) == sizeof(In), "Out and In must have same size");
		memcpy(&out, &in, sizeof(Out));
	}
/*
	cutil::bitwise_memcpy(f, i) 				// i -> f, bitwise memcpy
	f = bit_cast<float>(i);   					// equivalent
	f = *reinterpret_cast<volatile float*>(&i); // equivalent
	std::memcpy(&f, &i, sizeof(f)); 			// equivalent
	f = std::bit_cast<float>(i) 				// C++20
*/
	
	
	//* do `dynamic_cast` in DEBUG, assert if failed; do `static_cast` in RELEASE
	//   `PDerived` points to the derived class, `PBase` points to the base class
	//   `PBase` and  `PDerived` should be both pointers point to different types, with same `const` or `volatile` attributes.
	template<typename PDerived, typename PBase
			, _CUTIL_CONCEPT_POINTER_SAME_ATTRIBUTES(PDerived, PBase)
			, _CUTIL_CONCEPT_POINTER_DIFFERENT_TYPES(PDerived, PBase)
			, _CUTIL_CONCEPT_POINTER_IS_BASE_OF(PBase, PDerived)
		> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr PDerived safe_cast(PBase in) {
	#ifdef CUTIL_DEBUG_BUILD
		PDerived out = dynamic_cast<PDerived>(in);
		assert(out != nullptr && "dynamic cast failed");
		return out;
	#else //release
		return static_cast<PDerived>(in);
	#endif
	}
/*
	struct Base { virtual ~A(){} };
	struct A : Base {};
	struct B : Base {};
	
	std::unique_ptr<Base> pa = std::make_unique<A>();
	A* pa1 = cutil::safe_cast<A*>(pa.get()); // do dynamic_cast in debug, assert if failed; do static_cast in release
	const A* pa2 = cutil::safe_cast<const A*>(const_cast<const Base*>(pa.get())); // convert const pointer to const pointer, OK
	// const A* pa3 = cutil::safe_cast<const A*>(pa.get()); // ERROR
	// A* pa4 = cutil::safe_cast<A*>(const_cast<Base*>(pa.get())); // ERROR
*/

} // namespace type

namespace internal {
	template <typename... Args>
	struct non_const_overload_impl
	{
		template <typename R, typename T>
		constexpr auto operator()(R (T::*ptr)(Args...)) const noexcept -> decltype(ptr)
		{ return ptr; }

		template <typename R, typename T>
		static constexpr auto of(R (T::*ptr)(Args...)) noexcept -> decltype(ptr)
		{ return ptr; }
	};
	
	template <typename... Args>
	struct const_overload_impl
	{
		template <typename R, typename T>
		constexpr auto operator()(R (T::*ptr)(Args...) const) const noexcept -> decltype(ptr)
		{ return ptr; }

		template <typename R, typename T>
		static constexpr auto of(R (T::*ptr)(Args...) const) noexcept -> decltype(ptr)
		{ return ptr; }
	};
	
	template <typename... Args>
	struct overload_impl
		: cutil::internal::const_overload_impl<Args...>
		, cutil::internal::non_const_overload_impl<Args...>
	{
		using cutil::internal::const_overload_impl<Args...>::of;
		using cutil::internal::const_overload_impl<Args...>::operator();
		using cutil::internal::non_const_overload_impl<Args...>::of;
		using cutil::internal::non_const_overload_impl<Args...>::operator();

		template <typename R>
		constexpr auto operator()(R (*ptr)(Args...)) const noexcept -> decltype(ptr)
		{ return ptr; }

		template <typename R>
		static constexpr auto of(R (*ptr)(Args...)) noexcept -> decltype(ptr)
		{ return ptr; }
	};
}
inline namespace type {
	//* overloads for function pointers, use `cutil::overload` to get the overload object
	//  referenced from `QOverload` implementation
	template <typename... Args> constexpr _CUTIL_INLINE_CPP17
	cutil::internal::overload_impl<Args...> 				overload 			= {};
	
	// if there's const and non-const member function overloads with same signature, must to use below.
	template <typename... Args> constexpr _CUTIL_INLINE_CPP17
	cutil::internal::const_overload_impl<const Args...> 	const_overload 		= {};
	template <typename... Args> constexpr _CUTIL_INLINE_CPP17
	cutil::internal::non_const_overload_impl<Args...> 		non_const_overload 	= {};
	
}
/*
* Example:
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

*/

//======================== Repeat And Range Statements =========================
inline namespace range {
//* iterator utils
//* generate code like `container.begin(), container.end()`
#define CUTIL_IT_RANGE(_container) 		(_container).begin(), (_container).end()
//* generate code like `container.rbegin(), container.rend()`
#define CUTIL_CTI_RANGE(_container) 	(_container).cbegin(), (_container).cend()
//* generate code like `container.rbegin(), container.rend()`
#define CUTIL_RIT_RANGE(_container) 	(_container).rbegin(), (_container).rend()
//* generate code like `container.crbegin(), container.crend()`
#define CUTIL_CRIT_RANGE(_container) 	(_container).crbegin(), (_container).crend()
/* Example:
	std::vector<int> vec(10);
	std::iota(CUTIL_IT_RANGE(vec), 0); // fill vec with 0 to 9
*/


//* get if specified value is contained in the container, uses std::find() to compare as .end() iterator
//  unavailable for std::queue, std::priority_queue, std::deque
template<typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains(const T& container, const V& value)
{ // value in std::find is const T&, no need to use std::forward<>()
	return (std::find(container.begin(), container.end(), value) != container.end());
}

//* get if specified value by predicate is contained in the container
template<typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T)
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains_if(const T& container, Pred pred) {
	return (std::find_if(container.begin(), container.end(), pred) != container.end());
}
/*
	std::vector<int> vec = {1, 2, 3, 4, 5};
	if(cutil::contains(vec, 3)){
		// vec contains 3
	}
	if(cutil::contains(std::execution::par_seq, vec, 3)){
		// vec contains 3
	}
	if(cutil::contains_if(vec, [](int i){return i == 3;})){
		// vec contains 3
	}
*/

// C++17 executionPolicy version
template<typename ExecutionPolicy, typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T)
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains_if(ExecutionPolicy&& policy, const T& container, Pred pred) {
#ifdef CUTIL_CPP17_SUPPORTED
	return (std::find_if(std::forward<ExecutionPolicy>(policy), container.begin(), container.end(), pred) != container.end());
#else
	return cutil::contains_if(container, pred);
#endif
}

template<typename ExecutionPolicy, typename T, typename V, _CUTIL_CONCEPT_HAS_ITERATOR(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline bool contains(ExecutionPolicy&& policy, const T& container, const V& value) {
#ifdef CUTIL_CPP17_SUPPORTED
	return (std::find(std::forward<ExecutionPolicy>(policy), container.begin(), container.end(), value) != container.end());
#else
	return cutil::contains(container, value);
#endif
}



//* erase all elements with specific value of `std::vector`/`std::deque`
template<typename T, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T), _CUTIL_CONCEPT_MEMBER(T, shrink_to_fit())> _CUTIL_FUNC_STATIC
inline size_t erase_vector(T& container, const V& value) {
// #ifdef CUTIL_CPP20_SUPPORTED
	// return std::erase(container, value); // compiled with error
// #else
	auto newIt = std::remove(container.begin(), container.end(), value);
	size_t count = std::distance(newIt, container.end());
	container.erase(newIt, container.end()); // iterator will be invalidated
	return count;
// #endif
}

//* erase all elements by predicate of `std::vector`/`std::deque`
template <typename T, typename Pred, typename V = typename T::value_type, _CUTIL_CONCEPT_HAS_ITERATOR(T), _CUTIL_CONCEPT_MEMBER(T, shrink_to_fit())
	, _CUTIL_CONCEPT_INVOKABLE_RET(Pred, bool, std::declval<V>())> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
inline size_t erase_if_vector(T& container, Pred pred) {
// #ifdef CUTIL_CPP20_SUPPORTED
	// return std::erase_if(container, pred); // compiled with error
// #else
	size_t count = 0;
	auto newIt = std::remove_if(container.begin(), container.end(), pred);
	count = std::distance(newIt, container.end());
	container.erase(newIt, container.end());
	return count;
// #endif
}
/*
	std::vector<int> e1 = {1, 2, 2, 4, 2, 5, 4};
	size_t removed = cutil::erase_vector(e1, 2); // 3
	removed = cutil::erase_if_vector(e1, [](int i){return i == 4;}); // 2
	e1.clear();
	removed = cutil::erase_vector(e1, 6); // 0
*/


} // namespace range



//======================= Memory Operations =========================
inline namespace memory {
	
	//* get midpoint of two pointers
	template<typename P> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr P* midpoint(P* a, P* b) noexcept { // for pointers
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		return (a + (b - a) / 2);
	#endif
	}
	
	//* get offset of two pointers in bytes
	template <typename T, typename U> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline ptrdiff_t get_ptr_offset(T* higher, U* lower){
		return reinterpret_cast<uintptr_t>(higher) - reinterpret_cast<uintptr_t>(lower);
	}
	
	// get offset of the struct member to the struct base address
	template <typename U, typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline ptrdiff_t get_member_offset(T U::* member){
		return static_cast<ptrdiff_t>(reinterpret_cast<uintptr_t>(&(reinterpret_cast<U*>(0)->*member)));
	}
/*
	struct S { int a; int b; };
	ptrdiff_t offset = cutil::memory::get_member_offset(&A::b); // offset of b in struct S
	
	S s;
	ptrdiff_t offset = cutil::memory::get_ptr_offset(&s.a, &s.b); // offset of two pointers
	
*/

	// (UB) get value from the memory address in the specific type
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> _CUTIL_NODISCARD [[deprecated]] _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T& read_memory(P ptr) {
		return *reinterpret_cast<T*>(ptr); // add volatile might cause error
	}
	
	// (UB) set memory at the specific location in the specific type
	template<typename T, typename P, _CUTIL_CONCEPT_POINTER(P)> [[deprecated]] _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline void write_memory(P ptr, T&& val) {
		static_assert(sizeof(T) == sizeof(*ptr), "Size of T must be equal to the size of the memory at ptr");
		*reinterpret_cast<T*>(ptr) = val;
	}
/*
	uint16_t num = 0x1234;
	// uint16_t num2 = cutil::read_memory<uint16_t>(&num); // 0x1234
	// cutil::write_memory<uint16_t>(&num, 0x5678); // num: 0x5678
*/

	
	//* wrapper for C memory functions, but specify amount of elements, not bytes
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memcpy_type(T* out, const T* in, size_t amount = 1) {
		return memcpy(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memmove_type(T* out, const T* in, size_t amount = 1) {
		return memmove(out, in, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* memset_type(T& out, int value, size_t amount = 1) {
		return memset(&out, value, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline int memcmp_type(const T* ptr1, const T* ptr2, size_t amount = 1) {
		return memcmp(ptr1, ptr2, sizeof(T) * amount);
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* malloc_type(size_t amount = 1) {
		return static_cast<T*>(std::malloc(sizeof(T) * amount));
	}
	template <typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* calloc_type(size_t amount = 1) {
		return static_cast<T*>(std::calloc(amount, sizeof(T)));
	}
	template<typename T> _CUTIL_MAYBE_UNUSED _CUTIL_FUNC_STATIC
	inline T* realloc_type(T* ptr, size_t amount = 1) {
		return static_cast<T*>(std::realloc(ptr, sizeof(T) * amount));
	}
	
	//* delete heap pointer and set it to nullptr
	template<typename T> _CUTIL_FUNC_STATIC
	inline void free_ptr(T*& ptr) {
		if(ptr != nullptr){
			std::free(ptr);
			ptr = nullptr;
		}
	}
	template<typename T> _CUTIL_FUNC_STATIC
	inline void delete_ptr(T*& p) {
		if(p != nullptr){
			delete p;
			p = nullptr;
		}
	}
	template<typename T> _CUTIL_FUNC_STATIC
	inline void delete_array(T*& p) {
		if(p != nullptr){
			delete[] p;
			p = nullptr;
		}
	}

	
} // namespace memory



//==================== C++ Class Utilities ========================

//* set class constructor/moving/copying to disabled/default
// Default Constructor(no params) and Destructor
#define CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
	_CLASS_NAME() = default; \
	~_CLASS_NAME() = default;

// Disable copy constructor and copy operator=
#define CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
	_CLASS_NAME(const _CLASS_NAME & ) = delete;\
	_CLASS_NAME& operator=(const _CLASS_NAME & ) = delete;

// Default copy constructor and copy operator=
#define CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
	_CLASS_NAME(const _CLASS_NAME & ) = default;\
	_CLASS_NAME& operator=(const _CLASS_NAME & ) = default;

// Disable move constructor and move operator=
#define CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME) \
	_CLASS_NAME(_CLASS_NAME && ) noexcept = delete; \
	_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = delete;

// Default move constructor and move operator=
#define CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME) \
	_CLASS_NAME(_CLASS_NAME && ) noexcept = default; \
	_CLASS_NAME& operator=(_CLASS_NAME && ) noexcept = default;

// Disable moving and copying
#define CUTIL_CLASS_DISABLE_COPY_MOVE(_CLASS_NAME) \
	CUTIL_CLASS_DISABLE_COPY(_CLASS_NAME) \
	CUTIL_CLASS_DISABLE_MOVE(_CLASS_NAME)

// Default moving and copying
#define CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_COPY(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_MOVE(_CLASS_NAME)

// Default Constructor, Destructor, Copying, Moving
#define CUTIL_CLASS_DEFAULT_FUNCTIONS(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_CONSTRUCTOR(_CLASS_NAME) \
	CUTIL_CLASS_DEFAULT_COPY_MOVE(_CLASS_NAME)



//* generate getter and setter
// generate getter and setter with specific type (not recommended, and do not add `const` to the first parameter)
#define CUTIL_GETTER_TYPE(_type, _name, _getter) 	public: _type _getter() {return this->_name;}
#define CUTIL_SETTER_TYPE(_type, _name, _setter) 	public: void _setter(const _type& _val)	{this->_name = _val;}
#define CUTIL_MEMBER_TYPE(_type, _name, ...)		CUTIL_EXPAND(CUTIL_OVERLOAD_IDX(_CUTIL_MEMBER_TYPE_, CUTIL_VA_CNT(__VA_ARGS__))(_type, _name, __VA_ARGS__))
#define _CUTIL_MEMBER_TYPE_2(_type, _name, _getter, _setter)	CUTIL_GETTER_TYPE(_type, _name, _getter) CUTIL_SETTER_TYPE(_type, _name, _setter)
#define _CUTIL_MEMBER_TYPE_1(_type, _name, _func)				_CUTIL_MEMBER_TYPE_2(_type, _name, _func, _func)

// generate getter and setter with type deducing (uses `std::decay_t<decltype(_name)>`)
#define CUTIL_GETTER(_name, _getter) 		CUTIL_GETTER_TYPE(CUTIL_TYPEOF(_name), _name, _getter)
#define CUTIL_SETTER(_name, _setter) 		CUTIL_SETTER_TYPE(CUTIL_TYPEOF(_name), _name, _setter)
#define CUTIL_MEMBER(_name, ...) 			CUTIL_EXPAND(CUTIL_MEMBER_TYPE(CUTIL_TYPEOF(_name), _name, __VA_ARGS__))
/* example:
	class Test {
		private: int m_a {};
		CUTIL_GETTER(m_a, getA) // public: int  getA() {return this->m_a;}
		CUTIL_SETTER(m_a, setA) // public: void setA(const int& _val) {this->m_a = _val;}
		
		private: double m_b {};
		CUTIL_MEMBER(m_b, getB, setB)
		// public: double getB() {return this->m_b;}
		// public:  void  setB(const double& _val) {this->m_b = _val;}

		private: std::string m_c {};
		CUTIL_MEMBER(m_c, c)
		// public: std::string c() {return this->m_c;}
		// public:      void   c(const std::string& _val) {this->m_c = _val;}
	};
	Test test;
	
	// print
	fmt::println("Test::m_a = {}", test.getA());
	
	test.setB(3.1615925);
	fmt::println("Test::m_b = {}", test.getB());

	test.c("hello world!");
	fmt::println("Test::m_c = {}", test.c());
*/






_CUTIL_NAMESPACE_END
#endif // CUTIL_CPP_UTILS_H__
