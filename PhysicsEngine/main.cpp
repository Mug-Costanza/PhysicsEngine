//Project Files
#include "src/window.hpp"

int main()
{
    glewExperimental = true;
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Faild to initialize GLEW'" << std::endl;
        
        return -1;
    }
    
    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        
        return -1;
    }
    
    Window window(800, 600, "Physics Engine");
    
    if(window.getWindow() == NULL)
    {
        std::cout << "Window failed to initialize" << std::endl;
        return -1;
    }
    
    while(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window.getWindow()) == 0 )
    {
        window.run();
    }
    
    window.cleanUp();
    
    return 0;
}
