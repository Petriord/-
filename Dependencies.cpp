#include <windows.h>
#include <GL/freeglut.h>
#define G 9.8
#define ENERGY_LOSS_COEFFICIENT 0.9

bool direction = true;
double t = 0.002;
struct Ball {//��Ľṹ��
	GLdouble y;
	GLdouble vy;
};
Ball ball;
void init(void) {
	//��ʼ����������
	ball.y = 8.7501;
	ball.vy = 0.0;

	glClearColor(0.0, 0.0, 0.0, 1.0);//������ɫ

}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����������Ȼ���������׼��������һ֡�Ļ���
	glPushMatrix();//��ʾ����ǰ�ľ���״̬���浽�����ջ�У�����glPopMatrix()���Իָ�֮ǰ����ľ���״̬��
	glColor3f(0.0, 0.9, 0.0);//�߿���ɫ
	glBegin(GL_LINES);
	glVertex2f(-5.0, 9.0);
	glVertex2f(5.0, 9.0);
	glVertex2f(5.0, 9.0);
	glVertex2f(5.0, -3.0);
	glVertex2f(5.0, -3.0);
	glVertex2f(-5.0, -3.0);
	glVertex2f(-5.0, -3.0);
	glVertex2f(-5.0, 9.0);
	glEnd();
	glColor3f(0.0, 1.0, 1.0);//С����ɫ
	glTranslated(0, ball.y, 0); //����ͼ�����ƶ������������
	glutSolidSphere(1.5, 50, 50); //����һ������
	if (direction) {
		ball.y = ball.y - (ball.vy * t + 0.5 * G * t * t);
		ball.vy = ball.vy + G * t;
		if (ball.y <= -1.5) {
			direction = false;
			ball.vy *= ENERGY_LOSS_COEFFICIENT; // ÿ����ײ���ٶȼ�С
			// ����ٶȽӽ��㣬��ֹͣ�˶�
			if (ball.vy < 0.01) {
				ball.vy = 0.0;
			}
		}
	}
	else {
		ball.y = ball.y + (ball.vy * t - 0.5 * G * t * t);
		ball.vy = ball.vy - G * t;
		if (ball.y >= 7.5) {
			direction = true;
			ball.vy *= ENERGY_LOSS_COEFFICIENT;
			// ����ٶȽӽ��㣬��ֹͣ�˶�
			if (ball.vy < 0.01) {
				ball.vy = 0.0;
			}
		}
	}
	glPopMatrix();
	//����ǰ�󻺳���
	glutSwapBuffers();
}

void timer(int value)//��ʱ������Ⱦ֡���ػ��¼������趨��һ��ÿ�������봥��һ�εĶ�ʱ����
{
	glutPostRedisplay();
	glutTimerFunc(2, timer, 0);
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-15, 15, -15 * (GLfloat)h / (GLfloat)w, 15 * (GLfloat)h / (GLfloat)w, -15, 15);
	else
		glOrtho(-15 * (GLfloat)h / (GLfloat)w, 15 * (GLfloat)h / (GLfloat)w, -15, 15, -15, 15);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(450, 100);
	glutCreateWindow("С����������");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(2, timer, 0);//��ʱ��ÿ���루2���룩�ͻ����'timer'����
	glutMainLoop();
	return 0;
}