#include "Cube.h"
#include "FileManager.h"

Cube::Cube(const char* filepath, float x, float y, float z)
	: RenderableObject(filepath, x, y, z)
{
	//bool load = FileManager::Instance()->LoadOBJ(filepath, vertex, uv, normal);

	//FileManager::Instance()->indexVBO(vertex, uv, normal,
	//	indices, indexed_vertices, indexed_uvs,
	//	indexed_normals);
}
Cube::~Cube()
{

}

void Cube::Clean()
{

}

void Cube::Update()
{

}

void Cube::RenDeltaTime()
{

}