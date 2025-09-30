#include "Layer.h"

namespace apothic
{

	LayerStack::LayerStack()
	{
		m_InsertLayer = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_InsertLayer = m_Layers.emplace(m_InsertLayer, layer);
		layer->OnAttach();
	}

	void LayerStack::PusOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		layer->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			--m_InsertLayer;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		overlay->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
			if (it != m_Layers.end())
				m_Layers.erase(it);
	}

}