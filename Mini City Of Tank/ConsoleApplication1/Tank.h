struct Tank {
	int hp;   // ��ũ�� ü��
	int move_limit = 0.0; // �̵� ����
	float x, y, z; // ��ũ�� ��ġ
	float shoot_angle; // �߻� �� ���� ����
	float rotate_angle; //ȸ�� ����
	float power; // �߻� �Ҷ� �Ŀ�
	bool turn; // �÷��̾��� ��
	Missile missile; //
};