struct Missile {
	//�̻����� �Ұ�, �浹üũ,������,ź�� ����,
	float x, y, z; // �̻����� ��ġ -> �þ� ����
	float vertical_speed; // �����ӵ�
	float horizontal_speed; // ����ӵ�
	int type; // ź�� ����
	int damage; // ������
	float color[3];
	bool turn; // �߻���
};