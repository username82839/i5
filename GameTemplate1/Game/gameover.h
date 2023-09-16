#pragma once
class gameover:public IGameObject
{
public:
	gameover();
	~gameover();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender spriteRender;
};

