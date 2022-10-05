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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"


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
        //float positions[] = {
        //    -50.0f, -50.0f,  0.0f, 0.0f,
        //     50.0f, -50.0f,  1.0f, 0.0f,
        //     50.0f,  50.0f,  1.0f, 1.0f,
        //    -50.0f,  50.0f,  0.0f, 1.0f
        //}; //square: 0,1,2,2,3,0

        //unsigned int indices[] = {
        //    0, 1, 2,
        //    2, 3, 0
        //};


		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
  //      VertexArray va;
  //      VertexBuffer vb(positions, 4 * 4 * sizeof(float));
  //      
  //      VertexBufferLayout layout;
  //      layout.Push<float>(2);
  //      layout.Push<float>(2);
  //      va.AddBuffer(vb, layout);

  //      IndexBuffer ib(indices, 6);

  //      glm::mat4 proj = glm::ortho(0.0f, 690.0f, -0.0f,540.0f);
  //      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		///* glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0)); */
		///* glm::mat4 mvp = proj * view * model; */

  //      Shader shader("res/shaders/Basic.shader");
		//shader.Bind();
		//// shader.SetUniform4f("u_Colour", 0.8f, 0.3f, 0.8f, 1.0f);
  //      // shader.SetUniformM4f("u_MVP", mvp);

		//Texture texture("res/textures/logo.png");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

  //      va.Unbind();
		//vb.Unbind();
		//ib.Unbind();
		//shader.Unbind();

		Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();


		/*glm::vec3 translationA(200, 200, 0);
		glm::vec3 translationB(400, 200, 0);

        float r = 1.0f;
        float increment = 0.05f;

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);*/

        test::TestClearColor test;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
			renderer.Clear();
            /* glClear(GL_COLOR_BUFFER_BIT); */

            test.OnUpdate(0.0f);
            test.OnRender();

            ImGui_ImplGlfwGL3_NewFrame();

            test.OnImGuiRender();

			//{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			//	glm::mat4 mvp = proj * view * model;

			//	shader.Bind();

			//	shader.SetUniformM4f("u_MVP", mvp);
			//	renderer.Draw(va, ib, shader);
			//}

   //         /* shader.SetUniform4f("u_Colour", r, 0.0, 0.2, 1.0); */

			//{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			//	glm::mat4 mvp = proj * view * model;

			//	shader.Bind();

			//	shader.SetUniformM4f("u_MVP", mvp);
			//	renderer.Draw(va, ib, shader);
			//}


   //         if (r > 1.0f)
   //             increment = -increment;
   //         else if (r < 0.0f)
   //             increment = -increment;
   //         r += increment;


   //         {
   //             /* ImGui::SliderFloat("float", &f, 0.0f, 1.0f); */
			//	ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
			//	ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
   //             /* ImGui::ColorEdit3("clear color", (float*)&clear_color); */
   //             

   //             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
   //         }


            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
