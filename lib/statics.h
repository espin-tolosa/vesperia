#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

bool Log_Status   = true;
bool Write_Mesh   = true;
bool Write_Octree = false;
bool Write_Vec3   = false;
unsigned octreeSHM::Depth = 0;

float Window::time_since_last_key_pressed = 0.0f;
float Window::Camera_UpDown_Position = 0.0f;

bool Window::Rotation_Axis_X = 0;
bool Window::Rotation_Axis_Y = 0;
bool Window::Rotation_Axis_Z = 0;

#endif // STATICS_H_INCLUDED
