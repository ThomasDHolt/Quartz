#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Quartz
{
	class Shader
	{
	public:
		Shader(const std::string& pVertexSrc, const std::string& pFragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string pName, const glm::mat4& pMatrix);
	private:
		uint32_t m_RendererID;
	};
}