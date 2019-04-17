#include "bone.h"

Bone::Bone(Vector2d _position, Vector2d _mesh_position)
{
	length = 0;
	angle = 0;
	position = _position;
	mesh_position = _mesh_position;
	father = nullptr;
}

Bone::Bone(Bone* _father, double _length, double _angle)
{
	father = _father;
	father->addChildren(this);
	length = _length;
	angle = _angle;
	position = Vector2d(father->position.x() + cos(angle)*length, father->position.y() + sin(angle)*length);
	mesh_position = Vector2d(father->mesh_position.x() + cos(angle)*length, father->mesh_position.y() + sin(angle)*length);
}

Bone::~Bone() {}

void Bone::addChildren(Bone* child)
{
	children.push_back(child);
}

void Bone::updatePosition()
{
	if (father == nullptr)
	{
		return;
	}
	else
	{
		double x = father->position.x() + cos(angle)*length;
		double y = father->position.y() + sin(angle)*length;
		position.x() = x;
		position.y() = y;
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->updatePosition();
	}
}

void Bone::ccd(Bone* opBone, Vector2d target)
{
	if (father == nullptr) return; // root doesnt move
	Vector2d target_direction = target - father->position; target_direction.normalize();
	Vector2d objective_direction = opBone->position - father->position; objective_direction.normalize();
	Vector2d xAxis(1, 0);

	double theta_t = acos(target_direction.dot(xAxis)); if (target.y() < father->position.y()) theta_t = -theta_t;
	double theta_o = acos(objective_direction.dot(xAxis)); if (opBone->position.y() < father->position.y()) theta_o = -theta_o;
	double delta = theta_t - theta_o;

	angle += delta;
	
	updatePosition();

	if (opBone->position != target)
	{
		father->ccd(opBone, target);
	}
}

void Bone::draw()
{
	glColor3f(0, 0, 0);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2d(position.x(), position.y());
	glEnd();

	for (int i = 0; i < children.size(); i++)
	{
		glColor3f(1, 0, 0);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex2d(position.x(), position.y());
		glVertex2d(children[i]->position.x(), children[i]->position.y());
		glEnd();

		children[i]->draw();
	}
	return;
}