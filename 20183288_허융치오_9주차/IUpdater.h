#ifndef  IUPDATER_H_
#define  IUPDATER_H_

#include <iostream>

class IUpdater
{
protected:
	float DeltaTime = 0;
	float lastFrame = 0.0f;

public:
	virtual void RenDeltaTime() = 0;
	virtual void Update() = 0;
};

#endif // ! IUPDATER_H_