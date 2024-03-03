#include "enginepch.h"
#include "WindowsWindow.h"
#include "Engine/Log.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Engine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description) {
		ENGINE_CORE_ERROR("GLFW Error ({0}) : {1}", error_code, description);
	}

	std::unique_ptr<Window> Window::Create(const WindowProps& props) {
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title  = props.Title;
		m_Data.Width  = props.Width;
		m_Data.Height = props.Height;

		ENGINE_CORE_INFO("Creating Window {0}, ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success, "Could Not initialize GLFW!");
			
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(
			static_cast<int>(m_Data.Width),
			static_cast<int>(m_Data.Height),
			m_Data.Title.c_str(),
			nullptr,
			nullptr);

		if (!m_Window) {
			ENGINE_CORE_ERROR("Window Create Failed");
		}

		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize Glad!")

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = static_cast<unsigned int>(width);
			data.Height = static_cast<unsigned int>(height);

			WindowResizeEvent event{ data.Width, data.Height };
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xoffset, yoffset);
			data.EventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(xpos, ypos);
			data.EventCallback(event);
			}
		);
	}

	void WindowsWindow::ShutDown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enable) {
		if (enable) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = true;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}

}