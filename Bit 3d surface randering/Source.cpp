#include"Matrix3x3.h"
#include"Vector3d.h"
#include"Camera.h"
#include<Windows.h>

double t = 0;

double r = 1, b = 3;

double z = 0;


Vector3d WeirdTorus(double ö, double è)
{
	float R = r * sin(ö*2*t  + è);
	return Vector3d(-sin(ö) * (R * cos(è) - b), cos(ö) * (R * cos(è) - b), R * sin(è));
}


Vector3d Helix(double ö, double è)
{
	return Vector3d((r*cos(è)+b)*cos(2*ö)-r*sin(2 * ö)*sin(è), (r * cos(è) + b) * sin(2 * ö) + r * cos(2 * ö) * sin(è), 5*ö);
}

Vector3d Torus(double ö, double è)
{
	float R = r;
	return Vector3d(-sin(ö) * (R * cos(è) - b), cos(ö) * (R * cos(è) - b), R * sin(è));
}

Vector3d Sphere(double ö, double è)
{
	float R = r;
	return Vector3d(b * (sin(20 * t+PI) + 2) * sin(è / 2) * cos(ö), b * (cos(5 * t + PI/4) + 2) * sin(è / 2) * sin(ö), (cos(10 * t) + 2) * b * cos(è / 2));
}

Vector3d SpinningTorus(double ö, double è)
{
	return Matrix3x3::RotateX(PI*2*t) * Torus(ö,è);
}

Vector3d SpinningSphere(double ö, double è)
{
	return (cos(10*t)+2) * Sphere(ö, è)/2;
}

Vector3d SpinningHelix(double ö, double è)
{
	return Matrix3x3::RotateZ(PI * 2 * t) * Helix(ö, è) ;
}

Vector3d SpinningHelix2(double ö, double è)
{
	return Matrix3x3::RotateZ(PI * 2 * t + PI) * Helix(ö, è);
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