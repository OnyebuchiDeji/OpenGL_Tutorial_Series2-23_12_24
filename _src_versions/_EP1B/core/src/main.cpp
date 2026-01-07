#include "config.h"

int main()
{
    std::cout << "Yo! Yo! Yo!\n";

    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cout << "GLFW could not start!!!\n";
        return -1;
    }

    /**
     * @brief
     *  arg4: specifies which monitor the window will be full screened on.
     *      if NULL, it floats as a random window, not fullscreen anywhere.
     *      though one could specify primary monitor or secondary monitor fot it to appear
     *      full screen there.
     * 
     */
    window = glfwCreateWindow(640, 480, "Yo Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    //  Tell glad to fetch all openGL procedures
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    //  From the GLAD library for the OpenGL functions
    glClearColor(0.85f, 0.3f, 0.7f, 1.0f);

    /**
     * @brief 
     *  Keep the window up until the Close button is clicked.
     * 
     */
    while (!glfwWindowShouldClose(window))
    {
        /**
         * @brief 
         *  This keeps the event queue from overflowing by clearing it every frame. 
         */
        glfwPollEvents();

        //  To clear the color buffer and signalled by this bit.
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();


    return 0;
}