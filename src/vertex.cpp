#include "vertex.h"

Vertex::Vertex(Vector2d _position, Vector2d _mesh_position)
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
	Vector2d new_pos=Vector2d::Zero();
	for (int i = 0; i < related_bones.size(); i++)
	{
		Vector2d mesh_offset = mesh_position - related_bones[i]->mesh_position;
		Vector2d target_pos = related_bones[i]->position + mesh_offset;
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
	glVertex2d(position.x(), position.y());
	glEnd();
}