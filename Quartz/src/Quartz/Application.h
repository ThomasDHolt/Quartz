#pragma once

#include "Core.h"

#include "Window.h"
#include "Quartz/LayerStack.h"
#include "Quartz/Events/Event.h"
#include "Quartz/Events/ApplicationEvent.h"

#include "Quartz/ImGui/ImGuiLayer.h"

#include "Quartz/Renderer/Shader.h"
#include "Quartz/Renderer/Buffer.h"
#include "Quartz/Renderer/VertexArray.h"

#include "Quartz/Renderer/OrthographicCamera.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}