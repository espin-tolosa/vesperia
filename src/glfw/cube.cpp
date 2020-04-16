#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>
#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <cstdio>

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        if(key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, controls);

    // Get info of GPU and supported OpenGL version
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

/*void showFPS(GLFWwindow *pWindow, double *lastTime, int nbFrames)
{
    // Measure speed
     double currentTime = glfwGetTime();
std::cout << "lastTime before update: " << *lastTime << std::endl;
std::cout << "currentTime before update: " << currentTime << std::endl;
     double delta = currentTime - *lastTime;
     std::cout << "Delta Time: " << delta << std::endl;
     nbFrames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
	 //std::cout << 1000.0/double(nbFrames) << std::endl;

         double fps = nbFrames / delta;

         std::stringstream ss;
         ss << "GAME_NAME: cube" << " " << "VERSION: 0.1" << " [" << fps << " FPS]";

         glfwSetWindowTitle(pWindow, ss.str().c_str());

         nbFrames = 0;
         lastTime = &currentTime;

        std::cout << "Delta Time after update lastTime: " << delta << std::endl;
	std::cout << "lastTime after update: " << *lastTime << std::endl;
	std::cout << "currentTime after update: " << currentTime << std::endl;
	//std::cin.get();
	//unsigned int microseconds = 100;
	//usleep(microseconds);
     }

}*/

void drawOctree()
{
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.5f,  0.5f);
	glVertex2f( 0.5f,  0.5f);
	glVertex2f( 0.5f, -0.5f);
	glEnd();
}

void drawTetrahedron(double alpha0)
{

	float p0[3]{0.0f, 0.0f, 0.0f};
	float p1[3]{1.0f, 0.0f, 0.0f};
	float p2[3]{0.0f, 1.0f, 0.0f};
	float p3[3]{0.0f, 0.0f, 10.0f};
	
    GLfloat vertices[] =
    {
        p0[0],p0[1],p0[2], p2[0],p2[1],p2[2], p1[0],p1[1],p1[2], 
	p0[0],p0[1],p0[2], p1[0],p1[1],p1[2], p3[0],p3[1],p3[2],
	p1[0],p1[1],p1[2], p2[0],p2[1],p2[2], p3[0],p3[1],p3[2],
	p2[0],p2[1],p2[2], p0[0],p0[1],p0[2], p3[0],p3[1],p3[2]
    };

    GLfloat colors[] =
    {
        1, 0, 0,   0, 1, 0,   0, 0, 1,
        1, 0, 0,   0, 1, 0,   0, 0, 1,
        1, 0, 0,   0, 1, 0,   0, 0, 1,
        1, 0, 0,   0, 1, 0,   0, 0, 1
    };

    static float alpha = 0.0f;
    //attempt to rotate cube
    glRotatef(alpha0, 0,0,0);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 12 vertices */
    glDrawArrays(GL_TRIANGLES, 0, 12);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += alpha0;
}

void drawCube(double alpha0)
{
    GLfloat vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    static float alpha = 0.0f;
    //attempt to rotate cube
    glRotatef(alpha0, 0.0, 0.1, 0);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += alpha0;
}

void display( GLFWwindow* window)
{
    while(!glfwWindowShouldClose(window))
    {
        // Scale to window size
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        // Draw stuff
        glClearColor(0.0, 0.5, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,0,-5);

        //drawCube();
		drawOctree();
        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}


			static bool Rotation_Axis_X{0};
			static bool Rotation_Axis_Y{0};
			static bool Rotation_Axis_Z{0};

			static float time_since_last_key_pressed{0.0};

			static float Camera_UpDown_Position{0.0f};

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	std::cout << "KEY PRESSED: " << key << std::endl;
	if(glfwGetTime() -  time_since_last_key_pressed > 0.1)
	{
		time_since_last_key_pressed = glfwGetTime();
		if(key == 65){
			Rotation_Axis_X = !Rotation_Axis_X;	
		}
		else if(key == 87){
			Rotation_Axis_Y = !Rotation_Axis_Y;
		}
		else if(key == 68){
			Rotation_Axis_Z = !Rotation_Axis_Z;
		}
		else if(key == 49){
			glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    			glPointSize(10);
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		}
		else if(key == 50){		
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
		else if(key == 51){		
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		else if(key == 265){
			Camera_UpDown_Position -= 100.0f;
		}
		else if(key == 264){
			Camera_UpDown_Position += 100.0f;
		}

	}
}

class Window
{
		private:
			const char *m_Title;
			int m_Width, m_Height, m_FPSFrames;
			float m_ZFar, m_ZNear;
			GLFWwindow *m_Window;
			bool m_Closed;
		    double m_lastTime;

		public:
			double xMouse, yMouse;

		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void display() const;
			void showFPS();
			void drawLine(const float& x0, const float& y0, const float& z0, const float& x1, const float& y1, const float& z1, const int& r, const int& g, const int& b);
			void drawTetrahedron(double alpha0);

		private:
			bool init();

};

Window::Window(const char *title, int width, int height)
	: m_ZFar{1000.0f}, m_ZNear{0.1f}, m_lastTime{glfwGetTime()}, m_FPSFrames{0}
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	if(!init())
	glfwTerminate();
};


Window::~Window()
{
	glfwTerminate();
};


void Window::update()
{
	// Draw stuff 
	std::cout << "AXIS X ROTATE: " << Rotation_Axis_X << std::endl;
    	//double currentTime = glfwGetTime();
	
	double dark_green[3] = {0.0, 0.5, 0.3};
	glfwGetCursorPos(m_Window, &xMouse, &yMouse);
	std::cout << "Mouse Position: X= " << xMouse << " Y= " << yMouse << std::endl; 
	glClearColor(xMouse/800.0, yMouse/600.0, 0.0,  0.1); 
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//Display the cube
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 60, (double)m_Width / (double)m_Height, m_ZNear, m_ZFar );
        glMatrixMode(GL_MODELVIEW_MATRIX);
	glTranslatef(0,0,-0.01*Camera_UpDown_Position);
		drawCube(xMouse);
		drawTetrahedron(xMouse);
		showFPS();
		drawLine(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 1,0,0);
		drawLine(0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0,1,0);
		drawLine(0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0,0,1);
        // Update Screen
        glfwSwapBuffers(m_Window);
        // Check for any input, or window movement
        glfwPollEvents();
};

void Window::display() const
{
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( 60, (double)m_Width / (double)m_Height, 0.1, 100 );

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0,0,-5);

        drawCube(xMouse);
	//drawOctree();
        // Update Screen
        glfwSwapBuffers(m_Window);

        // Check for any input, or window movement
        glfwPollEvents();
};

bool Window::init()
{
	if(!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);	

	// Get info of GPU and supported OpenGL version
    	glfwMakeContextCurrent(m_Window);
    	printf("Renderer: %s\n", glGetString(GL_RENDERER));
    	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
	//states the pwindow to scan the keyboard to out method keyCallback
	glfwSetKeyCallback( m_Window, keyCallback );
	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Failed to create GLFW window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);

	return true;
};

bool Window::closed() const
{
	return glfwWindowShouldClose(m_Window);

};

void Window::showFPS()
{
    // Measure speed
     double currentTime = glfwGetTime();
     double delta = currentTime - m_lastTime;
     m_FPSFrames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago

         double fps = m_FPSFrames / delta;

         std::stringstream ss;
         ss << "GAME_NAME: cube" << " " << "VERSION: 0.1" << " [" << fps << " FPS]";

         glfwSetWindowTitle(m_Window, ss.str().c_str());

         m_FPSFrames = 0;
         m_lastTime = currentTime;
     }

}

void Window::drawLine(const float& x0, const float& y0, const float& z0, const float& x1, const float& y1, const float& z1, const int& r, const int& g, const int& b)
{
	glBegin(GL_LINES);
		glVertex3f(x0,y0,z0);
		glVertex3f(x1,y1,z1);
		glColor3f(r,g,b);
	glEnd();

	/*GLfloat polygonVertices[] =
	{
		2,10,0,
		10,30,0,
		50,5,10,
		40,40,5
	};*/

}

void Window::drawTetrahedron(double alpha0)
{

	float p0[3]{0.0f, 0.0f, 0.0f};
	float p1[3]{1.0f, 0.0f, 0.0f};
	float p2[3]{0.0f, 1.0f, 0.0f};
	float p3[3]{0.0f, 0.0f, 1.0f};
	
    GLfloat vertices[] =
    {
        p0[0],p0[1],p0[2], p2[0],p2[1],p2[2], p1[0],p1[1],p1[2], 
		p0[0],p0[1],p0[2], p1[0],p1[1],p1[2], p3[0],p3[1],p3[2],
		p1[0],p1[1],p1[2], p2[0],p2[1],p2[2], p3[0],p3[1],p3[2],
		p2[0],p2[1],p2[2], p0[0],p0[1],p0[2], p3[0],p3[1],p3[2]
    };

    GLfloat colors[] =
    {
        1, 0, 0,   1, 0, 0,   1, 0, 0,
        0, 1, 0,   0, 1, 0,   0, 1, 0,
        0, 0, 1,   0, 0, 1,   0, 0, 1,
        1, 0, 0,   0, 1, 0,   0, 0, 1
    };

    static float alpha = 0.0f;
    //attempt to rotate cube
    glRotatef(alpha0, Rotation_Axis_X, Rotation_Axis_Y, Rotation_Axis_Z);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 12 vertices */
    glDrawArrays(GL_TRIANGLES, 0, 12);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += alpha0;
}

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
