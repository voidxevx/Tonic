#include "OpenGL_VertexCollection.h"

#include "OpenGL_DataTypes.h"

#include <glad/glad.h>
#include <iostream>

namespace apothic::graphics
{

	VertexCollection* VertexCollection::CreateVertexCollection(float* vertecis, unsigned int vCount, unsigned int* indecis, unsigned int iCount, VertexLayout layout)
	{
		return new OpenGLVertexCollection(vertecis, vCount, indecis, iCount, layout);
	}

	OpenGLVertexCollection::OpenGLVertexCollection(float* vertecis, unsigned int vCount, unsigned int* indecis, unsigned int iCount, VertexLayout layout)
		: VertexCollection(vertecis, vCount, indecis, iCount, layout)
		, m_Layout(layout)
		, m_RenderIDs((unsigned int*)malloc(3 * sizeof(unsigned int)))
	{
		if (m_RenderIDs)
		{
			glGenVertexArrays(1, &m_RenderIDs[0]);
			glBindVertexArray(m_RenderIDs[0]);

			glGenBuffers(2, &m_RenderIDs[1]);

			glBindBuffer(GL_ARRAY_BUFFER, m_RenderIDs[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vCount, vertecis, GL_STATIC_DRAW);

			unsigned int index{};
			for (const VertexElement& element : m_Layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, (GLint)GetComponentCount(element.Type), ToGLType(element.Type), GL_FALSE, m_Layout.GetStride(), (const void*)element.Offset);
				++index;
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderIDs[2]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * iCount, indecis, GL_STATIC_DRAW);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}

	OpenGLVertexCollection::~OpenGLVertexCollection()
	{
		glDeleteBuffers(2, &m_RenderIDs[1]);
		glDeleteVertexArrays(1, &m_RenderIDs[0]);
		free(m_RenderIDs);
		m_RenderIDs = nullptr;
	}

	void OpenGLVertexCollection::Bind() const
	{
		glBindVertexArray(m_RenderIDs[0]);
	}

	void OpenGLVertexCollection::Unbind() const
	{
		glBindVertexArray(0);
	}

}