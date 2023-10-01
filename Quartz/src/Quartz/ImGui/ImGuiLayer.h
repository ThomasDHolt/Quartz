#pragma once

#include "Quartz/Layer.h"

namespace Quartz
{
	class QUARTZ_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& pEvent);
	private:
		float m_Time = 0.0f;
	};
}