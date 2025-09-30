#pragma once

#include "DataTypes.h"

#include <string>
#include <vector>

namespace apothic::graphics
{

	class Shader
	{
	public:
		Shader(const std::string& path) {}
		virtual ~Shader() {}

		virtual void SetUniform(const std::string& name, ApothicDataType type, const void* value) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		struct UniformElement {
			std::string name;
			ApothicDataType Type;

			bool operator==(const std::string& other)
			{
				return this->name == other;
			}
		};

		virtual std::vector<UniformElement> GetUniforms() const = 0;

		static Shader* CreateShader(const std::string& path);
	};

}