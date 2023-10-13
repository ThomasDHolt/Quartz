#include "qtpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Quartz
{
	VertexBuffer* VertexBuffer::Create(float* pVertices, uint32_t pSize)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		QT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(pVertices, pSize);
		}
		QT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* pIndices, uint32_t pSize)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		QT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(pIndices, pSize);
		}
		QT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}