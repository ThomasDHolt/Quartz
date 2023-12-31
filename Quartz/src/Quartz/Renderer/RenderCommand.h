#pragma once

#include "RendererAPI.h"

namespace Quartz
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& pColor)
		{
			s_RendererAPI->SetClearColor(pColor);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		inline static void DrawIndexed(const Ref<VertexArray>& pVertexArray)
		{
			s_RendererAPI->DrawIndexed(pVertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}