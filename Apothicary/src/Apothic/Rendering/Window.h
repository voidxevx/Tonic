#pragma once
#include <string>
#include <functional>
#include "Apothic/Core.h"
#include "../Events/Event.h"

namespace apothic
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width, Height;
        // Camera* camera;

		WindowProperties(std::string title = "-Apothicary-", unsigned int width = 1280, unsigned int height = 720)
			: Title(title)
			, Width(width)
			, Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& callback) = 0;

		static Window* CreateWindow(const WindowProperties& props = WindowProperties());
	};
}