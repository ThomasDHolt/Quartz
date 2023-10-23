#include "qtpch.h"
#include "Level.h"

#include <fstream>

namespace Quartz
{
	Level::Level(const std::string& pFilePath)
	{
		std::string source = ReadFile(pFilePath);
		auto data = PreProcess(source);
		m_Data = data;

		// Extract name from filepath
		auto lastSlash = pFilePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = pFilePath.rfind(".");
		auto count = lastDot == std::string::npos ? pFilePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = pFilePath.substr(lastSlash, count);
	}

	Level::Level(const std::string& pName, const std::string& pFilePath)
	{
		std::string source = ReadFile(pFilePath);
		auto data = PreProcess(source);
		m_Data = data;
		m_Name = pName;
	}

	Ref<Level> Level::Create(const std::string& pFilePath)
	{
		return std::make_shared<Level>(pFilePath);
	}

	Ref<Level> Level::Create(const std::string& pName, const std::string& pFilePath)
	{
		return std::make_shared<Level>(pName, pFilePath);
	}

	std::string Level::ReadFile(const std::string& pFilePath)
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

	std::vector<std::string> Level::PreProcess(const std::string& pSource)
	{
		std::vector<std::string> returnResult;

		size_t pos = 0;
		while (pos != std::string::npos)
		{
			size_t eol = pSource.find_first_of("\r\n", pos);
			//QT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos;
			
			size_t nextLinePos = pSource.find_first_not_of("\r\n", eol);
			if (nextLinePos == std::string::npos)
			{
				returnResult.push_back(pSource.substr(pos, pos - pSource.size() - 1));
			}
			else
			{
				returnResult.push_back(pSource.substr(pos, eol - pos));
			}
			pos = nextLinePos;
		}

		return returnResult;
	}
}