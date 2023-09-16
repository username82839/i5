#pragma once

class Player;
//���N���X�B
class Star : public IGameObject
{
public:
	Star();
	~Star();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ������B
	void Move();
	//��]�����B
	void Rotation();

	//�����o�ϐ��B
	ModelRender modelRender;	//���f�������_�\�B
	Vector3 position;		//���W�B
	int moveCount;		//��Ɉړ������Ɉړ����B
	Vector3 firstPosition;		//�ŏ��̍��W�B
	Quaternion rotation;	//�N�H�[�^�j�I���B
	Player* player;		//�v���C���[�B
};

