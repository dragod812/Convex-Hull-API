#include "include/glad.h"
#include "include/shader.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
using namespace glm;
using namespace std;

const GLuint SCR_WIDTH = 1920;
const GLuint SCR_HEIGHT = 1080;
vector< vec3 > Points;
void normalize(double *x, double *y){
	*y = SCR_HEIGHT - *y;
	*y = (*y*2)/(SCR_HEIGHT);
	*y -= 1;
	*x = (*x*2)/(SCR_WIDTH);
	*x -= 1;
}
void processKeyboardInput(GLFWwindow *window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		normalize(&xpos, &ypos);
		Points.push_back(vec3(xpos, ypos, 0));
		cout << xpos << ',' << ypos << endl;
	}
}
int main(){
	//initialise glfw and configure
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwCreateWindow: GLFWwindow* glfwCreateWindow(int width,int height, const char * title,GLFWmonitor * monitor,GLFWwindow * share )
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Convex Hull", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	//Use Shader class to read shader files and create shaders
	Shader sh("shaders/vertexShader.vs", "shaders/fragmentShader.fs");

	//mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//define vertex array objects and vertex buffer objects
	//VAO:subsequent vertex attribute calls from that point on will be stored inside the VAO. All the bindings of buffers are stored in the vertex array object.
	//VBO:store a large number of vertices in the GPU's memory. The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics card without having to send data a vertex a time.




	while(!glfwWindowShouldClose(window)){
		GLuint VAOP, VBOP;
		glGenVertexArrays(1, &VAOP);
		glGenBuffers(1, &VBOP);
		glBindVertexArray(VAOP);
		glBindBuffer(GL_ARRAY_BUFFER, VBOP);
		glBufferData(GL_ARRAY_BUFFER, Points.size()*sizeof(vec3), &Points[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		processKeyboardInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw Points as and when clicked;
		sh.use();
		glPointSize(6);
		glBindVertexArray(VAOP);
		//glBufferData(GL_ARRAY_BUFFER, Points.size()*sizeof(vec3), &Points[0], GL_DYNAMIC_DRAW);
		sh.setVec3("color", vec3(1.0, 0.0, 1.0));
        glDrawArrays(GL_POINTS, 0, Points.size());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//clear all perviously allocate GLFW resources.
	glfwTerminate();
	return 0;
}
