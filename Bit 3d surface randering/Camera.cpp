#include "Camera.h"
#include<string>
#include<sstream>
#include<iostream>

char GetBrightChar(float x) {

	if (x < 0.1)
		return ' ';
	else if (x < 0.2)
		return '.';
	else if (x < 0.3)
		return ':';
	else if (x < 0.4)
		return '-';
	else if (x < 0.5)
		return '+';
	else if (x < 0.6)
		return '*';
	else if (x < 0.7)
		return '#';
	else if (x < 0.8)
		return '%';
	else if (x < 0.9)
		return 'W';
	else if (x < 1)
		return '@';
	else
		return '&';
}

double sigmoid(double x)
{
	return 2 / (1 + exp(-x)) - 1;
}

Vector3d PartialDerivative(Vector3d(*func)(double, double), char c, double x, double y)
{
	double h = 000000.1;
	switch (c) {
	case 'x':
		return (func(x + h, y) - func(x, y)) / h;
		break;
	case'y':
		return (func(x, y + h) - func(x, y)) / h;
		break;
	}
}

Camera::Camera()
	:aspectRatio(4.0/3),position(0,0,0),view(1,0,0)
{

}

Camera::Camera(double aspectRatio, Vector3d position, Vector3d view)
	:aspectRatio(aspectRatio),position(position),view(view)
{
	UpdateVerteces();
}

void Camera::setScreenSize(int width, int height)
{
	screen.clear();
	screen.resize(height);
	for (unsigned i = 0; i < height; i++)
		screen[i].resize(width);

	screenHeight = height;
	screenWidth = width;
	UpdateVerteces();
}

void Camera::Move(Vector3d v)
{
	position += v;
	UpdateVerteces();
}

void Camera::PrintScreenShot(std::vector<Vector3d(*)(double, double)> surfaces, const Light& lightSource)
{
	//Accuracy:
	int N = 360, M = 60;


	ClearScreen();

	Vector3d u1 = Vertex[0] - Vertex[3], u2 = (Vertex[2]-Vertex[3])*aspectRatio;
	
	for (auto& surface : surfaces) {
		for (unsigned i = 0; i < N; i++) {
			for (unsigned j = 0; j < M; j++) {

				double vx = i * 2 * PI / N, vy= j * 2 * PI / M;
				Vector3d ray = surface(vx, vy)-position;
				Vector3d incPoint = ray * (dot(view, view) / dot(ray, view)) + position;
				incPoint -= Vertex[3];

				int y = round(screenHeight * dot(incPoint, u1));
				int x = round(screenWidth * dot(incPoint, u2));

				

				if (y >= 0 && y < screenHeight && x >= 0 && x < screenWidth) {
					Vector3d normalVec = cross(PartialDerivative(surface,'x',vx, vy),
						PartialDerivative(surface, 'y', vx, vy));
					normalVec /= normalVec.length();

					Vector3d lightRay = surface(i * 2 * PI / N, j * 2 * PI / N) - lightSource.position;
					double lightIndex = dot(lightRay, normalVec) / lightRay.length();

					if (screen[y][x].second == -1 || screen[y][x].second > ray.length()) {
						screen[y][x].first = GetBrightChar(sigmoid(lightIndex*2)+0.5);
						screen[y][x].second = ray.length();
					}

				}
				
			}
		}
	}

	std::string ss;

	for (unsigned i = 0; i < screenHeight; i++) {
		for (unsigned j = 0; j < screenWidth; j++) {
			if (screen[i][j].first == 0)
			{
				ss +="``";
			}
			else {
				ss += screen[i][j].first;
				ss += screen[i][j].first;
			}
		}
		ss +="|\n";
	}

	std::cout << ss;

}

Vector3d Camera::GetViewInSphericalCoords()
{
	fov = view.length();
	theta = acos(view.z / fov);
	phi = Arctan(view.x, view.y);

	f = view / fov;
	t = Vector3d(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta));
	p = Vector3d(- sin(phi), cos(phi),0);

	return Vector3d(fov,phi,theta);
}

void Camera::ClearScreen()
{
	for (unsigned i = 0; i < screenHeight; i++)
		for (unsigned j = 0; j < screenWidth; j++) {
			screen[i][j].first = 0;
			screen[i][j].second = -1;
		}
}

void Camera::UpdateVerteces()
{
	GetViewInSphericalCoords();

	Vertex[0] = position + view - t / 2 + p / (2 * aspectRatio);
	Vertex[1] = position + view - t / 2 - p / (2 * aspectRatio);
	Vertex[2] = position + view + t / 2 - p / (2 * aspectRatio);
	Vertex[3] = position + view + t / 2 + p / (2 * aspectRatio);
}

double Arctan(double x, double y)
{
	if (x > 0)
		return atan(y / x);
	else if (x < 0 && y >= 0)
		return atan(y / x) + PI;
	else if (x < 0 && y < 0)
		return atan(y / x) - PI;
	else if (x == 0 && y > 0)
		return PI / 2;
	else if (x == 0 && y < 0)
		return -PI / 2;
}
