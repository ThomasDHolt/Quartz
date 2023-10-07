#pragma once

#include <string>

namespace Quartz
{
	class Shader
	{
	public:
		Shader(const std::string& pVertexSrc, const std::string& pFragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}