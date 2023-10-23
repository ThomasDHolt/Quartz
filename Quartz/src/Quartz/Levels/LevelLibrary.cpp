#include "qtpch.h"
#include "LevelLibrary.h"

namespace Quartz
{
	void LevelLibrary::Add(const std::string& pName, const Ref<Level>& pLevel)
	{
		QT_CORE_ASSERT(!Exists(pName), "Level already exists!");
		m_Levels[pName] = pLevel;
	}

	void LevelLibrary::Add(const Ref<Level>& pLevel)
	{
		auto& name = pLevel->GetName();
		Add(name, pLevel);
	}

	Ref<Level> LevelLibrary::Load(const std::string& pFilePath)
	{
		auto level = Level::Create(pFilePath);
		Add(level);
		return level;
	}

	Ref<Level> LevelLibrary::Load(const std::string& pName, const std::string& pFilePath)
	{
		auto level = Level::Create(pName, pFilePath);
		Add(pName, level);
		return level;
	}

	Ref<Level> LevelLibrary::Get(const std::string& pName)
	{
		QT_CORE_ASSERT(Exists(pName), "Level not found!");
		return m_Levels[pName];
	}

	bool LevelLibrary::Exists(const std::string& pName) const
	{
		return m_Levels.find(pName) != m_Levels.end();
	}
}