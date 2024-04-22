#include <windows.h>
#include <GL/freeglut.h>
#define G 9.8
#define ENERGY_LOSS_COEFFICIENT 0.9

bool direction = true;
double t = 0.002;
struct Ball {//球的结构体
	GLdouble y;
	GLdouble vy;
};
Ball ball;
void init(void) {
	//初始化球体属性
	ball.y = 8.7501;
	ball.vy = 0.0;

	glClearColor(0.0, 0.0, 0.0, 1.0);//背景颜色

}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空颜色缓冲区和深度缓冲区，以准备进行新一帧的绘制
	glPushMatrix();//表示将当前的矩阵状态保存到矩阵堆栈中，调用glPopMatrix()可以恢复之前保存的矩阵状态。
	glColor3f(0.0, 0.9, 0.0);//边框颜色
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
	glColor3f(0.0, 1.0, 1.0);//小球颜色
	glTranslated(0, ball.y, 0); //将绘图中心移动到球体的中心
	glutSolidSphere(1.5, 50, 50); //绘制一个球体
	if (direction) {
		ball.y = ball.y - (ball.vy * t + 0.5 * G * t * t);
		ball.vy = ball.vy + G * t;
		if (ball.y <= -1.5) {
			direction = false;
			ball.vy *= ENERGY_LOSS_COEFFICIENT; // 每次碰撞后速度减小
			// 如果速度接近零，则停止运动
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
			// 如果速度接近零，则停止运动
			if (ball.vy < 0.01) {
				ball.vy = 0.0;
			}
		}
	}
	glPopMatrix();
	//交换前后缓冲区
	glutSwapBuffers();
}

void timer(int value)//定时触发渲染帧的重绘事件，并设定了一个每隔两毫秒触发一次的定时器。
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
	glutCreateWindow("小球自由落体");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(2, timer, 0);//定时器每两秒（2毫秒）就会调用'timer'函数
	glutMainLoop();
	return 0;
}