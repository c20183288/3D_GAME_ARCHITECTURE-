#ifndef TIME_H_
#define TIME_H_

#include <iostream>
#include <Windows.h>

class Time
{
private:
	int fixingframe;
	double perframe;
	LARGE_INTEGER frameinfo;
	LARGE_INTEGER preframecount;
	LARGE_INTEGER framecount;

	bool firstcall = false;

	~Time() {}
	static Time* t_instance;

	void SetFrame();
public:
	static Time* Instance()
	{
		if (t_instance == NULL)
		{
			t_instance = new Time();
		}
		return t_instance;
	}

	bool PerRenderFrame();
	void TimeOff();
};


#endif // !TIME_H_
