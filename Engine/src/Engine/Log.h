#pragma once

#include "Core.h"
#include "enginepch.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Engine
{
	class ENGINE_API Log
	{
	public:
		Log();
		virtual ~Log();

		static void Init(); 

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClintLogger;
	};
}


// 引擎层输出信息
#define ENGINE_CORE_TRACE(...)      ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)       ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)       ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)      ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...)   ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// 客户端输出信息
#define ENGINE_TRACE(...)			::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...)			::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...)		    ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)			::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...)		::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
