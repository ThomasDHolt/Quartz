#include "qtpch.h"
#include "Renderer.h"

namespace Quartz
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& pCamera)
	{
		m_SceneData->ViewProjectionMatrix = pCamera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& pShader, const std::shared_ptr<VertexArray>& pVertexArray)
	{
		pShader->Bind();
		pShader->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);

		pVertexArray->Bind();
		RenderCommand::DrawIndexed(pVertexArray);
	}
}