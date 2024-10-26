#pragma once

#include"Vector3d.h";
#include<vector>
#include"Light.h"

const double PI = 3.141592653589793;

double Arctan(double, double);

Vector3d PartialDerivative(Vector3d(*func)(double, double), char c, double x, double y);

char GetBrightChar(float x);

class Camera
{
public:
	Camera();
	Camera(double aspectRatio, Vector3d position, Vector3d view);

	void setScreenSize(int width, int height);
	void Move(Vector3d v);
	void PrintScreenShot(std::vector<Vector3d(*)(double,double)> surfaces, const Light& lightSource);
	
	

private:

	void UpdateVerteces();
	Vector3d GetViewInSphericalCoords();
	void ClearScreen();


	double aspectRatio, fov, phi, theta;
	Vector3d position, view;

	Vector3d p, t, f; //Unit Vectors in spherical coordinates

	Vector3d Vertex[4];
	std::vector<std::vector<std::pair<char,double>>> screen;

	int screenWidth,screenHeight;
	double rotation; //Later

};

