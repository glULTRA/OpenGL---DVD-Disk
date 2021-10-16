#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ctime>
#include <iostream>

#include "Shader.h"

float Vertices[10000];
float Vertices2[10000];

void Set_Frame_Buffer(GLFWwindow* window, int x, int height);
void UserInput(GLFWwindow* window);
glm::vec2 dir = glm::vec2(0.0f , 0.3f);

int main()
{
	// Random time
	srand(time(NULL));

	// Initialize GLFW
	glfwInit();

	// Initialize 3.3 Version (Core Profile)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(1000,800,"Lana", NULL, NULL);

	// Initialize Window
	if(!window) return -1;

	// Important Part !
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Set_Frame_Buffer);


	// Initialize Glad
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return -1;

	// Circle Data
	glm::vec3 EachColor = glm::vec3(0.8f, 0.2f, 1.0f);
	for(int i = 0, j = 0, Count = 0; i < 1010; i++ , j+=6)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(1000);

        float x = 0.5f * cosf(theta);
        float y = 0.5f * sinf(theta);

		if(x == 0 || y == 0) continue;
		
		if(i < 100)
		{
			EachColor.z -= 0.005f;
		}
		else if(i < 200){
			EachColor.z += 0.005f;
		}
		else if(i < 300){
			EachColor.z -= 0.005f;
		}
		else if(i < 400){
			EachColor.z += 0.005f;
		}
		else if(i < 500){
			EachColor.z -= 0.005f;
		}else if(i < 600){
			EachColor.z += 0.005f;
		}else if(i < 700){
			EachColor.z -= 0.005f;
		}else if(i < 800){
			EachColor.z += 0.005f;
		}else if(i < 900){
			EachColor.z -= 0.005f;
		}else if(i < 1000){
			EachColor.z += 0.005f;
		}

		Vertices[j] = x;
		Vertices[j + 1] = y ;
		Vertices[j + 2] = 0 ;

		// Color
		Vertices[j + 3] = EachColor.x;
		Vertices[j + 4] = EachColor.y;
		Vertices[j + 5] = EachColor.z;
    }

	// Small Circle 
    for(int i = 0; i < 1000; i+=3)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(1000);

        float x = 0.5 * cosf(theta);
        float y = 0.5 * sinf(theta);

		Vertices2[i] = x;
		Vertices2[i + 1] = y;
		Vertices2[i + 2] = 0;
	}


	// Buffers
	GLuint VBO,VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices, GL_STATIC_DRAW);
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) ( 3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Buffer 2 
	GLuint VBO2,VAO2;

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), &Vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	
	
	// Shader
	Shader shader("../res/Shader/LargeCircle.vert" , "../res/Shader/LargeCircle.frag"); // For run time
	Shader shader2("../res/Shader/SmallCircle.vert" , "../res/Shader/SmallCircle.frag"); // For run time
	shader.use();
	shader2.use();
	// Render loop.
	while(!glfwWindowShouldClose(window))
	{
		/* Update */
		UserInput(window);
		float time = glfwGetTime();
		
		float xValue = std::cos(time) / 2.0f + 0.5f;
		float yValue = std::sin(time) / 2.0f + 0.5f;
		float zValue = std::cos(time) / 2.0f + 0.5f;

		glm::vec3 Color = glm::vec3(1.0f);
		glm::mat4 shapePos = glm::mat4(1.0f);

		/* Render */
		glClearColor(0.04f,0.3f, 0.34f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();

		// Draw
		Color = glm::vec3(xValue, 0.4f,0.8f);
		shapePos = glm::rotate(shapePos, glm::radians(-180.0f) * time  , glm::vec3(0.0f, 0.0f, 1.0f));
		shapePos = glm::scale(shapePos, glm::vec3(0.78f));
		shader.setMat4("pos", shapePos);
		shader.setVec3("Color", Color);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0,2000);

		shader2.use();
		Color = glm::vec3(0.0f);
		shapePos = glm::mat4(1.0f);
		shapePos = glm::scale(shapePos, glm::vec3(0.15f));
		shader2.setMat4("pos", shapePos);
		shader2.setVec3("Color", Color);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 1000);

		shader2.use();
		shapePos = glm::mat4(1.0f);
		Color = glm::vec3(1.0f, 1.0f, 1.0f);
		shapePos = glm::scale(shapePos, glm::vec3(0.07f));
		shader2.setMat4("pos", shapePos);
		shader2.setVec3("Color", Color);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 1000);

		// Display
		glfwSwapBuffers(window);

		// Poll Events
		glfwPollEvents();
	}
	
}

void Set_Frame_Buffer(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void UserInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_TRUE) 
		glfwSetWindowShouldClose(window, true);

}