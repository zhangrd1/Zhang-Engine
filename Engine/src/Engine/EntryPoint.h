#pragma once

#include <iostream>
#include <memory>

#ifdef ENGINE_PLATFORM_WINDOW
	
extern std::unique_ptr<Engine::Application> Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	auto app = Engine::CreateApplication();
	app->Run();
	return 0;
}

#endif