#include<GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define LEFT -400
#define RIGHT 400
#define TOP 300
#define BOTTOM -300

#define NULL 0

#define SPEED 3

///화면 컨트롤을 위한 기본 함수 선언
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void MoveTimerFunction(int value);
void SetupRc();	// 필요한 변수 초기화
void RectCut(int Case);	// 도형 자르기

struct Point {
	int x, y;
};
struct Object {
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
	int x5, y5;
};

Object r1, r2, r3, r4, r5, r6;
Point point[2];
int cnt = 0, time = 0;
int dy1 = 0, dy2 = 0;
bool Click, Move, Go, Part;
bool Left, Right, Top, Bottom;

void main(int argc, char *argv[]) {
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 0); //    윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("숙제1"); // 윈도우 생성 (윈도우 이름) 
	SetupRc();	// 상태 변수 초기화
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(Keyboard);		// 키보드 입력
	glutMouseFunc(Mouse);	// 마우스 입력
	glutMotionFunc(Motion);	// 마우스 움직임
	glutTimerFunc(0, MoveTimerFunction, 0);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	glColor3f(1.0, 0.5, 1.0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(r1.x1, r1.y1 + dy1);
	glVertex2f(r1.x2, r1.y2 + dy1);
	glVertex2f(r1.x3, r1.y3 + dy1);
	glVertex2f(r1.x4, r1.y4 + dy1);
	glVertex2f(r1.x5, r1.y5 + dy1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(r2.x1, r2.y1 + dy2);
	glVertex2f(r2.x2, r2.y2 + dy2);
	glVertex2f(r2.x3, r2.y3 + dy2);
	glVertex2f(r2.x4, r2.y4 + dy2);
	glVertex2f(r2.x5, r2.y5 + dy2);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(r3.x1, r3.y1);
	glVertex2f(r3.x2, r3.y2);
	glVertex2f(r3.x3, r3.y3);
	glVertex2f(r3.x4, r3.y4);
	glEnd();

	glColor3f(0.3, 0.3, 0.3);

	glBegin(GL_LINE_LOOP);
	glVertex2f(r4.x1, r4.y1);
	glVertex2f(r4.x2, r4.y2);
	glVertex2f(r4.x3, r4.y3);
	glVertex2f(r4.x4, r4.y4);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(r5.x1, r5.y1);
	glVertex2f(r5.x2, r5.y2);
	glVertex2f(r5.x3, r5.y3);
	glVertex2f(r5.x4, r5.y4);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(r6.x1, r6.y1);
	glVertex2f(r6.x2, r6.y2);
	glVertex2f(r6.x3, r6.y3);
	glVertex2f(r6.x4, r6.y4);
	glEnd();

	glutSwapBuffers();
}
void SetupRc() {
	r1.x1 = 200, r1.y1 = 200;
	r1.x2 = 200, r1.y2 = 100;
	r1.x3 = 300, r1.y3 = 100;
	r1.x4 = 300, r1.y4 = 200;
	r1.x5 = 300, r1.y5 = 200;

	r2.x1 = 200, r2.y1 = 200;
	r2.x2 = 200, r2.y2 = 100;
	r2.x3 = 300, r2.y3 = 100;
	r2.x4 = 300, r2.y4 = 200;
	r2.x5 = 300, r2.y5 = 200;

	r3.x1 = -75, r3.y1 = -150;
	r3.x2 = -75, r3.y2 = -200;
	r3.x3 = 75, r3.y3 = -200;
	r3.x4 = 75, r3.y4 = -150;

	r4.x1 = -100, r4.y1 = -100;
	r4.x2 = -100, r4.y2 = -200;
	r4.x3 = -75, r4.y3 = -200;
	r4.x4 = -75, r4.y4 = -100;

	r5.x1 = 75, r5.y1 = -100;
	r5.x2 = 75, r5.y2 = -200;
	r5.x3 = 100, r5.y3 = -200;
	r5.x4 = 100, r5.y4 = -100;

	r6.x1 = -100, r6.y1 = -200;
	r6.x2 = -100, r6.y2 = -225;
	r6.x3 = 100, r6.y3 = -225;
	r6.x4 = 100, r6.y4 = -200;

	cnt = 0, dy1 = 0, dy2 = 0;
	Click = false, Move = true, Go = true, Part = false;
	Left = false, Right = false, Top = false, Bottom = false;
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(LEFT, RIGHT, BOTTOM, TOP, -1.0, 1.0);
}
void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Click = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		Click = false;
		if (Part == false) {
			if (Left == true && Right == true) {
				if (point[0].x == 200) {
					r1.x2 = point[0].x, r1.y2 = point[0].y;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x3 = point[1].x, r1.y3 = point[1].y;
					r2.x4 = point[1].x, r2.y4 = point[1].y;
					r2.x5 = point[1].x, r2.y5 = point[1].y;
				}
				else {
					r1.x2 = point[1].x, r1.y2 = point[1].y;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x3 = point[0].x, r1.y3 = point[0].y;
					r2.x4 = point[0].x, r2.y4 = point[0].y;
					r2.x5 = point[0].x, r2.y5 = point[0].y;
				}
				RectCut(1);
				Part = true;
			}
			else if (Left == true && Top == true) {
				if (point[0].x == 200) {
					r1.x2 = point[0].x, r1.y2 = point[0].y;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x3 = point[1].x, r1.y3 = point[1].y;
					r1.x4 = point[1].x, r1.y4 = point[1].y;
					r1.x5 = point[1].x, r1.y5 = point[1].y;
					r2.x5 = point[1].x, r2.y5 = point[1].y;
				}
				else {
					r1.x2 = point[1].x, r1.y2 = point[1].y;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x3 = point[0].x, r1.y3 = point[0].y;
					r1.x4 = point[0].x, r1.y4 = point[0].y;
					r1.x5 = point[0].x, r1.y5 = point[0].y;
					r2.x5 = point[0].x, r2.y5 = point[0].y;
				}
				RectCut(2);
				Part = true;
			}
			else if (Left == true && Bottom == true) {
				if (point[0].x == 200) {
					r1.x2 = point[0].x, r1.y2 = point[0].y;
					r1.x4 = r1.x3, r1.y4 = r2.y3;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x3 = point[1].x, r1.y3 = point[1].y;
					r2.x3 = point[1].x, r2.y3 = point[1].y;
					r2.x4 = point[1].x, r2.y4 = point[1].y;
					r2.x5 = point[1].x, r2.y5 = point[1].y;
				}
				else {
					r1.x2 = point[1].x, r1.y2 = point[1].y;
					r1.x4 = r1.x3, r1.y4 = r2.y3;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x3 = point[0].x, r1.y3 = point[0].y;
					r2.x3 = point[0].x, r2.y3 = point[0].y;
					r2.x4 = point[0].x, r2.y4 = point[0].y;
					r2.x5 = point[0].x, r2.y5 = point[0].y;
				}
				RectCut(3);
				Part = true;
			}
			else if (Right == true && Top == true) {
				if (point[0].x == 300) {
					r1.x4 = point[0].x, r1.y4 = point[0].y;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x5 = point[1].x, r1.y5 = point[1].y;
					r2.x2 = point[1].x, r2.y2 = point[1].y;
					r2.x3 = point[1].x, r2.y3 = point[1].y;
					r2.x4 = point[1].x, r2.y4 = point[1].y;
				}
				else {
					r1.x4 = point[1].x, r1.y4 = point[1].y;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x5 = point[0].x, r1.y5 = point[0].y;
					r2.x2 = point[0].x, r2.y2 = point[0].y;
					r2.x3 = point[0].x, r2.y3 = point[0].y;
					r2.x4 = point[0].x, r2.y4 = point[0].y;
				}
				RectCut(4);
				Part = true;
			}
			else if (Right == true && Bottom == true) {
				if (point[0].x == 300) {
					r1.x4 = point[0].x, r1.y4 = point[0].y;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x3 = point[1].x, r1.y3 = point[1].y;
					r2.x2 = r2.x3, r2.y2 = r2.y3;
					r2.x4 = point[1].x, r2.y4 = point[1].y;
					r2.x5 = point[1].x, r2.y5 = point[1].y;
				}
				else {
					r1.x4 = point[1].x, r1.y4 = point[1].y;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x3 = point[0].x, r1.y3 = point[0].y;
					r2.x2 = r2.x3, r2.y2 = r2.y3;
					r2.x4 = point[0].x, r2.y4 = point[0].y;
					r2.x5 = point[0].x, r2.y5 = point[0].y;
				}
				RectCut(5);
				Part = true;
			}
			else if (Top == true && Bottom == true) {
				if (point[0].y == 200) {
					r1.x4 = point[0].x, r1.y4 = point[0].y;
					r1.x5 = point[0].x, r1.y5 = point[0].y;
					r2.x1 = point[0].x, r2.y1 = point[0].y;

					r1.x3 = point[1].x, r1.y3 = point[1].y;
					r2.x2 = point[1].x, r2.y2 = point[1].y;
				}
				else {
					r1.x4 = point[1].x, r1.y4 = point[1].y;
					r1.x5 = point[1].x, r1.y5 = point[1].y;
					r2.x1 = point[1].x, r2.y1 = point[1].y;

					r1.x3 = point[0].x, r1.y3 = point[0].y;
					r2.x2 = point[0].x, r2.y2 = point[0].y;
				}
				RectCut(6);
				Part = true;
			}
		}
		glutPostRedisplay();
	}
}
void Motion(int x, int y) {
	if (Click == true) {
		// 왼쪽
		if (r1.x1 - 10 < x + LEFT && x + LEFT < r1.x1 + 10 && (r1.y1 - 100 < (600 - y) + BOTTOM && (600 - y) + BOTTOM < r1.y1)) {
			Left = true;
			point[cnt].x = r1.x1;
			point[cnt].y = (600 - y) + BOTTOM;
			if (cnt < 1)
				cnt += 1;
		}
		// 오른쪽
		else if (r1.x3 - 10 < x + LEFT && x + LEFT < r1.x3 + 10 && (r1.y1 - 100 < (600 - y) + BOTTOM && (600 - y) + BOTTOM < r1.y1)) {
			Right = true;
			point[cnt].x = r1.x3;
			point[cnt].y = (600 - y) + BOTTOM;
			if (cnt < 1)
				cnt += 1;
		}
		// 위쪽
		else if (r1.y1 - 10 < (600 - y) + BOTTOM && (600 - y) + BOTTOM < r1.y1 + 10 && r1.x1 < x + LEFT && x + LEFT < r1.x1 + 100) {
			Top = true;
			point[cnt].x = x + LEFT;
			point[cnt].y = r1.y1;
			if (cnt < 1)
				cnt += 1;
		}
		// 아래쪽
		else if (r1.y2 - 10 < (600 - y) + BOTTOM && (600 - y) + BOTTOM < r1.y2 + 10 && r1.x1 < x + LEFT && x + LEFT < r1.x1 + 100) {
			Bottom = true;
			point[cnt].x = x + LEFT;
			point[cnt].y = r1.y2;
			if (cnt < 1)
				cnt += 1;
		}
	}
}
void RectCut(int Case) {
	// Left == true && Right == true
	if (Case == 1) {
		if (((r1.y1 - r1.y2) + (r1.y4 - r1.y3)) * (r1.x4 - r1.x1) < ((r2.y1 - r2.y2) + (r2.y4 - r2.y3)) * (r2.x4 - r2.x1)) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
	// Left == true && Top == true
	else if (Case == 2) {
		if (((r1.y1 - r1.y2) * (r1.x4 - r1.x1)) / 2 > 400 - ((r1.y1 - r1.y2) * (r1.x4 - r1.x1)) / 2) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
	// Left == true && Bottom == true
	else if (Case == 3) {
		if (((r2.y1 - r2.y2) * (r2.x4 - r2.x1)) / 2 < 400 - ((r2.y1 - r2.y2) * (r2.x4 - r2.x1)) / 2) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
	// Right == true && Top == true
	else if (Case == 4) {
		if (((r2.y2 - r2.y3) * (r2.x4 - r2.x1)) / 2 > 400 - ((r2.y2 - r2.y3) * (r2.x4 - r2.x1)) / 2) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
	// Right == true && Bottom == true
	else if (Case == 5) {
		if (((r2.y1 - r2.y2) * (r2.x4 - r2.x1)) / 2 > 400 - ((r2.y1 - r2.y2) * (r2.x4 - r2.x1)) / 2) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
	// Top == true && Bottom == true
	else if (Case == 6) {
		if (((r1.x4 - r1.x1) + (r1.x3 - r1.x2)) * (r1.y1 - r1.y2) < ((r2.x4 - r2.x1) + (r2.x3 - r2.x2)) * (r2.y1 - r2.y2)) {
			glutTimerFunc(0, TimerFunction, 1);
		}
		else {
			glutTimerFunc(0, TimerFunction, 2);
		}
	}
}
void TimerFunction(int value){
	if (Part) {
		if (value == 1) {
			dy1 -= SPEED;
			r2.x1 += SPEED;
			r2.x2 += SPEED;
			r2.x3 += SPEED;
			r2.x4 += SPEED;
			r2.x5 += SPEED;
			if (r1.y2 < r1.y3){
				if (r1.y2 + dy1 < r3.y2 && r3.x1 < r1.x1 && r1.x4 < r3.x4) {
					dy1 += SPEED;
					Move = false;
				}
			}
			else{
				if (r1.y3 + dy1 < r3.y2 && r3.x1 < r1.x1 && r1.x4 < r3.x4){
					dy1 += SPEED;
					Move = false;
				}
			}
		}
		else if (value == 2) {
			dy2 -= SPEED;
			r1.x1 += SPEED;
			r1.x2 += SPEED;
			r1.x3 += SPEED;
			r1.x4 += SPEED;
			r1.x5 += SPEED;
			if (r1.y2 <= r1.y3){
				if (r1.y2 == r1.y3){
					if (r2.y1 + dy2 < r3.y2 && r3.x1 < r2.x1 && r2.x4 < r3.x4) {
						dy2 += SPEED;
						Move = false;
					}
				}
				else{
					if (r2.y2 + dy2 < r3.y2 && r3.x1 < r2.x1 && r2.x4 < r3.x4) {
						dy2 += SPEED;
						Move = false;
					}
				}
			}
			else{
				if (r2.y3 + dy2 < r3.y2 && r3.x1 < r2.x1 && r2.x4 < r3.x4) {
					cout << "x";
					dy2 += SPEED;
					Move = false;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, value); // 타이머
}
void MoveTimerFunction(int value) {
	if (Move) {
		++time;
		if (Go) {
			if (r3.y1 != -150 && time % 4 == 0){
				r3.y1 = -150;
			}
			r3.x1 += SPEED * 3;
			r3.x2 += SPEED * 3;
			r3.x3 += SPEED * 3;
			r3.x4 += SPEED * 3;
			r4.x1 += SPEED * 3;
			r4.x2 += SPEED * 3;
			r4.x3 += SPEED * 3;
			r4.x4 += SPEED * 3;
			r5.x1 += SPEED * 3;
			r5.x2 += SPEED * 3;
			r5.x3 += SPEED * 3;
			r5.x4 += SPEED * 3;
			r6.x1 += SPEED * 3;
			r6.x2 += SPEED * 3;
			r6.x3 += SPEED * 3;
			r6.x4 += SPEED * 3;
			if (r3.x4 > 375){
				Go = false;
				r3.y4 += 10;
			}
		}
		else {

			if (r3.y4 != -150 && time % 4 == 0){
				r3.y4 = -150;
			}
			r3.x1 -= SPEED * 3;
			r3.x2 -= SPEED * 3;
			r3.x3 -= SPEED * 3;
			r3.x4 -= SPEED * 3;
			r4.x1 -= SPEED * 3;
			r4.x2 -= SPEED * 3;
			r4.x3 -= SPEED * 3;
			r4.x4 -= SPEED * 3;
			r5.x1 -= SPEED * 3;
			r5.x2 -= SPEED * 3;
			r5.x3 -= SPEED * 3;
			r5.x4 -= SPEED * 3;
			r6.x1 -= SPEED * 3;
			r6.x2 -= SPEED * 3;
			r6.x3 -= SPEED * 3;
			r6.x4 -= SPEED * 3;
			if (r3.x1 < -375){
				Go = true;
				r3.y1 += 10;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, MoveTimerFunction, value); // 타이머
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
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