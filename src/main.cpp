#include "skinnedmesh.h"

Bone* root = new Bone(Vector2d(0,350),Vector2d(0,0));
Bone* bone1 = new Bone(root, 200, 0);
Bone* bone2 = new Bone(bone1, 200, 0);
Bone* bone3 = new Bone(bone2, 200, 0);
SkinnedMesh mesh(root);
double target_x = bone3->position.x(), target_y = bone3->position.y();

void changePoint(int x, int y)
{
	target_x = x;
	target_y = 700-y;
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	mesh.ccd(bone3, Vector2d(target_x, target_y));
	mesh.updateMeshPosition();
	mesh.draw();

	glColor3f(1, 0, 1);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2d(target_x, target_y);
	glEnd();

	glutPostRedisplay();
	glutSwapBuffers();
}


int main(int argc, char ** argv)
{
	Vertex* vertex0 = new Vertex(Vector2d(0, 50), Vector2d(0, 50)); mesh.addVertex(vertex0);
	Vertex* vertex1 = new Vertex(Vector2d(0, -50), Vector2d(0, -50)); mesh.addVertex(vertex1);
	Vertex* vertex2 = new Vertex(Vector2d(200, -50), Vector2d(200, -50)); mesh.addVertex(vertex2);
	Vertex* vertex3 = new Vertex(Vector2d(200, 50), Vector2d(200, 50)); mesh.addVertex(vertex3);
	Vertex* vertex4 = new Vertex(Vector2d(400, 50), Vector2d(400, 50)); mesh.addVertex(vertex4);
	Vertex* vertex5 = new Vertex(Vector2d(400, -50), Vector2d(400, -50)); mesh.addVertex(vertex5);
	Vertex* vertex6 = new Vertex(Vector2d(600, -50), Vector2d(600, -50)); mesh.addVertex(vertex6);
	Vertex* vertex7 = new Vertex(Vector2d(600, 50), Vector2d(600, 50)); mesh.addVertex(vertex7);
	
	vertex0->addRelatedBone(root, 0.5);	vertex0->addRelatedBone(bone1, 0.25); 	vertex0->addRelatedBone(bone2, 0.25);
	vertex1->addRelatedBone(root, 0.5); vertex1->addRelatedBone(bone1, 0.25); 	vertex1->addRelatedBone(bone2, 0.25);
	vertex2->addRelatedBone(bone1, 0.5); vertex2->addRelatedBone(root, 0.25);   vertex2->addRelatedBone(bone2, 0.25);
	vertex3->addRelatedBone(bone1, 0.5); vertex3->addRelatedBone(root, 0.25);   vertex3->addRelatedBone(bone2, 0.25);
	vertex4->addRelatedBone(bone2, 0.5); vertex4->addRelatedBone(bone1, 0.25);  vertex4->addRelatedBone(bone3, 0.25);
	vertex5->addRelatedBone(bone2, 0.5); vertex5->addRelatedBone(bone1, 0.25);  vertex5->addRelatedBone(bone3, 0.25);
	vertex6->addRelatedBone(bone3, 1.0); 
	vertex7->addRelatedBone(bone3, 1.0); 

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("SkinnedMesh_IK");
	glutMotionFunc(changePoint);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 700.0, 0.0, 700.0);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}