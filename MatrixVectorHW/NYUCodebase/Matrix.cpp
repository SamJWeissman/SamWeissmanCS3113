#include "Matrix.h"
#include "Vector.h"

Matrix::Matrix()
{

}

Matrix Matrix::inverse()
{
	float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];
	float v0 = m20 * m31 - m21 * m30;
	float v1 = m20 * m32 - m22 * m30;
	float v2 = m20 * m33 - m23 * m30;
	float v3 = m21 * m32 - m22 * m31;
	float v4 = m21 * m33 - m23 * m31;
	float v5 = m22 * m33 - m23 * m32;
	float t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
	float t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
	float t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
	float t30 = -(v3 * m10 - v1 * m11 + v0 * m12);
	float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);
	float d00 = t00 * invDet;
	float d10 = t10 * invDet;
	float d20 = t20 * invDet;
	float d30 = t30 * invDet;
	float d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;
	float d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;
	float d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	Matrix m2;
	m2.m[0][0] = d00;
	m2.m[0][1] = d01;
	m2.m[0][2] = d02;
	m2.m[0][3] = d03;
	m2.m[1][0] = d10;
	m2.m[1][1] = d11;
	m2.m[1][2] = d12;
	m2.m[1][3] = d13;
	m2.m[2][0] = d20;
	m2.m[2][1] = d21;
	m2.m[2][2] = d22;
	m2.m[2][3] = d23;
	m2.m[3][0] = d30;
	m2.m[3][1] = d31;
	m2.m[3][2] = d32;
	m2.m[3][3] = d33;
	return m2;
}

Matrix Matrix::operator*(const Matrix &n){
	float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	float n00 = n.m[0][0], n01 = n.m[0][1], n02 = n.m[0][2], n03 = n.m[0][3];
	float n10 = n.m[1][0], n11 = n.m[1][1], n12 = n.m[1][2], n13 = n.m[1][3];
	float n20 = n.m[2][0], n21 = n.m[2][1], n22 = n.m[2][2], n23 = n.m[2][3];
	float n30 = n.m[3][0], n31 = n.m[3][1], n32 = n.m[3][2], n33 = n.m[3][3];

	Matrix* retM = new Matrix();

	retM->m[0][0] = (m00 * n00) + (m01 * n10) + (m02 * n20) + (m03 * n30);
	retM->m[0][1] = (m00 * n01) + (m01 * n11) + (m02 * n21) + (m03 * n31);
	retM->m[0][2] = (m00 * n02) + (m01 * n12) + (m02 * n22) + (m03 * n32);
	retM->m[0][3] = (m00 * n03) + (m01 * n13) + (m02 * n23) + (m03 * n33);

	retM->m[1][0] = (m10 * n00) + (m11 * n10) + (m12 * n20) + (m13 * n30);
	retM->m[1][1] = (m10 * n01) + (m11 * n11) + (m12 * n21) + (m13 * n31);
	retM->m[1][2] = (m10 * n02) + (m11 * n12) + (m12 * n22) + (m13 * n32);
	retM->m[1][3] = (m10 * n03) + (m11 * n13) + (m12 * n23) + (m13 * n33);

	retM->m[1][0] = (m20 * n00) + (m21 * n10) + (m22 * n20) + (m23 * n30);
	retM->m[1][1] = (m20 * n01) + (m21 * n11) + (m22 * n21) + (m23 * n31);
	retM->m[1][2] = (m20 * n02) + (m21 * n12) + (m22 * n22) + (m23 * n32);
	retM->m[1][3] = (m20 * n03) + (m21 * n13) + (m22 * n23) + (m23 * n33);

	retM->m[1][0] = (m30 * n00) + (m31 * n10) + (m32 * n20) + (m33 * n30);
	retM->m[1][1] = (m30 * n01) + (m31 * n11) + (m32 * n21) + (m33 * n31);
	retM->m[1][2] = (m30 * n02) + (m31 * n12) + (m32 * n22) + (m33 * n32);
	retM->m[1][3] = (m30 * n03) + (m31 * n13) + (m32 * n23) + (m33 * n33);

	return *retM;
}

Vector Matrix::operator*(const Vector &v)
{
	float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	Vector* retV = new Vector();

	retV->x = (m00 * v.x) + (m01 * v.y) + (m02 * v.z) + (m03 * 1);
	retV->y = (m10 * v.x) + (m11 * v.y) + (m12 * v.z) + (m13 * 1);
	retV->z = (m20 * v.x) + (m21 * v.y) + (m22 * v.z) + (m23 * 1);

	return *retV;
}