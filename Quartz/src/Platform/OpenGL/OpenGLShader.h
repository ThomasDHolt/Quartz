#pragma once

#include "Quartz/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Quartz
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& pVertexSrc, const std::string& pFragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string pName, int pValue);

		void UploadUniformFloat(const std::string pName, float pValue);
		void UploadUniformFloat2(const std::string pName, const glm::vec2& pValues);
		void UploadUniformFloat3(const std::string pName, const glm::vec3& pValues);
		void UploadUniformFloat4(const std::string pName, const glm::vec4& pValues);

		void UploadUniformMat3(const std::string pName, const glm::mat3& pMatrix);
		void UploadUniformMat4(const std::string pName, const glm::mat4& pMatrix);
	private:
		uint32_t m_RendererID;
	};
}