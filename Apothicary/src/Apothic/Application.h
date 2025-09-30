#pragma once

#include "Core.h"
#include "Rendering/Window.h"
#include "Events/WindowEvent.h"
#include "Rendering/Layer.h"
#include "Rendering/Renderer.h"
#include <memory>
#include <Xenon.h>

namespace apothic
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	};

	Application* CreateApplication();

	extern xenon::registry* global_registry;
	extern graphics::Renderer* global_renderer;
}