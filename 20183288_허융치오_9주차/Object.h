#ifndef  __OBJECT_H__
#define  __OBJECT_H__

#include <iostream>
#include <vector>

#include "ICleanUp.h"
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Object : public IClean
{
protected:
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normal;
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;

	virtual void SetMVP(glm::mat4 m, glm::mat4 v, glm::mat4 p) {}
	virtual void SetPosition(glm::mat4 m) {}
	virtual glm::mat4 GetMVP() const { return MVP; }
public:

	virtual ~Object() {};

	virtual void Clean() {};
};


#endif // !OBJECT_H_