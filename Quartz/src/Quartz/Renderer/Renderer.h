#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Quartz
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& pCamera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& pShader, const std::shared_ptr<VertexArray>& pVertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}