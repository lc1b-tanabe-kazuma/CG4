#include "Stage.h"
using namespace KamataEngine;

Stage::~Stage() {
	delete spriteBG_;
	delete spriteBG2_;
}

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
	// コマンドリストの取得
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 画像描画前処理
	Sprite::PreDraw(commandList);

	// ステージの描画
	spriteBG_->Draw();
	spriteBG2_->Draw();

	// 画像描画後処理
	Sprite::PostDraw();
}