#pragma once

#include "Quartz/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Quartz
{
	class OpenGLContext: public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* pWindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}