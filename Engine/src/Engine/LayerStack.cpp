#include "enginepch.h"
#include "LayerStack.h"

namespace Engine {

	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {

	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> overlayer) {
		m_Layers.emplace_back(overlayer);
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> overlayer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}

}