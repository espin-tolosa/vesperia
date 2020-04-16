#include <iostream>

#include "lib/lib.h"

int main(int argc, char** argv)
{
	Window window("samuel Engine v0.0", 400,300);
	while (!window.closed())
	{
		window.update();
		system("sleep 0.01");
		//window.display();
	}

	return 0;
		
		/*    GLFWwindow* window = initWindow(1024, 620);
    if( NULL != window )
    {
        display( window );
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
*/
}
