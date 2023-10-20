#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Quartz
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& pCamera);
		static void EndScene();

		static void Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& pVertexArray, const glm::mat4& pTransform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}