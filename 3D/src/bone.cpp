#include "bone.h" 


Bone::Bone(Vector3d _position, Vector3d _mesh_position)
{
	length = 0;
	angle_x = 0; angle_z = 0;
	position = _position;
	mesh_position = _mesh_position;
	father = nullptr;
}

Bone::Bone(Bone* _father, double _length, double _angle_x, double _angle_z)
{
	father = _father;
	father->addChildren(this);
	length = _length;
	angle_x = _angle_x;
	angle_z = _angle_z;

	position = Vector3d(father->position.x() + fabs(length*sin(angle_z))*cos(angle_x),
						father->position.y() + fabs(length*sin(angle_z))*sin(angle_x),
						father->position.z() + length * cos(angle_z));
	
	mesh_position = Vector3d(father->mesh_position.x() + fabs(length*sin(angle_z))*cos(angle_x),
							 father->mesh_position.y() + fabs(length*sin(angle_z))*sin(angle_x),
							 father->mesh_position.z() + length * cos(angle_z));
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
		double x = father->position.x() + fabs(length*sin(angle_z))*cos(angle_x);
		double y = father->position.y() + fabs(length*sin(angle_z))*sin(angle_x);
		double z = father->position.z() + length * cos(angle_z);
		position = Vector3d(x, y, z);
	}

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->updatePosition();
	}
}

void Bone::ccd(Bone* opBone, Vector3d target)
{
	if (father == nullptr) return; //root doesnt move
	Vector3d target_direction = target - father->position; target_direction.normalize();
	Vector3d objective_direction = opBone->position - father->position; objective_direction.normalize();

	double angle_x_t = acos(target_direction.x());
	if (target.y() < father->position.y()) angle_x_t = -angle_x_t;
	double angle_z_t = acos(target_direction.z());

	double angle_x_o = acos(objective_direction.x());
	if (opBone->position.y() < father->position.y()) angle_x_o = -angle_x_o;
	double angle_z_o = acos(objective_direction.z());

	double delta_x = angle_x_t - angle_x_o;
	double delta_z = angle_z_t - angle_z_o;

	angle_x += delta_x;
	angle_z += delta_z;

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
	glVertex3d(position.x(), position.y(), position.z());
	glEnd();

	for (unsigned int i = 0; i < children.size(); i++)
	{
		glColor3f(1, 0, 0);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex3d(position.x(), position.y(), position.z());
		glVertex3d(children[i]->position.x(), children[i]->position.y(), children[i]->position.z());
		glEnd();

		children[i]->draw();
	}

	return;
}