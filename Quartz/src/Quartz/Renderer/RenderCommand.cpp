#include "qtpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Quartz
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}