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
	Bone(Vector2d _position, Vector2d _mesh_position);
	Bone(Bone* _father, double _length, double _angle);
	~Bone();

	void updatePosition();
	void draw();
	void addChildren(Bone* child);
	void ccd(Bone* opBone, Vector2d target);

public:
	double length;
	double angle;
	Vector2d position;
	Vector2d mesh_position;

	Bone* father;
	vector<Bone*> children;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};


#endif