#include "bsepch.h"

int TriangleMesh::GetCount() const
{
    return (vertexData.size() / 8); // TODO: to implement (with texture, now divide by 8)
}

void TriangleMesh::Init(std::string data)
{
    SetVertexData(data);
}

std::vector<float>& TriangleMesh::GetVertexData()
{
    return vertexData;
}

//void TriangleMesh::GenerateNormals()
//{
//}
