#include "Cube.h"
#include "NianShou01.h"
#include "NianShou02.h"
#include "Camera.h"
#include "FileManager.h"
#include "IUpdater.h"
#include "Renderer.h"
#include "TestCh.h"

int main()
{
	glm::mat4 cameraprojection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 cameraview = glm::lookAt(
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 1)
	);

	Cube* cube = new Cube("cube.obj", 3.0f, 0.0f, 0.0f);
	NianShou01* nianshou01 = new NianShou01("nianshou01.obj", -10.0f, -4.0f, 0.0f);
	NianShou02* nianshou02 = new NianShou02("nianshou02.obj", -10.0f, -4.0f, 0.0f);
	TestCh* test = new TestCh();

	Camera* maincamera = new Camera();
	maincamera->SetProjection(cameraprojection);
	maincamera->SetView(cameraview);

	Renderer::Instance()->AddNonrenderObject("MainCamera", *maincamera);

	Renderer::Instance()->SetWindowSize(1920, 1080);
	Renderer::Instance()->Render();

	delete cube;
	delete nianshou01;
	delete nianshou02;
	delete maincamera;

	return 0;
}
