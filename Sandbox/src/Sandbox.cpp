#include <Engine.h>

#include "iostream"

class SandBox : public Engine::Application
{
	SandBox() = default;
	~SandBox() = default;
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
	auto ptr = std::make_unique<Engine::Application>();
	return ptr;
}
