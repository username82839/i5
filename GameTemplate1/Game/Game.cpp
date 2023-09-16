#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "Ster.h"
#include "GameCamera.h"
#include"GameClear.h"
#include"gameover.h"

//gametemplete1�̂ق��I�I

Game::Game()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/stage1.wav");

	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	//�w�i�̃I�u�W�F�N�g�����B
	m_backgroud = NewGO<BackGround>(0,"background");

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//Star�N���X�̃I�u�W�F�N�g�����B
	Star* star1 = NewGO<Star>(0, "star");
	star1->position = { -800.0f,3500.0f,-800.0f };
	star1->firstPosition = star1->position;
	//SoundSource�̃I�u�W�F�N�g���쐬����B

	m_bgm = NewGO<SoundSource>(0);
	//WaveFileBank����o�^���ꂽwave�t�@�C���̃f�[�^�i0�ԁj�������Ă���B
	m_bgm->Init(0);
	//true�ɂ���ƁA�������[�v����B
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
		fontrender.SetText(L"������@\nB�E�E�E�X�s�[�hup\nA�E�E�E�W�����v(3�i�܂Łj\nLB�E�E�E�X���[���[�V����\n�I������ɂ�f4+alt�L�[�������Ă��������B");
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