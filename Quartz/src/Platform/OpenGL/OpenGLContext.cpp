#include "qtpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Quartz
{
	OpenGLContext::OpenGLContext(GLFWwindow* pWindowHandle)
		: m_WindowHandle(pWindowHandle)
	{
		QT_CORE_ASSERT(pWindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QT_CORE_ASSERT(status, "Failed to initialize Glad!");

		QT_CORE_INFO("OpenGL Info:");
		QT_CORE_INFO("    Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		QT_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		QT_CORE_INFO("   Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}