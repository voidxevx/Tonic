#pragma once
#include "../../Window.h"
#include "Apothic/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace apothic
{
	
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(const WindowProperties& props);
		virtual ~OpenGLWindow();

		virtual void OnUpdate() override;

		virtual inline unsigned int GetWidth() const override { return m_Data.Width;  }
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; }

		virtual inline void SetEventCallback(const EventCallback& callback) override { m_Data.callback = callback; }

	private:

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallback callback;
		} 
		m_Data;
	};
}