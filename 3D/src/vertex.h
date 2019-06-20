#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include "bone.h"

class Vertex
{
public:
	Vertex(Vector3d _position, Vector3d _mesh_position);
	~Vertex();

	void addRelatedBone(Bone* bone, double weight);
	void blendVertex();
	void draw();

public:
	Vector3d position;
	Vector3d mesh_position;

	vector<Bone*> related_bones;
	vector<double> weights;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif // !VERTEX_H
