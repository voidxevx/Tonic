#pragma once
#include "Shader.h"

#include <memory>

namespace apothic::graphics
{

	struct MaterialParameter
	{
		std::string name;
		ApothicDataType type;
		const void* value;
	};

	class Material
	{
		friend class MaterialInstance;
	public:
		Material(Shader* shader);
	private:
		void Bind(const std::vector<MaterialParameter>& parameters) const;
		void Unbind() const;
		std::vector<Shader::UniformElement> m_Uniforms;
		Shader* m_Shader;
	};

	class MaterialInstance
	{
	public:
		MaterialInstance(const std::shared_ptr<Material>& parent, const std::vector<MaterialParameter>& parameters);
		~MaterialInstance();

		void Bind() const;
		void Unbind() const;

		void SetMVP(argon::mat4* mvp);
		void SetProjection(argon::vec4* projection);

	private:
		std::shared_ptr<Material> m_ParentMaterial;
		std::vector<MaterialParameter> m_Parameters;
	};

	static MaterialInstance* MakeInstance(const std::shared_ptr<Material>& parent, const std::vector<MaterialParameter>& parameters)
	{
		return new MaterialInstance(parent, parameters);
	}

}