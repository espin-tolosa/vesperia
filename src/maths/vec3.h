#ifndef VEC3_H_INCLUDED
#define VEC3_H_INCLUDED

#include <iostream>
#include <cstddef>

struct vec3
{
float x,y,z;

vec3();
vec3(const float& x, const float& y, const float& z);

void Add(const vec3&  other);
void Add(const float& other);

void Substract(const vec3& other);
void Substract(const float& other);

void Multiply(const vec3& other);
void Multiply(const float& other);

void Divide(const vec3& other);
void Divide(const float& other);

vec3 Loc2Glob(const vec3& other,const vec3& glob_ref);
vec3 Glob2Loc(const vec3& other,const vec3& loc_ref);

float Dot  (const vec3& other);
float Dot  (const vec3& A, const vec3& B);
vec3 Cross(const vec3& A, const vec3& B);				//return normal vertex in GLOBAL REFERENCE
vec3 UCross(const vec3& A, const vec3& B);                          //return unitary normal vertex in GLOBAL REFERENCE
vec3 Cross(const vec3& origin, const vec3& p2, const vec3& p3);	//return normal vertex in LOCAL REFERENCE

float DotCross(const vec3& A, const vec3& B, const vec3& C);
float DotCross(const vec3& origin, const vec3& p1, const vec3& p2, const vec3& p3);

//Rotation of p1 around global origin (0,0,0)
//this functions are the older rotations
vec3 RotX(const vec3& p1, const float& alpha);
vec3 RotY(const vec3& p1, const float& alpha);
vec3 RotZ(const vec3& p1, const float& alpha);

//Rotations along local origin p0
//this rotations are newer and still not implemented
//in the rst of the code that uses rotations
//    void LocRotX(const vec3& p0, float alpha);
//    void LocRotY(const vec3& p0, float alpha);
//    void LocRotZ(const vec3& p0, float alpha);

void LocRotX(const float& alpha);
void LocRotY(const float& alpha);
void LocRotZ(const float& alpha);

vec3 AbsoluteVec3(const vec3& p1);

float Norma();
float Norma(const vec3& other);

//Create a vertex between 3Dline Xi-Xj as: X(sigma(0:1))->|Xi:Xj|
vec3 Line(const vec3& Xi, const vec3& Xj, const float& sigma);

//Pointer functions to run over arrays elements of vec3 type
void ArithmeticForEach(vec3* array, const int& size_array, const vec3& other,  int method_type);
//Pointer functions to run over arrays elements of vec3 type
void LocRotForEach(vec3* array, const int& size_array, const float& alpha, int method_type);

friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);

//Multiplation overloading
vec3 friend operator*(const float& a, const vec3& b)
{
return vec3(a*b.x, a*b.y, a*b.z);
}

vec3 friend operator*(const vec3& b, const float a)
{
return vec3(a*b.x, a*b.y, a*b.z);
}

vec3 friend operator*(const vec3& a, const vec3& b)
{
return vec3(a.x*b.x, a.y*b.y, a.z*b.z);
}
//Division overloading
vec3 friend operator/(const float& a, const vec3& b)
{
std::cout<<"[WARNING]: Operation vec3/float shoul be used instead float/vec3 to avoid notation abuse\nd";
return vec3(b.x/a, b.y/a, b.z/a);
}

vec3 friend operator/(const vec3& b, const float a)
{
return vec3(b.x/a, b.y/a, b.z/a);
}

vec3 friend operator/(const vec3& a, const vec3& b)
{
return vec3(a.x/b.x, a.y/b.y, a.z/b.z);
}
//Sum overloading
vec3 friend operator+(const float& a, const vec3& b)
{
return vec3(a+b.x, a+b.y, a+b.z);
}

vec3 friend operator+(const vec3& b, const float a)
{
return vec3(a+b.x, a+b.y, a+b.z);
}
vec3 friend operator+(const vec3& a, const vec3& b)
{
return vec3(a.x+b.x, a.y+b.y, a.z+b.z);
}
//Difference overloading
vec3 friend operator-(const float& a, const vec3& b)
{
return vec3(a-b.x, a-b.y, a-b.z);
}

vec3 friend operator-(const vec3& b, const float a)
{
return vec3(a-b.x, a-b.y, a-b.z);
}

vec3 friend operator-(const vec3& a, const vec3& b)
{
return vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

};

#endif // VEC3_H_INCLUDED
