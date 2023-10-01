#pragma once

#include <qtpch.h>

#include "Quartz/Core.h"
#include "Quartz/Events/Event.h"

namespace Quartz
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& pTitle = "Quartz Engine",
			unsigned int pWidth = 1280,
			unsigned int pHeight = 720)
			: Title(pTitle), Width(pWidth), Height(pHeight)
		{
		}
	};

	class QUARTZ_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& pCallback) = 0;
		virtual void SetVSync(bool pEnabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& pProps = WindowProps());
	};
}