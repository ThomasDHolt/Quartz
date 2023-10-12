#include "qtpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Quartz
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType pType)
	{
		switch (pType)
		{
		case Quartz::ShaderDataType::Float:		return GL_FLOAT;
		case Quartz::ShaderDataType::Float2:	return GL_FLOAT;
		case Quartz::ShaderDataType::Float3:	return GL_FLOAT;
		case Quartz::ShaderDataType::Float4:	return GL_FLOAT;
		case Quartz::ShaderDataType::Mat3:		return GL_FLOAT;
		case Quartz::ShaderDataType::Mat4:		return GL_FLOAT;
		case Quartz::ShaderDataType::Int:		return GL_INT;
		case Quartz::ShaderDataType::Int2:		return GL_INT;
		case Quartz::ShaderDataType::Int3:		return GL_INT;
		case Quartz::ShaderDataType::Int4:		return GL_INT;
		case Quartz::ShaderDataType::Bool:		return GL_BOOL;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& pVertexBuffer)
	{
		QT_CORE_ASSERT(pVertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		pVertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = pVertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(pVertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& pIndexBuffer)
	{
		glBindVertexArray(m_RendererID);
		pIndexBuffer->Bind();

		m_IndexBuffer = pIndexBuffer;
	}
}