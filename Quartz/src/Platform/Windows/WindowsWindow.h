#pragma once

#include "Quartz/Window.h";

#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Quartz
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& pProps);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& pCallback) override { m_Data.EventCallback = pCallback; }
		void SetVSync(bool pEnabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& pProps);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}