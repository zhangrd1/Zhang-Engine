#pragma once

#include "enginepch.h"
#include "Core.h"
#include "Layer.h"

namespace Engine {
	class ENGINE_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> overlayer);
		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> overlayer);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::vector<std::shared_ptr<Layer>>::iterator m_LayerInsert;

	};
}