#include "OpenGL_Shader.h"

#include "OpenGL_DataTypes.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace apothic::graphics
{

	Shader* Shader::CreateShader(const std::string& path)
	{
		return new OpenGLShader(path);
	}

	OpenGLShader::OpenGLShader(const std::string& path)
		: Shader(path)
	{
		m_RenderID = glCreateProgram();
		unsigned int shaders[2];
		OpenGLShaderSource source = ParseShader(path);

		CompileShaderSource(source.vertexSrc, GL_VERTEX_SHADER, shaders[0]);
		CompileShaderSource(source.fragmentSrc, GL_FRAGMENT_SHADER, shaders[1]);

		glAttachShader(m_RenderID, shaders[0]);
		glAttachShader(m_RenderID, shaders[1]);
		glLinkProgram(m_RenderID);
		glValidateProgram(m_RenderID);

		glDeleteShader(shaders[0]);
		glDeleteShader(shaders[1]);
	}

	OpenGLShader::~OpenGLShader()
	{}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::CompileShaderSource(const std::string& source, unsigned int type, unsigned int& id)
	{
		id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "COMPILATION ERROR ----- " << (type == GL_VERTEX_SHADER ? "VEREX SHADER" : "FRAGMENT SHADER") << " ----- " << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			id = NULL;
			free(message);
		}
	}

	OpenGLShader::OpenGLShaderSource OpenGLShader::ParseShader(const std::string& path) const
	{
		std::ifstream stream(path);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else if (line.find("#version") != std::string::npos)
			{
				ss[0] << line << std::endl;
				ss[1] << line << std::endl;
			}
			else
			{
				if (type != ShaderType::NONE)
					ss[(int)type] << line << std::endl;
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_Uniforms.count(name) > 0)
		{
			return m_Uniforms[name];
		}

		unsigned int loc = glGetUniformLocation(m_RenderID, name.c_str());
		m_Uniforms[name] = loc;
		return loc;
	}

	std::vector<Shader::UniformElement> OpenGLShader::GetUniforms() const
	{
		std::vector<Shader::UniformElement> uniforms;
		int uniformCount;
		glGetProgramiv(m_RenderID, GL_ACTIVE_UNIFORMS, &uniformCount);

		for (int i{}; i < uniformCount; ++i)
		{
			char name[256];
			int length;
			int size;
			GLenum type;

			glGetActiveUniform(m_RenderID, i, sizeof(name), &length, &size, &type, name);

			uniforms.push_back({ name, GetApothicDataType(type) });
		}

		return uniforms;
	}

	void OpenGLShader::SetUniform(const std::string& name, ApothicDataType type, const void* value)
	{
		unsigned int loc = GetUniformLocation(name);

		switch (type)
		{
		case ApothicDataType::Float:
		{
			float v = *(float*)value;
			glUniform1f(loc, v);
			break;
		}
		case ApothicDataType::Double:
		{
			double v = *(double*)value;
			glUniform1d(loc, v);
			break;
		}
		case ApothicDataType::Int:
		{
			int v = *(int*)value;
			glUniform1i(loc, v);
			break;
		}
		case ApothicDataType::Uint:
		{
			unsigned int v = *(unsigned int*)value;
			glUniform1ui(loc, v);
			break;
		}
		case ApothicDataType::fvec2:
		{
			argon::vec2 v = *(argon::vec2*)value;
			glUniform2f(loc, v[0], v[1]);
			break;
		}
		case ApothicDataType::fvec3:
		{
			argon::vec3 v = *(argon::vec3*)value;
			glUniform3f(loc, v[0], v[1], v[2]);
			break;
		}
		case ApothicDataType::fvec4:
		{
			argon::vec4 v = *(argon::vec4*)value;
			glUniform4f(loc, v[0], v[1], v[2], v[3]);
			break;
		}
		case ApothicDataType::dvec2:
		{
			argon::dvec2 v = *(argon::dvec2*)value;
			glUniform2d(loc, v[0], v[1]);
			break;
		}
		case ApothicDataType::dvec3:
		{
			argon::dvec3 v = *(argon::dvec3*)value;
			glUniform3d(loc, v[0], v[1], v[2]);
			break;
		}
		case ApothicDataType::dvec4:
		{
			argon::dvec4 v = *(argon::dvec4*)value;
			glUniform4d(loc, v[0], v[1], v[2], v[3]);
			break;
		}
		case ApothicDataType::ivec2:
		{
			argon::ivec2 v = *(argon::ivec2*)value;
			glUniform2i(loc, v[0], v[1]);
			break;
		}
		case ApothicDataType::ivec3:
		{
			argon::ivec3 v = *(argon::ivec3*)value;
			glUniform3i(loc, v[0], v[1], v[2]);
			break;
		}
		case ApothicDataType::ivec4:
		{
			argon::ivec4 v = *(argon::ivec4*)value;
			glUniform4i(loc, v[0], v[1], v[2], v[3]);
			break;
		}
		case ApothicDataType::uivec2:
		{
			argon::uivec2 v = *(argon::uivec2*)value;
			glUniform2ui(loc, v[0], v[1]);
			break;
		}
		case ApothicDataType::uivec3:
		{
			argon::uivec3 v = *(argon::uivec3*)value;
			glUniform3ui(loc, v[0], v[1], v[2]);
			break;
		}
		case ApothicDataType::uivec4:
		{
			argon::uivec4 v = *(argon::uivec4*)value;
			glUniform4ui(loc, v[0], v[1], v[2], v[3]);
			break;
		}

		case ApothicDataType::fmat2:
		{
			argon::mat2 v = *(argon::mat2*)value;
			glUniformMatrix2fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat3:
		{
			argon::mat3 v = *(argon::mat3*)value;
			glUniformMatrix3fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat4:
		{
			argon::mat4 v = *(argon::mat4*)value;
			glUniformMatrix4fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat2x3:
		{
			argon::mat2x3 v = *(argon::mat2x3*)value;
			glUniformMatrix2x3fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat3x2:
		{
			argon::mat3x2 v = *(argon::mat3x2*)value;
			glUniformMatrix3x2fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat3x4:
		{
			argon::mat3x4 v = *(argon::mat3x4*)value;
			glUniformMatrix3x4fv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::fmat4x3:
		{
			argon::mat4x3 v = *(argon::mat4x3*)value;
			glUniformMatrix4x3fv(loc, 1, GL_TRUE, v.Data());
			break;
		}

		case ApothicDataType::dmat2:
		{
			argon::dmat2 v = *(argon::dmat2*)value;
			glUniformMatrix2dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat3:
		{
			argon::dmat3 v = *(argon::dmat3*)value;
			glUniformMatrix3dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat4:
		{
			argon::dmat4 v = *(argon::dmat4*)value;
			glUniformMatrix4dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat2x3:
		{
			argon::dmat2x3 v = *(argon::dmat2x3*)value;
			glUniformMatrix2x3dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat3x2:
		{
			argon::dmat3x2 v = *(argon::dmat3x2*)value;
			glUniformMatrix3x2dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat3x4:
		{
			argon::dmat3x4 v = *(argon::dmat3x4*)value;
			glUniformMatrix3x4dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		case ApothicDataType::dmat4x3:
		{
			argon::dmat4x3 v = *(argon::dmat4x3*)value;
			glUniformMatrix4x3dv(loc, 1, GL_TRUE, v.Data());
			break;
		}
		default:
			break;
		}
	}

}