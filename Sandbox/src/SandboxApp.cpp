#include "qtpch.h"
#include <Quartz.h>

#include "imgui/imgui.h"

class ExampleLayer : public Quartz::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		if (Quartz::Input::IsKeyPressed(QT_KEY_TAB))
			QT_TRACE("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Quartz::Event& pEvent) override
	{
		//QT_TRACE("{0}", pEvent);
	}
};

class Sandbox : public Quartz::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Quartz::Application* Quartz::CreateApplication()
{
	return new Sandbox();
}