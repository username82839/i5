#pragma once

class Player;

class Player : public IGameObject
{
public:
	//�����o�֐��錾
	Player();
	~Player();

	bool Start();

	void Move();
	void Update();
	void PlayAnimation();
	void Rotation();
	void ManageState();
	void Render(RenderContext& rc);
	

	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_jump,
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};

	
	//�����o�ϐ��Ƃ��̐錾
	ModelRender modelRender;
	Vector3 m_position;
	AnimationClip m_animClips[enAnimationClip_Num]; //�A�j���[�V�����N���b�v
	CharacterController characterController; //�L�����N�^�[�R���g���[���[
	Vector3 m_moveSpeed;//�ړ����x�B
	Quaternion rotation;
	Vector3		forward = Vector3::AxisZ;
	

	int playerState = 0;
	int jumpstate = 0;
	int starCount = 0;
};

