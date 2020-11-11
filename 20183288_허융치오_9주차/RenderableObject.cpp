#include "RenderableObject.h"
#include "MakeableObjectFucCall.h"
#include "FileManager.h"
#include "Renderer.h"

RenderableObject::RenderableObject()
{


	MakeableObjectFucCall::Instance()->AddUpdateObject(this);
	MakeableObjectFucCall::Instance()->AddCleanObject(this);
	MakeableObjectFucCall::Instance()->AddInitObject(this);
}
RenderableObject::RenderableObject(const char* filepath
	, float x, float y, float z)
{
	bool load = FileManager::Instance()->LoadOBJ(filepath, vertex, uv, normal);

	FileManager::Instance()->indexVBO(vertex, uv, normal,
		indices, indexed_vertices, indexed_uvs,
		indexed_normals);

	glm::mat4 move = glm::mat4(1.0f);
	move = glm::translate(move, glm::vec3(x, y, z));

	SetPosition(move);
	Renderer::Instance()->AddObject(*this);
}

RenderableObject::~RenderableObject()
{

}

void RenderableObject::Init()
{

}
void RenderableObject::SetMVP(glm::mat4 m, glm::mat4 v, glm::mat4 p)
{
	MVP = m * v * p;
}
void RenderableObject::SetPosition(glm::mat4 m)
{
	Model = m;
}

glm::mat4 RenderableObject::GetMVP() const
{
	return MVP;
}

std::vector<glm::vec3> RenderableObject::GetVertex() const
{
	return vertex;
}
std::vector<glm::vec2> RenderableObject::GetUV() const
{
	return uv;
}
std::vector<glm::vec3> RenderableObject::GetNormal() const
{
	return normal;
}

glm::mat4 RenderableObject::GetPosition() const
{
	return Model;
}

void RenderableObject::Clean()
{

}