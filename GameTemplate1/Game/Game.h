#pragma once
#include "sound/SoundSource.h"
#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;


class Game : public IGameObject
{
public:
	//�����o�֐��錾�B
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	int jumpstate = 0;

	GameCamera* gameCamera;
	BackGround* m_backgroud;//�w�i
	Player* player;
	FontRender fontrender;
	Vector3 m_position;
	SkyCube* m_skyCube = nullptr;
	SoundSource* m_bgm = nullptr;
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
};

