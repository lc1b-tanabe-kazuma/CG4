#pragma once
#include "KamataEngine.h"

class Stage {
public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Sprite* spriteBG_ = nullptr;
	uint32_t textureHandleBG_ = 0;
	KamataEngine::Vector2 posBG_ = {0, 0};
	KamataEngine::Vector2 scrollSpeed_ = {1.0f, 0.0f};
	KamataEngine::Sprite* spriteBG2_ = nullptr;
};