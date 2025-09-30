#include "OpenGL_Renderer.h"
#include "../../../Application.h"

#include <glad/glad.h>

namespace apothic::graphics
{

	Renderer* Renderer::CreateRenderer()
	{
		return new OpenGLRenderer();
	}

	OpenGLRenderer::OpenGLRenderer()
		: Renderer()
	{
		m_DefaultMVP = new argon::mat4{
			new float[16]
			{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1,
			}
		};
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		free(m_DefaultMVP);
		m_DefaultMVP = nullptr;
	}

	void OpenGLRenderer::Submit(XenonID entity)
	{
		if (global_registry->HasComponent<RenderObject>(entity) && global_registry->HasComponent<TransformComponent>(entity))
			m_RenderRequests.push_back(entity);
	}

	void OpenGLRenderer::Process()
	{
		for (const XenonID& entity : m_RenderRequests)
		{
			RenderObject* object = global_registry->GetComponent<RenderObject>(entity);
			TransformComponent* transform = global_registry->GetComponent<TransformComponent>(entity);

			object->Bind();
			if (m_OrthoCamera)
				object->Material->SetMVP(m_OrthoCamera->GetViewMatrix());
			else
				object->Material->SetMVP(m_DefaultMVP);

			object->Material->SetProjection(transform->transform);

			glDrawElements(GL_TRIANGLES, object->VertexCollection->GetIndeciCount(), GL_UNSIGNED_INT, nullptr);
		}
		m_RenderRequests.clear();
	}

}