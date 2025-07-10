/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
Updated:		9 JUL 2025
  License:		MIT License
* You can include this header in header files.
*/

#ifndef CUTIL_BASE_BASE_H__
#define CUTIL_BASE_BASE_H__

//* warning: do not use macros with name starting with underscore `_` externally.


//* include vital C headers
#ifdef __cplusplus
	#include <cstdio>
	#include <cstdlib>
	#include <cstdint>
	#include <cfloat>
	#include <limits> // for epsilon of float
#else //. !__cplusplus
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>	// uint32_t
	#include <float.h>	// floating-point limits
	#if defined(CUTIL_C99_SUPPORTED) && !defined(CUTIL_C23_SUPPORTED)
		#include <stdbool.h> // bool support since C99, before C23 (became keyword)
	#endif
#endif // __cplusplus


//* get compiler type and version
//  macro `CUTIL_COMPILER_XXX` is not unique
//  if you are using mingw64, it will define both CUTIL_COMPILER_MINGW and CUTIL_COMPILER_MINGW64
#if defined(_MSC_VER)
    #define CUTIL_COMPILER_MSVC					1
    #define CUTIL_COMPILER_MSVC_VERSION  		_MSC_VER // VVRR
    #define CUTIL_COMPILER_MSVC_VERSION_MAJOR	(_MSC_VER / 100)
    #define CUTIL_COMPILER_MSVC_VERSION_MINOR 	(_MSC_VER % 100)
	#if (_MSC_FULL_VER > 99999999) // VVRRPPPP / VVRRPPPPP
    	#define CUTIL_COMPILER_VERSION_PATCH	(_MSC_FULL_VER % 100000) // 194334604
	#else
		#define CUTIL_COMPILER_VERSION_PATCH 	(_MSC_FULL_VER % 10000) // 13103077
	#endif
    #if (_MSC_VER >= 1930) // 193x, 194x
        #define CUTIL_COMPILER_MSVC_2022  1 // Visual Studio 2022
    #elif (_MSC_VER >= 1920)
        #define CUTIL_COMPILER_MSVC_2019  1 // Visual Studio 2019
    #elif (_MSC_VER >= 1910)
        #define CUTIL_COMPILER_MSVC_2017  1 // Visual Studio 2017
    #elif (_MSC_VER >= 1900)
        #define CUTIL_COMPILER_MSVC_2015  1 // Visual Studio 2015
	#elif (_MSC_VER >= 1800)
		#define CUTIL_COMPILER_MSVC_2013  1 // Visual Studio 2013
	#elif (_MSC_VER >= 1700)
		#define CUTIL_COMPILER_MSVC_2012  1 // Visual Studio 2012
	#elif (_MSC_VER >= 1600)
		#define CUTIL_COMPILER_MSVC_2010  1 // Visual Studio 2010
	#elif (_MSC_VER >= 1500)
		#define CUTIL_COMPILER_MSVC_2008  1 // Visual Studio 2008
	#elif (_MSC_VER >= 1400)
		#define CUTIL_COMPILER_MSVC_2005  1 // Visual Studio 2005
	#elif (_MSC_VER >= 1300)
		#define CUTIL_COMPILER_MSVC_2003  1 // Visual Studio .NET 2003
	#elif (_MSC_VER >= 1200)
		#define CUTIL_COMPILER_MSVC_6     1 // Visual Studio 6.0
    #endif
#endif
#if defined(__GNUC__)
    #define CUTIL_COMPILER_GCC					1
	#ifdef __GNUC_PATCHLEVEL__
    	#define CUTIL_COMPILER_GCC_VERSION  	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
		#define CUTIL_COMPILER_GCC_VERSION_PATCH 	__GNUC_PATCHLEVEL__
	#else
		#define CUTIL_COMPILER_GCC_VERSION  	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
	#endif
    #define CUTIL_COMPILER_GCC_VERSION_MAJOR 	__GNUC__
    #define CUTIL_COMPILER_GCC_VERSION_MINOR 	__GNUC_MINOR__
#endif
#if defined(__clang__)
    #define CUTIL_COMPILER_CLANG    			1
    #define CUTIL_COMPILER_CLANG_VERSION  		(__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
    #define CUTIL_COMPILER_CLANG_VERSION_MAJOR __clang_major__
    #define CUTIL_COMPILER_CLANG_VERSION_MINOR __clang_minor__
    #define CUTIL_COMPILER_CLANG_VERSION_PATCH __clang_patchlevel__
#endif
#if defined(__NVCC__) // CUDA compiler
    #define CUTIL_COMPILER_NVCC					1
#endif
#if defined(__MINGW32__) || defined(__MINGW64__)
    #define CUTIL_COMPILER_MINGW    			1
    #if defined(__MINGW64__)
        #define CUTIL_COMPILER_MINGW64  		1
		#define CUTIL_COMPILER_MINGW_VERSION_MAJOR  __MINGW64_VERSION_MAJOR // 11
		#define CUTIL_COMPILER_MINGW_VERSION_MINOR  __MINGW64_VERSION_MINOR // 0
    #else
        #define CUTIL_COMPILER_MINGW32  		1
		#define CUTIL_COMPILER_MINGW_VERSION_MAJOR  __MINGW32_MAJOR_VERSION // 5
		#define CUTIL_COMPILER_MINGW_VERSION_MINOR  __MINGW32_MINOR_VERSION // 1
    #endif
#endif
#if defined(__INTEL_COMPILER) || defined(__ICC)
    #define CUTIL_COMPILER_ICC					1
    #define CUTIL_COMPILER_ICC_VERSION  		__INTEL_COMPILER // VRP
    #define CUTIL_COMPILER_ICC_VERSION_MAJOR 	(__INTEL_COMPILER / 100)
    #define CUTIL_COMPILER_ICC_VERSION_MINOR 	((__INTEL_COMPILER % 100) / 10)
    #define CUTIL_COMPILER_ICC_VERSION_PATCH 	(__INTEL_COMPILER % 10)
#endif
#if defined(__CC_ARM)
    #define CUTIL_COMPILER_ARMCC				1
    #define CUTIL_COMPILER_ARMCC_VERSION  		__ARMCC_VERSION // VRPBBB
	#define CUTIL_COMPILER_ARMCC_VERSION_MAJOR  (__ARMCC_VERSION / 100000)
	#define CUTIL_COMPILER_ARMCC_VERSION_MINOR  ((__ARMCC_VERSION % 100000) / 10000)
	#define CUTIL_COMPILER_ARMCC_VERSION_PATCH  ((__ARMCC_VERSION % 10000) / 1000)
#endif
#if defined(__IAR_SYSTEMS_ICC__)
    #define CUTIL_COMPILER_IAR					1
    #define CUTIL_COMPILER_VERSION				__VER__ // VRR
	#define CUTIL_COMPILER_IAR_VERSION_MAJOR 	(__VER__ / 100)
	#define CUTIL_COMPILER_IAR_VERSION_MINOR 	(__VER__ % 100)
#endif
#if defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define CUTIL_COMPILER_BORLAND				1
	#if defined(__CODEGEARC__)
		#define CUTIL_COMPILER_BORLAND_VERSION  	__CODEGEARC__
	#else
		#define CUTIL_COMPILER_BORLAND_VERSION  	__BORLANDC__
	#endif
#endif
#if defined(__llvm__)
	#define CUTIL_COMPILER_LLVM					1
#endif



//* get CPU architecture
// example:
//  #if(CUTIL_CPU_ARCH_X86_64) // x86-64
//  #if(CUTIL_CPU_ARCH_X86_32 && CUTIL_CPU_ARCH_32BIT) // x86-32
//  #if(CUTIL_CPU_ARCH_ARM && CUTIL_CPU_ARCH_32BIT) // ARMv7, ARMv8-A 32-bit
//  #ifdef(CUTIL_ENDIAN_LITTLE) 	// little-endian
//  #ifdef(CUTIL_ENDIAN_BIG) 		// big-endian
#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
	#define CUTIL_CPU_ARCH_X86				1
	#define CUTIL_CPU_ARCH_X86_64			1
	#define CUTIL_ENDIAN_LITTLE				1
	#define CUTIL_CPU_ARCH_64BIT			1
#elif defined(__i386__) || defined(_M_IX86)
	#define CUTIL_CPU_ARCH_X86				1
	#define CUTIL_CPU_ARCH_X86_32			1
	#define CUTIL_ENDIAN_LITTLE				1
	#define CUTIL_CPU_ARCH_32BIT			1
#elif defined(__aarch64__) || defined(__ARM64__) || defined(_M_ARM64)
	#define CUTIL_CPU_ARCH_ARM				1
	#define CUTIL_CPU_ARCH_ARM_64			1
	#define CUTIL_CPU_ARCH_64BIT			1
	#if defined(__AARCH64EB__)
		#define CUTIL_ENDIAN_BIG			1
	#elif defined(__AARCH64EL__)
		#define CUTIL_ENDIAN_LITTLE			1
	#endif
#elif defined(__arm__) || defined(_M_ARM)
	#define CUTIL_CPU_ARCH_ARM				1
	#define CUTIL_CPU_ARCH_ARM_32        	1
	#define CUTIL_CPU_ARCH_32BIT			1
	#if defined(__ARMEB__) || defined(__THUMBEB__)
		#define CUTIL_ENDIAN_BIG			1
	#elif defined(__ARMEL__) || defined(__THUMBEL__)
		#define CUTIL_ENDIAN_LITTLE			1
	#endif
#elif defined(__EMSCRIPTEN__) || defined(__wasm__)
	#define CUTIL_CPU_ARCH_WASM				1
	#define CUTIL_ENDIAN_LITTLE				1
	#if defined(__wasm64__)
		#define CUTIL_CPU_ARCH_WASM_64		1
		#define CUTIL_CPU_ARCH_64BIT		1
	#else
		#define CUTIL_CPU_ARCH_WASM_32		1
		#define CUTIL_CPU_ARCH_32BIT		1
	#endif
#else
	#define CUTIL_CPU_ARCH_UNKNOWN			1
	#warning "Unknown CPU Architecture"
#endif
#if !defined(CUTIL_ENDIAN_LITTLE) && !defined(CUTIL_ENDIAN_BIG)
	#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
		#define CUTIL_ENDIAN_LITTLE			1
	#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
		#define CUTIL_ENDIAN_BIG			1
	#else
		#define CUTIL_ENDIAN_UNKNOWN		1
		#warning "Unknown CPU Endianness"
	#endif
#endif


//* Get OS Type
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
    #define CUTIL_OS_WINDOWS			1
    #if defined(_WIN64)
        #define CUTIL_OS_WINDOWS_64		1
    #else // _WIN32 is defined both for 32-bit and 64-bit Windows
        #define CUTIL_OS_WINDOWS_32		1
    #endif
	#if defined(__CYGWIN__)
    	#define CUTIL_OS_CYGWIN				1
	#endif
#elif defined(__ANDROID__)
    #define CUTIL_OS_ANDROID			1 	// `CUTIL_OS_LINUX` is also defined
	#define CUTIL_OS_LINUX				1
#elif defined(__linux__) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__)
	#define CUTIL_OS_LINUX				1
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
	#define CUTIL_OS_APPLE				1
    #if (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE) \
	|| (defined(TARGET_OS_IPHONE_SIMULATOR) && TARGET_OS_IPHONE_SIMULATOR)
        #define CUTIL_OS_IOS			1
	#elif defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
		#define CUTIL_OS_WATCHOS		1
	#elif defined(TARGET_OS_TV) && TARGET_OS_TV
		#define CUTIL_OS_TVOS			1
	#elif defined(TARGET_OS_VISION) && TARGET_OS_VISION
		#define CUTIL_OS_VISIONOS		1
    #elif defined(TARGET_OS_MAC) && TARGET_OS_MAC
        #define CUTIL_OS_MACOS			1
    #endif
#elif defined(__harmony__) || defined(_HARMONYOS) || defined(HARMONYOS)
	#define CUTIL_OS_HARMONYOS			1
#endif
#if !defined(CUTIL_CPU_ARCH_64BIT) && !defined(CUTIL_CPU_ARCH_32BIT)
	#if defined(__LP64__) || defined(_LP64) || defined(_WIN64) || defined(__x86_64__) \
	|| defined(__aarch64__) || defined(__powerpc64__) || defined(__mips64) || defined(__wasm64__)
		#define CUTIL_CPU_ARCH_64BIT			1
	#else
		#define CUTIL_CPU_ARCH_32BIT			1
	#endif
#endif

//* get CPU pointer size
#define CUTIL_PTR_SIZE  	sizeof(void*) // pointer size, 4 or 8 bytes


//* get C++ language standard version
// in MSVC compiler, `__cplusplus` always equals to `199711L` without compiler argument `/Zc:__cplusplus`,
//    but `_MSVC_LANG`(Prior to VS2015) equals to cpp standard version
#ifdef __cplusplus
	#ifdef _MSVC_LANG // example: #if CUTIL_CPP_LANG >= 201103L
		#define CUTIL_CPP_LANG			_MSVC_LANG	// for MSVC
	#else //. !defined _MSVC_LANG
		#define CUTIL_CPP_LANG			__cplusplus // for GCC, Clang (also MSVC with the copiler argument `/Zc:__cplusplus`)
	#endif // _MSVC_LANG
#endif // __cplusplus
#if (CUTIL_CPP_LANG >= 199711L) // >= C++98
	#define CUTIL_CPP98_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201103L) // >= C++11
	#define CUTIL_CPP11_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201402L) // >= C++14
	#define CUTIL_CPP14_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 201703L) // >= C++17
	#define CUTIL_CPP17_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 202002L) // >= C++20
	#define CUTIL_CPP20_SUPPORTED	1
#endif
#if (CUTIL_CPP_LANG >= 202302L) // >= C++23
	#define CUTIL_CPP23_SUPPORTED	1
#endif
/* example:
	#if CUTIL_CPP_LANG >= 199711L	// C++98
	#if CUTIL_CPP_LANG >= 201103L	// C++11
	#if CUTIL_CPP_LANG >= 201402L	// C++14
	#if CUTIL_CPP_LANG >= 201703L	// C++17
	#if CUTIL_CPP_LANG >= 202002L	// C++20
	#if CUTIL_CPP_LANG >= 202302L	// C++23 (temporary not supported)
*/


//* get C language standard version
#ifndef __cplusplus
	#ifdef __STDC_VERSION__
		#define CUTIL_C_LANG	__STDC_VERSION__
	#else // C89 didn't define this macro
		#define CUTIL_C_LANG	198912L
	#endif
#endif //. ! __cplusplus
#if (CUTIL_C_LANG >= 198912L) // >= C89
	#define CUTIL_C89_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 199901L) // >= C99
	#define CUTIL_C99_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 201112L) // >= C11
	#define CUTIL_C11_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 201710L) // >= C17
	#define CUTIL_C17_SUPPORTED	1
#endif
#if (CUTIL_C_LANG >= 202311L) // >= C23
	#define CUTIL_C23_SUPPORTED	1
#endif
/* example:
	#if CUTIL_C_LANG >= 198912L	// C89
	#if CUTIL_C_LANG >= 199901L	// C99
	#if CUTIL_C_LANG >= 201112L	// C11
	#if CUTIL_C_LANG >= 201710L	// C17
	#if CUTIL_C_LANG >= 202311L	// C23
*/



//* ==== Environment Check, `> C99/C++11` with `##__VA_ARGS__` extension (available in MSVC(>VS2015 U3)/GCC/Clang)
#if (!defined(__cplusplus)) && !defined(CUTIL_C99_SUPPORTED)
	#error This Header DO NOT SUPPORTS C89! - >=C99 or C++ Required.
#elif defined(__cplusplus) && !defined(CUTIL_CPP14_SUPPORTED)
	#error This Header DO NOT SUPPORTS C++98! - >=C++14 Required.
#else
	// available
#endif




//* detect whether build mode is in Debug or Release
#if (!defined(NDEBUG)) || defined(_DEBUG)
	#define CUTIL_DEBUG_BUILD 	 1 	// Debug
#else
	#define CUTIL_DEBUG_BUILD 	 0 	// Release RelWithDebInfo MinSizeRel
#endif


//* C++ namespace
#ifndef CUTIL_PARAM_USE_SHORTEN_NAMESPACE
	#define CUTIL_PARAM_USE_SHORTEN_NAMESPACE 	1	//* use shorter namespace `cu::` instead of `cutil::`
#endif // CUTIL_PARAM_USE_SHORTEN_NAMESPACE
#ifdef __cplusplus // C++
	#define _CUTIL_NAMESPACE						cutil
	#define _CUTIL_NAMESPACE_SHORT					cu
	#define _CUTIL_NAMESPACE_BEGIN					namespace _CUTIL_NAMESPACE {
	#define _CUTIL_NAMESPACE_END					}
	#define _CUTIL_NAMESPACE_BEGIN_NAME(_NAME)		namespace _NAME {
	#define _CUTIL_NAMESPACE_END_NAME(_NAME)		}
	#if CUTIL_PARAM_USE_SHORTEN_NAMESPACE == 1
		_CUTIL_NAMESPACE_BEGIN
		_CUTIL_NAMESPACE_END
		namespace _CUTIL_NAMESPACE_SHORT = _CUTIL_NAMESPACE;
	#endif // CUTIL_PARAM_USE_SHORTEN_NAMESPACE
#else  // C
	#define _CUTIL_NAMESPACE_ALIAS
	#define _CUTIL_NAMESPACE_BEGIN
	#define _CUTIL_NAMESPACE_END
	#define _CUTIL_NAMESPACE_BEGIN_NAME(_NAME)
	#define _CUTIL_NAMESPACE_END_NAME(_NAME)
#endif // defined __cplusplus


//* constexpr function
#ifdef CUTIL_CPP17_SUPPORTED // C++17
	#define _CUTIL_CONSTEXPR_CPP17	constexpr
#else
	#define _CUTIL_CONSTEXPR_CPP17
#endif
#ifdef CUTIL_CPP20_SUPPORTED // C++20
	#define _CUTIL_CONSTEXPR_CPP20	constexpr
#else
	#define _CUTIL_CONSTEXPR_CPP20
#endif


//* attributes
#ifdef CUTIL_CPP17_SUPPORTED // C++17
	#define _CUTIL_NODISCARD	[[nodiscard]]
	#define _CUTIL_MAYBE_UNUSED	[[maybe_unused]]
#else
	#define _CUTIL_NODISCARD
	#define _CUTIL_MAYBE_UNUSED
#endif

//* likely and unlikely
// 目前实现尚未测试，可能存在问题
// current implementation is not tested, may have issues
#ifdef CUTIL_CPP20_SUPPORTED // C++20
	#define _CUTIL_IF_LIKELY(_EXPR)		(_EXPR) [[likely]]
	#define _CUTIL_IF_UNLIKELY(_EXPR)	(_EXPR) [[unlikely]]
	#define _CUTIL_LIKELY				[[likely]]
	#define _CUTIL_UNLIKELY				[[unlikely]]
#elif defined(CUTIL_COMPILER_GCC) || defined(CUTIL_COMPILER_CLANG) // GCC/Clang
	#define _CUTIL_IF_LIKELY(_EXPR)		__builtin_expect(!!(_EXPR), 1)
	#define _CUTIL_IF_UNLIKELY(_EXPR)	__builtin_expect(!!(_EXPR), 0)
	#define _CUTIL_LIKELY
	#define _CUTIL_UNLIKELY
#else	// MSVC
	#define _CUTIL_IF_LIKELY			(_EXPR)
	#define _CUTIL_IF_UNLIKELY			(_EXPR)
	#define _CUTIL_LIKELY
	#define _CUTIL_UNLIKELY
#endif // C++20

//* `::` for C++
#ifdef __cplusplus
	#define _CUTIL_DBL_COLON ::
#else // C
	#define _CUTIL_DBL_COLON
#endif // __cplusplus

//* add `static` decoration for inline functions
#ifndef CUTIL_FORCE_FUNCTION_STATIC
	#define CUTIL_FORCE_FUNCTION_STATIC 0	// default is 0
#endif // CUTIL_FORCE_FUNCTION_STATIC
#ifdef __cplusplus // C++
	#if (CUTIL_FORCE_FUNCTION_STATIC == 1)
		#define _CUTIL_FUNC_STATIC static
	#else
		#define _CUTIL_FUNC_STATIC
	#endif
#else // C
	#if (CUTIL_FORCE_FUNCTION_STATIC == 1)
		#define _CUTIL_FUNC_STATIC static
	#else
		#define _CUTIL_FUNC_STATIC
	#endif
#endif // __cplusplus


//* `__FUNCTION__`(not standard, but supported by MSVC/GCC/Clang) or `__func__`(C99/C++11)
#if defined(_MSC_VER) || defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER) \
|| defined(__CUDA_ARCH__) || defined(__CC_ARM)
	#define _CUTIL_FUNC_NAME		__FUNCTION__
#else
	#define _CUTIL_FUNC_NAME		__func__
#endif


//* get decayed type of variable, only for GNU C, C23, C++11
#ifndef __cplusplus // C
	#if defined(__GNUC__) || defined(CUTIL_C23_SUPPORTED)
		#define CUTIL_TYPEOF(_VAR)	typeof(_VAR)	// only for GNU C, and C23.
	#endif
#else // C++		// C++11
	#ifdef CUTIL_CPP11_SUPPORTED 	//* >= C++11
		#define CUTIL_TYPEOF(_VAR)	std::decay<decltype(_VAR)>::type
		// int& -> int; const int -> int; const int* const -> const int*; int[] -> int*;
	#endif
#endif //. ! __cplusplus

// force use `NOMINMAX` for Windows
#if defined(__cplusplus) && defined(CUTIL_OS_WINDOWS) && !defined(NOMINMAX)
	#define NOMINMAX 	// before `#include <windows.h>`
	#ifdef max
		#undef max  	// after `#include <windows.h>`
	#endif
	#ifdef min
		#undef min
	#endif
#endif

//* check if headers are included
#if defined(__cplusplus) && defined(FMT_VERSION)
	#define CUTIL_FMT_INCLUDED		1
#endif
#if (CUTIL_OS_WINDOWS == 1) && (defined(_WINDOWS_) || defined(WINAPI))
	#define CUTIL_WINAPI_INCLUDED	1
#endif


//* check if the literal encoding is UTF-8
#ifndef CUTIL_FORCE_UTF8
	#define CUTIL_FORCE_UTF8	1	// default is 0, not force UTF-8
#endif // CUTIL_FORCE_UTF8
#ifdef __cplusplus
	_CUTIL_NAMESPACE_BEGIN
		enum {
			is_utf8_enabled = ("\u00A7"[1] == '\xA7')
		};
	_CUTIL_NAMESPACE_END
	#if(CUTIL_FORCE_UTF8 == 1)
		static_assert(cutil::is_utf8_enabled
			, "UTF-8 encoding is not enabled. Please add `/utf-8` to compiler options if you are using MSVC."
		);
	#endif // CUTIL_FORCE_UTF8
#endif

//* inline variable
#ifdef CUTIL_CPP17_SUPPORTED // C++17
	#define _CUTIL_INLINE_CPP17	inline
#else
	#define _CUTIL_INLINE_CPP17
#endif



//===================== Basic Macros =========================
#define CUTIL_EMPTY()										// empty macro function
#define CUTIL_DEFAULT										// empty macro
// #define CUTIL_DEFER(_x)			_x CUTIL_EMPTY
#define CUTIL_EXPAND(...)			__VA_ARGS__ 			// expand `__VA_ARGS__` in MSVC without `/Zc:preprocessor`
#define CUTIL_SELF(_x)				_x						// expand
#define CUTIL_ZERO()				0						// do not delete `()`
#define CUTIL_COMMA					,						// a comma that can avoid recognizing as seperator of arguments
#define CUTIL_CAT_IMPL(_1, _2)		_1 ## _2 				// do not merge with `_CUTIL_CAT_2()`
#define CUTIL_CAT(_1, _2)			CUTIL_CAT_IMPL(_1, _2) 	// for enable unwrapping after `##` concatenation


#define _CUTIL_GET_1ST_ARG(_1, ...)		_1
#define _CUTIL_CHK_1ST_ARG(...)			CUTIL_EXPAND(_CUTIL_GET_1ST_ARG(__VA_ARGS__, 0)) // if 1st param dosen't exist, returns 0
#define _CUTIL_GET_2ND_ARG(_1, _2, ...)	_2
#define _CUTIL_CHK_2ND_ARG(...)			CUTIL_EXPAND(_CUTIL_GET_2ND_ARG(__VA_ARGS__, 0, 0)) // if 2nd param dosen't exist, returns 0
#define _CUTIL_GET_63TH_ARG(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, \
							A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,_63,...)  _63


// #define _CUTIL_PARAMS_SINCE_2ND(_1, ...)	 CUTIL_EXPAND(__VA_ARGS__) // retrive all params since 2nd, and drop 1st param
// #define _CUTIL_PARAMS_SINCE_3RD(_1, _2, ...) CUTIL_EXPAND(__VA_ARGS__)


//* string conversion support
#define CUTIL_STR(_1)				#_1
#define CUTIL_LSTR(_1)				CUTIL_CAT_IMPL(L, #_1)	// wchar_t
#define CUTIL_U8STR(_1)				CUTIL_CAT_IMPL(u8, #_1) 	// C++17, char8_t
#define CUTIL_U16STR(_1)			CUTIL_CAT_IMPL(u, #_1) 	// C++11, char16_t
#define CUTIL_U32STR(_1)			CUTIL_CAT_IMPL(U, #_1) 	// C++11, char32_t


//* BOOL statement
#define CUTIL_NOT(_x)				_CUTIL_CHK_2ND_ARG(CUTIL_CAT(_CUTIL_NOT_, _x))
#define _CUTIL_NOT_0				~, 1
#define _CUTIL_NOT_false			~, 1
#define _CUTIL_NOT_FALSE			~, 1
#define _CUTIL_NOT_nullptr			~, 1
#define _CUTIL_NOT_NULL				~, 1
#define _CUTIL_NOT_00				~, 1
#define _CUTIL_NOT_000				~, 1
#define _CUTIL_NOT_0000				~, 1
#define _CUTIL_NOT_00000			~, 1
#define _CUTIL_NOT_000000			~, 1
#define _CUTIL_NOT_0000000			~, 1
#define _CUTIL_NOT_00000000			~, 1
#define _CUTIL_NOT_0b0				~, 1
#define _CUTIL_NOT_0b00				~, 1
#define _CUTIL_NOT_0b000			~, 1
#define _CUTIL_NOT_0b0000			~, 1
#define _CUTIL_NOT_0b00000			~, 1
#define _CUTIL_NOT_0b000000			~, 1
#define _CUTIL_NOT_0b0000000		~, 1
#define _CUTIL_NOT_0b00000000		~, 1
#define _CUTIL_NOT_0x0				~, 1
#define _CUTIL_NOT_0x00				~, 1
#define _CUTIL_NOT_0x000			~, 1
#define _CUTIL_NOT_0x0000			~, 1
#define _CUTIL_NOT_0x00000			~, 1
#define _CUTIL_NOT_0x000000			~, 1
#define _CUTIL_NOT_0x0000000		~, 1
#define _CUTIL_NOT_0x00000000		~, 1


#define CUTIL_BOOL(_x)				CUTIL_NOT(CUTIL_NOT(_x))

#define CUTIL_OR(_x, _y)			CUTIL_CAT(_CUTIL_OR_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_OR_0(_x)				_x
#define _CUTIL_OR_1(_x)				1

#define CUTIL_AND(_x, _y)			CUTIL_CAT(_CUTIL_AND_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_AND_0(_x)			0
#define _CUTIL_AND_1(_x)			_x

#define CUTIL_XOR(_x, _y)			CUTIL_CAT(_CUTIL_XOR_, CUTIL_BOOL(_x))(CUTIL_BOOL(_y))
#define _CUTIL_XOR_0(_x)			_x
#define _CUTIL_XOR_1(_x)			CUTIL_NOT(_x)

#define CUTIL_NOR(_x, _y)			CUTIL_NOT(CUTIL_OR(_x, _y))
/*
	CUTIL_BOOL(abcd);	// -> 1
	CUTIL_BOOL(345);	// -> 1
	CUTIL_BOOL(1);		// -> 1
	CUTIL_BOOL(0);		// -> 0
	CUTIL_BOOL();		// ERROR: you must provide an argument, or it will be evaluated to 1.
*/



//* IF statement
#define CUTIL_IF(_condition, _trueVal, _falseVal) CUTIL_CAT(_CUTIL_IF_, CUTIL_BOOL(_condition))((_trueVal), _falseVal)
#define _CUTIL_IF_0(_trueVal, _falseVal) 		_falseVal
#define _CUTIL_IF_1(_trueVal, _falseVal) 		_trueVal
/*
	CUTIL_IF(1, a, b)		-> a
	CUTIL_IF(0, a, b)		-> b
	CUTIL_IF(666, a, b)		-> a
*/



//* get count of arguments, up to 35 params
#define CUTIL_VA_EXISTS(...) 	CUTIL_EXPAND(CUTIL_BOOL(_CUTIL_GET_1ST_ARG(CUTIL_ZERO __VA_ARGS__)()))
// #define CUTIL_COMMA_OPT(...)	CUTIL_EXPAND(CUTIL_CAT(_CUTIL_IF_, CUTIL_VA_EXISTS(__VA_ARGS__))(CUTIL_COMMA, CUTIL_EMPTY()))

#define _CUTIL_VA_CNT_0(...)	0	// for compilers that do not support `##__VA_ARGS__` to eliminate leading comma if empty
#define _CUTIL_VA_CNT_1(...)	CUTIL_EXPAND(_CUTIL_GET_63TH_ARG("ignored", __VA_ARGS__, \
			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define CUTIL_VA_CNT(...)		CUTIL_OVERLOAD_IDX(_CUTIL_VA_CNT_, CUTIL_VA_EXISTS(__VA_ARGS__))(__VA_ARGS__)
// #define CUTIL_VA_CNT(...)		CUTIL_EXPAND(_CUTIL_GET_63TH_ARG("ignored", ##__VA_ARGS__, \
// 			Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,35,34,33,32,31,30,29,28,27, \
// 			26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
/*
 Examples:
	int a = CUTIL_VA_CNT(); 			// -> 0
	int b = CUTIL_VA_CNT(b1); 			// -> 1
	int c = CUTIL_VA_CNT(c1, c2); 		// -> 2
	int d = CUTIL_VA_CNT(c1, c2, c3); 	// -> 3
	...
	int a = CUTIL_VA_EXISTS(); 			// -> 0
	int b = CUTIL_VA_EXISTS(b1); 		// -> 1
	int c = CUTIL_VA_EXISTS(c1, c2); 	// -> 1
	int d = CUTIL_VA_EXISTS(c1, c2, c3);// -> 1
*/


//* macro function overloading support
#define CUTIL_OVERLOAD_IDX(_func, _idx)		CUTIL_CAT(_func, _idx)
#define CUTIL_OVERLOAD_AMOUNT(_func, ...) 	CUTIL_OVERLOAD_IDX(_func, CUTIL_VA_CNT(__VA_ARGS__))
/* example:
	CUTIL_OVERLOAD_IDX(MyFunc, 2)(); 	// MyFunc2();
	CUTIL_OVERLOAD_IDX(var_, 3) = 10; 	// var_3 = 10;
	
	// Deduce suffix by amount of arguments within the macro
	CUTIL_OVERLOAD_AMOUNT(MyFunc, 2, 4, 6)(2, 4, 6); // MyFunc3(2, 4, 6);
*/


#endif /* CUTIL_BASE_BASE_H__ */
