#pragma once

#include "Quartz/Layer.h"

#include "Quartz/Events/ApplicationEvent.h"
#include "Quartz/Events/MouseEvent.h"
#include "Quartz/Events/KeyEvent.h"

namespace Quartz
{
	class QUARTZ_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}