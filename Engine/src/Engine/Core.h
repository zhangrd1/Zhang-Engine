#pragma once

/* 宏定义等基本模块 */

#ifdef ENGINE_PLATFORM_WINDOW
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Sorry, ZHANG Engine only supports Windows!
#endif

#define BIT(x) (1 << x)