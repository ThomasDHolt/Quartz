#pragma once

#include "Level.h"

#include <string>

namespace Quartz
{
	class LevelLibrary
	{
	public:
		void Add(const Ref<Level>& pLevel);
		void Add(const std::string& pName, const Ref<Level>& pLevel);

		Ref<Level> Load(const std::string& pFilePath);
		Ref<Level> Load(const std::string& pName, const std::string& pFilePath);

		Ref<Level> Get(const std::string& pName);

		bool Exists(const std::string& pName) const;
	private:
		std::unordered_map<std::string, Ref<Level>> m_Levels;
	};
}