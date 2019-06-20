#pragma once
#ifndef BONE_H
#define BONE_H

#include <Eigen/Dense>
#include <vector>
#include <cassert>
#include <glut.h>
#include <iostream>
#include <cmath>

#define PI 3.1415926535

using namespace std;
using namespace Eigen;

class Bone
{
public:
	Bone(Vector3d _position, Vector3d _mesh_position);
	Bone(Bone* _father, double _length, double _angle_x, double _angle_z);
	~Bone();

	void updatePosition();
	void draw();
	void addChildren(Bone* child);
	void ccd(Bone* opBone, Vector3d target);

public:
	double length;
	double angle_x, angle_z;
	Vector3d position;
	Vector3d mesh_position;

	Bone* father;
	vector<Bone*> children;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif