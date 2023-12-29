#pragma once
#include "bsepch.h"

class TriangleMesh : public Geometry
{
public:
	TriangleMesh() : Geometry(TRIANGLE_MESH) {}
	virtual ~TriangleMesh() {}

	// Inherited functions
	virtual int GetCount() const;

	// Specific functions
	//void GenerateNormals();

	std::vector<float>& GetVertexData();


private:
	/*std::vector<float> vertexData;
	std::vector<int> vertexIndices;
	std::vector<int> vertexNormals;*/

	//void LoadVertexData(std::string data); // for educational purposes, we load from a string only

protected:
	void Init(std::string data);

};
