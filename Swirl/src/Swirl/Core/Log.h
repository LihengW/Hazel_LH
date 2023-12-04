#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Swirl {
	class HAZEL_API Log
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

// Core Log macros
#define SW_CORE_TRACE(...)      ::Swirl::Log::GetCoreLogger()->trace(__VA_ARGS__) 
#define SW_CORE_ERROR(...)      ::Swirl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SW_CORE_WARN(...)       ::Swirl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SW_CORE_INFO(...)       ::Swirl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SW_CORE_CRITICAL(...)   ::Swirl::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log macros
#define HZ_TRACE(...)      ::Swirl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_ERROR(...)      ::Swirl::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_WARN(...)       ::Swirl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_INFO(...)       ::Swirl::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_CRITICAL(...)   ::Swirl::Log::GetClientLogger()->critical(__VA_ARGS__)