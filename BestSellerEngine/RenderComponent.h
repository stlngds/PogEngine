#pragma once
#include "bsepch.h"
// This type of render component only supports ONE mesh per game object
struct ShaderData
{
	std::string VertexShaderFile;
	std::string FragmentShaderFile;
	std::vector<std::string> Attributes;
};

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	void Initialize();
	void Update();
	void Shutdown();
	void HandleEvent(Event* evt);
	void Serialize() {}
	void Deserialize(const rapidjson::Value& obj);

	void Draw();

	Geometry* GetGeometry();
	Shader* GetShaderHandle() const;
	void SetColor(std::vector<Color*> colors);

	std::vector<Material*>* GetMaterialsReference();
	void LoadMaterials();
	void SetShaderData(std::string vertexFile, std::string fragmentFile);
	void SetShaderHandle(Shader* newShader);

	void SetTexture(std::string filepath) { texture = Renderer::GetInstance()->BuildTexture(filepath); }
	void SetTexture(Texture* newtex) { texture = newtex; }
	Texture* GetTexture() { return texture; }

	template <class T>
	void SetGeometry(std::string vertexData)
	{
		Geometry* mesh = new T;
		mesh->SetVertexData(vertexData);
		GetOwner()->SetGeometry(mesh);
	}

	template <class T> 
	void SetGeometry(std::vector<float> vertexData)
	{
		Geometry* mesh = new T;
		mesh->SetVertexData(vertexData);
		GetOwner()->SetGeometry(mesh);
	}

	template <class T>
	void SetGeometry(VertexBuffer* invbo) {
		Geometry* mesh = new T;
		mesh->SetVertexBuffer(invbo);
		GetOwner()->SetGeometry(mesh);
	}

private:
	Shader* shaderHandle;
	Texture* texture;
	ShaderData shaderData;
};
