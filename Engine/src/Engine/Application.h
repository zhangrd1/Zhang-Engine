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

		void run();
	};

	std::unique_ptr<Application> CreateApplication();
}



