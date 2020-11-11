#ifndef NONRENDERABLEOBJECT_H_
#define NONRENDERABLEOBJECT_H_

#include "Object.h"
#include "IUpdater.h"
#include "IInit.h"

class NonRenderableObject : public Object, public IUpdater, public IInit
{
private:


protected:


public:
	NonRenderableObject();
	virtual ~NonRenderableObject();

	void SetProjection(glm::mat4 p);
	void SetView(glm::mat4 v);

	glm::mat4 GetProjection() const;
	glm::mat4 GetView() const;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void RenDeltaTime() override;
	virtual void SetMVP(glm::mat4 m, glm::mat4 v, glm::mat4 p) override;
	virtual void SetPosition(glm::mat4 m) override;
	virtual glm::mat4 GetMVP() const override;


};

#endif // !NONRENDERABLEOBJECT_H_