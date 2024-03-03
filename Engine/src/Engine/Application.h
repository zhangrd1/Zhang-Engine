#pragma once

#include "enginepch.h"
#include "Core.h"
#include "Engine/Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Engine/LayerStack.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);

		void PushLayer(std::shared_ptr<Layer> Layer);
		void PushOverlay(std::shared_ptr<Layer> Layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running {true};
		LayerStack m_LayerStack;
	};

	// 在客户端中定义
	std::unique_ptr<Application> CreateApplication();
}



