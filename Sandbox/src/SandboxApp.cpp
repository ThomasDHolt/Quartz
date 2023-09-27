#include "qtpch.h"
#include <Quartz.h>

class Sandbox : public Quartz::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Quartz::Application* Quartz::CreateApplication()
{
	return new Sandbox();
}