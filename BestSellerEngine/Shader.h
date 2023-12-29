#pragma once
//#include <string>
//#include <unordered_map>
#include "bsepch.h"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	Shader(const std::string& vsfp, const std::string& fsfp);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int GetID();

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniformMatrix4fv(const std::string& name, int count, bool transpose, const float* value);

private:
	unsigned int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	ShaderProgramSource ParseShaders(const std::string& vsfp, const std::string& fsfp);
};