#include <iostream>
#include <cstdio>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"



Window::Window(const char *title, int width, int height)
	: m_ZFar{1000.0f}, m_ZNear{0.1f}, m_lastTime{glfwGetTime()}, m_FPSFrames{0}
	//Rotation_Axis_X{0},
	//Rotation_Axis_Y{0},
	//Rotation_Axis_Z{0}

{
	
	//float Window::time_since_last_key_pressed;
	//float Window::Camera_UpDown_Position;
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

void Window::update(structuredHexMesh* mesh)
{
	// Draw stuff 
	//std::cout << "AXIS X ROTATE: " << Rotation_Axis_X << std::endl;
    	//double currentTime = glfwGetTime();
	
	double dark_green[3] = {0.0, 0.5, 0.3};
	glfwGetCursorPos(m_Window, &xMouse, &yMouse);
	//std::cout << "Mouse Position: X= " << xMouse << " Y= " << yMouse << std::endl; 
	glClearColor(0.01, 0.01, 0.01, 0.1); 
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//Display the cube
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective( -60, (double)m_Width / (double)m_Height, m_ZNear, m_ZFar );
        glMatrixMode(GL_MODELVIEW_MATRIX);
	std::cout << "CAMERA UPDOW POSITION: " << Displace_Axis_Z << std::endl;
//	glTranslatef(0,0,-0.01*Camera_UpDown_Position);

	glTranslatef(Displace_Axis_X, Displace_Axis_Y, Displace_Axis_Z);
//attempt to rotate cube
    	glRotatef(xMouse, Rotation_Axis_X, Rotation_Axis_Y, Rotation_Axis_Z);
		//drawCube(xMouse);
		//drawTetrahedron(xMouse);
		mesh->drawMesh(xMouse);
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

//AUXILIARY FUNCTIONS
//---------------------------------------------------------------------------- 
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

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	std::cout << "KEY PRESSED: " << key << std::endl;
	if(glfwGetTime() -  Window::time_since_last_key_pressed > 0.1)
	{
		Window::time_since_last_key_pressed = glfwGetTime();
		if(key == 88){
			Window::Rotation_Axis_X = !Window::Rotation_Axis_X;	
		}
		else if(key == 89){
			Window::Rotation_Axis_Y = !Window::Rotation_Axis_Y;
		}
		else if(key == 90){
			Window::Rotation_Axis_Z = !Window::Rotation_Axis_Z;
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
		else if(key == 264){
			Window::Displace_Axis_Y -= 0.01f;
		}
		else if(key == 265){
			Window::Displace_Axis_Y += 0.01f;
		}
		else if(key == 263){
			Window::Displace_Axis_X -= 0.01f;
		}
		else if(key == 262){
			Window::Displace_Axis_X += 0.01f;
		}
		else if(key == 32){
			Window::Displace_Axis_Z -= 0.1f;
		}

	}
}


/*
		else if(key == 265){
			Window::Displace_Axis_X -= 10.0f;
		}
		else if(key == 264){
			Window::Displace_Axis_X += 10.0f;

		else if(key == 263){
			Window::Displace_Axis_Y -= 10.0f;
		}
		else if(key == 262){
			Window::Displace_Axis_Y += 10.0f;
		}
		*/
