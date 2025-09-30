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

		// creating entity & component
		tempent = apothic::global_registry->CreateEntity();
		apothic::global_registry->AddComponent<apothic::graphics::RenderObject>(tempent, new apothic::graphics::RenderObject{tempvc, tempmati});
		apothic::global_registry->AddComponent<apothic::graphics::TransformComponent>(tempent, new apothic::graphics::TransformComponent{ new argon::vec4(100, 100, 0, 0) });

		tempent2 = apothic::global_registry->CreateEntity();
		apothic::global_registry->AddComponent<apothic::graphics::RenderObject>(tempent2, new apothic::graphics::RenderObject{ tempvc, tempmati });
		apothic::global_registry->AddComponent<apothic::graphics::TransformComponent>(tempent2, new apothic::graphics::TransformComponent{ new argon::vec4(250, 100, 0, 0) });





		/* matrix test - */
		argon::mat3 location = argon::translation_mat3(argon::vec2(12, 30));
		argon::mat3 rotation = argon::rotation2D_mat3(15);

		argon::mat3 transform = location * rotation;
		std::cout << "Location: " << location << std::endl;
		std::cout << "Rotation: " << rotation << std::endl;
		std::cout << "\nTransform" << transform << std::endl;

	}

	~RenderLayer()
	{
		free(tempvc);
		free(tempsh);
		free(tempmati);
	}

	virtual void OnUpdate() override
	{
		apothic::global_renderer->Submit(tempent);
		apothic::global_renderer->Submit(tempent2);
	}

	virtual void OnEvent(apothic::Event& event)
	{
		apothic::EventDispatcher disp(event);
		disp.Dispatch<apothic::WindowResizeEvent>(std::bind(&RenderLayer::OnUpdateCamera, this, std::placeholders::_1));
	}

private:
	XenonID tempent = 0;
	XenonID tempent2 = 0;
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