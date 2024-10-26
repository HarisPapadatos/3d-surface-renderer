#include "Matrix3x3.h"
#include"Vector3d.h"

Matrix3x3::Matrix3x3()
{
}

Matrix3x3::Matrix3x3(double** arr)
{
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++)
			e[i][j] = arr[i][j];
}

Matrix3x3::Matrix3x3(const std::array<std::array<double, 3>, 3>&arr)
{
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++)
			e[i][j] = arr[i][j];
}

double Matrix3x3::Trace()
{
	return e[0][0]*e[1][1]*e[2][2];
}

Vector3d Matrix3x3::GetRow(size_t idx)const
{
	return e[idx];
}

Vector3d Matrix3x3::GetColumn(size_t idx)const
{
	return Vector3d(e[0][idx],e[1][idx],e[3][idx]);
}

double Matrix3x3::Determinant() const
{
	return e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) -
		   e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]) +
		   e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
}

double Matrix3x3::SubDeterminant(size_t row, size_t column) const
{
	double m[4];
	size_t id = 0;
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++)
			if (row != i && column != j)
			{
				m[id] = e[i][j];
				id++;
			}
	return m[0]*m[3]-m[1]*m[2];
}

Matrix3x3 Matrix3x3::Inverse() const
{
	Matrix3x3 n;
	for(unsigned i=0;i<3;i++)
		for (unsigned j = 0; j < 3; j++)
			n[i][j] = SubDeterminant(j,i) * ((i + j) % 2 == 0 ? 1 : -1);
	return n / Determinant();
}

Matrix3x3 Matrix3x3::Transpose() const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++)
			n[i][j] = e[j][i];
	return n;
}

Vector3d Matrix3x3::operator[](size_t idx) const
{
	return e[idx];
}

Vector3d& Matrix3x3::operator[](size_t idx)
{
	return e[idx];
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other)const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		n[i] = e[i] + other.e[i];
	return n;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other)const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		n[i] = e[i] - other.e[i];
	return n;
}

Matrix3x3 Matrix3x3::operator-() const
{
	return Matrix3x3();
}

Matrix3x3 Matrix3x3::operator*(double a)const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		n[i] = e[i] *a;
	return n;
}

Matrix3x3 Matrix3x3::operator/(double a)const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		n[i] = e[i] / a;
	return n;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other)const
{
	Matrix3x3 n;
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++) {
			double s = 0;
			for (unsigned k = 0; k < 3; k++)
				s += e[i][k] * other[k][j];
			n[i][j] = s;
		}
	return n;
}

Vector3d Matrix3x3::operator*(const Vector3d& v)const
{
	//Maybe needs some rework
	return v.x * Vector3d(e[0][0], e[1][0], e[2][0]) +
		   v.y * Vector3d(e[0][1], e[1][1], e[2][1]) +
		   v.z * Vector3d(e[0][2], e[1][2], e[2][2]);
}

Matrix3x3 Matrix3x3::RotateX(double a)
{
	Matrix3x3 n ({ {
		{1,0,0},
		{0,cos(a),-sin(a)},
		{0,sin(a),cos(a)}
		} });
	return n;
}

Matrix3x3 Matrix3x3::RotateY(double a)
{
	Matrix3x3 n({ {
		{cos(a),0,sin(a)},
		{0,1,0},
		{-sin(a),0,cos(a)}
		} });
	return n;
}

Matrix3x3 Matrix3x3::RotateZ(double a)
{
	Matrix3x3 n({ {
		{cos(a),-sin(a),0},
		{sin(a), cos(a),0},
		{0,0,1}
		} });
	return n;
}

Matrix3x3 Matrix3x3::Reflect(Vector3d a)
{
	a = a.getUnitVector();
	Matrix3x3 n({ {
		{ 1 - a.x * a.x,-2 * a.x * a.y,-2 * a.x * a.z},
		{-2 * a.x * a.y, 1 - a.y * a.y,-2 * a.y * a.z},
		{-2 * a.x * a.z,-2 * a.y * a.z, 1 - a.z * a.z}
		} });
	return n;
}

