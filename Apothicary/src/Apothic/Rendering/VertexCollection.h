#pragma once

#include "Vertexlayout.h"

namespace apothic::graphics
{

	class VertexCollection
	{
	public:
		VertexCollection(float* vertecis, unsigned int vCount, unsigned int* indecis, unsigned int iCount, VertexLayout layout) 
			: m_IndecisCount(iCount)
		{}
		virtual ~VertexCollection() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const VertexLayout GetLayout() const = 0;
		inline unsigned int GetIndeciCount() const { return m_IndecisCount; }

		static VertexCollection* CreateVertexCollection(float* vertecis, unsigned int vCount, unsigned int* indecis, unsigned int iCount, VertexLayout layout);
	private:
		unsigned int m_IndecisCount;
	};

}