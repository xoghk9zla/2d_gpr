struct Tank {
	int hp;   // 탱크의 체력
	int move_limit = 0.0; // 이동 제한
	float x, y, z; // 탱크의 위치
	float shoot_angle; // 발사 할 때의 각도
	float rotate_angle; //회전 각도
	float power; // 발사 할때 파워
	bool turn; // 플레이어의 턴
	Missile missile; //
};