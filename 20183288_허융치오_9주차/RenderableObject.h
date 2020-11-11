#ifndef RENDERABLEOBJECT_H_
#define RENDERABLEOBJECT_H_

#include "Object.h"
#include "IUpdater.h"
#include "IInit.h"

class RenderableObject : public Object, public IUpdater, public IInit
{
private:

protected:
	bool load;

public:
	virtual ~RenderableObject();
	RenderableObject();
	RenderableObject(const char* filepath, float x, float y, float z);

	virtual void SetMVP(glm::mat4 m, glm::mat4 v, glm::mat4 p) override; 
	virtual void SetPosition(glm::mat4 m) override;
	virtual std::vector<glm::vec3> GetVertex() const;
	virtual std::vector<glm::vec2> GetUV() const;
	virtual std::vector<glm::vec3> GetNormal() const;
	virtual glm::mat4 GetMVP() const override;
	virtual glm::mat4 GetPosition() const;

	virtual void Init() override;
	virtual void RenDeltaTime() {}
	virtual void Update() { std::cout << "运行渲染" << std::endl; }
	virtual void Clean() override;
};

#endif // !RENDERABLEOBJECT_H_