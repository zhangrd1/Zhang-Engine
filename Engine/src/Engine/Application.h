#pragma once

#include "Core.h"

#include <memory>

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
	};

	// 在客户端中定义
	std::unique_ptr<Application> CreateApplication();
}



