#include<Oak.h>

class ExampleLayer : public Oak::Layer
{
public:
    ExampleLayer()
        :Layer("Example")
    {}

    void OnUpdate() override
    {
        OAK_INFO("example OnUpdate");
    }

    void OnEvent(Oak::Event& event) override
    {
        OAK_TRACE("{0}", event);
    }
};


class Sandox :public Oak::Application {
public:
	Sandox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new Oak::ImGuiLayer());
	}
	
	~Sandox() {

	}
};

Oak::Application* Oak::CreateApplication() {
	return new Sandox();
}