#include "qtpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Quartz
{
	Ref<Shader> Shader::Create(const std::string& pFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	QT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(pFilePath);
		}

		QT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& pName, const std::string& pVertexSrc, const std::string& pFragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	QT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(pName, pVertexSrc, pFragmentSrc);
		}

		QT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& pName, const Ref<Shader>& pShader)
	{
		QT_CORE_ASSERT(!Exists(pName), "Shader already exists!");
		m_Shaders[pName] = pShader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& pShader)
	{
		auto& name = pShader->GetName();
		Add(name, pShader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& pFilePath)
	{
		auto shader = Shader::Create(pFilePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& pName, const std::string& pFilePath)
	{
		auto shader = Shader::Create(pFilePath);
		Add(pName, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& pName)
	{
		QT_CORE_ASSERT(Exists(pName), "Shader not found!");
		return m_Shaders[pName];
	}

	bool ShaderLibrary::Exists(const std::string& pName) const
	{
		return m_Shaders.find(pName) != m_Shaders.end();
	}
}