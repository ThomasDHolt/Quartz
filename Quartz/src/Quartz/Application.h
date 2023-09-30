#pragma once

#include "Core.h"

#include "Quartz/LayerStack.h"
#include "Quartz/Events/Event.h"
#include "Quartz/Events/ApplicationEvent.h"

#include "Window.h"

namespace Quartz
{
	class QUARTZ_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* pLayer);
		void PushOverlay(Layer* pLayer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}