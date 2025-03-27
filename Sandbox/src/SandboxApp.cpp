#include<Oak.h>
#include "imgui/imgui.h"

class ExampleLayer : public Oak::Layer
{
public:
    ExampleLayer()
        :Layer("Example")
    {}

    void OnUpdate() override
    {
        if (Oak::Input::IsKeyPressed(OAK_KEY_TAB)) {
            OAK_TRACE("Table key is pressed!");
        }
    }


    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("hello world");
        ImGui::End();

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
	}
	
	~Sandox() {

	}
};

Oak::Application* Oak::CreateApplication() {
	return new Sandox();
}