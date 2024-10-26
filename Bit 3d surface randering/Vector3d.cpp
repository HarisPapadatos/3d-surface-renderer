#include "Vector3d.h"
#include<math.h>



Vector3d::Vector3d()
	:x(0),y(0),z(0)
{
}

Vector3d::Vector3d(double x, double y, double z)
	:x(x),y(y),z(z)
{
}

double Vector3d::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3d Vector3d::getUnitVector() const
{
	return (* this) / length();
}

double Vector3d::operator[](size_t idx) const
{
	switch (idx) {
	case 0:
		return x; break;
	case 1:
		return y; break;
	case 2:
		return z; break;
	}
}

double& Vector3d::operator[](size_t idx)
{
	switch (idx) {
	case 0:
		return x; break;
	case 1:
		return y; break;
	case 2:
		return z; break;
	}
}

Vector3d Vector3d::operator+(const Vector3d& v)const
{
	return Vector3d(x+v.x,y+v.y,z+v.z);
}

Vector3d Vector3d::operator-(const Vector3d& v)const
{
	return Vector3d(x-v.x,y-v.y,z-v.z);
}

Vector3d Vector3d::operator*(double a)const
{
	return Vector3d(x*a,y*a,z*a);
}

Vector3d Vector3d::operator/(double a)const
{
	return Vector3d(x/a,y/a,z/a);
}

Vector3d Vector3d::operator+=(const Vector3d& v)
{
	return *this = *this+v;
}

Vector3d Vector3d::operator-=(const Vector3d& v)
{
	return *this = *this - v;
}

Vector3d Vector3d::operator*=(double a)
{
	return *this = *this *a;
}

Vector3d Vector3d::operator/=(double a)
{
	return *this = *this / a;
}

bool Vector3d::operator==(const Vector3d& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

Vector3d Vector3d::operator-() const
{
	return Vec0-(*this);
}

Vector3d operator*(double a, const Vector3d& v)
{
	return v * a;
}

double dot(const Vector3d& a, const Vector3d& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}


Vector3d cross(const Vector3d& a, const Vector3d& b)
{
	return Vector3d(a.y*b.z-a.z*b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
