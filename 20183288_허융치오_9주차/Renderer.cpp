#include "Renderer.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "FileManager.h"
#include "Time.h"
#include "MakeableObjectFucCall.h"

Renderer* Renderer::r_instance;

Renderer::Renderer()
{
	nonrenderableObject = new std::map<std::string, NonRenderableObject>();
}

void Renderer::SetWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

void Renderer::DrawWindow(const char* exename)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, exename, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
}
void Renderer::AddObject(RenderableObject& renderableobject)
{
	renderableObject.push_back(renderableobject);
}
void Renderer::AddNonrenderObject(std::string name, NonRenderableObject& nonrenderableobject)
{
	nonrenderableObject->
		//insert(<std::string, NonRenderableObject>(name, nonrenderableobject));
		insert(std::make_pair(name, nonrenderableobject));
}
void Renderer::Clean()
{
	if (!renderableObject.empty())
	{
		for (std::vector<RenderableObject>::iterator cleaniter = renderableObject.begin();
			cleaniter != renderableObject.end();
			++cleaniter)
		{
			cleaniter->Clean();
		}
		std::vector<RenderableObject>().swap(renderableObject);
	}
	if (!nonrenderableObject->empty())
	{
		nonrenderableObject->clear();
	}
	MakeableObjectFucCall::Instance()->CallAllClean();
}

void Renderer::RenDeltaTime()
{
	float currentframe = glfwGetTime();
	DeltaTime = currentframe - lastFrame;
	lastFrame = currentframe;

}

void Renderer::Update()
{

	MakeableObjectFucCall::Instance()->CallAllUpdate();
}

void Renderer::KeyboardInput(GLFWwindow* window)
{
	float cameraSpeed = 10.0f * DeltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (fov < 1.0f)
			fov = 1.0f;
		else
			fov -= 0.5f;
	}
	else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{ 
		if (fov > 45.0f)
			fov = 45.0f;
		else
			fov += 0.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		checkmousecursor = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		checkmousecursor = true;
	}
}

void Renderer::MouseInput(GLFWwindow* window)
{
	if (checkmousecursor == false)
		return;
	float xoffset = xpos - lastmousex;
	float yoffset = lastmousey - ypos;
	lastmousex = xpos;
	lastmousey = ypos;
	// 

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch >= 90.0f)
		pitch = 89.0f;
	if (pitch <= -90.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Renderer::SettingCamera()
{
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		SettingCameraZoom =
			nonrenderableObject->find("MainCamera")->second.GetProjection();
		SettingCameraMove =
			nonrenderableObject->find("MainCamera")->second.GetView();
	}
	else
	{
		SettingCameraZoom = glm::perspective(glm::radians(fov), (float)windowWidth
			/ (float)windowHeight, 0.1f, 100.0f);
		SettingCameraMove = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
}

void Renderer::Render()
{
	if (renderableObject.empty())
		return;

	DrawWindow("20183288_week 9 report");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//MVP = object->GetMVP();
	GLuint programID = FileManager::Instance()->LoadShaders("vs.shader", "fs.shader");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	std::vector<RenderableObject>::iterator obiter;
	std::vector<NonRenderableObject>::iterator nonobiter;

	std::vector<glm::mat4> rendermvp(renderableObject.size());
	std::vector<GLuint> vertexbuffer(renderableObject.size());
	std::vector<GLuint> uvbuffer(renderableObject.size());
	std::vector<GLuint> normalbuffer(renderableObject.size());

	int setbuffer = 0;
	int renderbuffer = 0;

	for (obiter = renderableObject.begin(); obiter != renderableObject.end(); ++obiter)
	{
		glGenBuffers(1, &vertexbuffer[setbuffer]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[setbuffer]);
		glBufferData(GL_ARRAY_BUFFER, obiter->GetVertex().size() * sizeof(glm::vec3), &(obiter->GetVertex())[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uvbuffer[setbuffer]);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[setbuffer]);
		glBufferData(GL_ARRAY_BUFFER, obiter->GetUV().size() * sizeof(glm::vec2), &(obiter->GetUV())[0], GL_STATIC_DRAW);

		glGenBuffers(1, &normalbuffer[setbuffer]);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[setbuffer]);
		glBufferData(GL_ARRAY_BUFFER, obiter->GetNormal().size() * sizeof(glm::vec3), &(obiter->GetNormal())[0], GL_STATIC_DRAW);

		rendermvp[setbuffer] = obiter->GetMVP();
		setbuffer++;
	}

	glm::mat4 rotate = glm::mat4(1.0f);
	float rotangle = 1.0f;

	MakeableObjectFucCall::Instance()->CallAllInit();

	do {

		if (Time::Instance()->PerRenderFrame())
		{
			RenDeltaTime();
			Update();
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		KeyboardInput(window);

		glfwGetCursorPos(window, &xpos, &ypos);
		MouseInput(window);

		SettingCamera();

		renderbuffer = 0;
		rotate = glm::rotate(rotate, glm::radians(rotangle), glm::vec3(0.0f, 1.0f, 0.0f));

		for (obiter = renderableObject.begin(); obiter != renderableObject.end(); ++obiter)
		{
			//obiter->SetP(rendermvp[renderbuffer], rotate);
			obiter->SetMVP(SettingCameraZoom, SettingCameraMove, obiter->GetPosition());
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(obiter->GetMVP())[0][0]);
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(TextureID, 0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[renderbuffer]);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[renderbuffer]);
			glVertexAttribPointer(
				1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				2,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[renderbuffer]);
			glVertexAttribPointer(
				2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset

			);
			glDrawArrays(GL_TRIANGLES, 0, obiter->GetVertex().size());
			renderbuffer++;
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	Clean();
	glDeleteProgram(programID);
}