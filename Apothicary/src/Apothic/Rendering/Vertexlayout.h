#pragma once

#include "DataTypes.h"
#include "Apothic/Core.h"

#include <string>
#include <vector>

namespace apothic::graphics
{

	struct VertexElement
	{
		ApothicDataType Type;
		std::string Name;
		unsigned int Size;
		unsigned int Offset;

		VertexElement(ApothicDataType type, const std::string& name)
			: Type(type)
			, Name(name)
			, Size((unsigned int)GetDataTypeSize(type))
			, Offset(0)
		{}
	};

	class VertexLayout
	{
	public:
		VertexLayout(const std::initializer_list<VertexElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<VertexElement> GetElements() const { return m_Elements; }
		inline const unsigned int GetStride() const { return m_Stride; }

		std::vector<VertexElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexElement>::iterator end() { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride()
		{
			unsigned int offset = 0;
			for (VertexElement& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<VertexElement> m_Elements;
		unsigned int m_Stride = 0;
	};

}