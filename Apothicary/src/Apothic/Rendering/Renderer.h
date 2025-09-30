#pragma once

#include <xenon.h>
#include "DataTypes.h"
#include "VertexCollection.h"
#include "Material.h"
#include "Camera.h"

namespace apothic::graphics
{

	struct RenderObject
	{
		VertexCollection* VertexCollection;
		MaterialInstance* Material;

		void Bind() const
		{
			VertexCollection->Bind();
			Material->Bind();
		}

		void Unbind() const
		{
			VertexCollection->Unbind();
			Material->Unbind();
		}
	};

	struct TransformComponent
	{
		argon::vec4* transform;
	};

	class Renderer
	{
	public:
		Renderer() {}
		virtual ~Renderer() {}

		virtual void Submit(XenonID entity) = 0;
		virtual void Process() = 0;

		static Renderer* CreateRenderer();

		void AttachCamera(OrthographicCamera* camera)
		{
			m_OrthoCamera = camera;
		}

	protected:
		OrthographicCamera* m_OrthoCamera = nullptr;
	};
}