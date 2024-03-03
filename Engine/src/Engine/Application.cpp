#include "enginepch.h"
#include "Application.h"
#include "Engine/Log.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));		
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		ENGINE_INFO(e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(std::shared_ptr<Layer> layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(std::shared_ptr<Layer> layer) {
		m_LayerStack.PushOverlay(layer);
	}
}