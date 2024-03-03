#include "enginepch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
	Log::Log() = default;
	Log::~Log() = default;

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClintLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%H:%M:%S] %n: %v %s");  // 所有样式详见 spdlog wiki

		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->info("Hello, This is Zhang Engine");

		s_ClintLogger = spdlog::stdout_color_mt("APP");
		s_ClintLogger->set_level(spdlog::level::trace);
		s_ClintLogger->info("Hello, This is SandBox");

	}

	std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger>& Log::GetClientLogger()
	{
		return s_ClintLogger;
	}


}
