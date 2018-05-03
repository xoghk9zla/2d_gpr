#include<GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "Missile.h"
#include "Tank.h"
#include "Item.h"
#include "Structure.h"

#include "collide.h"

#define G 1
#define PIE 3.14
#define RADIAN PIE / 180

#define NORMAL 456123
#define OBJECT_DESTROY 456124
#define DAMAGE_UP 456125
#define HEAL 456126

#define THE_NUMBER_OF_ITEM 2
#define THE_NUMBER_OF_OBJECT 15

using namespace std;

///화면 컨트롤을 위한 기본 함수 선언
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);
void init(); // 변수 초기 값으로 초기화
void Camera_move(int value);
bool Collide_tank(Tank t, Structure* ob);
bool Collide_missile(Missile m, Structure *ob, Item *item, Tank t);

Tank player1, player2;
Item item[2];
Structure object[THE_NUMBER_OF_OBJECT];
GLUquadricObj *obj;

bool camera_move1[2];
bool camera_move2[2];
float camera_x, camera_y, camera_z;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(300, 150); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Mini Tank Of City"); // 윈도우 생성 (윈도우 이름) 
	init(); // 변수들 초기값으로 초기화
	glutDisplayFunc(DrawScene); // 출력 함수의 지정
	glutKeyboardFunc(keyboard); // 키보드 입력
	glutSpecialFunc(specialkeyboard); // 키보드 입력(특수키)
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid DrawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	if (player1.turn) {
		gluLookAt(player1.x - 300 * sin(player1.rotate_angle * RADIAN), player1.y + 100, player1.z - 300 * cos(player1.rotate_angle * RADIAN), player1.x, player1.y, player1.z, 0.0, 1.0, 0.0);
	}
	else if (player2.turn) {
		gluLookAt(player2.x - 300 * sin(-player2.rotate_angle * RADIAN), player2.y + 100, player2.z + 300 * cos(player2.rotate_angle * RADIAN), player2.x, player2.y, player2.z, 0.0, 1.0, 0.0);
	}
	else if (player1.missile.turn) {
		gluLookAt(player1.missile.x - 300 * sin(player1.rotate_angle * RADIAN), player1.missile.y + 100, player1.missile.z - 300 * cos(player1.rotate_angle * RADIAN), player1.missile.x, player1.missile.y, player1.missile.z, 0.0, 1.0, 0.0);
	}
	else if (player2.missile.turn) {
		gluLookAt(player2.missile.x + 300 * sin(player2.rotate_angle * RADIAN), player2.missile.y + 100, player2.missile.z + 300 * cos(player2.rotate_angle * RADIAN), player2.missile.x, player2.missile.y, player2.missile.z, 0.0, 1.0, 0.0);
	}
	else if (camera_move1[0] || camera_move1[1]) {
		gluLookAt(camera_x, camera_y + 100, camera_z, player2.x, player2.y, player2.z, 0.0, 1.0, 0.0);
	}
	else if (camera_move2[0] || camera_move2[1]) {
		gluLookAt(camera_x, camera_y + 100, camera_z, player1.x, player1.y, player1.z, 0.0, 1.0, 0.0);
	}

	glPushMatrix();

	// p1.탱크 그리기
	glPushMatrix();

	glTranslatef(player1.x, player1.y, player1.z);
	glRotatef(player1.rotate_angle, 0, 1, 0);

	glTranslatef(-player1.x, -player1.y, -player1.z);

	glPushMatrix();

	glTranslatef(player1.x, player1.y, player1.z);
	glRotatef(-player1.rotate_angle, 0, 1, 0);

	glTranslatef(-player1.x, -player1.y, -player1.z);
	// 폭탄
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);

	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);

	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);

	glVertex3f(player1.missile.x + 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);

	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x + 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);

	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z + 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y + 10.0, player1.missile.z - 10.0);
	glVertex3f(player1.missile.x - 10.0, player1.missile.y - 10.0, player1.missile.z - 10.0);

	glEnd();
	glPopMatrix();
	// 체력바
	for (float i = 0; i < player1.hp / 20; i++)
	{
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(player1.x - 15 + (i * 15), player1.y + 45, player1.z);
		glScalef(10, 10, 10);
		glutSolidCube(1.0);
		glPopMatrix();
	}

	// 파워
	glPushMatrix();
	glTranslatef(0, 58, 0);

	glBegin(GL_QUADS);

	if (player1.missile.type == NORMAL)
		glColor3f(1.0, 1.0, 0.0);
	else if (player1.missile.type == OBJECT_DESTROY)
		glColor3f(1.0, 1.0, 1.0);
	else if (player1.missile.type == DAMAGE_UP)
		glColor3f(0.0, 1.0, 1.0);

	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z + 5);
	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z + 5);

	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z + 5);
	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z - 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z - 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z + 5);

	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z - 5);
	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z - 5);
	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z + 5);
	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z + 5);

	glVertex3f(player1.x + 20.0, player1.y + 5, player1.z - 5);
	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z - 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z - 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z - 5);

	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z - 5);
	glVertex3f(player1.x + 20.0, player1.y - 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z - 5);

	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z + 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y + 5, player1.z - 5);
	glVertex3f(player1.x + 20.0 - (player1.power - 10) * 40 / 30, player1.y - 5, player1.z - 5);

	glEnd();
	glPopMatrix();
	//슛 엥글
	glPushMatrix();
	glTranslatef(-30, 0, -50);

	glBegin(GL_QUADS);

	glColor3f(0.0, 1.0, 1.0);

	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20, player1.z + 5);
	glVertex3f(player1.x + 5, player1.y - 20, player1.z + 5);

	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);
	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);

	glVertex3f(player1.x + 5, player1.y - 20, player1.z - 5);
	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);
	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);
	glVertex3f(player1.x + 5, player1.y - 20, player1.z + 5);

	glVertex3f(player1.x + 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);
	glVertex3f(player1.x + 5, player1.y - 20, player1.z - 5);
	glVertex3f(player1.x - 5, player1.y - 20, player1.z - 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);

	glVertex3f(player1.x + 5, player1.y - 20, player1.z - 5);
	glVertex3f(player1.x + 5, player1.y - 20, player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20, player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20, player1.z - 5);

	glVertex3f(player1.x - 5, player1.y - 20, player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z + 5);
	glVertex3f(player1.x - 5, player1.y - 20 + (player1.shoot_angle / 90 * 40), player1.z - 5);
	glVertex3f(player1.x - 5, player1.y - 20, player1.z - 5);

	glEnd();
	glPopMatrix();
	//탱크
	glBegin(GL_QUADS);

	glColor3f(1.0, 0.0, 0.0);

	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z + 50.0);
	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z + 50.0);

	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z + 50.0);
	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z - 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z - 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z + 50.0);

	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z - 50.0);
	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z - 50.0);
	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z + 50.0);
	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z + 50.0);

	glVertex3f(player1.x + 20.0, player1.y + 20.0, player1.z - 50.0);
	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z - 50.0);
	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z - 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z - 50.0);

	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z - 50.0);
	glVertex3f(player1.x + 20.0, player1.y - 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z - 50.0);

	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z + 50.0);
	glVertex3f(player1.x - 20.0, player1.y + 20.0, player1.z - 50.0);
	glVertex3f(player1.x - 20.0, player1.y - 20.0, player1.z - 50.0);

	glEnd();

	glPopMatrix();

	glPopMatrix();

	// p2.탱크 그리기
	glPushMatrix();

	glPushMatrix();

	glTranslatef(player2.x, player2.y, player2.z);
	glRotatef(player2.rotate_angle, 0, 1, 0);

	glTranslatef(-player2.x, -player2.y, -player2.z);

	glPushMatrix();
	glTranslatef(player2.x, player2.y, player2.z);
	glRotatef(-player2.rotate_angle, 0, 1, 0);

	glTranslatef(-player2.x, -player2.y, -player2.z);
	// 폭탄
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);

	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);

	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);

	glVertex3f(player2.missile.x + 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);

	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x + 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);

	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z + 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y + 10.0, player2.missile.z - 10.0);
	glVertex3f(player2.missile.x - 10.0, player2.missile.y - 10.0, player2.missile.z - 10.0);

	glEnd();

	glPopMatrix();

	for (float i = 0; i < player2.hp / 20; i++)
	{
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(player2.x - 15 + (i * 15), player2.y + 45, player2.z);
		glScalef(10, 10, 10);
		glutSolidCube(1.0);
		glPopMatrix();
	}
	//게이지
	glPushMatrix();
	glTranslatef(0, 58, 0);

	glBegin(GL_QUADS);

	if (player2.missile.type == NORMAL)
		glColor3f(1.0, 1.0, 0.0);
	else if (player2.missile.type == OBJECT_DESTROY)
		glColor3f(1.0, 1.0, 1.0);
	else if (player2.missile.type == DAMAGE_UP)
		glColor3f(0.0, 1.0, 1.0);

	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z + 5);
	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z + 5);

	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z + 5);
	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z - 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z - 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z + 5);

	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z - 5);
	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z - 5);
	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z + 5);
	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z + 5);

	glVertex3f(player2.x + 20.0, player2.y + 5, player2.z - 5);
	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z - 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z - 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z - 5);

	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z - 5);
	glVertex3f(player2.x + 20.0, player2.y - 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z - 5);

	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z + 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y + 5, player2.z - 5);
	glVertex3f(player2.x + 20.0 - (player2.power - 10) * 40 / 30, player2.y - 5, player2.z - 5);

	glEnd();
	glPopMatrix();

	//슛 엥글
	glPushMatrix();
	glTranslatef(30, 0, 50);

	glBegin(GL_QUADS);

	glColor3f(0.0, 1.0, 1.0);

	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20, player2.z + 5);
	glVertex3f(player2.x + 5, player2.y - 20, player2.z + 5);

	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);
	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);

	glVertex3f(player2.x + 5, player2.y - 20, player2.z - 5);
	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);
	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);
	glVertex3f(player2.x + 5, player2.y - 20, player2.z + 5);

	glVertex3f(player2.x + 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);
	glVertex3f(player2.x + 5, player2.y - 20, player2.z - 5);
	glVertex3f(player2.x - 5, player2.y - 20, player2.z - 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);

	glVertex3f(player2.x + 5, player2.y - 20, player2.z - 5);
	glVertex3f(player2.x + 5, player2.y - 20, player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20, player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20, player2.z - 5);

	glVertex3f(player2.x - 5, player2.y - 20, player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z + 5);
	glVertex3f(player2.x - 5, player2.y - 20 + (player2.shoot_angle / 90 * 40), player2.z - 5);
	glVertex3f(player2.x - 5, player2.y - 20, player2.z - 5);

	glEnd();
	glPopMatrix();


	glBegin(GL_QUADS);

	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z + 50.0);
	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z + 50.0);

	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z + 50.0);
	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z - 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z - 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z + 50.0);

	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z - 50.0);
	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z - 50.0);
	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z + 50.0);
	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z + 50.0);

	glVertex3f(player2.x + 20.0, player2.y + 20.0, player2.z - 50.0);
	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z - 50.0);
	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z - 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z - 50.0);

	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z - 50.0);
	glVertex3f(player2.x + 20.0, player2.y - 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z - 50.0);

	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z + 50.0);
	glVertex3f(player2.x - 20.0, player2.y + 20.0, player2.z - 50.0);
	glVertex3f(player2.x - 20.0, player2.y - 20.0, player2.z - 50.0);

	glEnd();

	glPopMatrix();
	// 오브젝트 그리기
	for (int i = 0; i < THE_NUMBER_OF_OBJECT; ++i) {
		glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(object[i].x, object[i].y, object[i].z);
		glRotatef(-90, 1.0, 0.0, 0.0);
		gluCylinder(obj, object[i].r, object[i].r, object[i].height, 20, 8);
		glPopMatrix();
	}
	for (int i = 0; i < THE_NUMBER_OF_ITEM; ++i) {
		glPushMatrix();
		glColor3f(1.0, 0.5, 0.5);
		glTranslatef(item[i].x, item[i].y, item[i].z);
		glRotatef(-90, 1.0, 0.0, 0.0);
		gluCylinder(obj, item[i].r, item[i].r, item[i].height, 20, 8);
		glPopMatrix();
	}
	// 맵 그리기(바닥)
	glColor3f(0.6, 0.45, 0.12);
	glScalef(1.5, 0.2, 3.0);
	glutSolidCube(1000);

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}
void init() {
	player1.x = rand() % 1000 - 500;
	player2.x = -(rand() % 1000 - 500);

	player1.y = 125.0;
	player2.y = 125.0;

	player1.z = rand() % 100 + 75 - 1500;
	player2.z = 1500 - (rand() % 100 + 75);

	player1.shoot_angle = 30.0;
	player2.shoot_angle = 30.0;

	player1.rotate_angle = 0.0;
	player2.rotate_angle = 0.0;

	player1.missile.x = player1.x;
	player1.missile.y = player1.y;
	player1.missile.z = player1.z;

	player2.missile.x = player2.x;
	player2.missile.y = player2.y;
	player2.missile.z = player2.z;

	player1.power = 30.0;
	player1.shoot_angle = 60.0;

	player2.power = 30.0;
	player2.shoot_angle = 60.0;

	player1.turn = true;
	player2.turn = false;

	player1.missile.type = NORMAL;
	player2.missile.type = NORMAL;

	player1.missile.damage = 20;
	player2.missile.damage = 20;

	player1.missile.turn = false;
	player2.missile.turn = false;

	for (int i = 0; i < THE_NUMBER_OF_OBJECT; ++i) {
		object[i].x = rand() % 1300 - 650, object[i].y = 100, object[i].z = rand() % 2000 - 1000;
		object[i].r = rand() % 60 + 30, object[i].height = rand() % 350 + 50;
	}
	for (int i = 0; i < THE_NUMBER_OF_ITEM; ++i) {
		item[i].x = rand() % 1300 - 650, item[i].y = 500, item[i].z = rand() % 2000 - 1000;
		item[i].r = 50, item[i].height = 100;
	}
	camera_move1[0] = false;
	camera_move1[1] = false;
	camera_move2[0] = false;
	camera_move2[1] = false;
	obj = gluNewQuadric();
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(0, Camera_move, 1);
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, 3000.0);
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case  GLUT_KEY_LEFT:
		// 탱크를 왼쪽으로 회전
		if (player1.turn)
			player1.rotate_angle += 5;
		else if (player2.turn)
			player2.rotate_angle += 5;
		glutPostRedisplay();
		break;
	case  GLUT_KEY_RIGHT:
		// 탱크를 왼쪽으로 회전
		if (player1.turn)
			player1.rotate_angle -= 5;
		else if (player2.turn)
			player2.rotate_angle -= 5;
		glutPostRedisplay();
		break;
	case  GLUT_KEY_UP:
		//앞으로 이동
		if (player1.turn) {
			if (player1.move_limit < 60) {
				if (!Collide_tank(player1, object)) {
					++player1.move_limit;
					player1.x += 5 * sin(player1.rotate_angle * RADIAN);
					player1.z += 5 * cos(player1.rotate_angle * RADIAN);
					player1.missile.x += 5 * sin(player1.rotate_angle * RADIAN);
					player1.missile.z += 5 * cos(player1.rotate_angle * RADIAN);
				}
				else {
					player1.x -= 10 * sin(player1.rotate_angle * RADIAN);
					player1.z -= 10 * cos(player1.rotate_angle * RADIAN);
					player1.missile.x -= 10 * sin(player1.rotate_angle * RADIAN);
					player1.missile.z -= 10 * cos(player1.rotate_angle * RADIAN);
				}
			}
		}
		else if (player2.turn) {
			if (player2.move_limit < 60) {
				if (!Collide_tank(player2, object)) {
					++player2.move_limit;
					player2.x -= 5 * sin(player2.rotate_angle * RADIAN);
					player2.z -= 5 * cos(player2.rotate_angle * RADIAN);
					player2.missile.x -= 5 * sin(player2.rotate_angle * RADIAN);
					player2.missile.z -= 5 * cos(player2.rotate_angle * RADIAN);
				}
				else {
					player2.x += 10 * sin(player2.rotate_angle * RADIAN);
					player2.z += 10 * cos(player2.rotate_angle * RADIAN);
					player2.missile.x += 10 * sin(player2.rotate_angle * RADIAN);
					player2.missile.z += 10 * cos(player2.rotate_angle * RADIAN);
				}
			}
		}
		glutPostRedisplay();
		break;
	case  GLUT_KEY_DOWN:
		// 뒤로 이동
		if (player1.turn) {
			if (player1.move_limit < 60) {
				if (!Collide_tank(player1, object)) {
					++player1.move_limit;
					player1.x -= 5 * sin(player1.rotate_angle * RADIAN);
					player1.z -= 5 * cos(player1.rotate_angle * RADIAN);
					player1.missile.x -= 5 * sin(player1.rotate_angle * RADIAN);
					player1.missile.z -= 5 * cos(player1.rotate_angle * RADIAN);
				}
				else {
					player1.x += 10 * sin(player1.rotate_angle * RADIAN);
					player1.z += 10 * cos(player1.rotate_angle * RADIAN);
					player1.missile.x += 10 * sin(player1.rotate_angle * RADIAN);
					player1.missile.z += 10 * cos(player1.rotate_angle * RADIAN);
				}
			}
		}
		else if (player2.turn) {
			if (player2.move_limit < 60) {
				if (!Collide_tank(player2, object)) {
					++player2.move_limit;
					player2.x += 5 * sin(player2.rotate_angle * RADIAN);
					player2.z += 5 * cos(player2.rotate_angle * RADIAN);
					player2.missile.x += 5 * sin(player2.rotate_angle * RADIAN);
					player2.missile.z += 5 * cos(player2.rotate_angle * RADIAN);
				}
				else {
					player2.x -= 10 * sin(player2.rotate_angle * RADIAN);
					player2.z -= 10 * cos(player2.rotate_angle * RADIAN);
					player2.missile.x -= 10 * sin(player2.rotate_angle * RADIAN);
					player2.missile.z -= 10 * cos(player2.rotate_angle * RADIAN);
				}
			}
		}
		glutPostRedisplay();
		break;
	}
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'z':
	case 'Z':
		if (player1.turn) {
			if (player1.shoot_angle < 90) {
				player1.shoot_angle++;
			}
		}
		else {
			if (player2.shoot_angle < 90) {
				player2.shoot_angle++;
			}
		}
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		if (player1.turn) {
			if (player1.shoot_angle > 0) {
				player1.shoot_angle--;
			}
		}
		else {
			if (player2.shoot_angle > 0) {
				player2.shoot_angle--;
			}
		}
		glutPostRedisplay();
		break;
	case ',':
	case '<':
		if (player1.turn) {
			if (player1.power > 10) {
				player1.power--;
			}
		}
		else {
			if (player2.power > 10) {
				player2.power--;
			}
		}
		glutPostRedisplay();
		break;
	case '.':
	case '>':
		if (player1.turn) {
			if (player1.power < 40) {
				player1.power++;
			}
		}
		else {
			if (player2.power < 40) {
				player2.power++;
			}
		}
		glutPostRedisplay();
		break;
	case 'b':
		if (player1.turn) {
			player1.missile.horizontal_speed = player1.power * cos(player1.shoot_angle * RADIAN);
			player1.missile.vertical_speed = -player1.power * sin(player1.shoot_angle * RADIAN);
			player1.move_limit = 0;
			player1.turn = false;
			player1.missile.turn = true;
		}
		else if (player2.turn) {
			player2.missile.horizontal_speed = player2.power * cos(player2.shoot_angle * RADIAN);
			player2.missile.vertical_speed = -player2.power * sin(player2.shoot_angle * RADIAN);
			player2.move_limit = 0;
			player2.turn = false;
			player2.missile.turn = true;
		}
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
void Camera_move(int value) {
	if (player1.missile.turn) {
		if (!Collide_missile(player1.missile, object, item, player2)) {
			player1.missile.vertical_speed += G;
			player1.missile.y -= player1.missile.vertical_speed;
			player1.missile.z += player1.missile.horizontal_speed * cos(player1.rotate_angle * RADIAN);
			player1.missile.x += player1.missile.horizontal_speed * sin(player1.rotate_angle * RADIAN);
		}
		else {
			player1.missile.turn = false;
			camera_move1[0] = true;
			camera_move1[1] = true;
			camera_x = player1.missile.x;
			camera_y = player2.y;
			camera_z = player1.missile.z;
			player1.missile.x = player1.x;
			player1.missile.y = player1.y;
			player1.missile.z = player1.z;
		}
	}
	else if (player2.missile.turn) {
		if (!Collide_missile(player2.missile, object, item, player1)) {
			player2.missile.vertical_speed += G;
			player2.missile.y -= player2.missile.vertical_speed;
			player2.missile.z -= player2.missile.horizontal_speed * cos(player2.rotate_angle * RADIAN);
			player2.missile.x -= player2.missile.horizontal_speed * sin(player2.rotate_angle * RADIAN);
		}
		else {
			player2.missile.turn = false;
			camera_move2[0] = true;
			camera_move2[1] = true;
			camera_x = player2.missile.x;
			camera_y = player1.y;
			camera_z = player2.missile.z;
			player2.missile.x = player2.x;
			player2.missile.y = player2.y;
			player2.missile.z = player2.z;
		}
	}
	else if (camera_move1[0] || camera_move1[1]) {

		if (player2.x - 30 < camera_x && camera_x < player2.x + 30) {
			camera_move1[0] = false;
			if (!camera_move1[0] && !camera_move1[1]) {
				player2.turn = true;
			}
		}
		else {
			camera_x < player2.x ? camera_x += 30 : camera_x -= 30;
		}
		if (player2.z - 30 < camera_z && camera_z < player2.z + 30) {
			camera_move1[1] = false;
			if (!camera_move1[0] && !camera_move1[1]) {
				player2.turn = true;
			}
		}
		else {
			camera_z < player2.z ? camera_z += 30 : camera_z -= 30;
		}
	}
	else if (camera_move2[0] || camera_move2[1]) {

		if (player1.x - 30 < camera_x && camera_x < player1.x + 30) {
			camera_move2[0] = false;
			if (!camera_move2[0] && !camera_move2[1]) {
				player1.turn = true;
			}
		}
		else {
			camera_x < player1.x ? camera_x += 30 : camera_x -= 30;
		}
		if (player1.z - 30 < camera_z && camera_z < player1.z + 30) {
			camera_move2[1] = false;
			if (!camera_move2[0] && !camera_move2[1]) {
				player1.turn = true;
			}
		}
		else {
			camera_z < player1.z ? camera_z += 30 : camera_z -= 30;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, Camera_move, value); // 타이머
}