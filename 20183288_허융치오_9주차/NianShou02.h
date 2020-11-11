#ifndef NIANSHOU02_H_
#define NIANSHOU02_H_

#include "RenderableObject.h"
#include "IUpdater.h"

class NianShou02 : public RenderableObject, public IUpdater
{
private:

public:
	NianShou02(const char* filepath, float x, float y, float z);
	~NianShou02();

	virtual void Clean() final;
	virtual void RenDeltaTime() override;
	virtual void Update() override;
};

#endif // !NIANSHOU01_H_