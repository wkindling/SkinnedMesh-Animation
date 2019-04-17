#pragma once
#ifndef SKINNEDMESH_H
#define SKINNEDMESH_H
#include "vertex.h"

class SkinnedMesh
{
public:
	SkinnedMesh(Bone* _root);
	~SkinnedMesh();

	void ccd(Bone* opBone, Vector2d target);
	void draw();
	void updateBonePosition();
	void updateMeshPosition();
	void addVertex(Vertex* vertex);

public:
	Bone* root;
	vector<Vertex*> vertices;
};


#endif