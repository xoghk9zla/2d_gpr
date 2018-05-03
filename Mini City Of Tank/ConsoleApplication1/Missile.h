struct Missile {
	//미사일이 할것, 충돌체크,데미지,탄의 종류,
	float x, y, z; // 미사일의 위치 -> 시야 관리
	float vertical_speed; // 수직속도
	float horizontal_speed; // 수평속도
	int type; // 탄의 종류
	int damage; // 데미지
	float color[3];
	bool turn; // 발사중
};