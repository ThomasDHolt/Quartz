#pragma once

#ifdef QT_PLATFORM_WINDOWS

	extern Quartz::Application* Quartz::CreateApplication();

	int main(int argc, char** argv)
	{
		printf("Quartz Engine\n");
		auto app = Quartz::CreateApplication();
		app->Run();
		delete app;
	}
#endif