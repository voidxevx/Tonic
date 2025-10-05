#include "Application.h"
#include "Rendering/Renderer.h"
#include "Rendering/RenderSystem.h"
#include <iostream>

#ifndef APOTHIC_SET_MAX_REGISTRY
	#define MAX_ENTITIES 1000
	#define MAX_SYSTEMS 32
	#define MAX_ARCHETYPES 64
#endif

namespace apothic
{
	xenon::registry* global_registry = new xenon::registry(MAX_ENTITIES, MAX_SYSTEMS, MAX_ARCHETYPES);
	graphics::Renderer* global_renderer = graphics::Renderer::CreateRenderer();

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::CreateWindow());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		global_registry->RegisterComponent<RenderObject>();
		global_registry->RegisterComponent<TransformComponent>();

		global_registry->RegisterArchetype<RenderSystem, RenderObject, TransformComponent>();
	}

	Application::~Application()
	{
		
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;

		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PusOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			global_registry->UpdateSystems();
			m_Window->OnUpdate();
		}
	}

}