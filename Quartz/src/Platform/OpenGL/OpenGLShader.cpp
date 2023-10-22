#include "qtpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Quartz
{
	static GLenum ShaderTypeFromString(const std::string& pType)
	{
		if (pType == "vertex")		return GL_VERTEX_SHADER;
		if (pType == "fragment")	return GL_FRAGMENT_SHADER;

		QT_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& pFilePath)
	{
		std::string source = ReadFile(pFilePath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		auto lastSlash = pFilePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = pFilePath.rfind(".");
		auto count = lastDot == std::string::npos ? pFilePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = pFilePath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& pName, const std::string& pVertexSrc, const std::string& pFragmentSrc)
		: m_Name(pName)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = pVertexSrc;
		sources[GL_FRAGMENT_SHADER] = pFragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& pSource)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = pSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = pSource.find_first_of("\r\n", pos);
			QT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = pSource.substr(begin, eol - begin);
			QT_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = pSource.find_first_not_of("\r\n", eol);
			pos = pSource.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = pSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? pSource.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& pName, int pValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniform1i(location, pValue);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& pName, float pValue)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniform1f(location, pValue);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& pName, const glm::vec2& pValues)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniform2f(location, pValues.x, pValues.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& pName, const glm::vec3& pValues)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniform3f(location, pValues.x, pValues.y, pValues.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& pName, const glm::vec4& pValues)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniform4f(location, pValues.x, pValues.y, pValues.z, pValues.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& pName, const glm::mat3& pMatrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(pMatrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& pName, const glm::mat4& pMatrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, pName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(pMatrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& pFilePath)
	{
		std::string result;
		std::ifstream in(pFilePath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			QT_CORE_ERROR("Could not open file '{0}'", pFilePath);
		}

		return result;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& pShaderSources)
	{
		GLuint program = glCreateProgram();
		QT_CORE_ASSERT(pShaderSources.size() <= 2, "We only support 2 shaders for now!");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : pShaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				QT_CORE_ERROR("{0}", infoLog.data());
				QT_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			for(auto id : glShaderIDs)
				glDeleteProgram(id);

			QT_CORE_ASSERT(false, "shader link failure!");
			QT_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}
}