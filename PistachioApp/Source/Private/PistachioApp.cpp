#include <imgui.h>

#include "Pistachio/Application.h"
#include "Pistachio/EntryPoint.h"

#include "Pistachio/Image.h"

class ExampleLayer : public Pistachio::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Pistachio::Application* Pistachio::CreateApplication(int argc, char** argv)
{
	Pistachio::ApplicationSpecification spec;
	spec.Name = "Pistachio Example";

	Pistachio::Application* app = new Pistachio::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}