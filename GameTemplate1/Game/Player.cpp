#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].Load("Assets/animData/jump.tka");
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);
	//���j�e�B�����̃��f����ǂݍ��ށB
	modelRender.Init("Assets/modelData/unityChan.tkm", m_animClips, enAnimationClip_Num, enModelUpAxisY);
	//�L�����R��������������B
	characterController.Init(25.0f, 75.0f, m_position);
}


Player::~Player()
{

}

bool Player::Start()
{
	return true;
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
	right *= stickL.x * 400.0f;
	forward *= stickL.y * 400.0f;
	if (g_pad[0]->IsPress(enButtonB))
	{
		right *= 3;
		forward *= 3;
	}
	if (g_pad[0]->IsPress(enButtonLB1))
	{
		right /=3;
		forward /= 3;
	}
	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//�n�ʂɕt���Ă�����B
	if (characterController.IsOnGround()==true)
	{
		//�d�͂𖳂����B
		m_moveSpeed.y = 0.0f;
		jumpstate = 0;
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v������B
			m_moveSpeed.y = 800.0f;
		}


	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 17.0f;
		if (g_pad[0]->IsPress(enButtonLB1))
		{
			m_moveSpeed.y += 10.0f;
		}
	}

	if (characterController.IsOnGround() == false)
	{
		if (g_pad[0]->IsTrigger(enButtonA) && jumpstate == 1)
		{
			jumpstate = 2;
			m_moveSpeed.y = 1000.0f;
			if (g_pad[0]->IsPress(enButtonLB1))
			{
				m_moveSpeed.y -= 1.0f;
			}
		}
		if (g_pad[0]->IsTrigger(enButtonA) && jumpstate == 0)
		{
			jumpstate = 1;
			m_moveSpeed.y = 1000.0f;
			if (g_pad[0]->IsPress(enButtonLB1))
			{
				m_moveSpeed.y -= 1.0f;
			}
			
		}
	}
	

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	modelRender.SetPosition(m_position);
	
}

void Player::Update()
{
	Move();
	PlayAnimation();
	ManageState();
	Rotation();
	

	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	/*if (g_pad[0]->IsTrigger(enButtonA)) {
		//Play�֐��̑������͕⊮���ԁB
		//�ҋ@���[�V�����̐؂�ւ��͕⊮���Ԃ�ݒ肵�Ă��Ȃ��̂ŁA�A�j���[�V�������p�L���ƕς��B
		modelRender.PlayAnimation(enAnimationClip_idle);
	}
	//B�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	 if (g_pad[0]->IsPress(enButtonB))
	{
		modelRender.PlayAnimation(enAnimationClip_run, 0.2f);
		m_position.z += 5.0f;
	}
	//Y�{�^���������ꂽ������A�j���[�V�������Đ�����B
	else if (g_pad[0]->IsPress(enButtonY)) {
		modelRender.PlayAnimation(enAnimationClip_walk, 0.2f);
		m_position.z += 1.0f;
	}
	*/

	//sample

	if (g_pad[0]->IsPress(enButtonX))
	{
		m_position.x = 0.0f;
		m_position.y = 0.0f;
	}

	
	// g_renderingEngine->DisableRaytracing();
	modelRender.Update();
}

void Player::PlayAnimation()
{

		/*
		if (fabsf(m_moveSpeed.x) <= 0.001f || fabsf(m_moveSpeed.z) <= 0.001f)
		{
			playerState == 0;
		}

		*/


	switch (playerState)
	{
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		modelRender.PlayAnimation(enAnimationClip_idle);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		modelRender.PlayAnimation(enAnimationClip_jump);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		modelRender.PlayAnimation(enAnimationClip_walk);
		break;
	case 3:
		modelRender.PlayAnimation(enAnimationClip_run);
		break;
	}
	modelRender.Update();
}

void Player::Rotation()
{/*
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		rotation.SetRotationYFromDirectionXZ(m_position);

		//�G�`������ɉ�]��������B
		modelRender.SetRotation(rotation);
	}
	*/
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	rotation.SetRotationY(-angle);
	//��]��ݒ肷��B
	modelRender.SetRotation(rotation);

	//�v���C���[�̐��ʃx�N�g�����v�Z����B
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1(�W�����v��)�ɂ���B
		playerState = 1;
		//������ManageState�̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B

	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�ړ����x�����ȏゾ������B
		if (m_moveSpeed.LengthSq() >= 200.0f * 200.0f)
		{
			//�X�e�[�g�𑖂�ɂ���B
			playerState = 2;
			return;
		}
		else
		{
			//�����ɂ���B
			playerState = 2;
			return;
		}

	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��ҋ@�ɂ���B
		playerState = 0;
		return;
	}
	
}

void Player::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}