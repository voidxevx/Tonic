#pragma once

#include "../../VertexCollection.h"

namespace apothic::graphics
{

	class OpenGLVertexCollection : public VertexCollection
	{
	public:
		OpenGLVertexCollection(float* vertecis, unsigned int vCount, unsigned int* indecis, unsigned int iCount, VertexLayout layout);
		virtual ~OpenGLVertexCollection();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual const VertexLayout GetLayout() const { return m_Layout; }

	private:
		VertexLayout m_Layout;

		unsigned int* m_RenderIDs;
	};

}