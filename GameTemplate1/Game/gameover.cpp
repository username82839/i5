#include "stdafx.h"
#include "gameover.h"
#include "Title.h"

gameover::gameover()
{
	spriteRender.Init("Assets/sprite/gameover.dds", 1920.0f, 1080.0f);
}

gameover::~gameover()
{

}

void gameover::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void gameover::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}