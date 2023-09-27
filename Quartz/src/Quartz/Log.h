#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Quartz
{
	class QUARTZ_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define QT_CORE_FATAL(...)    ::Quartz::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define QT_CORE_ERROR(...)    ::Quartz::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QT_CORE_WARN(...)     ::Quartz::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QT_CORE_INFO(...)     ::Quartz::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QT_CORE_TRACE(...)    ::Quartz::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define QT_FATAL(...)         ::Quartz::Log::GetClientLogger()->critical(__VA_ARGS__)
#define QT_ERROR(...)         ::Quartz::Log::GetClientLogger()->error(__VA_ARGS__)
#define QT_WARN(...)          ::Quartz::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QT_INFO(...)          ::Quartz::Log::GetClientLogger()->info(__VA_ARGS__)
#define QT_TRACE(...)         ::Quartz::Log::GetClientLogger()->trace(__VA_ARGS__)