#include<GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Star{
	float x, y, z;
	float size;
	float rgb[3];
};

///화면 컨트롤을 위한 기본 함수 선언
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void SetupRc();	// 필요한 변수 초기화
void TimerFunction(int value);
bool collide(Star p);


float TransX = 0.0, TransY = 0.0, TransZ = 0.0;
float LookX = 0.0, LookY = 0.0, LookZ = 0.0;
float Propeller_Angle = 0.0;
float Line_x = 0, Line_y = 0, Line_z = 0;
float mx, my, mz;
float t;

GLfloat ctrlpoints[30][3];
Star star[3000];
Star planet[10];
int cnt = 1;
int cur = 1;
int move_cnt = 0;

void main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("어린왕자"); // 윈도우 생성 (윈도우 이름) 
	SetupRc();	// 상태 변수 초기화
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);	// 키보드 입력
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutTimerFunc(100, TimerFunction, 0);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslatef(TransX, TransY, TransZ);

	glTranslated(-100.0, -100.0, 0.0);

	glRotatef(90, 0.0, 1.0, 0.0);

	glRotatef(LookX, 1.0, 0.0, 0.0);
	glRotatef(LookY, 0.0, 1.0, 0.0);
	glRotatef(LookZ, 0.0, 0.0, 1.0);

	for (int i = 0; i < 3000; ++i){
		glPushMatrix();
		glColor3f(star[i].rgb[0], star[i].rgb[1], star[i].rgb[2]);
		glTranslatef(star[i].x, star[i].y, star[i].z);
		glutSolidSphere(5, 20, 20);
		glPopMatrix();
	}

	for (int i = 0; i < 10; ++i){
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(planet[i].x, planet[i].y, planet[i].z);
		glutSolidSphere(planet[i].size, 20, 20);
		glPopMatrix();
	}

	glPushMatrix();
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 8, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 10; i++)
		glEvalCoord1f((GLfloat)i / 10.0);
	glEnd();

	glDisable(GL_MAP1_VERTEX_3);

	glPointSize(5.0);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < cnt; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(100, 100, 100);
	glutWireCube(200);

	glPopMatrix();

	glPushMatrix();

	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(Line_x, 200.0 - Line_y, -300.0);
	glVertex3f(Line_x, 200.0 - Line_y, 300.0);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-300.0, 200.0 - Line_y, Line_z);
	glVertex3f(300.0, 200.0 - Line_y, Line_z);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(Line_x, -300.0, Line_z);
	glVertex3f(Line_x, 300.0, Line_z);

	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(mx, my, mz);
	// 본체
	glPushMatrix();

	glColor3f(1.0f, 0.5f, 0.5f);
	glTranslatef(0.0, 200, 0.0);

	glPushMatrix();

	glTranslatef(-7.5, -9.0, 0.0);
	glScalef(0.25, 0.25, 3.0);
	glutWireCube(10);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(7.5, -9.0, 0.0);
	glScalef(0.25, 0.25, 3.0);
	glutWireCube(10);

	glPopMatrix();

	glScalef(0.75, 0.75, 1.0);
	glutWireCube(20);

	// 프로펠러 기둥
	glPushMatrix();

	glTranslatef(0.0, 13.75, 0.0);
	glScalef(0.25, 0.375, 0.125);
	glutWireCube(20);

	glPopMatrix();
	// 꼬리
	glPushMatrix();

	glTranslatef(0.0, 0.0, -15.0);

	glPushMatrix();

	glTranslatef(0.0, 0.0, -7.5);
	glScalef(1.0, 0.25, 0.25);
	glutWireCube(20);

	glPopMatrix();

	glScalef(0.25, 0.25, 0.5);
	glutWireCube(20);

	glPopMatrix();

	glRotatef(Propeller_Angle, 0.0, 1.0, 0.0);
	// 프로펠러
	glPushMatrix();

	glTranslatef(0.0, 17.5, 0.0);
	glScalef(0.25, 0.25, 1.5);
	glutWireCube(20);

	glPopMatrix();
	// 프로펠러
	glPushMatrix();

	glTranslatef(0.0, 17.5, 0.0);
	glScalef(1.5, 0.25, 0.25);
	glutWireCube(20);

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}
void SetupRc() {
	TransX = 0.0, TransY = 0.0, TransZ = 0.0;
	LookX = 0.0, LookY = 0.0, LookZ = 0.0;
	
	for (int i = 0; i < 9; ++i){
		planet[i].x = i * (10 + i);
		planet[i].y = rand() % 200;
		planet[i].z = i * 20;
		planet[i].size = rand() % 5 + 15;
	}
	planet[9].x = 200;
	planet[9].y = 0;
	planet[9].z = 200;
	planet[9].size = 30;
	for (int i = 0; i < 500; ++i){
		star[i].x = rand() % 1000 + 1000;
		star[i].y = rand() % 3000 - 1000;
		star[i].z = rand() % 3000 - 1000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	for (int i = 500; i < 1000; ++i){
		star[i].x = rand() % 1000 - 2000;
		star[i].y = rand() % 3000 - 1000;
		star[i].z = rand() % 3000 - 1000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	for (int i = 1000; i < 1500; ++i){
		star[i].x = rand() % 3000 - 1000;
		star[i].y = rand() % 1000 + 1000;
		star[i].z = rand() % 3000 - 1000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	for (int i = 1500; i < 2000; ++i){
		star[i].x = rand() % 3000 - 1000;
		star[i].y = rand() % 1000 - 2000;
		star[i].z = rand() % 3000 - 1000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	for (int i = 2000; i < 2500; ++i){
		star[i].x = rand() % 3000 - 1000;
		star[i].y = rand() % 3000 - 1000;
		star[i].z = rand() % 1000 + 1000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	for (int i = 2500; i < 3000; ++i){
		star[i].x = rand() % 3000 - 1000;
		star[i].y = rand() % 3000 - 1000;
		star[i].z = rand() % 1000 - 2000;
		star[i].rgb[0] = (rand() % 100) * 0.01;
		star[i].rgb[1] = (rand() % 100) * 0.01;
		star[i].rgb[2] = (rand() % 100) * 0.01;
	}
	Propeller_Angle = 0.0;
	Line_x = 0, Line_y = 0, Line_z = 0;
	mx = 0.0, my = 0.0, mz = 0.0;
	cnt = 1;
	t = 0.0;
	for (int i = 0; i < 30; ++i){
		ctrlpoints[i][0] = 0;
		ctrlpoints[i][1] = 200;
		ctrlpoints[i][2] = 0;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MAP1_VERTEX_3);
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, 3000.0);
	gluLookAt(0, 0, 500, 0, 0, 1, 0, 1, 0);
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
	case 'W':
		TransY += 5;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		TransY -= 5;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		TransX -= 5;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		TransX += 5;
		glutPostRedisplay();
		break;
	case '+':
		TransZ += 5;
		glutPostRedisplay();
		break;
	case '-':
		TransZ -= 5;
		glutPostRedisplay();
		break;
	case 'x':
		LookX += 5;
		glutPostRedisplay();
		break;
	case 'X':
		LookX -= 5;
		glutPostRedisplay();
		break;
	case 'y':
		LookY += 5;
		glutPostRedisplay();
		break;
	case 'Y':
		LookY -= 5;
		glutPostRedisplay();
		break;
	case 'z':
		LookZ += 5;
		glutPostRedisplay();
		break;
	case 'Z':
		LookZ -= 5;
		glutPostRedisplay();
		break;
	case '1':
		if (Line_x < 200)
			++Line_x;
		glutPostRedisplay();
		break;
	case '2':
		if (Line_x > 0)
			--Line_x;
		glutPostRedisplay();
		break;
	case '3':
		if (Line_y < 200)
			++Line_y;
		glutPostRedisplay();
		break;
	case '4':
		if (Line_y > 0)
			--Line_y;
		glutPostRedisplay();
		break;
	case '5':
		if (Line_z < 200)
			++Line_z;
		glutPostRedisplay();
		break;
	case '6':
		if (Line_z > 0)
			--Line_z;
		glutPostRedisplay();
		break;
	case '7':
		
				for (int i = cnt; i < 30; ++i){
					ctrlpoints[i][0] = Line_x;
					ctrlpoints[i][1] = 200 - Line_y;
					ctrlpoints[i][2] = Line_z;
				}
				if (cnt < 30)
					++cnt;
	
		break;
	case '8':
		for (int i = cnt; i < 30; ++i){
			ctrlpoints[i][0] = ctrlpoints[cnt - 1][0];
			ctrlpoints[i][1] = ctrlpoints[cnt - 1][1];
			ctrlpoints[i][2] = ctrlpoints[cnt - 1][2];
		}
		--cnt;
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		SetupRc();
		glutPostRedisplay();
		break;
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}
}
bool collide(Star p){
	if (p.x - p.size / 2 < ctrlpoints[cnt][0] && ctrlpoints[cnt][0] < p.x + p.size / 2 && 200 - p.y - p.size / 2 < ctrlpoints[cnt][1] && ctrlpoints[cnt][1] < 200 - p.y + p.size / 2 && p.z - p.size / 2 < ctrlpoints[cnt][2] && ctrlpoints[cnt][2] < p.z + p.size / 2)
		return true;
	else 
		return false;
}
void TimerFunction(int value) {
	Propeller_Angle += 5;
	for (int i = 0; i < 3000; ++i){
		star[i].rgb[0] += 0.001;
		star[i].rgb[1] += 0.001;
		star[i].rgb[2] += 0.001;
		if (star[i].rgb[0] > 1)
			star[i].rgb[0] = 0;
		if (star[i].rgb[1] > 1)
			star[i].rgb[1] = 0;
		if (star[i].rgb[2] > 1)
			star[i].rgb[2] = 0;
	}
	if (cnt - cur >= 1 && t < 1){		
		t += 0.01;
		mx = (1 - t) * (1 - t) * ctrlpoints[cur][0] + 2 * t * (1 - t) * ctrlpoints[cur + 1][0] + t * t * ctrlpoints[cur + 2][0];
		my = (1 - t) * (1 - t) * (ctrlpoints[cur][1] - 200) + 2 * t * (1 - t) * (ctrlpoints[cur][1] - 200) + t * t * (ctrlpoints[cur + 2][1] - 200);
		mz = (1 - t) * (1 - t) * ctrlpoints[cur][2] + 2 * t * (1 - t) * ctrlpoints[cur + 1][2] + t * t * ctrlpoints[cur + 2][2];

		if (t > 1){
			t = 0;
			if (cnt > cur)
				++cur;
			cout << cnt << ", " << cur << endl;
		}		
	}
	
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, value); // 타이머
}