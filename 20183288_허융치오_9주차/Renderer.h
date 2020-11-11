#ifndef RENDERER_H_
#define RENDERER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>

#include "ICleanUp.h"
#include "IUpdater.h"
#include "../include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class RenderableObject;
class NonRenderableObject;

class Renderer : public IClean, public IUpdater
{
private:
	static Renderer* r_instance;
	Renderer();

	GLFWwindow* window;
	std::vector<RenderableObject> renderableObject;
	std::map<std::string, NonRenderableObject>* nonrenderableObject;


	void SettingCamera();
	void DrawWindow(const char* exename);
	glm::vec3 cameraPos = glm::vec3(-20.0f, 10.0f, -10.0f);
	glm::vec3 cameraFront = glm::vec3(-10.0f, -10.0f, -10.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 SettingCameraZoom;
	glm::mat4 SettingCameraMove;

	int windowWidth = 900;
	int windowHeight = 700;

	double xpos = 0;
	double ypos = 0;

	float lastmousex = 0.0f;
	float lastmousey = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;

	float fov = 45.0f;
	bool checkmousecursor = true;

public:
	//	float DeltaTime = 0.0f;
	static Renderer* Instance()
	{
		if (r_instance == NULL)
		{
			r_instance = new Renderer();
		}
		return r_instance;
	}
	void SetWindowSize(int width, int height);
	void Render();

	void AddObject(RenderableObject& renderableobject);
	void AddNonrenderObject(std::string name, NonRenderableObject& nonrenderableobject);

	void KeyboardInput(GLFWwindow* window);
	void MouseInput(GLFWwindow* window);

	virtual void Clean() override;
	virtual void RenDeltaTime() override;
	virtual void Update() override;

};

#endif // !