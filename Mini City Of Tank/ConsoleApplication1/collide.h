#include <math.h>

#include "Tank.h"
#include "Item.h"
#include "Missile.h"
#include "Structure.h"

#define THE_NUMBER_OF_ITEM 2
#define THE_NUMBER_OF_OBJECT 15

bool Collide_tank(Tank t, Structure* ob){
	if (-750 > t.x || t.x > 750)
		return true;
	if (-1500 > t.z || t.z > 1500)
		return true;
	for (int i = 0; i < THE_NUMBER_OF_OBJECT; ++i) {
		if (sqrt((ob[i].x - t.x) * (ob[i].x - t.x) + (ob[i].z - t.z) * (ob[i].z - t.z)) < ob[i].r + 20)
			return true;
		if (sqrt((ob[i].x - t.x) * (ob[i].x - t.x) + (ob[i].z - t.z + 30) * (ob[i].z - t.z + 30)) < ob[i].r + 20)
			return true;
		if (sqrt((ob[i].x - t.x) * (ob[i].x - t.x) + (ob[i].z - t.z - 30) * (ob[i].z - t.z - 30)) < ob[i].r + 20)
			return true;
	}
	return false;

}
bool Collide_missile(Missile m, Structure *ob, Item *item, Tank t){
	if (m.y < 100)
		return true;
	if (-750 > m.x || m.x > 750)
		return true;
	if (-1500 > m.z || m.z > 1500)
		return true;
	for (int i = 0; i < THE_NUMBER_OF_OBJECT; ++i) {
		if (sqrt((ob[i].x - m.x)*(ob[i].x - m.x) + (ob[i].z - m.z)*(ob[i].z - m.z)) < ob[i].r + 20 && ob[i].height > m.y) {
			if (player1.missile.turn && player1.missile.type == OBJECT_DESTROY) {
				ob[i].x = 30000, ob[i].z = 30000;
				player1.missile.type = NORMAL;
			}
			else if (player2.missile.turn && player2.missile.type == OBJECT_DESTROY) {
				player2.missile.type = NORMAL;
			}
			return true;
		}
		if (sqrt((ob[i].x - m.x)*(ob[i].x - m.x) + (ob[i].z - m.z + 30)*(ob[i].z - m.z + 30)) < ob[i].r + 20 && ob[i].height + 100> m.y) {
			if (player1.missile.turn && player1.missile.type == OBJECT_DESTROY) {
				ob[i].x = 30000, ob[i].z = 30000;
				player1.missile.type = NORMAL;
			}
			else if (player2.missile.turn && player2.missile.type == OBJECT_DESTROY) {
				player2.missile.type = NORMAL;
			}
			return true;
		}
		if (sqrt((ob[i].x - m.x)*(ob[i].x - m.x) + (ob[i].z - m.z - 30)*(ob[i].z - m.z - 30)) < ob[i].r + 20 && ob[i].height + 100> m.y) {
			if (player1.missile.turn && player1.missile.type == OBJECT_DESTROY) {
				ob[i].x = 30000, ob[i].z = 30000;
				player1.missile.type = NORMAL;
			}
			else if (player2.missile.turn && player2.missile.type == OBJECT_DESTROY) {
				player2.missile.type = NORMAL;
			}
			return true;
		}
	}
	for (int i = 0; i < THE_NUMBER_OF_ITEM; ++i) {
		if (sqrt((item[i].x - m.x)*(item[i].x - m.x) + (item[i].z - m.z)*(item[i].z - m.z)) < item[i].r + 20 && (item[i].y < m.y && m.y < item[i].y + item[i].height)) {
			item[i].x = rand() % 1300 - 650, item[i].z = rand() % 2000 - 1000;
			if (rand() % 3 == 0) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = OBJECT_DESTROY;
				}
				else {
					player2.missile.type = OBJECT_DESTROY;
				}
			}
			else if (rand() % 3 == 1) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = DAMAGE_UP;
				}
				else {
					player2.missile.type = DAMAGE_UP;
				}
			}
			else if (rand() % 3 == 2) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					if (player1.hp < 60)
						player1.hp += 20;
				}
				else {
					if (player2.hp < 60)
						player2.hp += 20;
				}
			}
			return true;
		}
		if (sqrt((item[i].x - m.x)*(item[i].x - m.x) + (item[i].z - m.z + 30)*(item[i].z - m.z + 30)) < item[i].r + 20 && (item[i].y < m.y && m.y < item[i].y + item[i].height)) {
			item[i].x = rand() % 1300 - 650, item[i].z = rand() % 2000 - 1000;
			if (rand() % 3 == 0) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = OBJECT_DESTROY;
				}
				else {
					player2.missile.type = OBJECT_DESTROY;
				}
			}
			else if (rand() % 3 == 1) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = DAMAGE_UP;
				}
				else {
					player2.missile.type = DAMAGE_UP;
				}
			}
			else if (rand() % 3 == 2) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					if (player1.hp < 60)
						player1.hp += 20;
				}
				else {
					if (player2.hp < 60)
						player2.hp += 20;
				}
			}
			return true;
		}
		if (sqrt((item[i].x - m.x)*(item[i].x - m.x) + (item[i].z - m.z - 30)*(item[i].z - m.z - 30)) < item[i].r + 20 && (item[i].y < m.y && m.y < item[i].y + item[i].height)) {
			item[i].x = rand() % 1300 - 650, item[i].z = rand() % 2000 - 1000;
			if (rand() % 3 == 0) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = OBJECT_DESTROY;
				}
				else {
					player2.missile.type = OBJECT_DESTROY;
				}
			}
			else if (rand() % 3 == 1) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					player1.missile.type = DAMAGE_UP;
				}
				else {
					player2.missile.type = DAMAGE_UP;
				}
			}
			else if (rand() % 3 == 2) {
				if (player1.missile.turn)
				if (player1.missile.turn) {
					if (player1.hp < 60)
						player1.hp += 20;
				}
				else {
					if (player2.hp < 60)
						player2.hp += 20;
				}
			}
			return true;
		}
	}

	if (sqrt((t.x - m.x)*(t.x - m.x) + (t.z - m.z + 10)*(t.z - m.z + 10)) < 30 && t.y + 20 > m.y) {
		if (player1.missile.turn) {
			if (player1.missile.type == DAMAGE_UP) {
				player2.hp -= player1.missile.damage * 2;
				player1.missile.type = NORMAL;
			}
			else {
				player2.hp -= player1.missile.damage;
			}
		}
		else {
			if (player2.missile.type == DAMAGE_UP) {
				player1.hp -= player2.missile.damage * 2;
				player2.missile.type = NORMAL;
			}
			else {
				player1.hp -= player2.missile.damage;
			}
		}
		return true;
	}
	if (sqrt((t.x - m.x)*(t.x - m.x) + (t.z - m.z + 30)*(t.z - m.z + 30)) < 30 && t.y + 20 > m.y) {
		if (player1.missile.turn) {
			if (player1.missile.type == DAMAGE_UP) {
				player2.hp -= player1.missile.damage * 2;
				player1.missile.type = NORMAL;
			}
			else {
				player2.hp -= player1.missile.damage;
			}
		}
		else {
			if (player2.missile.type == DAMAGE_UP) {
				player1.hp -= player2.missile.damage * 2;
				player2.missile.type = NORMAL;
			}
			else {
				player1.hp -= player2.missile.damage;
			}
		}
		return true;
	}
	if (sqrt((t.x - m.x)*(t.x - m.x) + (t.z - m.z - 30)*(t.z - m.z - 30)) < 30 && t.y + 20 > m.y) {
		if (player1.missile.turn) {
			if (player1.missile.type == DAMAGE_UP) {
				player2.hp -= player1.missile.damage * 2;
				player1.missile.type = NORMAL;
			}
			else {
				player2.hp -= player1.missile.damage;
			}
		}
		else {
			if (player2.missile.type == DAMAGE_UP) {
				player1.hp -= player2.missile.damage * 2;
				player2.missile.type = NORMAL;
			}
			else {
				player1.hp -= player2.missile.damage;
			}
		}
		return true;
	}
	if (sqrt((t.x - m.x)*(t.x - m.x) + (t.z - m.z - 10)*(t.z - m.z - 10)) < 30 && t.y + 20 > m.y) {
		if (player1.missile.turn) {
			if (player1.missile.type == DAMAGE_UP) {
				player2.hp -= player1.missile.damage * 2;
				player1.missile.type = NORMAL;
			}
			else {
				player2.hp -= player1.missile.damage;
			}
		}
		else {
			if (player2.missile.type == DAMAGE_UP) {
				player1.hp -= player2.missile.damage * 2;
				player2.missile.type = NORMAL;
			}
			else {
				player1.hp -= player2.missile.damage;
			}
		}
		return true;
	}

	return false;
}