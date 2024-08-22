#include <imgui.h>
#include <optional>

#include "Pistachio/Application.h"
#include "Pistachio/EntryPoint.h"

#include "Pistachio/Image.h"

class AppLayer : public Pistachio::Layer
{
public:
	virtual void OnUIRender() override
	{
		DrawMenuPanel();
		DrawViewport();
	}

	void DrawMenuPanel()
	{
		ImGui::Begin("Menu");
		bRenderImage = ImGui::Button("Render");
		ImGui::End();
	}

	void DrawViewport()
	{
		ImGui::Begin("Viewport");
		ViewportHeight = ImGui::GetContentRegionAvail().y; // NOLINT(*-narrowing-conversions)
		ViewportWidth = ImGui::GetContentRegionAvail().x; // NOLINT(*-narrowing-conversions)

		if (bRenderImage)
		{
			Render();
		}

		if (Image)
		{
			ImGui::Image(Image->GetDescriptorSet(),
			{
				static_cast<float>(Image->GetWidth()),
				static_cast<float>(Image->GetHeight())
			});
		}
		ImGui::End();
	}

	/// Render the scene into Viewport
	void Render()
	{
		if (!Image // first time rendering this will be null
			|| ViewportHeight != Image->GetHeight() // resized in y axis since last render
			|| ViewportWidth != Image->GetWidth() //resized in x axis since last render
			|| ImageBuffer.size() != Image->GetWidth() * Image->GetHeight()) // buffer is empty (in first render) or otherwise incorrect size somehow
		{
			Image = std::make_unique<Pistachio::Image>(ViewportWidth, ViewportHeight, Pistachio::ImageFormat::RGBA);
			ImageBuffer = std::vector<uint32_t>(ViewportWidth * ViewportHeight); // RGBA fits in 32 bit type
		}

		for (auto& pixel : ImageBuffer)
		{
			pixel = 0xFFFFFF00;
		}
		Image->SetData(ImageBuffer.data());
		bRenderImage = false;
	}

private:
	std::unique_ptr<Pistachio::Image> Image;
	std::vector<uint32_t> ImageBuffer;
	uint32_t ViewportWidth = 0, ViewportHeight = 0;
	bool bRenderImage = false;
};

Pistachio::Application* Pistachio::CreateApplication(int argc, char** argv)
{
	Pistachio::ApplicationSpecification Spec;
	Spec.Name = "Ray Tracing";

	Pistachio::Application* App = new Pistachio::Application(Spec);
	App->PushLayer<AppLayer>();
	App->SetMenubarCallback([App]
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				App->Close();
			}
			ImGui::EndMenu();
		}
	});
	return App;
}