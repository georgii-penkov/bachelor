// drawoverride.cpp
// This file overrides the Draw method of the Point class using OpenGL (GLAD + GLFW + GLM)

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "threedgeometry.cpp"  // Assuming it contains the definition of Point and dependencies
#include <iostream>

// Override or extend the Point::Draw method to use OpenGL
void Point::Draw() const {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex3f(this->X(), this->Y(), this->Z());
    glEnd();
}

// Basic GLFW + GLAD setup for demonstration
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//int main() {
void drawoverride(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        //return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Point Draw", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        //return -1;
    }

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Normally you'd upload the projection/view matrix to a shader here
        // This placeholder assumes fixed pipeline usage, for demonstration only

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));

        Point p(1.0, 1.0, 1.0);
        p.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    //return 0;
}