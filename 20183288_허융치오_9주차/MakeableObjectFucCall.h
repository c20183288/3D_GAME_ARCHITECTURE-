#ifndef MAKEABLEOEJCTFUCALL_H
#define MAKEABLEOEJCTFUCALL_H

#include <iostream>
#include <vector>

class IUpdater;
class IClean;
class IInit;

class MakeableObjectFucCall
{
private:
	std::vector<IUpdater*> objupdater;
	std::vector<IClean*> objcleaner;
	std::vector<IInit*> objinit;

	static MakeableObjectFucCall* m_instance;

public:
	static MakeableObjectFucCall* Instance()
	{
		if (m_instance == NULL)
		{
			m_instance = new MakeableObjectFucCall();
		}
		return m_instance;
	}

	void AddInitObject(IInit* init);
	void AddUpdateObject(IUpdater* updater);
	void AddCleanObject(IClean* cleaner);

	void CallAllInit();
	void CallAllUpdate();
	void CallAllClean();
};

#endif // !MAKEABLEOEJCTFUCALL_H?