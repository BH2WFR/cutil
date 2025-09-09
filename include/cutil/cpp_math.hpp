/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		9 JUL 2025
  License:		MIT License
* You can include this header in header files.
* C++14 or later is required.
*/

#ifndef CUTIL_CPP_MATH_HPP__
#define CUTIL_CPP_MATH_HPP__

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
#include <utility>
#include <array>
#ifdef CUTIL_CPP20_SUPPORTED
	#include <bit>
#endif


_CUTIL_NAMESPACE_BEGIN




//======================= Math Constants =========================
/* instructions:
	float 		pi 		= cutil::numbers::pi_f;
	double 		pi 		= cutil::numbers::pi;
	long double pi_ld 	= cutil::numbers::pi_ld
	
	float 		pi 		= cutil::Numbers<float>::pi;
	double 		pi 		= cutil::Numbers<double>::pi;
	long double pi_ld 	= cutil::Numbers<long double>::pi
*/
template <typename T, _CUTIL_CONCEPT_FLOAT(T)>
struct Numbers {
	// defined as long double type.
	//* mathematical constants
	static constexpr T e 			= static_cast<T>(2.718281828459045235360287471352662498L); //*  e
	static constexpr T log2e 		= static_cast<T>(1.442695040888963407359924681001892137L); //*  log2(e)
	static constexpr T log10e 		= static_cast<T>(0.434294481903251827651128918916605082L); //*  log10(e)
	static constexpr T ln2 			= static_cast<T>(0.693147180559945309417232121458176568L); //*  ln(2)
	static constexpr T ln10 		= static_cast<T>(2.302585092994045684017991454684364208L); //*  ln(10)

	static constexpr T pi 			= static_cast<T>(3.141592653589793238462643383279502884L); //*  pi
	static constexpr T two_pi 		= static_cast<T>(6.283185307179586476925286766559005768L); //*  2 * pi
	static constexpr T three_pi 	= static_cast<T>(9.424777960769379715387930149838508653L); //*  3 * pi
	static constexpr T pi_half 		= static_cast<T>(1.570796326794896619231321691639751442L); //*  pi / 2
	static constexpr T pi_third 	= static_cast<T>(1.047197551196597746154214461093167628L); //*  pi / 3
	static constexpr T pi_quarter 	= static_cast<T>(0.7853981633974483096156608458198757210L);//*  pi / 4
	static constexpr T inv_pi 		= static_cast<T>(0.3183098861837906715377675267450287241L);//*  1 / pi
	static constexpr T inv_sqrt_pi 	= static_cast<T>(0.5641895835477562869480794515607725858L);//*  1 / sqrt(pi)
	static constexpr T two_inv_pi 	= static_cast<T>(0.6366197723675813430755350534900574481L);//*  2 / pi
	static constexpr T two_sqrt_pi 	= static_cast<T>(1.128379167095512573896158903121545172L); //*  2 / sqrt(pi)

	static constexpr T sqrt2 		= static_cast<T>(1.414213562373095048801688724209698079L); //*  sqrt(2)
	static constexpr T inv_sqrt2 	= static_cast<T>(0.7071067811865475244008443621048490393L);//*  1 / sqrt(2)
	static constexpr T sqrt3 		= static_cast<T>(1.732050807568877293527446341505872367L); //*  sqrt(3)
	static constexpr T inv_sqrt3 	= static_cast<T>(0.577350269189625764509148780501957456L); //*  1 / sqrt(3)

	static constexpr T phi 			= static_cast<T>(1.618033988749894848204586834365638118L); //*  (1 + sqrt(5)) / 2, golden ratio
	static constexpr T inv_phi 		= static_cast<T>(0.6180339887498948482045868343656381177L);//*  2 / (1 + sqrt(5)), inverted golden ratio

	static constexpr T egamma 		= static_cast<T>(0.5772156649015328606065120900824024310L);//*  Euler-Mascheroni constant
	
	//* special values of floating point types
	static constexpr T inf 			= std::numeric_limits<T>::infinity();  //* infinity
	static constexpr T neg_inf 		= -std::numeric_limits<T>::infinity(); //* minus infinity
	static constexpr T nan 			= std::numeric_limits<T>::quiet_NaN(); //* NaN (not a number)
	
	//* limits of the type T
	static constexpr T epsilon 		= std::numeric_limits<T>::epsilon(); 	//* machine epsilon, the smallest value that can be added to 1.0 to get a different value
	static constexpr T min 			= std::numeric_limits<T>::min(); 		//* minimum positive value
	static constexpr T max 			= std::numeric_limits<T>::max(); 		//* maximum value
	static constexpr T lowest 		= std::numeric_limits<T>::lowest(); 	//* lowest value, the most negative value
	static constexpr T denorm_min 	= std::numeric_limits<T>::denorm_min(); //* minimum denormalized value (==0.5), the smallest positive value that can be represented as a denormalized number
	static constexpr T round_error 	= std::numeric_limits<T>::round_error();//* the maximum error due to rounding
};
#if CUTIL_PARAM_USE_SHORTEN_NAMESPACE
template<typename T>
using Num = Numbers<T>; // shorter alias
#endif // CUTIL_PARAM_USE_SHORTEN_NAMESPACE

inline namespace numbers { // inline
	//* alternatives for C++20 std::numbers
	//* double versions
	constexpr double e 				= cutil::Numbers<double>::e;
	constexpr double log2e 			= cutil::Numbers<double>::log2e;
	constexpr double log10e 		= cutil::Numbers<double>::log10e;
	constexpr double ln2 			= cutil::Numbers<double>::ln2;
	constexpr double ln10			= cutil::Numbers<double>::ln10;
		
	constexpr double pi 			= cutil::Numbers<double>::pi;
	constexpr double two_pi 		= cutil::Numbers<double>::two_pi;
	constexpr double three_pi 		= cutil::Numbers<double>::three_pi;
	constexpr double pi_half 		= cutil::Numbers<double>::pi_half;
	constexpr double pi_third 		= cutil::Numbers<double>::pi_third;
	constexpr double pi_quarter 	= cutil::Numbers<double>::pi_quarter;
	constexpr double inv_pi 		= cutil::Numbers<double>::inv_pi;
	constexpr double inv_sqrt_pi 	= cutil::Numbers<double>::inv_sqrt_pi;
	constexpr double two_inv_pi 	= cutil::Numbers<double>::two_inv_pi;
	constexpr double two_sqrt_pi 	= cutil::Numbers<double>::two_sqrt_pi;
	
	constexpr double sqrt2 			= cutil::Numbers<double>::sqrt2;
	constexpr double inv_sqrt2 		= cutil::Numbers<double>::inv_sqrt2;
	constexpr double sqrt3 			= cutil::Numbers<double>::sqrt3;
	constexpr double inv_sqrt3 		= cutil::Numbers<double>::inv_sqrt3;
	
	constexpr double phi 			= cutil::Numbers<double>::phi;
	constexpr double inv_phi 		= cutil::Numbers<double>::inv_phi;
		
	constexpr double egamma 		= cutil::Numbers<double>::egamma;
	
	constexpr double inf 			= cutil::Numbers<double>::inf;
	constexpr double neg_inf 		= cutil::Numbers<double>::neg_inf;
	constexpr double nan 			= cutil::Numbers<double>::nan;
	
	//* float versions
	constexpr float e_f 			= cutil::Numbers<float>::e;
	constexpr float log2e_f 		= cutil::Numbers<float>::log2e;
	constexpr float log10e_f 		= cutil::Numbers<float>::log10e;
	constexpr float ln2_f 			= cutil::Numbers<float>::ln2;
	constexpr float ln10_f 			= cutil::Numbers<float>::ln10;
	
	constexpr float pi_f 			= cutil::Numbers<float>::pi;
	constexpr float two_pi_f 		= cutil::Numbers<float>::two_pi;
	constexpr float three_pi_f 		= cutil::Numbers<float>::three_pi;
	constexpr float pi_half_f 		= cutil::Numbers<float>::pi_half;
	constexpr float pi_third_f 		= cutil::Numbers<float>::pi_third;
	constexpr float pi_quarter_f 	= cutil::Numbers<float>::pi_quarter;
	constexpr float inv_pi_f 		= cutil::Numbers<float>::inv_pi;
	constexpr float inv_sqrt_pi_f 	= cutil::Numbers<float>::inv_sqrt_pi;
	constexpr float two_inv_pi_f 	= cutil::Numbers<float>::two_inv_pi;
	constexpr float two_sqrt_pi_f 	= cutil::Numbers<float>::two_sqrt_pi;
	
	constexpr float sqrt2_f 		= cutil::Numbers<float>::sqrt2;
	constexpr float inv_sqrt2_f 	= cutil::Numbers<float>::inv_sqrt2;
	constexpr float sqrt3_f 		= cutil::Numbers<float>::sqrt3;
	constexpr float inv_sqrt3_f 	= cutil::Numbers<float>::inv_sqrt3;
	
	constexpr float phi_f 			= cutil::Numbers<float>::phi;
	constexpr float inv_phi_f 		= cutil::Numbers<float>::inv_phi;
		
	constexpr float egamma_f 		= cutil::Numbers<float>::egamma;
	
	constexpr float inf_f 			= cutil::Numbers<float>::inf;
	constexpr float neg_inf_f 		= cutil::Numbers<float>::neg_inf;
	constexpr float nan_f 			= cutil::Numbers<float>::nan;
	
	//* long double versions
	constexpr long double e_ld 				= cutil::Numbers<long double>::e;
	constexpr long double log2e_ld 			= cutil::Numbers<long double>::log2e;
	constexpr long double log10e_ld 		= cutil::Numbers<long double>::log10e;
	constexpr long double ln2_ld 			= cutil::Numbers<long double>::ln2;
	constexpr long double ln10_ld 			= cutil::Numbers<long double>::ln10;
	
	constexpr long double pi_ld 			= cutil::Numbers<long double>::pi;
	constexpr long double two_pi_ld 		= cutil::Numbers<long double>::two_pi;
	constexpr long double three_pi_ld 		= cutil::Numbers<long double>::three_pi;
	constexpr long double pi_half_ld 		= cutil::Numbers<long double>::pi_half;
	constexpr long double pi_third_ld 		= cutil::Numbers<long double>::pi_third;
	constexpr long double pi_quarter_ld 	= cutil::Numbers<long double>::pi_quarter;
	constexpr long double inv_pi_ld 		= cutil::Numbers<long double>::inv_pi;
	constexpr long double inv_sqrt_pi_ld 	= cutil::Numbers<long double>::inv_sqrt_pi;
	constexpr long double two_inv_pi_ld 	= cutil::Numbers<long double>::two_inv_pi;
	constexpr long double two_sqrt_pi_ld 	= cutil::Numbers<long double>::two_sqrt_pi;
	
	constexpr long double sqrt2_ld 			= cutil::Numbers<long double>::sqrt2;
	constexpr long double inv_sqrt2_ld 		= cutil::Numbers<long double>::inv_sqrt2;
	constexpr long double sqrt3_ld 			= cutil::Numbers<long double>::sqrt3;
	constexpr long double inv_sqrt3_ld 		= cutil::Numbers<long double>::inv_sqrt3;
	
	constexpr long double phi_ld 			= cutil::Numbers<long double>::phi;
	constexpr long double inv_phi_ld 		= cutil::Numbers<long double>::inv_phi;
	
	constexpr long double egamma_ld 		= cutil::Numbers<long double>::egamma;
	
	constexpr long double inf_ld 			= cutil::Numbers<long double>::inf;
	constexpr long double neg_inf_ld 		= cutil::Numbers<long double>::neg_inf;
	constexpr long double nan_ld 			= cutil::Numbers<long double>::nan;
}
#if CUTIL_PARAM_USE_SHORTEN_NAMESPACE
namespace num = cutil::numbers;  // shorter alias
#endif // CUTIL_PARAM_USE_SHORTEN_NAMESPACE



//======================= Numeric and Math Operations =========================
inline namespace math { // inline
	//* limit the numeric variable to the range [_MIN, _MAX], same as `std::clamp(var, min, max)` in C++17
	//  by default, comp == std::less<T>()
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clamp(const T& var, const T& min, const T& max) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::clamp(var, min, max);
	#else
		assert((min < max) && "`min` should be less than `max`");
		return std::min(std::max(var, min), max);
	#endif
	}
	template<typename T, typename Comp
		, _CUTIL_CONCEPT((cutil::internal::is_invocable_r<bool, Comp, T, T>::value))> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T clamp(const T& var, const T& min, const T& max, Comp comp) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::clamp(var, min, max, comp);
	#else
		assert((comp(min, max)) && "`min` should be less than `max`");
		return std::min(std::max(var, min, comp), max, comp);
	#endif
	}
	
	//* limit the numeric variable to the range [_MIN, _MAX], same as `var = std::clamp(var, min, max)` in C++17
	//  by default, comp == std::less<T>()
	template<typename T, typename R = T, _CUTIL_CONCEPT_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline void limit(T& var, const R& min, const R& max) noexcept {
		var = cutil::math::clamp(var, static_cast<T>(min), static_cast<T>(max));
	}
	template<typename T, typename Comp, typename R = T, _CUTIL_CONCEPT_CONVERTIBLE(R, T)
		, typename std::enable_if_t<cutil::internal::is_invocable_r<bool, Comp, T, T>::value, bool> = true> _CUTIL_FUNC_STATIC
	inline void limit(T& var, const R& min, const R& max, Comp comp) noexcept {
		var = cutil::math::clamp(var, static_cast<T>(min), static_cast<T>(max), comp);
	}
	
	//* get if a numeric variable is within the interval [_MIN, _MAX]
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
		return (var >= min) && (var <= max);
	}
	//* get if a numeric variable is within the interval (_MIN, _MAX)
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_open_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
		return (var > min) && (var < max);
	}
	
#ifdef CUTIL_CPP17_SUPPORTED //* >= C++17
	//* Comparison function to check if a value is within a specified interval
	template <bool LeftClosed, bool RightClosed, typename T, typename R = T
			, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool num_in_interval(T var, R min, R max) noexcept {
		assert((min < max) && "`min` should be less than `max`");
		if constexpr (LeftClosed && RightClosed) {
			return (var >= min) && (var <= max); // [min, max]
		} else if constexpr (LeftClosed && !RightClosed) {
			return (var >= min) && (var < max);  // [min, max)
		} else if constexpr (!LeftClosed && RightClosed) {
			return (var > min) && (var <= max);  // (min, max]
		} else {
			return (var > min) && (var < max);   // (min, max)
		}
	}
#else
	
#endif
/*
	int a = 35, b = 26, c = 19, d = 35;
	d = std::clamp(d, 20, 30);  		// C++17, equivalent to above
	d = cutil::math::clamp(d, 20, 30); 	// C++14, equivalent to above
	d = cutil::math::clamp(d, 20, 30, std::less<int>()); // equivalent to above
	cutil::limit(d, 20, 30);			// d: 30, equivalent to `d = cutil::clamp(d, 20, 30);`
	cutil::limit(d, 20, 30, std::less<int>());	// equivalent to above
	fmt::println("{} {} {}", a, b, c); // output: 30 26 20
	

	bool ret = cutil::math::num_in_interval(a, 20, 40);				  // whether a is in [20, 40]
	bool ret = cutil::math::num_in_open_interval(c, 20, 30);		  // whether c is in (20, 30)
	bool ret = cutil::math::num_in_interval<true, true>(a, 20, 40);	  // whether a is in [20, 40], C++17
	bool ret = cutil::math::num_in_interval<true, false>(a, 20, 40);  // whether a is in [20, 40), C++17
	bool ret = cutil::math::num_in_interval<false, false>(a, 20, 40); // whether a is in [20, 40], C++17
*/


	//* increase the value of variable, but if the result exceeds the limit(>=), it will not be increased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool increase_under_limit(T& var, L max, int inc = 1) noexcept {
		assert(var <= max);
		if((var + static_cast<T>(inc)) <= static_cast<T>(max)) {
			var += static_cast<T>(inc);
			return false;
		}
		return true;
	}
	// increase the value of variable, but if the result exceeds the limit(>=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool increase_under_limit_clamp(T& var, L max, int inc = 1) noexcept {
		if(cutil::math::increase_under_limit(var, max, inc)) {
			var = static_cast<T>(max);
			return true;
		}
		return false;
	}
	
	//* decrease the value of variable, but if the result is less than the limit(<=), it will not be decreased
	//  if exceeded, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_above_limit(T& var, L min, int dec = 1) noexcept {
		assert(var >= min);
		if((var - static_cast<T>(dec)) >= static_cast<T>(min)){
			var -= static_cast<T>(dec);
			return false;
		}
		return true;
	}
	// decrease the value of variable, but if the result is less than the limit(<=), it will be clamped to the limit
	// if clamped, returns true.
	template<typename T, typename L = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(L, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_above_limit_clamp(T& var, L min, int dec = 1) noexcept {
		if(cutil::math::decrease_above_limit(var, min, dec)){
			var = static_cast<T>(min);
			return true;
		}
		return false;
	}
	
	//* increase the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline bool increase_rolling(T& var, R min, R max, int inc = 1) noexcept {
		assert(min < max && cutil::num_in_interval(var, min, max));
		if((var + static_cast<T>(inc)) <= max){
			var += static_cast<T>(inc);
			return false;
		}
		var = static_cast<T>(min);
		return true;
	}
	
	//* decrease the value of variable, and rolling within the range [_MIN, _MAX]
	//  if rolled, returns true.
	template<typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC_CONVERTIBLE(R, T)> _CUTIL_FUNC_STATIC
	inline bool decrease_rolling(T& var, R min, R max, int dec = 1) noexcept {
		assert(min < max && cutil::num_in_interval(var, min, max));
		if((var - static_cast<T>(dec)) >= min){
			var -= static_cast<T>(dec);
			return false;
		}
		var = max;
		return true;
	}
	
	//* increase the value of variable, and prevent overflowing,
	// if it is near to be overflowed, it will not increased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)> _CUTIL_FUNC_STATIC
	inline bool increase_no_overflow(T& var, int inc = 1) noexcept {
		assert(inc > 0);
		return (static_cast<T>(var + inc) > var) ? (var += inc, false) : (true);
	}
	//* decrease the value of variable, and prevent underflowing,
	// if it is near to be underflowed, it will not decreased any more and return true.
	template<typename T, _CUTIL_CONCEPT_ARITHMETIC(T)> _CUTIL_FUNC_STATIC
	inline bool decrease_no_underflow(T& var, int dec = 1) noexcept {
		assert(dec > 0);
		return (static_cast<T>(var - dec) < var) ? (var -= dec, false) : (true);
	}
/*
	int8_t num = 0;
	cutil::math::increase_under_limit(num, 5, 1); // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::increase_under_limit(num, 5);    // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::decrease_above_limit(num, 0, 1); // step:1, result: 1 2 3 4 5 5 5 5 5 5 5 5
	cutil::math::decrease_above_limit(num, 0);    // step:1, result: 5 4 3 2 1 0 0 0 0 0 0 0

	cutil::math::increase_rolling(num, 0, 5, 1);  // step:1, result: 1 2 3 4 5 0 1 2 3 4 5 0
	cutil::math::increase_rolling(num, 0, 5);     // step:1, result: 1 2 3 4 5 0 1 2 3 4 5 0
	cutil::math::decrease_rolling(num, 0, 5, 1);  // step:1, result: 5 4 3 2 1 0 5 4 3 2 1 0
	cutil::math::decrease_rolling(num, 0, 5);     // step:1, result: 5 4 3 2 1 0 5 4 3 2 1 0
	
	num = 124;
	bool isOverflowed  = cutil::math::increase_no_overflow(num, 1); // prevent overflowing, 125 126 127 127 127 127, returns true if near to overflow
	bool isOverflowed2 = cutil::math::increase_no_overflow(num);    // equivalent
	num = -125;
	bool isOverflowed3 = cutil::math::decrease_no_underflow(num, 1); // prevent underflowing, -126 -127 -128 -128 -128 -128, returns true if near to overflow
	bool isOverflowed4 = cutil::math::decrease_no_underflow(num);    // equivalent

*/

	//* constexpr abs() of an number, overloaded for unsigned integer types
	template<typename T, _CUTIL_CONCEPT_SIGNED_OR_FLOAT(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T abs(T num) noexcept { // for signed intergers and `float`, `double`, `long double`
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::abs(num); // not constexpr
		}
	#endif // C++20
		return (num < 0) ? -num : num; // in C++14/17/20, std::abs() is not constexpr
	}
	template<typename U, _CUTIL_CONCEPT_UNSIGNED(U)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline U constexpr abs(U num) noexcept { // for `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `size_t`
		return num;
	}
	
	//* constexpr isInf()
	// there are CPU instructions to check for infinity, but they are not portable
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isinf(F num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::isinf(num); // not constexpr
		}
	#endif // C++20
		return (num == std::numeric_limits<F>::infinity() || num == -std::numeric_limits<F>::infinity());
	}
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isinf(I) noexcept {
		return false;
	}
	
	//* constexpr isNaN()
	// there are CPU instructions to check for NaN, but they are not portable
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isnan(F num) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		if (!std::is_constant_evaluated()){
			return std::isnan(num); // not constexpr
		}
	#endif // C++20
		return (num != num); // NaN is not equal to anything, including itself
	}
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool isnan(I num) noexcept {
		return false;
	}
	
	//* get gcd (greatest common divisor)
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I gcd(I a, I b) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::gcd(a, b);
	#else
		if(b == 0){
			return cutil::math::abs(a);
		}
		if(a == 0){
			return cutil::math::abs(b);
		}
		return cutil::math::gcd(b, a % b);
	#endif
	}
	
	//* get lcm (least common multiple)
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I lcm(I a, I b) noexcept {
	#ifdef CUTIL_CPP17_SUPPORTED
		return std::lcm(a, b);
	#else
		if(a == 0 || b == 0) {
			return 0;
		}
		return cutil::math::abs(a * b / cutil::math::gcd(a, b));
	#endif
	}
	
	//* get midpoint of two integer or floating point numbers
	// if a and b are integers, the result is also truncated to an integer
	// eg. midpoint(6, 9) -> 7; midpoint(6.0, 9.0) -> 7.5
	template<typename I, _CUTIL_CONCEPT_INTEGRAL(I)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr I midpoint(I a, I b) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		using uint_t = std::make_unsigned_t<I>;
		int k = 1;
		if(a < b) {
			return a + static_cast<I>(static_cast<uint_t>(b - a) / 2);
		}else{
			return b - static_cast<I>(static_cast<uint_t>(a - b) / 2);
		}
	#endif
	}
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F midpoint(F a, F b) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		constexpr auto max = std::numeric_limits<F>::max() / 2;
		constexpr auto min = std::numeric_limits<F>::min() * 2;
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return std::numeric_limits<F>::quiet_NaN(); // NaN, return NaN
		}else if(cutil::math::abs(a) < max && cutil::math::abs(b) < max) { // normal case
			return ((a + b) / 2);
		}else if(cutil::math::abs(a) < min){ // a < min and b >= max
			return (a + (b / 2));
		}else if(cutil::math::abs(b) < min){ // b < min and a >= max
			return ((a / 2) + b);
		}else{ // a, b >= max
			return ((a / 2) + (b / 2));
		}
	#endif
	}
	//* get midpoint of two pointers
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T* midpoint(T* a, T* b) noexcept { // for pointers
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::midpoint(a, b);
	#else
		return (a + (b - a) / 2);
	#endif
	}
	

} // namespace math

namespace internal{
	template<typename T>
	struct float_to_int;
	template<>
	struct float_to_int<float> {
		using type = int32_t;
	};
	template<>
	struct float_to_int<double> {
		using type = int64_t;
	};
	
	struct long_double_8_bytes {};
	struct long_double_16_bytes {};
	using long_double_tag = std::conditional_t<sizeof(long double) == 8, long_double_8_bytes, long_double_16_bytes>;
	
	template<typename T, _CUTIL_CONCEPT_FLOAT_WITHOUT_LONGDOUBLE(T)> _CUTIL_FUNC_STATIC _CUTIL_CONSTEXPR_CPP20
	inline bool fequal_ulp_impl(T a, T b, int32_t maxUlpDiff) noexcept {
		using intType_t = typename cutil::internal::float_to_int<std::remove_cv_t<T>>::type;
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return false; // NaN is not equal to anything, including itself
		}
		if(cutil::math::isinf(a) || cutil::math::isinf(b)) {
			return (a == b); // +inf == +inf, -inf == -inf, but +inf != -inf, inf != non-inf
		}
		intType_t intA;
		intType_t intB;
	#ifdef CUTIL_CPP20_SUPPORTED
		intA = std::bit_cast<intType_t>(a);
		intB = std::bit_cast<intType_t>(b);
	#else // C++14/17, not constexpr
		memcpy(&intA, &a, sizeof(intType_t));
		memcpy(&intB, &b, sizeof(intType_t));
		// intA = *reinterpret_cast<volatile intType_t*>(&intA); // UB
		// intB = *reinterpret_cast<volatile intType_t*>(&intB); // UB
	#endif
		if((intA < 0) != (intB < 0)) {
			// return (intA == intB); // one is negative, the other is positive
			return false;
		}
		intType_t diff = cutil::math::abs(intA - intB);
		return (diff <= cutil::math::abs(maxUlpDiff)); // check if the difference is within the allowed ULP (Units in the Last Place)
	}
	// in windows MSVC/MinGW, long double is 8-bytes, equals to double
	inline _CUTIL_CONSTEXPR_CPP20 _CUTIL_FUNC_STATIC
	bool fequal_ulp_impl(long double a, long double b, int32_t maxUlpDiff, long_double_8_bytes) noexcept {
		return cutil::internal::fequal_ulp_impl<double>(static_cast<double>(a), static_cast<double>(b), maxUlpDiff);
	}
	// in linux, long double is 16-bytes
	inline _CUTIL_FUNC_STATIC
	bool fequal_ulp_impl(long double a, long double b, int32_t maxUlpDiff, long_double_16_bytes) noexcept {
		static_assert(sizeof(long double) <= 16, "");
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return false; // NaN is not equal to anything, including itself
		}
		if(cutil::math::isinf(a) || cutil::math::isinf(b)) {
			return (a == b); // +inf == +inf, -inf == -inf, but +inf != -inf, inf != non-inf
		}
		
		constexpr size_t size = 16;
		std::array<uint64_t, 2> intA {};
		std::array<uint64_t, 2> intB {};
		memcpy(intA.data(), &a, size);
		memcpy(intB.data(), &b, size);
	#if defined(CUTIL_ENDIAN_LITTLE)
		constexpr size_t mantissa_idx {0}; // little-endian
		constexpr size_t exponent_idx {1};
	#elif defined(CUTIL_ENDIAN_BIG)
		constexpr size_t mantissa_idx {1}; // big-endian
		constexpr size_t exponent_idx {0};
	#else
		static_assert(false, "Unknown CPU endianness");
	#endif
		// little-endian
		if(intA[exponent_idx]  != intB[exponent_idx]) {
			return false;
		}
		int64_t diff = cutil::math::abs(static_cast<int64_t>(intA[mantissa_idx]) - static_cast<int64_t>(intB[mantissa_idx]));
		return (diff <= cutil::math::abs(maxUlpDiff));
		
	}
	
	
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool fequal_eps_impl(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) noexcept {
		if(cutil::math::isnan(a) || cutil::math::isnan(b)) {
			return false; // NaN is not equal to anything, including itself
		}
		if(cutil::math::isinf(a) || cutil::math::isinf(b)) {
			return (a == b); // +inf == +inf, -inf == -inf, but +inf != -inf, inf != non-inf
		}
		return (cutil::math::abs(a - b) <= cutil::math::abs(epsilon)); // overloaded abs() for floating number in <cstdlib>
	}
	
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr T lerp_impl(T a, T b, T t) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::lerp((a), (b), t);
	#else
		constexpr T one = static_cast<T>(1);
		constexpr T zero = static_cast<T>(0);
		if(cutil::math::isnan(a) || cutil::math::isnan(b) || cutil::math::isnan(t)) {
			return std::numeric_limits<T>::quiet_NaN(); // NaN, return NaN
		}else if((a <= zero && b >= zero) || (a >= zero && b <= zero)){
			return ((t * b) + ((one - t) * a));
		}else if(t == one){
			return b;
		}
		const T x = (a + (t * (b - a))); // calculate interpolation value
		if((t > one) == (b > a)){
			return std::max(b, x); // if t > 1, return b if x > b, else return x
		}else{
			return std::min(b, x); // if t < 1, return b if x < b, else return x
		}
	#endif
	}
	
	template <typename T, typename R = T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow_impl(const T base, const size_t exp) noexcept { // `base` should != 0
		if(exp == 0){
			return static_cast<R>(1);
		}
		if(exp == 1){
			return static_cast<R>(base);
		}
		if(exp == 2){
			return static_cast<R>(base * base);
		}
		if(exp == 3){
			return static_cast<R>(base * base * base);
		}
		int tmp = cutil::internal::pow_impl(base, exp/2);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}
	
#ifdef CUTIL_CPP17_SUPPORTED
	template <const size_t exp, typename T, typename R = T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow_impl(const T base) noexcept { // `base` should != 0
		if constexpr (exp == 0) {
			return static_cast<R>(1);
		}else if constexpr (exp == 1) {
			return static_cast<R>(base);
		}else if constexpr (exp == 2) {
			return static_cast<R>(base * base);
		}else if constexpr (exp == 3) {
			return static_cast<R>(base * base * base);
		}
		R tmp = cutil::internal::pow_impl<exp / 2, T, R>(base);
		if (exp % 2 == 0){
			return static_cast<R>(tmp * tmp);
		}else{
			return static_cast<R>(base * tmp * tmp);
		}
	}
#else // C++14
	
#endif // C++17
	
	
	template <typename T, typename U, _CUTIL_CONCEPT_SIGNED(T), _CUTIL_CONCEPT_SIGNED(U)>
	constexpr inline bool cmp_equal_impl(T t, U u) noexcept {
		return (t == u);
	}
	template <typename T, typename U, _CUTIL_CONCEPT_UNSIGNED(T), _CUTIL_CONCEPT_UNSIGNED(U)>
	constexpr inline bool cmp_equal_impl(T t, U u) noexcept {
		return (t == u);
	}
	template <typename T, typename U, _CUTIL_CONCEPT_SIGNED(T), _CUTIL_CONCEPT_UNSIGNED(U)>
	constexpr inline bool cmp_equal_impl(T t, U u) noexcept {
		return ((t >= 0) && (static_cast<std::make_unsigned_t<T>>(t) == u));
	}
	template <typename T, typename U, _CUTIL_CONCEPT_UNSIGNED(T), _CUTIL_CONCEPT_SIGNED(U)>
	constexpr inline bool cmp_equal_impl(T t, U u) noexcept {
		return ((u >= 0) && (t == static_cast<std::make_signed_t<U>>(u)));
	}

	template <typename T, typename U, _CUTIL_CONCEPT_SIGNED(T), _CUTIL_CONCEPT_SIGNED(U)>
	constexpr inline bool cmp_less_impl(T t, U u) noexcept {
		return (t < u);
	}
	template <typename T, typename U, _CUTIL_CONCEPT_UNSIGNED(T), _CUTIL_CONCEPT_UNSIGNED(U)>
	constexpr inline bool cmp_less_impl(T t, U u) noexcept {
		return (t < u);
	}
	template <typename T, typename U, _CUTIL_CONCEPT_SIGNED(T), _CUTIL_CONCEPT_UNSIGNED(U)>
	constexpr inline bool cmp_less_impl(T t, U u) noexcept {
		return (t < 0 || (static_cast<std::make_unsigned_t<T>>(t) < u));
	}
	template <typename T, typename U, _CUTIL_CONCEPT_UNSIGNED(T), _CUTIL_CONCEPT_SIGNED(U)>
	constexpr inline bool cmp_less_impl(T t, U u) noexcept {
		return (u >= 0 && (t < static_cast<std::make_unsigned_t<U>>(u)));
	}
	
	template <typename R, typename T, _CUTIL_CONCEPT_SIGNED(R), _CUTIL_CONCEPT_SIGNED(T)>
	constexpr inline bool in_range(T t) noexcept {
		return (t >= std::numeric_limits<R>::min() && t <= std::numeric_limits<R>::max());
	}
	template <typename R, typename T, _CUTIL_CONCEPT_UNSIGNED(R), _CUTIL_CONCEPT_UNSIGNED(T)>
	constexpr inline bool in_range(T t) noexcept {
		return (t <= std::numeric_limits<R>::max());
	}
	template <typename R, typename T, _CUTIL_CONCEPT_SIGNED(R), _CUTIL_CONCEPT_UNSIGNED(T)>
	constexpr inline bool in_range(T t) noexcept {
		return (t <= std::make_unsigned_t<R>(std::numeric_limits<R>::max()));
	}
	template <typename R, typename T, _CUTIL_CONCEPT_UNSIGNED(R), _CUTIL_CONCEPT_SIGNED(T)>
	constexpr inline bool in_range(T t) noexcept {
		return (t >= 0 && std::make_unsigned_t<T>(t) <= std::numeric_limits<R>::max());
	}
	
} // namespace internal


inline namespace math { // inline
	//* power function with unsigned integer exponent
	//  int ret = cutil::pow(2, 3); // 2^3 = 8
	//  size_t ret = cutil::pow<int, size_t>(2, 3); // return as size_t
	//  int ret = cutil::pow<3>(2); // 2^3 = 8, >=C++17
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	//  specially, pow(3, 0) == 1, pow(0, 0) == 1, pow(0, 3) == 0
	template <typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base, const size_t exp) noexcept {
		if(base == static_cast<T>(0)) {
			if(exp > 0){
				return static_cast<R>(0); // 0^exp = 0 for exp > 0
			}else{ // exp == 0, 0^0 is usually defined as 1
				return static_cast<R>(1); // 0^0 is usually defined as 1
			}
		}
		return cutil::internal::pow_impl<T, R>(base, exp); // call the implementation
	}
	
	//* factorial function
	//  int ret = cutil::factorial(3); // 3! = 6
	//  size_t ret = cutil::factorial<int, size_t>(3); // return as size_t
	template <typename T, typename R = T, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial(const T base) noexcept {
		assert(cutil::math::num_in_interval(base, 0, 40) && "`base` should be in [0, 40]");
		if (base <= 1) {
			return static_cast<R>(1);
		}else if(base == 2){
			return static_cast<R>(2);
		}else if(base == 3){
			return static_cast<R>(6);
		}
		R result = base;
		for(T i = (base - 1); i > 1; --i){
			result *= i;
		}
		return result;
	}
	
#ifdef CUTIL_CPP17_SUPPORTED
	//* power function with unsigned integer exponent (C++17)
	//  int ret = cutil::pow<3>(2); // 2^3 = 8, >=C++17
	//  size_t ret = cutil::pow<3, int, size_t>(2); // return as size_t
	//  from https://stackoverflow.com/questions/1505675/power-of-an-integer-in-c
	//  specially, pow<0>(3) == 1, pow<0>(0) == 1, pow<3>(0) == 0
	template <const size_t exp, typename T, typename R = T, _CUTIL_CONCEPT_ARITHMETIC(T), _CUTIL_CONCEPT_ARITHMETIC(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base) noexcept {
		if(base == 0){
			if constexpr (exp > 0) {
				return static_cast<R>(0); // 0^exp = 0 for exp > 0
			}else{ // exp == 0
				return static_cast<R>(1); // 0^0 is usually defined as 1
			}
		}
		return cutil::internal::pow_impl<exp, T, R>(base); // call the implementation
	}
	
	//* factorial function (C++17)
	//  int ret = cutil::factorial<3>(); // 3! = 6
	//  size_t ret = cutil::factorial<3, size_t>(); // return as size_t
	template <const size_t base, typename R = size_t, _CUTIL_CONCEPT_INTEGRAL(R)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial() noexcept {
		if constexpr (base <= 1) {
			return static_cast<R>(1);
		}else if constexpr (base == 2) {
			return static_cast<R>(2);
		}else if constexpr (base == 3) {
			return static_cast<R>(6);
		}else{
			return static_cast<R>(base) * cutil::math::factorial<base - 1, R>();
		}
	}
	
#else // C++14
	template <const size_t exp, typename T, typename R = T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R pow(const T base) noexcept {
		return cutil::math::pow(base, exp);
	}
	
	template <const size_t base, typename R = size_t> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr R factorial() noexcept {
		return cutil::math::factorial<R>(base);
	}
#endif // C++17
	
	//* Compares two floating-point numbers for equality within a specified epsilon.
	//  recommended to compare to zero.
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(float a, float b, float epsilon = std::numeric_limits<float>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(double a, double b, double epsilon = std::numeric_limits<double>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	bool fequal_eps(long double a, long double b, long double epsilon = std::numeric_limits<long double>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, b, epsilon);
	}
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr bool fequal_zero(T a, T epsilon = std::numeric_limits<T>::epsilon()) noexcept {
		return cutil::internal::fequal_eps_impl(a, static_cast<T>(0), epsilon);
	}
	
	//* Compares two floating-point numbers for equality within a specified ULP (Units in the Last Place).
	//  recommended to compare with two non-zero numbers.
	//  not constexpr in C++14/17, but constexpr in C++20
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline _CUTIL_CONSTEXPR_CPP20
	bool fequal_ulp(float a, float b, int32_t maxUlpDiff = 4) {
		return cutil::internal::fequal_ulp_impl(a, b, maxUlpDiff);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline _CUTIL_CONSTEXPR_CPP20
	bool fequal_ulp(double a, double b, int32_t maxUlpDiff = 4) {
		return cutil::internal::fequal_ulp_impl(a, b, maxUlpDiff);
	}
	// long double is 8-bytes in MSVC/MinGW, and 16-bytes in linux.
	// this is not tested for Linux, BE CAREFUL!
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline // not constexpr in linux
	bool fequal_ulp(long double a, long double b, int32_t maxUlpDiff = 4) {
		return cutil::internal::fequal_ulp_impl(a, b, maxUlpDiff, cutil::internal::long_double_tag{});
	}
/*
	bool isEqual4 = cutil::math::fequal_eps(a, b); // (abs(a - b) <= std::numeric_limits<decltype(a)>::epsilon())
	bool isEqual5 = cutil::math::fequal_eps(c, d, 0.0001); // equivalent
	
	bool isEqual6 = cutil::math::fequal_ulp(a, b); // (abs(a - b) <= 4 ULP)
	bool isEqual7 = cutil::math::fequal_ulp(c, d, 2); // equivalent, 2 ULP
*/

	
	//* linear interpolation, (a + (b - a) * t)
	//  t should be in the range [0, 1]. if t = 0, returns a; if t == 1, returns b.
	//  use std::lerp() since C++20
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	float lerp(float a, float b, float t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	double lerp(double a, double b, double t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline constexpr
	long double lerp(long double a, long double b, long double t) noexcept {
		return cutil::internal::lerp_impl(a, b, t);
	}
	

	//* convert degrees to radians, (degree * M_PI / 180.0)
	// `cutil::fequal_eps(cutil::numbers::pi_3, cutil::math::deg2rad(60.0)) == true`
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F deg2rad(F degree) noexcept {
		// no need to check for NaN or inf
		return (degree * cutil::Numbers<F>::pi / static_cast<F>(180.0));
	}
	
	//* convert radians to degrees, (radian * 180.0 / M_PI)
	// `cutil::fequal_eps(60.0, cutil::math::rad2deg(cutil::numbers::pi_3)) == true`
	template<typename F, _CUTIL_CONCEPT_FLOAT(F)> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline constexpr F rad2deg(F radian) noexcept {
		// no need to check for NaN or inf
		return (radian * static_cast<F>(180.0) / cutil::Numbers<F>::pi);
	}
	

	//* safe integer comparison
	// Unlike builtin comparison operators, negative signed integers always compare
	// less than (and not equal to) unsigned integers: the comparison is safe against
	// non-value-preserving integer conversion.
	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_equal(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_equal(t, u);
	#endif // C++20
		return cutil::internal::cmp_equal_impl(t, u);
	}

	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_not_equal(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_not_equal(t, u);
	#endif // C++20
		return !cutil::internal::cmp_equal_impl(t, u);
	}

	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_less(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_less(t, u);
	#endif // C++20
		return cutil::internal::cmp_less_impl(t, u);
	}

	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_less_equal(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_less_equal(t, u);
	#endif // C++20
		return !cutil::internal::cmp_less_impl(u, t);
	}

	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_greater(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_greater(t, u);
	#endif // C++20
		return cutil::internal::cmp_less_impl(u, t);
	}

	template<typename T, typename U, _CUTIL_CONCEPT_INTEGRAL(T), _CUTIL_CONCEPT_INTEGRAL(U)> _CUTIL_NODISCARD
	constexpr inline bool cmp_greater_equal(T t, U u) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::cmp_greater_equal(t, u);
	#endif // C++20
		return !cutil::internal::cmp_less_impl(t, u);
	}
	/*
	Instruction:
		bool cmp;
		cmp = cutil::cmp_less(-1, 1U); 			// true
		cmp = cutil::cmp_less_equal(-1, 1u); 	// false
		cmp = cutil::cmp_greater(-1, 1u); 		// false
		cmp = cutil::cmp_not_equal(-1, 0xFFFFFFFFu); // true
		
		// signed-unsigned safe
	*/



	//* check if a value is within the range of a integer type
	template<typename R, typename T, _CUTIL_CONCEPT_INTEGRAL(R), _CUTIL_CONCEPT_INTEGRAL(T)> _CUTIL_NODISCARD
	constexpr inline bool in_range(T t) noexcept {
	#ifdef CUTIL_CPP20_SUPPORTED
		return std::in_range<R>(t);
	#endif // C++20
		return cutil::internal::in_range<R>(t);
	}
	/*
		bool a = cutil::in_range<size_t>(-1); // false
		bool b = cutil::in_range<int>(-1); // true
		bool c = cutil::in_range<unsigned int>(-1); // false
		static_assert(cutil::in_range<size_t>(999), "999 is in range of size_t");
	*/
	
	
	//* get any digit of a decimal number
	//    cutil::get_digit(12345, 0)      == 5; // get the last digit
	//    cutil::get_digit<1>(12345)      == 4; // get the second last digit
	//    cutil::get_digit(12345, 2)      == 3; // get the third last digit
	//    cutil::get_digit(12345, -1)     == 0; // get the first digit after the decimal point
	//    cutil::get_digit(123.456, -1)   == 6; // get the first digit after the decimal point
	//    cutil::get_digit< -2>(123.456)  == 5; // get the second digit after the decimal point
	template<typename T, _CUTIL_CONCEPT_INTEGRAL(T)> _CUTIL_NODISCARD
	constexpr inline uint8_t get_digit(T num, int32_t digit) noexcept {
		if(digit < 0){
			return 0;
		}
		auto abs_num = cutil::math::abs(num);
		return static_cast<uint8_t>((abs_num % cutil::math::pow(10, digit + 1)) / cutil::math::pow(10, digit));
	}
	template<typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD
	constexpr inline uint8_t get_digit(T num, int32_t digit) noexcept {
		if(digit < 0) { // get the digit after the decimal point
			auto decimal_part = static_cast<uint32_t>(cutil::math::abs(num) * cutil::math::pow(10, -digit));
			return static_cast<uint8_t>(decimal_part % 10);
		}else{ // get the digit before the decimal point
			auto integer_part = static_cast<uint32_t>(cutil::math::abs(num));
			return static_cast<uint8_t>((integer_part % cutil::math::pow(10, digit + 1)) / cutil::math::pow(10, digit));
		}
	}
	template<int32_t digit, typename T, _CUTIL_CONCEPT_INTEGRAL(T)> _CUTIL_NODISCARD
	constexpr inline uint8_t get_digit(T num) noexcept {
		static_assert(digit >= 0, "digit should be non-negative for integer numbers");
		auto abs_num = cutil::math::abs(num);
		return static_cast<uint8_t>((abs_num % cutil::math::pow(10, digit + 1)) / cutil::math::pow(10, digit));
	}
	template<int32_t digit, typename T, _CUTIL_CONCEPT_FLOAT(T)> _CUTIL_NODISCARD
	constexpr inline uint8_t get_digit(T num) noexcept {
		auto abs_num = cutil::math::abs(num);
		if _CUTIL_CONSTEXPR_CPP17 (digit < 0) { // get the digit after the decimal point
			auto decimal_part = static_cast<uint32_t>(abs_num * cutil::math::pow(10, -digit));
			return static_cast<uint8_t>(decimal_part % 10);
		}else{ // get the digit before the decimal point
			auto integer_part = static_cast<uint32_t>(abs_num);
			return static_cast<uint8_t>((integer_part % cutil::math::pow(10, digit + 1)) / cutil::math::pow(10, digit));
		}
	}
	
	
	
	
	
} // namespace math


_CUTIL_NAMESPACE_END

#endif /* CUTIL_CPP_MATH_HPP__ */
