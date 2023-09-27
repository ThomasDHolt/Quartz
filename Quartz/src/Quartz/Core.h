#pragma once

#ifdef QT_PLATFORM_WINDOWS
	#ifdef QT_BUILD_DLL
		#define QUARTZ_API __declspec(dllexport)
	#else
		#define QUARTZ_API __declspec(dllimport)
	#endif
#else
	#error Quartz only supports Windows!
#endif

#define BIT(x) (1 << x)