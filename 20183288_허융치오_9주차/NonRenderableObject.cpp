#include "NonRenderableObject.h"
#include "MakeableObjectFucCall.h"

NonRenderableObject::NonRenderableObject()
{
	MakeableObjectFucCall::Instance()->AddUpdateObject(this);
	MakeableObjectFucCall::Instance()->AddCleanObject(this);
	MakeableObjectFucCall::Instance()->AddInitObject(this);
}
NonRenderableObject::~NonRenderableObject()
{

}


void NonRenderableObject::Init()
{

}
void NonRenderableObject::Update()
{

}
void NonRenderableObject::RenDeltaTime()
{

}
void NonRenderableObject::SetProjection(glm::mat4 p)
{
	Projection = p;
}
void NonRenderableObject::SetView(glm::mat4 v)
{
	View = v;
}

glm::mat4 NonRenderableObject::GetProjection() const
{
	return Projection;
}
glm::mat4 NonRenderableObject::GetView() const
{
	return View;
}

void NonRenderableObject::SetMVP(glm::mat4 m, glm::mat4 v, glm::mat4 p)
{

	MVP = m * v * p;
}

void NonRenderableObject::SetPosition(glm::mat4 m)
{
	Model = m;
}

glm::mat4 NonRenderableObject::GetMVP() const
{
	return MVP;
}

void NonRenderableObject::Clean()
{

}
