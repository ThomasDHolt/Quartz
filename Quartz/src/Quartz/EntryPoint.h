#pragma once

#ifdef QT_PLATFORM_WINDOWS

	extern Quartz::Application* Quartz::CreateApplication();

	int main(int argc, char** argv)
	{
		Quartz::Log::Init();
		QT_CORE_INFO("CoreLogger initialized!");
		QT_INFO("ClientLogger initialized!");
		
		auto app = Quartz::CreateApplication();
		app->Run();
		delete app;
	}
#endif