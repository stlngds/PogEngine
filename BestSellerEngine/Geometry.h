#pragma once
#include "bsepch.h"

class Geometry
{
public:
	enum Type
	{
		TRIANGLE_MESH,		//0
		TRIANGLE_STRIP,		//1
		POINT_CLOUD,		//2
		PARTICLES,			//3
		MAX					//4
	};

	Geometry() {}
	Geometry(Type type) : GType(type) {}
	virtual ~Geometry() {}

	Type GType;

	virtual int GetCount() const = 0;

	void SetVertexData(std::string data) {
		std::istringstream str(data);
		std::string s;
		while (std::getline(str, s, ','))
		{
			vertexData.push_back((float)atof(s.c_str()));
		}
	}
	void SetVertexData(std::vector<float> data) { vertexData = data; }
	void SetVertexArray(VertexArray* invao) { VAO = invao; }
	void SetVertexBuffer(VertexBuffer* invbo) { VBO = invbo; }
	void SetIndexBuffer(IndexBuffer* inibo) { IBO = inibo; }
	void SetVertexBufferLayout(VertexBufferLayout* invbl) { VBL = invbl; }

	//GLuint VBO;
	//GLuint VAO; // TODO: Refactor to get rid of this
	IndexBuffer* IBO = nullptr; // We use this instead of Geometry subclasses??
	VertexBuffer* VBO = nullptr;
	VertexArray* VAO = nullptr;
	VertexBufferLayout* VBL = nullptr;

private:


protected:

	std::vector<float> vertexData;
	std::vector<int> vertexIndices;
	std::vector<int> vertexNormals;


};

