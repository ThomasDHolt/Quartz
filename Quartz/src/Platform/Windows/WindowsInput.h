#pragma once

#include "Quartz/Input.h"

namespace Quartz
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int pKeyCode) override;

		virtual bool IsMouseButtonPressedImpl(int pButton) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}