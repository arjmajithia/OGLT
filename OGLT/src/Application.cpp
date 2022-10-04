#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 1240, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glewInit();

    {
        float positions[] = {
            100.5f, 100.0f, 0.0f, 0.0f,
            200.0f, 100.0f, 1.0f, 0.0f,
            200.0f, 200.0f, 1.0f, 1.0f,
            100.0f, 200.0f, 0.0f, 1.0f
        }; //square: 0,1,2,2,3,0

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };


		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        /*unsigned int buffer;
        GLCALL(glGenBuffers(1, &buffer));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));*/

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 690.0f, -0.0f,540.0f);
        //glm::mat4 proj = glm::ortho(0.75f, -0.75f, -0.625f, 0.625f);

        Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		// shader.SetUniform4f("u_Colour", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformM4f("u_MVP", proj);

		Texture texture("res/textures/logo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

        float r = 1.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
			renderer.Clear();
            /* glClear(GL_COLOR_BUFFER_BIT); */

			shader.Bind();
            // shader.SetUniform4f("u_Colour", r, 0.0, 0.2, 1.0);

            // GLCALL(glBindVertexArray(vao));
            /* va.Bind(); */
            /* ib.Bind(); */

            //GLClearError();
            renderer.Draw(va, ib, shader);
            /* GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); */
            //ASSERT(GLLogCall());
            //glDrawArrays(GL_TRIANGLES, 0, 6);

            if (r > 1.0f)
                increment = -increment;
            else if (r < 0.0f)
                increment = -increment;
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
