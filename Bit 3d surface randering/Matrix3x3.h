#pragma once
#include<array>
#include<utility>
#include"Vector3d.h"

class Matrix3x3;


class Matrix3x3
{
public:
	Matrix3x3();
	Matrix3x3(double** arr);
	Matrix3x3(const std::array<std::array<double, 3>, 3>&);

	double Trace();
	Vector3d GetRow(size_t idx)const;
	Vector3d GetColumn(size_t idx)const;
	double Determinant()const;
	double SubDeterminant(size_t row, size_t column)const;
	Matrix3x3 Inverse()const;
	Matrix3x3 Transpose()const;

	Vector3d operator[](size_t idx) const;
	Vector3d& operator[](size_t idx);

	Matrix3x3 operator+(const Matrix3x3& other)const;
	Matrix3x3 operator-(const Matrix3x3& other)const;
	Matrix3x3 operator-()const;
	Matrix3x3 operator*(double a)const;
	Matrix3x3 operator/(double a)const;

	Matrix3x3 operator*(const Matrix3x3& other)const;
	Vector3d operator*(const Vector3d& v)const;

	static Matrix3x3 RotateX(double a);
	static Matrix3x3 RotateY(double a);
	static Matrix3x3 RotateZ(double a);
	static Matrix3x3 Reflect(Vector3d a);

private:
	//first coordinate/dimation chooses the row
	//second one chooses the column
	//e.g.: a[0][2] is the element at the FIRST row and THIRD column
	std::array<Vector3d, 3> e;

};

static const Matrix3x3 Mtx0({{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }});
static const Matrix3x3 Mtx1({{ {1, 0, 0}, {0, 1, 0}, {0, 1, 0} }});


