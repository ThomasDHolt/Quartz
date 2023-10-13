#include "qtpch.h"
#include "Renderer.h"

namespace Quartz
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& pVertexArray)
	{
		pVertexArray->Bind();
		RenderCommand::DrawIndexed(pVertexArray);
	}
}