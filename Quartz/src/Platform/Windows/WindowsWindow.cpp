#include "qtpch.h"
#include "WindowsWindow.h"

#include "Quartz/Events/KeyEvent.h"
#include "Quartz/Events/MouseEvent.h"
#include "Quartz/Events/ApplicationEvent.h"

#include "glad/glad.h"

namespace Quartz
{
	static bool s_GLFWInitialised = false;

	static void GLFWErrorCallback(int pError, const char* pDescription)
	{
		QT_CORE_ERROR("GLFW Error ({0}): {1}", pError, pDescription);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow((int)pProps.Width, (int)pProps.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QT_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* pWindow, int pWidth, int pHeight)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
			data.Width = pWidth;
			data.Height = pHeight;

			WindowResizeEvent event(pWidth, pHeight);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* pWindow)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* pWindow, int pKey, int pScanCode, int pAction, int pMods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);
			
			switch (pAction)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(pKey, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(pKey);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(pKey, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* pWindow, int pButton, int pAction, int pMods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);

			switch (pAction)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(pButton);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(pButton);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* pWindow, double pXOffset, double pYOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);

			MouseScrolledEvent event((float)pXOffset, (float)pYOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* pWindow, double pXPos, double pYPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(pWindow);

			MouseMovedEvent event((float)pXPos, (float)pYPos);
			data.EventCallback(event);
		});
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