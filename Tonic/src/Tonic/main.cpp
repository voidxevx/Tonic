#include <Apothic.h>

#include <iostream>
#include <functional>

class RenderLayer : public apothic::Layer
{
public:
	RenderLayer()
	{
		// createing temp assets
		tempvc = apothic::graphics::VertexCollection::CreateVertexCollection(
			new float[8]
			{
				-50.0f, -50.0f,
				 50.0f, -50.0f,
				-50.0f,  50.0f,
				 50.0f,  50.0f,
			},
			8,
			new unsigned int[6]
			{
				0, 1, 2,
				2, 3, 1,
			},
			6,
			{ {apothic::ApothicDataType::fvec2, "position"} }
		);
		tempsh = apothic::graphics::Shader::CreateShader("content/Shaders/FlatColor.shader");
		tempmat = std::make_shared<apothic::graphics::Material>(tempsh);
		tempmati = apothic::graphics::MakeInstance(tempmat, { apothic::graphics::MaterialParameter{"u_Color", apothic::ApothicDataType::fvec4, new argon::vec4{0.2f, 0.3f, 0.45f} } });

		tempcam = new apothic::graphics::OrthographicCamera(1280, 720);
		apothic::global_renderer->AttachCamera(tempcam);

		// creating entities & components
		XenonID ent = apothic::global_registry->CreateEntity();
		apothic::global_registry->SetTickEnabled(ent);
		apothic::global_registry->AddComponent(ent, new apothic::RenderObject{tempvc, tempmati});
		apothic::global_registry->AddComponent(ent, new apothic::TransformComponent{ new argon::vec4(100, 100, 0, 0) });

		ent = apothic::global_registry->CreateEntity();
		apothic::global_registry->SetTickEnabled(ent);
		apothic::global_registry->AddComponent(ent, new apothic::RenderObject{ tempvc, tempmati });
		apothic::global_registry->AddComponent(ent, new apothic::TransformComponent{ new argon::vec4(250, 100, 0, 0) });

	}

	~RenderLayer()
	{
		free(tempvc);
		free(tempsh);
		free(tempmati);
	}

	virtual void OnEvent(apothic::Event& event)
	{
		apothic::EventDispatcher disp(event);
		disp.Dispatch<apothic::WindowResizeEvent>(std::bind(&RenderLayer::OnUpdateCamera, this, std::placeholders::_1));
	}

private:
	apothic::graphics::VertexCollection* tempvc;
	apothic::graphics::Shader* tempsh;
	std::shared_ptr<apothic::graphics::Material> tempmat;
	apothic::graphics::MaterialInstance* tempmati;
	apothic::graphics::OrthographicCamera* tempcam;

	bool OnUpdateCamera(apothic::WindowResizeEvent& e)
	{
		tempcam->SetScreenWidthHeight(e.GetWidth(), e.GetHeight());
		return true;
	}
};




class TonicApp : public apothic::Application
{
public:
	TonicApp()
		: Application()
	{
		PushLayer(new RenderLayer());
	}
	
	~TonicApp() 
	{
	}
};

apothic::Application* apothic::CreateApplication()
{
	return new TonicApp();
}