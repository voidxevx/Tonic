#pragma once

#include <xenon.h>
#include "../Application.h"

namespace apothic
{
	class RenderSystem : public xenon::SystemInterface
	{
	public:
		RenderSystem(XenonArchetype set)
			: xenon::SystemInterface(set)
		{
		}

		~RenderSystem()
		{
		}

		virtual void OnSystemUpdate(xenon::registry* reg, XenonID entity) override
		{
			global_renderer->Submit(entity);
		}
	};
}