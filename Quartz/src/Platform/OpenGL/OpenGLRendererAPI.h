#pragma once

#include "Quartz/Renderer/RendererAPI.h"

namespace Quartz
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& pColor) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& pVertexArray) override;
	};
}