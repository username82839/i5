#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "Ster.h"
#include "GameCamera.h"
#include"GameClear.h"
#include"gameover.h"

//gametemplete1のほう！！

Game::Game()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/stage1.wav");

	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	//背景のオブジェクトを作る。
	m_backgroud = NewGO<BackGround>(0,"background");

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//Starクラスのオブジェクトを作る。
	Star* star1 = NewGO<Star>(0, "star");
	star1->position = { -800.0f,3500.0f,-800.0f };
	star1->firstPosition = star1->position;
	//SoundSourceのオブジェクトを作成する。

	m_bgm = NewGO<SoundSource>(0);
	//WaveFileBankから登録されたwaveファイルのデータ（0番）を持ってくる。
	m_bgm->Init(0);
	//trueにすると、音がループする。
	m_bgm->Play(true);
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(gameCamera);
	DeleteGO(m_backgroud);
	DeleteGO(m_bgm);
}


bool Game::Start()
{	
	
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
	g_renderingEngine->SetCascadeNearAreaRates(0.01f, 0.1f, 0.5f);

	return true;
	
}

void Game::Update()
{
	
	if (player->m_position.y <= -100.0)
	{
		NewGO<gameover>(0, "Gameovar");
		DeleteGO(this);
		
	}
	if (player->m_position.y >= 0.0)
	{
		fontrender.SetText(L"操作方法\nB・・・スピードup\nA・・・ジャンプ(3段まで）\nLB・・・スローモーション\n終了するにはf4+altキーを押してください。");
		fontrender.SetPosition({ -950.0f,-300.0f,0.0f });
		fontrender.SetColor(g_vec4Black);

	}
	if (player->starCount == 1)
	{
		NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}
}


void Game::Render(RenderContext& rc)
{
	fontrender.Draw(rc);
}