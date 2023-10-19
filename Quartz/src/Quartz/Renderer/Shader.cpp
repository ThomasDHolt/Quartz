#include "qtpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Quartz
{
	Shader* Shader::Create(const std::string& pVertexSrc, const std::string& pFragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	QT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(pVertexSrc, pFragmentSrc);
		}

		QT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}