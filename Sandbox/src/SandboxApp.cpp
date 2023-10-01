#include "qtpch.h"
#include <Quartz.h>

class ExampleLayer : public Quartz::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		QT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Quartz::Event& pEvent) override
	{
		QT_TRACE("{0}", pEvent);
	}
};

class Sandbox : public Quartz::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Quartz::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Quartz::Application* Quartz::CreateApplication()
{
	return new Sandbox();
}