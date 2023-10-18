#pragma once

#include "Quartz/Core.h"
#include "Quartz/Core/Timestep.h"
#include "Quartz/Events/Event.h"

namespace Quartz
{
	class QUARTZ_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep pTimestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& pEvent) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}