#ifndef CUBE_H_
#define CUBE_H_

#include "RenderableObject.h"
#include "IUpdater.h"

class Cube : public RenderableObject, public IUpdater
{
private:

public:
	Cube(const char* filepath, float x, float y, float z);
	~Cube();

	virtual void Clean() final;
	virtual void RenDeltaTime() override;
	virtual void Update() override;
};

#endif // !CUBE_H_