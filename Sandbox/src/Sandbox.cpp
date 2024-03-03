#include <Engine.h>

#include <memory>

class ExampleLayer : public Engine::Layer {
public:
	ExampleLayer()
		: Layer("ExampleLayer") {}

	void OnUpdate() override {
		ENGINE_INFO("Example::Update");
	}

	void OnEvent(Engine::Event& e) override {
		ENGINE_TRACE(e);
	}
};

class SandBox : public Engine::Application
{
public:
	SandBox() {
		PushLayer(std::make_shared<ExampleLayer>());
	}
};

std::unique_ptr<Engine::Application> Engine::CreateApplication()
{
	auto ptr = std::make_unique<SandBox>();
	return ptr;
}
