#pragma once

#include "Event.h"

#include <sstream>

namespace Quartz
{
	class QUARTZ_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int pKeyCode)
			: m_KeyCode(pKeyCode) {}

		int m_KeyCode;
	};

	class QUARTZ_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int pKeyCode, int pRepeatCount)
			: KeyEvent(pKeyCode), m_RepeatCount(pRepeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class QUARTZ_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int pKeyCode)
			: KeyEvent(pKeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}