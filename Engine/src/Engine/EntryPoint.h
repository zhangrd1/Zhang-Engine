#pragma once

#ifdef ENGINE_PLATFORM_WINDOW
	
extern std::unique_ptr<Engine::Application> Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	auto app = Engine::CreateApplication();

	if (app) {
		app->Run();
	}
	else {
		ENGINE_CORE_ERROR("CreateApplication Failed!");
	}

	return 0;
}


#endif