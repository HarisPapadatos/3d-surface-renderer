#include"Matrix3x3.h"
#include"Vector3d.h"
#include"Camera.h"
#include<Windows.h>

double t = 0;

double r = 1, b = 3;

double z = 0;


Vector3d WeirdTorus(double �, double �)
{
	float R = r * sin(�*2*t  + �);
	return Vector3d(-sin(�) * (R * cos(�) - b), cos(�) * (R * cos(�) - b), R * sin(�));
}


Vector3d Helix(double �, double �)
{
	return Vector3d((r*cos(�)+b)*cos(2*�)-r*sin(2 * �)*sin(�), (r * cos(�) + b) * sin(2 * �) + r * cos(2 * �) * sin(�), 5*�);
}

Vector3d Torus(double �, double �)
{
	float R = r;
	return Vector3d(-sin(�) * (R * cos(�) - b), cos(�) * (R * cos(�) - b), R * sin(�));
}

Vector3d Sphere(double �, double �)
{
	float R = r;
	return Vector3d(b * (sin(20 * t+PI) + 2) * sin(� / 2) * cos(�), b * (cos(5 * t + PI/4) + 2) * sin(� / 2) * sin(�), (cos(10 * t) + 2) * b * cos(� / 2));
}

Vector3d SpinningTorus(double �, double �)
{
	return Matrix3x3::RotateX(PI*2*t) * Torus(�,�);
}

Vector3d SpinningSphere(double �, double �)
{
	return (cos(10*t)+2) * Sphere(�, �)/2;
}

Vector3d SpinningHelix(double �, double �)
{
	return Matrix3x3::RotateZ(PI * 2 * t) * Helix(�, �) ;
}

Vector3d SpinningHelix2(double �, double �)
{
	return Matrix3x3::RotateZ(PI * 2 * t + PI) * Helix(�, �);
}

int main()
{
	Camera cam(1,{0,0,20},{0,0,-1});
	cam.setScreenSize(200,200);

	Light light;
	light.position = Vector3d(100, 100, 50);

	while (true) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		cam.PrintScreenShot({ SpinningTorus },light);
		t += 0.04;
	}

	system("pause");
}