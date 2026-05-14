#include "GameScene.h"
#include "MyMath.h"
#include <imgui.h>
#include <numbers>

using namespace KamataEngine;

void GameScene::Initialize() {
	// テクスチャーインスタンスの作成
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// モデルの初期化
	Model2::StaticInitialize();

	// カメラの初期化
	camera_.Initialize();

	//
	worldTransform_.Initialize();

	// モデルの生成
	model2_ = Model2::CreateRing(8, 5.0f, 10.0f);

	// エフェクトの初期化
	const float kPi = std::numbers::pi_v<float>;

	for (uint32_t i = 0; i < kCount; i++) {

		Effect* effect = new Effect();

		effect->Initialize(&camera_);

		effect->AddRotationZ((2.0f * kPi / kCount) * i);

		effects_.push_back(effect);
	}
}

void GameScene::Update() {

	for (uint32_t i = 0; i < kCount; i++) {
		effects_[i]->Update();
	}

	// Imguiの表示
#ifdef _DEBUG
	
#endif
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dオブジェクト描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	// モデルの描画
	for (uint32_t i = 0; i < kCount; i++) {
		effects_[i]->Draw();
	}

	// 3Dオブジェクト後処理
	Model2::PostDraw();
}

GameScene::~GameScene() {
	delete model2_;
	Model2::StaticFinalize();
	for (uint32_t i = 0; i < kCount; i++) {
		delete effects_[i];
	}
}
