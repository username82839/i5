#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{
	//アニメーションクリップをロードする。
	m_animClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_jump].Load("Assets/animData/jump.tka");
	m_animClips[enAnimationClip_jump].SetLoopFlag(false);
	//ユニティちゃんのモデルを読み込む。
	modelRender.Init("Assets/modelData/unityChan.tkm", m_animClips, enAnimationClip_Num, enModelUpAxisY);
	//キャラコンを初期化する。
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
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算。
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
	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//地面に付いていたら。
	if (characterController.IsOnGround()==true)
	{
		//重力を無くす。
		m_moveSpeed.y = 0.0f;
		jumpstate = 0;
		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ジャンプさせる。
			m_moveSpeed.y = 800.0f;
		}


	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
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
	

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	modelRender.SetPosition(m_position);
	
}

void Player::Update()
{
	Move();
	PlayAnimation();
	ManageState();
	Rotation();
	

	//Aボタンが押されたら待機モーションを再生する。
	/*if (g_pad[0]->IsTrigger(enButtonA)) {
		//Play関数の第二引数は補完時間。
		//待機モーションの切り替えは補完時間を設定していないので、アニメーションがパキっと変わる。
		modelRender.PlayAnimation(enAnimationClip_idle);
	}
	//Bボタンが押されたら走りアニメーションを再生する。
	 if (g_pad[0]->IsPress(enButtonB))
	{
		modelRender.PlayAnimation(enAnimationClip_run, 0.2f);
		m_position.z += 5.0f;
	}
	//Yボタンが押されたら歩きアニメーションを再生する。
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
		//待機アニメーションを再生する。
		modelRender.PlayAnimation(enAnimationClip_idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		modelRender.PlayAnimation(enAnimationClip_jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
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
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		rotation.SetRotationYFromDirectionXZ(m_position);

		//絵描きさんに回転を教える。
		modelRender.SetRotation(rotation);
	}
	*/
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	rotation.SetRotationY(-angle);
	//回転を設定する。
	modelRender.SetRotation(rotation);

	//プレイヤーの正面ベクトルを計算する。
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

void Player::ManageState()
{
	//地面に付いていなかったら。
	if (characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする。
		playerState = 1;
		//ここでManageStateの処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。

	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//移動速度が一定以上だったら。
		if (m_moveSpeed.LengthSq() >= 200.0f * 200.0f)
		{
			//ステートを走りにする。
			playerState = 2;
			return;
		}
		else
		{
			//歩きにする。
			playerState = 2;
			return;
		}

	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを待機にする。
		playerState = 0;
		return;
	}
	
}

void Player::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}