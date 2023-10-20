#include "qtpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

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

	void Renderer::Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& pVertexArray, const glm::mat4& pTransform)
	{
		pShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(pShader)->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(pShader)->UploadUniformMat4("u_Transform", pTransform);

		pVertexArray->Bind();
		RenderCommand::DrawIndexed(pVertexArray);
	}
}