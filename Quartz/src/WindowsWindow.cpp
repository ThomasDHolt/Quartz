#include "qtpch.h"
#include "WindowsWindow.h"

namespace Quartz
{
	static bool s_GLFWInitialised = false;

	Window* Window::Create(const WindowProps& pProps)
	{
		return new WindowsWindow(pProps);
	}

	WindowsWindow::WindowsWindow(const WindowProps& pProps)
	{
		Init(pProps);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& pProps)
	{
		m_Data.Title = pProps.Title;
		m_Data.Width = pProps.Width;
		m_Data.Height = pProps.Height;

		QT_CORE_INFO("Creating window {0} ({1}, {2})", pProps.Title, pProps.Width, pProps.Height);

		if (!s_GLFWInitialised)
		{
			int success = glfwInit();
			QT_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow((int)pProps.Width, (int)pProps.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool pEnabled)
	{
		if (pEnabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = pEnabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}