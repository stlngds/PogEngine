#pragma once

#include "bsepch.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Initialize()
{
	// load geometry here
	LoadMaterials();
}

void RenderComponent::Update()
{
	//debug
	GameObject* go = GetOwner();

	// update transform in the rendering system using corresponding shader
	std::vector<std::string> uniforms = { "MVP" };
	shaderHandle->Bind();
	Renderer::GetInstance()->UpdateModelMatrix(&GetOwner()->GetWorldTransform(), shaderHandle->GetID(), uniforms[0]);
	shaderHandle->Unbind();
}

void RenderComponent::Shutdown()
{
}

void RenderComponent::HandleEvent(Event* evt)
{

}

void RenderComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	// Deserialize the color setup
	std::vector<Color*> colors;
	const rapidjson::Value& colorsV = componentMembers.FindMember(GameObjectSystemComponentConstants::COLORS)->value;
	std::vector<Material*> mats;
	if (colorsV.IsObject())
	{
		for (rapidjson::Value::ConstMemberIterator it = colorsV.MemberBegin(); it != colorsV.MemberEnd(); ++it)
		{
			// for each color component
			auto colorArray = it->value.GetArray();
			Color* color = new Color;
			for (size_t i = 0; i < colorArray.Size(); ++i)
			{
				float c = colorArray[i].GetFloat();
				color->SetColor(i, c);
			}
			colors.push_back(color);
		}
		this->SetColor(colors);
		mats = *GetOwner()->GetMaterialsReference();
	}

	// Deserialize the texture coords setup
	std::vector<TexCoord> textCoords;
	const rapidjson::Value& textCoordsV = componentMembers.FindMember(GameObjectSystemComponentConstants::TEXTURE_COORDS)->value;
	if (textCoordsV.IsObject())
	{
		for (rapidjson::Value::ConstMemberIterator it = textCoordsV.MemberBegin(); it != textCoordsV.MemberEnd(); ++it)
		{
			auto textCoordArray = it->value.GetArray();
			TexCoord coords;
			coords.x = textCoordArray[0].GetFloat();
			coords.y = textCoordArray[1].GetFloat();
			textCoords.push_back(coords);
		}
	}

	// Deserialize indices
	
	std::vector<unsigned int> indices;
	auto indicesV = componentMembers.FindMember(GameObjectSystemComponentConstants::INDICES);
	if (indicesV->value.IsArray())
		for (size_t i = 0; i < indicesV->value.Size(); ++i) {
			indices.push_back(indicesV->value.GetArray()[i].GetInt());
		}
	
	// Deserialize the vertices 
	std::vector<float> vertexDataFloats;
	const rapidjson::Value& verticesV = componentMembers.FindMember(GameObjectSystemComponentConstants::VERTICES)->value;

	int color_count = 0;
	int texcoord_count = 0;
	for (rapidjson::Value::ConstMemberIterator it = verticesV.MemberBegin(); it != verticesV.MemberEnd(); ++it)
	{
		// for each vertex component
		auto vertexArray = it->value.GetArray();
		for (size_t i = 0; i < vertexArray.Size(); ++i)
		{
			float vn = vertexArray[i].GetFloat();
			vertexDataFloats.push_back(vn);
		}
		if (colorsV.IsObject())
		{
			Color* color = static_cast<Color*>(mats[color_count++]);
			auto cs = color->GetColor();
			for (size_t i = 0; i < cs.size() - 1; ++i)
			{
				vertexDataFloats.push_back(cs[i]);
			}
		}
		if (textCoordsV.IsObject())
		{
			vertexDataFloats.push_back(textCoords[texcoord_count].x);
			vertexDataFloats.push_back(textCoords[texcoord_count].y);
			texcoord_count++;
		}
	}

	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(&vertexDataFloats[0], vertexDataFloats.size() * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(&indices[0], sizeof(indices)); 
	VertexBufferLayout* layout = new VertexBufferLayout;
	if (verticesV.IsObject()) layout->Push<float>(3);
	if (colorsV.IsObject()) layout->Push<float>(3); // 4 breaks it??
	if (textCoordsV.IsObject()) layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);

	// Texture
	const std::string texPath = componentMembers.FindMember(GameObjectSystemComponentConstants::TEXTURE_PATH)->value.GetString();
	if (texPath != "")
		this->SetTexture(new Texture(texPath));

	// Deserialize the Mesh type
	std::string MeshType;
	
	rapidjson::Value::ConstMemberIterator meshIt = componentMembers.FindMember(GameObjectSystemComponentConstants::MESH_TYPE);
	MeshType = meshIt->value.GetString();
	if (MeshType == GameObjectSystemComponentConstants::TRIANGLE_MESH)
	{
		//this->SetGeometry<TriangleMesh>(vertexData);
		this->SetGeometry<TriangleMesh>(vertexDataFloats);
	}// TODO: Implement conditionals for other types of mesh

	// TODO: Make sure parameters aren't empty.
	this->GetGeometry()->SetVertexArray(va);
	this->GetGeometry()->SetVertexBuffer(vb);
	this->GetGeometry()->SetVertexBufferLayout(layout);
	this->GetGeometry()->SetIndexBuffer(ib);

	// Deserialize the Shader setup
	rapidjson::Value::ConstMemberIterator shaderIt = componentMembers.FindMember(GameObjectSystemComponentConstants::SHADER);
	auto shaderMember = shaderIt->value.FindMember(GameObjectSystemComponentConstants::VERTEX_FILE);
	shaderData.VertexShaderFile = shaderMember->value.GetString();
	auto shaderMember2 = shaderIt->value.FindMember(GameObjectSystemComponentConstants::FRAGMENT_FILE);
	shaderData.FragmentShaderFile = shaderMember2->value.GetString();

	const rapidjson::Value& attributes = shaderIt->value.FindMember(GameObjectSystemComponentConstants::ATTRIBUTES)->value;

	for (rapidjson::Value::ConstMemberIterator it = attributes.MemberBegin(); it != attributes.MemberEnd(); ++it)
		shaderData.Attributes.push_back(it->value.GetString());

	this->LoadMaterials();
}

void RenderComponent::LoadMaterials()
{
	
	// load something meaningful. i.e. shader
	std::string vertexShader = shaderData.VertexShaderFile;
	std::string fragmentShader = shaderData.FragmentShaderFile;

	shaderHandle = Renderer::GetInstance()->BuildShader(vertexShader, fragmentShader);
	//shaderHandle = Renderer::GetInstance()->BuildShader("basic.glsl");
	Renderer::GetInstance()->GenerateSceneBuffers(this->GetGeometry(), this->GetGeometry()->GetCount());
	Renderer::GetInstance()->InterpretBuffers(this->GetGeometry()); 

	// can load textures too
	// texture = Renderer::GetInstance()->BuildTexture("Textures/ushaVictory.png");
	
}

void RenderComponent::SetShaderData(std::string vertexFile, std::string fragmentFile)
{
	shaderData.VertexShaderFile = vertexFile;
	shaderData.FragmentShaderFile = fragmentFile;
	//shaderData.Attributes = attributes;
}

void RenderComponent::SetShaderHandle(Shader* newShader) {
	shaderHandle = newShader;
}

std::vector<Material*>* RenderComponent::GetMaterialsReference()
{
	return GetOwner()->GetMaterialsReference();
}

void RenderComponent::SetColor(std::vector<Color*> colors)
{
	for (Color* color : colors)
		GetOwner()->GetMaterialsReference()->push_back(color);
}

Geometry* RenderComponent::GetGeometry()
{
	return GetOwner()->GetGeometry();
}

void RenderComponent::Draw()
{
	shaderHandle->Bind();
	texture->Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (GetOwner()->GetGeometry()->IBO != nullptr) {
		Renderer::GetInstance()->Draw(*GetOwner()->GetGeometry()->VAO, *GetOwner()->GetGeometry()->IBO, *shaderHandle);
	}
	else {
		Renderer::GetInstance()->Draw(*GetOwner()->GetGeometry()->VAO, *GetOwner()->GetGeometry()->IBO, *shaderHandle);
	}

	glDisable(GL_BLEND);
	texture->Unbind();
	shaderHandle->Unbind();
}

Shader* RenderComponent::GetShaderHandle() const
{
	return shaderHandle;
}