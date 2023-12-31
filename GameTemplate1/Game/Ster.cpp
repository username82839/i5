#include "stdafx.h"
#include"Ster.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Star::Star()
{
	//☆のモデルを読み込む。
	modelRender.Init("Assets/modelData/star.tkm");

	player = FindGO<Player>("player");

	//☆を削除する時の音を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/get.wav");
}

Star::~Star()
{

}

void Star::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//絵描きさんの更新処理。
	modelRender.Update();

	//プレイヤーから☆に向かうベクトルを計算。
	Vector3 diff = player->m_position - position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{
		//効果音を再生する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->SetVolume(3.5f);
		se->Play(false);

		player->starCount += 1;

		//自身を削除する。
		DeleteGO(this);
	}
}

void Star::Move()
{
	//moveCountが0の時。
	if (moveCount == 0)
	{
		//上に移動する。
		position.y += 1.0f;
	}
	//moveCountが1の時。
	else if (moveCount == 1)
	{
		//下に移動する。
		position.y -= 1.0f;
	}

	//y座標が初期座標y+100.0fを超えたら。
	if (position.y >= firstPosition.y + 100.0f)
	{
		//moveCountを1にする(下に移動するようにする)。
		moveCount = 1;
	}
	//y座標が初期座標-100.0fより下になったら。
	else if (position.y <= firstPosition.y - 100.0f)
	{
		//moveCountを0にする(上に移動するようにする)。
		moveCount = 0;
	}

	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
}

//回転処理。
void Star::Rotation()
{
	//回転を加算する。
	rotation.AddRotationDegY(2.0f);

	//絵描きさんに回転を教える。
	modelRender.SetRotation(rotation);
}

void Star::Render(RenderContext& rc)
{
	//☆を描画する。
	modelRender.Draw(rc);
}