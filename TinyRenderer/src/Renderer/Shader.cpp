//
// Created by Sayama on 11/09/2024.
//

#include <algorithm>
#include <glad/glad.h>
#include "TinyRenderer/Renderer/Shader.hpp"
#include "TinyRenderer/Core/Logger.hpp"

using namespace std::string_literals;

namespace tr {

	GLenum ShaderSourceTypeToGLType(ShaderType sst)
	{
		switch (sst) {

			case ShaderType::COMPUTE: return GL_COMPUTE_SHADER;
			case ShaderType::VERTEX: return GL_VERTEX_SHADER;
			case ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
			case ShaderType::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER;
			case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
			case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
		}
		TR_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
		return 0;
	}

	std::string ShaderSourceTypeToString(ShaderType sst)
	{
		switch (sst) {

			case ShaderType::COMPUTE: return "COMPUTE"s;// return GL_COMPUTE_SHADER;
			case ShaderType::VERTEX: return "VERTEX"s;// return GL_VERTEX_SHADER;
			case ShaderType::TESS_CONTROL: return "TESS_CONTROL"s;// return GL_TESS_CONTROL_SHADER;
			case ShaderType::TESS_EVALUATION: return "TESS_EVALUATION"s;// return GL_TESS_EVALUATION_SHADER;
			case ShaderType::GEOMETRY: return "GEOMETRY"s;// return GL_GEOMETRY_SHADER;
			case ShaderType::FRAGMENT: return "FRAGMENT"s;// return GL_FRAGMENT_SHADER;
		}
		TR_ASSERT(false, "Unknown ShaderSource type {}", (int)sst);
		return ""s;
	}

	std::shared_ptr<Shader> Shader::Create(const std::unordered_map<ShaderType, ConstShaderSourcePtr>& sources)
	{
		return std::make_shared<Shader>(sources);
	}
	std::shared_ptr<Shader> Shader::Create(std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources)
	{
		return std::make_shared<Shader>(sources);
	}
	std::shared_ptr<Shader> Shader::Create(ConstShaderSourcePtr vertexShader, ConstShaderSourcePtr fragmentShader)
	{
		return std::make_shared<Shader>(vertexShader, fragmentShader);
	}

	Shader::Shader(const std::unordered_map<ShaderType, ConstShaderSourcePtr>& sources_map) {
		std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources{nullptr};
		for (auto&&[type, source] : sources_map)
		{
			sources[(uint8_t)type] = source;
		}
		CompileShaders(sources);
		LinkShaders();
	}

	Shader::Shader(std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources) {
		CompileShaders(sources);
		LinkShaders();

	}

	Shader::Shader(ConstShaderSourcePtr vertexShader, ConstShaderSourcePtr fragmentShader) {
		std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources{nullptr};
		sources[(uint8_t)ShaderType::VERTEX] = vertexShader;
		sources[(uint8_t)ShaderType::FRAGMENT] = fragmentShader;
		CompileShaders(sources);
		LinkShaders();
	}

	Shader::~Shader() {
		for (auto& shader : m_Shaders) {
			if (shader) {
				glDeleteShader(shader.value());
				shader = std::nullopt;
			}
		}
		glDeleteProgram(m_RendererID);
	}

	bool Shader::CompileShaders(const std::array<ConstShaderSourcePtr, c_ShaderTypeCount>& m_Sources) {
		TR_ASSERT(!m_Sources.empty(), "No can be created as there is no source.");
		if(m_Sources.empty()) return false;

		for (uint8_t type = 0; type < c_ShaderTypeCount; ++type)
		{
			ConstShaderSourcePtr source = m_Sources[type];
			if(!source) continue;
			std::string_view sourceStr = source->GetSource();
			if(sourceStr.empty()) continue;
			TR_ASSERT(sourceStr.size() < INT_MAX, "Cannot handle shader source greater than {}.", INT_MAX);

			m_Shaders[type] = glCreateShader(ShaderSourceTypeToGLType((ShaderType)type));
			const char* c_source = sourceStr.data();
			int size = static_cast<int>(sourceStr.size());
			glShaderSource(m_Shaders[type].value(), 1, &c_source, &size);
			glCompileShader(m_Shaders[type].value());

			GLint vertex_compiled;
			glGetShaderiv(m_Shaders[type].value(), GL_COMPILE_STATUS, &vertex_compiled);
			if (vertex_compiled != GL_TRUE)
			{
				GLint TotalLenght=0;
				glGetShaderiv(m_Shaders[type].value(), GL_INFO_LOG_LENGTH, &TotalLenght);
				std::vector<char> logs(TotalLenght);
				glGetShaderInfoLog(m_Shaders[type].value(), TotalLenght, nullptr, logs.data());
				if(logs.empty())
				{
					TR_ERROR("{} - Shader Compilation Failed without giving any informations.", ShaderSourceTypeToString((ShaderType)type));
				}
				else
				{
					TR_ERROR("{} - Shader Compilation Failed:\n{}", ShaderSourceTypeToString((ShaderType)type), logs.data());
				}
				return false;
			}
		}

		return std::any_of(m_Shaders.begin(), m_Shaders.end(), [&](const auto &item) { return item;});
	}

	bool Shader::LinkShaders() {
		m_RendererID = glCreateProgram();

		for (const auto& shader : m_Shaders) {
			if(shader) {
				glAttachShader(m_RendererID, shader.value());
			}
		}

		glLinkProgram(m_RendererID);

		GLint program_linked;
		GLint vertex_compiled;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &vertex_compiled);
		if (vertex_compiled != GL_TRUE)
		{
			GLint TotalLenght=0;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &TotalLenght);
			std::vector<char> logs(TotalLenght);
			glGetProgramInfoLog(m_RendererID, TotalLenght, nullptr, logs.data());
			if(logs.empty())
			{
				TR_ERROR("Shader Linking Failed without giving any informations.");
			}
			else
			{
				TR_ERROR("Shader Linking Failed:\n{}", logs.data());
			}
			return false;
		}
		return true;
	}



	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	uint32_t Shader::GetRendererID() const
	{
		return m_RendererID;
	}
} // tr