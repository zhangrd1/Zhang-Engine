#pragma once

#include <memory>

#ifdef ENGINE_PLATFORM_WINDOW
	
extern std::unique_ptr<Engine::Application> Engine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->run();
	return 0;
}

#endif