/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/

#ifndef CUTIL_ALL_H__
#define CUTIL_ALL_H__

//* core header
#include <cutil/base.h>


//* Console Utils
#include <cutil/console_utils.h>


//* C utils (macros)
#include <cutil/c_utils.h>


//* Cpp Utils (templates)
#ifdef __cplusplus
#include <cutil/cpp_base.hpp>
#include <cutil/cpp_utils.hpp>
#include <cutil/cpp_bits.hpp>
#include <cutil/cpp_math.hpp>
#include <cutil/cpp_scope_guard.hpp>
#include <cutil/cpp_string_utils.hpp>
#include <cutil/qt_utils.hpp>
#endif // __cplusplus


//* CUDA Utils
#include <cutil/cuda_utils.h>



#endif /* CUTIL_ALL_H__ */
