//
// Created by Sayama on 11/09/2024.
//

#pragma once
#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <array>
#include <optional>
#include <memory>

namespace tr {

	static inline constexpr uint8_t c_ShaderTypeCount = 6;

	enum class ShaderType : uint8_t
	{
		COMPUTE = 0,
		VERTEX,
		TESS_CONTROL,
		TESS_EVALUATION,
		GEOMETRY,
		FRAGMENT
	};

	class ShaderSource
	{
	public:
		virtual ~ShaderSource() {}
		virtual std::string_view GetSource() const = 0;
	};

	class StringShaderSource : public ShaderSource
	{
	public:
		StringShaderSource(std::string source) : m_Source(std::move(source)) {}
		virtual ~StringShaderSource() override = default;
	public:
		virtual std::string_view GetSource() const override {return m_Source;};
	private:
		std::string m_Source;
	};

	using ConstShaderSourcePtr = const ShaderSource*;

	class Shader {
	public:
		static std::shared_ptr<Shader> Create(const std::unordered_map<ShaderType, ConstShaderSourcePtr>& sources);
		static std::shared_ptr<Shader> Create(std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources);
		static std::shared_ptr<Shader> Create(ConstShaderSourcePtr vertexShader, ConstShaderSourcePtr fragmentShader);
	public:
		Shader(const std::unordered_map<ShaderType, ConstShaderSourcePtr>& sources);
		Shader(std::array<ConstShaderSourcePtr, c_ShaderTypeCount> sources);
		Shader(ConstShaderSourcePtr vertexShader, ConstShaderSourcePtr fragmentShader);
		~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
	public:
		void Bind();
		void Unbind();
		[[nodiscard]] uint32_t GetRendererID() const;
	public:
//		void SetUniformMat4(const std::string& name, const Mat4& matrix);
//		void SetUniformMat3(const std::string& name, const Mat3& matrix);
//		void SetUniformVec4(const std::string& name, const Vec4& vector);
//		void SetUniformVec3(const std::string& name, const Vec3& vector);
//		void SetUniformFloat(const std::string& name, float value);
//		void SetUniformTexture(const std::string& name, uint32_t slot);
	private:
		bool CompileShaders(const std::array<ConstShaderSourcePtr, c_ShaderTypeCount>& m_Sources);
		bool LinkShaders();
	private:
		std::array<std::optional<uint32_t>, c_ShaderTypeCount> m_Shaders;
		uint32_t m_RendererID;

	};

} // tr
