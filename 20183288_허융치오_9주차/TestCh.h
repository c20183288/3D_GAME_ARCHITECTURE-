#include <iostream>
#include "RenderableObject.h"
#include "IUpdater.h"

class TestCh : public RenderableObject
{
public:
	TestCh() {}

	virtual void Init() final { std::cout << "启动test" << std::endl; }
	virtual void Clean() final { std::cout << "清除test" << std::endl; }
	virtual void RenDeltaTime() override {}
	virtual void Update() final { std::cout << "更新test" << std::endl; }
};