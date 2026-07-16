#include "Stage.h"
using namespace KamataEngine;

void Stage::Initialize() {
	textureHandleBG_ = KamataEngine::TextureManager::Load("stage.png");
	spriteBG_ = KamataEngine::Sprite::Create(textureHandleBG_, posBG_);
	spriteBG2_ = KamataEngine::Sprite::Create(textureHandleBG_, Vector2(posBG_.x + 1280.0f, posBG_.y));
	spriteBG_->SetSize({1280.0f, 720.0f});
	spriteBG2_->SetSize({1280.0f, 720.0f});
}

void Stage::Update() {
	// 背景をスクロールさせる
	posBG_.x -= 1.0f;
	if (posBG_.x <= -1280.0f) {
		posBG_.x = 0.0f;
	}
	spriteBG_->SetPosition(posBG_);
	spriteBG2_->SetPosition(Vector2(posBG_.x + 1280.0f, posBG_.y));
}

void Stage::Draw() {
	// ステージの描画
	spriteBG_->Draw();
	spriteBG2_->Draw();
}