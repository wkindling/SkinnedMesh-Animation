#include "vertex.h"


Vertex::Vertex(Vector3d _position, Vector3d _mesh_position)
{
	position = _position;
	mesh_position = _mesh_position;
}

Vertex::~Vertex() {}

void Vertex::addRelatedBone(Bone* bone, double weight)
{
	related_bones.push_back(bone);
	weights.push_back(weight);
}

void Vertex::blendVertex()
{
	Vector3d new_pos = Vector3d::Zero();
	for (int i = 0; i < related_bones.size(); i++)
	{
		Vector3d mesh_offset = mesh_position - related_bones[i]->mesh_position;
		Vector3d target_pos = related_bones[i]->position + mesh_offset;
		new_pos += target_pos * weights[i];
	}
	position = new_pos;
	return;
}

void Vertex::draw()
{
	glColor3f(0, 0, 1);
	glPointSize(5.0);

	glBegin(GL_POINTS);
	glVertex3d(position.x(), position.y(), position.z());
	glEnd();
}