#pragma once

#include "Quartz/Core.h"

namespace Quartz
{
	class QUARTZ_API Input
	{
	public:
		inline static bool IsKeyPressed(int pKeyCode) { return s_Instance->IsKeyPressedImpl(pKeyCode); }

		inline static bool IsMouseButtonPressed(int pButton) { return s_Instance->IsMouseButtonPressedImpl(pButton); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int pKeyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int pButton) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}