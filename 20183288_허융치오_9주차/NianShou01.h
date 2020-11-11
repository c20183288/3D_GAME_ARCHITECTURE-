#ifndef NIANSHOU01_H_
#define NIANSHOU01_H_

#include "RenderableObject.h"
#include "IUpdater.h"

class NianShou01 : public RenderableObject, public IUpdater
{
private:

public:
	NianShou01(const char* filepath, float x, float y, float z);
	~NianShou01();

	virtual void Clean() final;
	virtual void RenDeltaTime() override;
	virtual void Update() override;
};

#endif // !NIANSHOU01_H_