/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		9 JUL 2025
  License:		MIT License
* You can include this header in header files.
* C++14 or later is required.
*/

#ifndef CUTIL_BASE_CPP_BASE_HPP__
#define CUTIL_BASE_CPP_BASE_HPP__

#include <cutil/base.h>

#include <type_traits>
#include <functional>

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif
_CUTIL_NAMESPACE_BEGIN


//===============  concepts ================
namespace internal {
	template <typename T>
	struct is_uint : std::integral_constant<bool
					, std::is_integral<T>::value
					&& std::is_unsigned<T>::value
					&& !std::is_same<std::remove_cv_t<T>, bool>::value
			> {};
	
	template <typename T>
	struct is_signed_or_float : std::integral_constant<bool
					, (std::is_signed<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value)
					|| std::is_floating_point<T>::value
			> {};
	
	template <typename From, typename To = From>
	struct is_arithmetic_and_convertible : std::integral_constant<bool
				, std::is_arithmetic<From>::value
				&& std::is_arithmetic<To>::value
				&& std::is_convertible<From, To>::value
				&& !std::is_same<std::remove_cv_t<From>, bool>::value
				&& !std::is_same<std::remove_cv_t<To>, bool>::value
			>{};
	
	template <typename From, typename To = From>
	struct is_integral_and_convertible : std::integral_constant<bool
				, std::is_integral<From>::value
				&& std::is_integral<To>::value
				&& std::is_convertible<From, To>::value
				&& !std::is_same<std::remove_cv_t<From>, bool>::value
				&& !std::is_same<std::remove_cv_t<To>, bool>::value
			>{};
	
	template <typename T>
	struct has_iterators : std::integral_constant<bool
				, std::is_same<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value
			>{};
	
	template <typename T, typename U>
	struct has_same_size : std::integral_constant<bool, sizeof(T) == sizeof(U)>{};
	
	template <typename Ptr>
	struct remove_const_pointer_to_type {
		using type = typename std::remove_const_t<typename std::remove_pointer_t<Ptr>>;
	};
	
	template <typename P1, typename P2>
	struct is_same_pointer_types : std::integral_constant<bool
								,  std::is_pointer<P1>::value
								&& std::is_pointer<P2>::value
								&& std::is_same<typename cutil::internal::remove_const_pointer_to_type<P1>::type
											  , typename cutil::internal::remove_const_pointer_to_type<P2>::type
									>::value
							>{};
	
	template <typename P1, typename P2>
	struct is_pointer_both_same_attributes : std::integral_constant<bool
										,  std::is_pointer<P1>::value
										&& std::is_pointer<P2>::value
										&& (   std::is_const<typename std::remove_pointer_t<P1>>::value
											== std::is_const<typename std::remove_pointer_t<P2>>::value)
										&& (  std::is_volatile<typename std::remove_pointer_t<P1>>::value
											== std::is_volatile<typename std::remove_pointer_t<P2>>::value)
									>{};
	
	template <typename PBase, typename PDerived>
	struct is_base_of_pointer : std::integral_constant<bool
									,  std::is_pointer<PBase>::value
									&& std::is_pointer<PDerived>::value
									&& std::is_base_of<
											  typename cutil::internal::remove_const_pointer_to_type<PBase>::type
											, typename cutil::internal::remove_const_pointer_to_type<PDerived>::type
										>::value
									>{};
	

	
#ifndef CUTIL_CPP17_SUPPORTED // C++14
	namespace detail {
		// SFINAE辅助模板
		template<bool B, typename T = void>
		using enable_if_t = typename std::enable_if_t<B, T>;

		// 检测函数调用并转换返回类型
		template<typename R, typename F, typename... Args>
		auto is_invocable_r_helper(F&& f, Args&&... args) ->
			decltype(static_cast<R>(std::forward<F>(f)(std::forward<Args>(args)...)), std::true_type{});
		template<typename R, typename F, typename... Args>
		std::false_type is_invocable_r_helper(...);

		// 主实现类
		template<typename R, typename F, typename... Args>
		struct is_invocable_r_impl {
			using type = decltype(is_invocable_r_helper<R>(
				std::declval<F>(), std::declval<Args>()...
			));
		};
	}
	// C++17 std::void_t implementation for C++14
	template <typename...>
	using void_t = void;
	
	// C++17 std:is_invocable implementation for C++14
	template<typename R, typename F, typename... Args>
	struct is_invocable_r : cutil::internal::detail::is_invocable_r_impl<R, F, Args...>::type {};

	template<typename F, typename... Args>
	struct is_invocable : cutil::internal::detail::is_invocable_r_impl<void, F, Args...>::type {};

#else // >= C++17
	template <typename...>
	using void_t = std::void_t<>;
	
	template<typename R, typename F, typename... Args>
	using is_invocable_r = std::is_invocable_r<R, F, Args...>;

	template<typename F, typename... Args>
	using is_invocable = std::is_invocable<F, Args...>;
#endif
} // internal
#define _CUTIL_CONCEPT(_TYPE) 				\
			typename std::enable_if_t<_TYPE, bool> = false
#define _CUTIL_CONCEPT_SAME_REMOVE_CV(T1, T2) 	\
			typename std::enable_if_t<std::is_same<std::remove_cv_t<T1>, std::remove_cv_t<T2>>::value, bool> = true
#define _CUTIL_CONCEPT_UNSIGNED(T) 			\
			typename std::enable_if_t<cutil::internal::is_uint<T>::value, bool> = false
#define _CUTIL_CONCEPT_SIGNED(T)			\
			typename std::enable_if_t<std::is_signed<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value, bool> = false
#define _CUTIL_CONCEPT_INTEGRAL(T) 			\
			typename std::enable_if_t<std::is_integral<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value, bool> = false
#define _CUTIL_CONCEPT_FLOAT(T) 			\
			typename std::enable_if_t<std::is_floating_point<T>::value, bool> = false
#define _CUTIL_CONCEPT_FLOAT_WITHOUT_LONGDOUBLE(T) \
			typename std::enable_if_t<std::is_floating_point<T>::value && !std::is_same<std::remove_cv_t<T>, long double>::value, bool> = false
#define _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T) 	\
			typename std::enable_if_t<cutil::internal::is_signed_or_float<T>::value, bool> = false
#define _CUTIL_CONCEPT_ARITHMETIC(T)		\
			typename std::enable_if_t<std::is_arithmetic<T>::value && !std::is_same<std::remove_cv_t<T>, bool>::value, bool> = false
#define _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(From, To) \
			typename std::enable_if_t<cutil::internal::is_arithmetic_and_convertible<From, To>::value, bool> = true
// #define _CUTIL_CONCEPT_INTEGRAL_CONVERTIBLE(From, To) 	\
// 			typename std::enable_if_t<cutil::internal::is_integral_and_convertible<From, To>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER(T) 			\
			typename std::enable_if_t<std::is_pointer<T>::value, bool> = false
// #define _CUTIL_CONCEPT_IS_SAME(T1, T2) 	\
// 			typename std::enable_if_t<std::is_same<T1, T2>::value, bool> = true
// #define _CUTIL_CONCEPT_IS_DIFFERENT(T1, T2) \
// 			typename std::enable_if_t<!std::is_same<T1, T2>::value, bool> = true
#define _CUTIL_CONCEPT_IS_ENUM(T)	\
			typename std::enable_if_t<std::is_enum<T>::value, bool> = false
#define _CUTIL_CONCEPT_CONVERTIBLE(From, To) \
			typename std::enable_if_t<std::is_convertible<From, To>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_DIFFERENT_TYPES(P1, P2) \
			typename std::enable_if_t< ! cutil::internal::is_same_pointer_types<P1, P2>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_SAME_ATTRIBUTES(P1, P2) \
			typename std::enable_if_t<cutil::internal::is_pointer_both_same_attributes<P1, P2>::value, bool> = true
#define _CUTIL_CONCEPT_POINTER_IS_BASE_OF(PBase, PDerived) \
			typename std::enable_if_t<cutil::internal::is_base_of_pointer<PBase, PDerived>::value, bool> = true
#define _CUTIL_CONCEPT_COMPARABLE(T, U, COMP) 	\
			typename = decltype(std::declval<T>() COMP std::declval<U>())

#define _CUTIL_CONCEPT_MEMBER(T, Member) 	\
			typename = decltype(std::declval<T>().Member)
#define _CUTIL_CONCEPT_FUNCTION(T, Func, ...) 	\
			typename = decltype(Func(std::declval<T>(__VA_ARGS__)))
#define _CUTIL_CONCEPT_INVOKABLE(Func, ...) 	\
			typename = decltype(std::declval<Func>()(__VA_ARGS__))
#define _CUTIL_CONCEPT_INVOKABLE_RET(Func, Ret, ...) 	\
			typename = decltype(std::declval<Func>()(__VA_ARGS__) == std::declval<Ret>())
#define _CUTIL_CONCEPT_HAS_ITERATOR(T)  	\
			typename std::enable_if_t<cutil::internal::has_iterators<T>::value, bool> = true

#define _CUTIL_CONCEPT_SAME_SIZE(T, U) 		\
			typename std::enable_if_t<cutil::internal::has_same_size<T, U>::value, bool> = true




#ifdef CUTIL_CPP20_SUPPORTED
	_CUTIL_NODISCARD inline constexpr bool is_constant_evaluated() noexcept {
		return std::is_constant_evaluated();
	}
#else
	#if (defined(__clang__) && __clang_major__ >= 10) || (defined(__GNUC__) && __GNUC__ >= 10)
		// GCC and Clang support __builtin_is_constant_evaluated() since gcc 10 and Clang 10
		_CUTIL_NODISCARD inline constexpr bool is_constant_evaluated() noexcept {
			return __builtin_is_constant_evaluated();
		}
	#elif defined(_MSC_VER) && (_MSC_VER >= 1920)
		// MSVC supports __builtin_is_constant_evaluated() since Visual Studio 2019 version 16.0
		_CUTIL_NODISCARD inline constexpr bool is_constant_evaluated() noexcept {
			return __builtin_is_constant_evaluated();
		}
	#elif defined(_MSC_VER) && (_MSC_VER < 1920)
		constexpr bool is_constant_evaluated() noexcept { // this only works in MSVC
			struct C {};
			struct M : C { int a; };
			struct N : C { int a; };
			return &M::a != static_cast<int C::*>(&N::a);
		}
	#else
		// Fallback for C++14/17, always return false
		// Note: This will not work as intended in C++20, but is a placeholder for C++14/17
		_CUTIL_NODISCARD inline constexpr bool is_constant_evaluated() noexcept {
			return false;
		}
	#endif
#endif





_CUTIL_NAMESPACE_END
#endif /* CUTIL_BASE_CPP_BASE_HPP__ */
