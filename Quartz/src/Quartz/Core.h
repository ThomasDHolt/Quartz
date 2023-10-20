#pragma once

#include <memory>

#ifdef QT_PLATFORM_WINDOWS
	#if QT_DYNAMIC_LINK
		#ifdef QT_BUILD_DLL
			#define QUARTZ_API __declspec(dllexport)
		#else
			#define QUARTZ_API __declspec(dllimport)
		#endif
	#else
		#define QUARTZ_API
	#endif
#else
	#error Quartz only supports Windows!
#endif

#ifdef QT_DEBUG
	#define QT_ENABLE_ASSERTS
#endif

#ifdef QT_ENABLE_ASSERTS
	#define QT_ASSERT(x, ...) { if(!(x)) { QT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QT_CORE_ASSERT(x, ...) { if(!(x)) { QT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QT_ASSERT(x, ...)
	#define QT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define QT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Quartz
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}