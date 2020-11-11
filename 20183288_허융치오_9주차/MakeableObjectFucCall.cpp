#include "MakeableObjectFucCall.h"
#include "IUpdater.h"
#include "ICleanUp.h"
#include "IInit.h"

MakeableObjectFucCall * MakeableObjectFucCall::m_instance;

void MakeableObjectFucCall::AddInitObject(IInit* init)
{
	objinit.push_back(init);
}
void MakeableObjectFucCall::AddUpdateObject(IUpdater* updater)
{
	objupdater.push_back(updater);
	//objupdater->push_back(*updater);
}
void MakeableObjectFucCall::AddCleanObject(IClean* cleaner)
{
	objcleaner.push_back(cleaner);
}


void MakeableObjectFucCall::CallAllInit()
{
	std::vector<IInit*>::iterator iter;
	for (iter = objinit.begin(); iter != objinit.end(); iter++)
	{
		(*iter)->Init();
	}
}
void MakeableObjectFucCall::CallAllUpdate()
{
	std::vector<IUpdater*>::iterator iter;
	for (iter = objupdater.begin(); iter != objupdater.end(); iter++)
	{
		(*iter)->Update();
	}

}
void MakeableObjectFucCall::CallAllClean()
{
	std::vector<IClean*>::iterator iter;
	for (iter = objcleaner.begin(); iter != objcleaner.end(); iter++)
	{
		(*iter)->Clean();
	}
}