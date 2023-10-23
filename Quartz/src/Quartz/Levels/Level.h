#pragma once

#define MAX_MAP_WIDTH	50
#define MAX_MAP_HEIGHT	50

#include <string>

namespace Quartz
{
	class Level
	{
	public:
		Level(const std::string& pFilePath);
		Level(const std::string& pName, const std::string& pFilePath);

		const std::string& GetName() { return m_Name; }
		const std::vector<std::string> GetData() { return m_Data; }

		const std::string& GetRow(const int pRow) { return m_Data[pRow]; }

		static Ref<Level> Create(const std::string& pFilePath);
		static Ref<Level> Create(const std::string& pName, const std::string& pFilePath);
	private:
		std::string ReadFile(const std::string& pFilePath);
		std::vector<std::string> PreProcess(const std::string& pSource);
	private:
		std::vector<std::string> m_Data;
		std::string m_Name;
	};
}