#pragma once

namespace Quartz
{
	class Timestep
	{
	public:
		Timestep(float pTime = 0.0f)
			: m_Time(pTime)
		{
		}

		float GetSeconds() { return m_Time; }
		float GetMilliseconds() { return m_Time * 1000.0f; }
	private:
		float m_Time = 0.0f;
	};
}