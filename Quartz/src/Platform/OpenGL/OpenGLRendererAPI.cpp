#include "qtpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Quartz
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& pColor)
	{
		glClearColor(pColor.r, pColor.g, pColor.b, pColor.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& pVertexArray)
	{
		glDrawElements(GL_TRIANGLES, pVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}