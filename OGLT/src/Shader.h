#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderPSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
		
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformM4f(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int GetUniformLocation(const std::string& name);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderPSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
};
