
#pragma once

class Game {
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

extern Game* g_game;
