/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CUTIL_CUDA_UTILS_H__
#define CUTIL_CUDA_UTILS_H__
#include <cutil/base.h>



#if defined(__CUDACC__) //* CUDA
#include <cutil/console_utils.h>

_CUTIL_NAMESPACE_BEGIN
_CUTIL_NAMESPACE_BEGIN_NAME(cuda)

//==================== CUDA Utils ==========================

#define CUTIL_CUDA_ERROR_MESSAGE(_CUDA_ERROR, _REASON) 		\
	fprintf(stderr, FLRed CBold	"\n==== ERROR, cudaError: " FLWhite "%d" FLRed ", reason: " FLWhite _REASON CRst "\n" \
			FRed "    file: " FCyan  __FILE__ "\n" 			\
			FRed "    func: " FCyan "%s\n" 					\
			FRed "    line: " FCyan "%d\n" 					\
			CRst "\n" , (_CUDA_ERROR), _CUTIL_FUNC_NAME, __LINE__ 	\
	)

#define CUTIL_CUDA_WARNING_MESSAGE(_CUDA_ERROR, _REASON) 	\
	fprintf(stderr, FLYellow "\n==== WARNING, cudaError: " FLWhite "%d" FLYellow ", reason: " FLWhite _REASON CRst "\n" \
			FYellow "    file: " FCyan  __FILE__ "\n" 		\
			FYellow "    func: " FCyan "%s\n" 				\
			FYellow "    line: " FCyan "%d\n" 				\
			CRst "\n" , (_CUDA_ERROR), _CUTIL_FUNC_NAME, __LINE__ 	\
	)


#define CUTIL_CUDA_ERROR_MESSAGE_IF_NOT_SUCCESS(_CUDA_ERROR, _REASON) \
	do {if (_CUDA_ERROR != 0) {CUTIL_CUDA_ERROR_MESSAGE(_REASON);}} while(0) //* cudaSuccess == 0

#define CUTIL_CUDA_WARNING_MESSAGE_IF_NOT_SUCCESS(_CUDA_ERROR, _REASON) \
	do {if (_CUDA_ERROR != 0) {CUTIL_CUDA_WARNING_MESSAGE(_REASON);}} while(0)


// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息, 并退出当前函数, 第三个参数为 return 值, void 则不填写
#define CUTIL_CUDA_RETURN_IF_NOT_SUCCESS(_CUDA_ERROR, _REASON, ...) 	do {\
	if (_CUDA_ERROR != 0) { 							\
		CUTIL_CUDA_ERROR_MESSAGE(_CUDA_ERROR, _REASON); \
		return __VA_ARGS__; 							\
	}} while(0)

// 进行 cuda 部分操作后, 将返回值传入此宏定义中, 如果执行失败, 则输出信息并强行停止程序
#define CUTIL_CUDA_ABORT_IF_NOT_SUCCESS(_CUDA_ERROR, _REASON, _RET) 	do {\
	if (_CUDA_ERROR != 0) { 							\
		CUTIL_CUDA_ERROR_MESSAGE(_CUDA_ERROR, _REASON) 	\
		exit(_RET); 									\
	}} while(0)


_CUTIL_NAMESPACE_END_NAME(cuda)
_CUTIL_NAMESPACE_END
#endif // __CUDACC__
#endif // CUTIL_CUDA_UTILS_H__
