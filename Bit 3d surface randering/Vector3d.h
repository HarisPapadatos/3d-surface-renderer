#pragma once

#include<functional>

class Vector3d;


Vector3d operator*(double a, const Vector3d& v);

double dot(const Vector3d& a,const Vector3d& b);
Vector3d cross(const Vector3d& a, const Vector3d& b);

class Vector3d
{
public:

	Vector3d();
	Vector3d(double x, double y, double z);

	double length()const;
	Vector3d getUnitVector()const;

	double operator[](size_t idx)const;
	double& operator[](size_t idx);

	Vector3d operator+(const Vector3d& v)const;
	Vector3d operator-(const Vector3d& v)const;
	Vector3d operator*(double a)const;
	Vector3d operator/(double a)const;

	Vector3d operator+=(const Vector3d& v);
	Vector3d operator-=(const Vector3d& v);
	Vector3d operator*=(double a);
	Vector3d operator/=(double a);

	bool operator==(const Vector3d& v)const;
	Vector3d operator-()const;

	double x, y, z;
};

static const Vector3d VecI(1,0,0), VecJ(0,1,0), VecK(0,0,1), Vec0(0,0,0);

