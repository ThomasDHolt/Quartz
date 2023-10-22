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

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& pFilePath);
		static Ref<Shader> Create(const std::string& pName, const std::string& pVertexSrc, const std::string& pFragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& pShader);
		void Add(const std::string& pName, const Ref<Shader>& pShader);
		Ref<Shader> Load(const std::string& pFilePath); // Texture.glsl
		Ref<Shader> Load(const std::string& pName, const std::string& pFilePath);

		Ref<Shader> Get(const std::string& pName);

		bool Exists(const std::string& pName) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}