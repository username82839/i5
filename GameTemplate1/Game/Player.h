#pragma once

class Player;

class Player : public IGameObject
{
public:
	//メンバ関数宣言
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
		enAnimationClip_idle,	//待機アニメーション。
		enAnimationClip_run,	//走りアニメーション。
		enAnimationClip_walk,	//歩きアニメーション。
		enAnimationClip_jump,
		enAnimationClip_Num,	//アニメーションクリップの数。
	};

	
	//メンバ変数とかの宣言
	ModelRender modelRender;
	Vector3 m_position;
	AnimationClip m_animClips[enAnimationClip_Num]; //アニメーションクリップ
	CharacterController characterController; //キャラクターコントローラー
	Vector3 m_moveSpeed;//移動速度。
	Quaternion rotation;
	Vector3		forward = Vector3::AxisZ;
	

	int playerState = 0;
	int jumpstate = 0;
	int starCount = 0;
};

