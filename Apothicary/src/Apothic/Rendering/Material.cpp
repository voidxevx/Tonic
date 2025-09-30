#include "Material.h"

#include <algorithm>

namespace apothic::graphics
{

	Material::Material(Shader* shader)
		: m_Shader(shader)
	{
		 m_Uniforms = m_Shader->GetUniforms();
	}

	void Material::Bind(const std::vector<MaterialParameter>& parameters) const
	{
		m_Shader->Bind();
		for (const auto& para : parameters)
		{
			m_Shader->SetUniform(para.name, para.type, para.value);
		}
	}

	void Material::Unbind() const
	{
		m_Shader->Unbind();
	}

	MaterialInstance::MaterialInstance(const std::shared_ptr<Material>& parent, const std::vector<MaterialParameter>& parameters)
		: m_ParentMaterial(parent)
	{

		for (const auto& para : parameters) if 
			(std::find(m_ParentMaterial->m_Uniforms.begin(), m_ParentMaterial->m_Uniforms.end(), para.name) != m_ParentMaterial->m_Uniforms.end())
				m_Parameters.push_back(para);

	}

	MaterialInstance::~MaterialInstance()
	{
		for (const auto& para : m_Parameters)
		{
			delete para.value;
		}
	}

	void MaterialInstance::Bind() const
	{
		m_ParentMaterial->Bind(m_Parameters);
	}

	void MaterialInstance::Unbind() const
	{
		m_ParentMaterial->Unbind();
	}

	void MaterialInstance::SetMVP(argon::mat4* mvp)
	{
		m_ParentMaterial->m_Shader->SetUniform("u_MVP", ApothicDataType::fmat4, mvp);
	}

	void MaterialInstance::SetProjection(argon::vec4* projection)
	{
		m_ParentMaterial->m_Shader->SetUniform("u_Position", ApothicDataType::fvec4, projection);
	}

}