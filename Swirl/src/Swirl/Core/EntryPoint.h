#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Swirl::Application* Swirl::CreateApplication();

int main(int argc, char** argv)
{
	Swirl::Log::Init();
	SW_CORE_WARN("Initialized Log!");
	int a = 5;
	SW_CORE_INFO("Hello! Var={0}", a);

	auto app = Swirl::CreateApplication();
	app->Run();
	delete app;
}

#endif
