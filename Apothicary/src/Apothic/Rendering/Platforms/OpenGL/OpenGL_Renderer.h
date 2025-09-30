#pragma once

#include "../../Renderer.h"

namespace apothic::graphics
{

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		virtual void Submit(XenonID entity) override;
		virtual void Process() override;

	private:
		std::vector<XenonID> m_RenderRequests;

		argon::mat4* m_DefaultMVP;
	};

}