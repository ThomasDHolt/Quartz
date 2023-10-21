#pragma once

#include <string>

namespace Quartz
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& pFilePath);
		static Shader* Create(const std::string& pVertexSrc, const std::string& pFragmentSrc);
	};
}