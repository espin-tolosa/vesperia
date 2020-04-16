#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <iostream>
//#include <conio.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <stdlib.h> /* system, NULL, EXIT_FAILURE */
#include <new>

//
// GLFW----------
//
#include <cstdio>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <GL/glew.h>

//USER SOURCES
#include "../constants/compiler.h" //contains usefull constants
#include "../src/maths/vectors.h"
#include "../src/geometry/meshes.h"
#include "../src/logs/log.h"
#include "../src/functions/setfun.h"

//#include "../src/materials/eos.h"
//#include "../src/materials/gas.h"

//#include "../src/phase/phase.h"

#include "../src/vtk/vtk_udef.h"

#include "../src/glfw/window.h"

#endif // LIB_H_INCLUDED
