#include "skinnedmesh.h"

SkinnedMesh::SkinnedMesh(Bone* _root)
{
	root = _root;
}

SkinnedMesh::~SkinnedMesh() {}

void SkinnedMesh::ccd(Bone* opBone, Vector2d target)
{
	int count = 0;
	while (opBone->position != target)
	{
		count++;
		opBone->ccd(opBone, target);
		if (count == 88) break;
	}
}

void SkinnedMesh::draw()
{
	root->draw();
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i]->draw();
	}
	glColor3d(1, 1, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2d(vertices[0]->position.x(), vertices[0]->position.y());
	glVertex2d(vertices[1]->position.x(), vertices[1]->position.y());
	
	glVertex2d(vertices[0]->position.x(), vertices[0]->position.y());
	glVertex2d(vertices[3]->position.x(), vertices[3]->position.y());
	
	glVertex2d(vertices[1]->position.x(), vertices[1]->position.y());
	glVertex2d(vertices[2]->position.x(), vertices[2]->position.y());
	
	glVertex2d(vertices[2]->position.x(), vertices[2]->position.y());
	glVertex2d(vertices[3]->position.x(), vertices[3]->position.y());

	glVertex2d(vertices[4]->position.x(), vertices[4]->position.y());
	glVertex2d(vertices[3]->position.x(), vertices[3]->position.y());

	glVertex2d(vertices[2]->position.x(), vertices[2]->position.y());
	glVertex2d(vertices[5]->position.x(), vertices[5]->position.y());

	glVertex2d(vertices[4]->position.x(), vertices[4]->position.y());
	glVertex2d(vertices[5]->position.x(), vertices[5]->position.y());

	glVertex2d(vertices[4]->position.x(), vertices[4]->position.y());
	glVertex2d(vertices[7]->position.x(), vertices[7]->position.y());

	glVertex2d(vertices[6]->position.x(), vertices[6]->position.y());
	glVertex2d(vertices[5]->position.x(), vertices[5]->position.y());

	glVertex2d(vertices[6]->position.x(), vertices[6]->position.y());
	glVertex2d(vertices[7]->position.x(), vertices[7]->position.y());
	glEnd();
}

void SkinnedMesh::updateBonePosition()
{
	root->updatePosition();
}

void SkinnedMesh::updateMeshPosition()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i]->blendVertex();
	}
}

void SkinnedMesh::addVertex(Vertex* vertex)
{
	vertices.push_back(vertex);
}


