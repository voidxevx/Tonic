#pragma once

#include "../../Shader.h"
#include <unordered_map>

namespace apothic::graphics
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void SetUniform(const std::string& name, ApothicDataType type, const void* value);
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual std::vector<UniformElement> GetUniforms() const override;

	private:
		unsigned int m_RenderID;

		void CompileShaderSource(const std::string& source, unsigned int type, unsigned int& id);
		struct OpenGLShaderSource 
		{ 
			std::string vertexSrc;
			std::string fragmentSrc;
		} ParseShader(const std::string& path) const;

		unsigned int GetUniformLocation(const std::string& name);

		std::unordered_map<std::string, unsigned int> m_Uniforms;

	};

}
