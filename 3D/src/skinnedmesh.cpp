#include "skinnedmesh.h"


SkinnedMesh::SkinnedMesh(Bone* _root)
{
	root = _root;
}

SkinnedMesh::~SkinnedMesh() {}


void SkinnedMesh::ccd(Bone* opBone, Vector3d target)
{
	int count = 0;
	while (opBone->position != target)
	{
		count++;
		opBone->ccd(opBone, target);
		if (count == THRESHOLD) break;
	}
}

void SkinnedMesh::draw()
{
	root->draw();
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i]->draw();
	}
	/**/
	glColor3f(1, 1, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i++)
	{
		glVertex3d(vertices[i]->position.x(), vertices[i]->position.y(), vertices[i]->position.z());
		glVertex3d(vertices[i+4]->position.x(), vertices[i+4]->position.y(), vertices[i+4]->position.z());

		glVertex3d(vertices[i+4]->position.x(), vertices[i+4]->position.y(), vertices[i+4]->position.z());
		glVertex3d(vertices[i+8]->position.x(), vertices[i+8]->position.y(), vertices[i+8]->position.z());
		
		glVertex3d(vertices[i+8]->position.x(), vertices[i+8]->position.y(), vertices[i+8]->position.z());
		glVertex3d(vertices[i+12]->position.x(), vertices[i+12]->position.y(), vertices[i+12]->position.z());
	}
	for (int j = 0; j < 4; j++)
	{
		int index = 4 * j;
		glVertex3d(vertices[index]->position.x(), vertices[index]->position.y(), vertices[index]->position.z());
		glVertex3d(vertices[index+1]->position.x(), vertices[index+1]->position.y(), vertices[index+1]->position.z());
		
		glVertex3d(vertices[index+1]->position.x(), vertices[index+1]->position.y(), vertices[index+1]->position.z());
		glVertex3d(vertices[index+2]->position.x(), vertices[index+2]->position.y(), vertices[index+2]->position.z());
		
		glVertex3d(vertices[index+2]->position.x(), vertices[index+2]->position.y(), vertices[index+2]->position.z());
		glVertex3d(vertices[index+3]->position.x(), vertices[index+3]->position.y(), vertices[index+3]->position.z());
		
		glVertex3d(vertices[index+3]->position.x(), vertices[index+3]->position.y(), vertices[index+3]->position.z());
		glVertex3d(vertices[index]->position.x(), vertices[index]->position.y(), vertices[index]->position.z());
	}

	glEnd();


	/**/
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

