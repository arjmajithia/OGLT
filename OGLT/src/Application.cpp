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






int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        }; //square: 0,1,2,2,3,0

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        
        VertexArray vao;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        vao.AddBuffer(vb, layout);


        /*unsigned int buffer;
        GLCALL(glGenBuffers(1, &buffer));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));*/

        IndexBuffer ib(indices, 6);

        /*unsigned int ibo;
        GLCALL(glGenBuffers(1, &ibo));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW)); */  // can use unsigned char or short, but must be unsigned

        Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Colour", 0.8f, 0.3f, 0.8f, 1.0f);

        vao.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

        float r = 1.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            GLCALL(shader.Bind());
            GLCALL(shader.SetUniform4f("u_Colour", r, 0.0, 0.2, 1.0));

            // GLCALL(glBindVertexArray(vao));
            vao.Bind();
            ib.Bind();

            //GLClearError();
            GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
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
