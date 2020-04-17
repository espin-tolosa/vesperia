#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "../geometry/structuredHexMesh.h"

void drawOctree();
void drawTetrahedron(double alpha0);
void drawCube(double alpha0);
//static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

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
			static float Displace_Axis_X;
			static float Displace_Axis_Y;
			static float Displace_Axis_Z;
			static bool Rotation_Axis_X;
			static bool Rotation_Axis_Y;
			static bool Rotation_Axis_Z;
			static float time_since_last_key_pressed;
			static float Camera_UpDown_Position;

		public:
			Window(const char *title, int width, int height);
			~Window();
			bool closed() const;
			void update(structuredHexMesh* mesh);
			void display() const;
			void showFPS();
			void drawLine(const float& x0, const float& y0, const float& z0, const float& x1, const float& y1, const float& z1, const int& r, const int& g, const int& b);
			void drawTetrahedron(double alpha0);
			static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		private:
			bool init();

};

#endif // WINDOW_H_INCLUDED
