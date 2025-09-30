#include "OpenGL_Window.h"
#include <iostream>

#include "../../../Events/ApplicationEvent.h"
#include "../../../Events/KeyEvent.h"
#include "../../../Events/MouseEvent.h"
#include "../../../Events/WindowEvent.h"

#include "../../../Application.h"

namespace apothic
{
	static bool s_GLFWInitialized = false;

	static void GLFW_ErrorCallBack(int count, const char* desc)
	{
		std::cout << "[" << count << "] - " << desc << std::endl;
	}

	Window* Window::CreateWindow(const WindowProperties& props)
	{
		return new OpenGLWindow(props);
	}

	OpenGLWindow::OpenGLWindow(const WindowProperties& props)
		: m_Window(nullptr)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		if (!s_GLFWInitialized)
		{
			int valid = glfwInit();
			if (valid == GLFW_FALSE)
				return;
			glfwSetErrorCallback(GLFW_ErrorCallBack);
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/*GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		m_Data.Width = mode->width;
		m_Data.Height = mode->height;*/

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
			return;
		glfwSwapInterval(1);
		glfwSetWindowUserPointer(m_Window, &m_Data);


		// ----- Event callbacks -----

		// window events -----
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.callback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event{};
			data.callback(event);
		});

		// Key event -----
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent eventPressed(key, 0);
				data.callback(eventPressed);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent eventReleased(key);
				data.callback(eventReleased);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent eventRepeat(key, 1);
				data.callback(eventRepeat);
				break;
			}
			}
		});
		// mouse events -----
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int modes)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent eventPressed(button);
				data.callback(eventPressed);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent eventReleased(button);
				data.callback(eventReleased);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(xOffset, yOffset);
			data.callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event(xPosition, yPosition);
			data.callback(event);
		});
	}

	OpenGLWindow::~OpenGLWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	void OpenGLWindow::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		global_renderer->Process();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}