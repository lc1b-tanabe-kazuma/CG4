#include "GameScene.h"
#include "MyMath.h"
#include <imgui.h>
#include <numbers>
#include <random>

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

	// 星生成
	SpawnStarEffect();
}

void GameScene::Update() {

	// エフェクトの削除
	for (auto it = effects_.begin(); it != effects_.end();) {

		if ((*it)->IsDead()) {

			delete *it;

			it = effects_.erase(it);
		} else {

			++it;
		}
	}

	// エフェクトの更新
	for (uint32_t i = 0; i < effects_.size(); i++) {
		effects_[i]->Update();
	}

	// エフェクトが全て死んでいたら新たに生成
	if (effects_.empty()) {
		SpawnStarEffect();
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
	for (uint32_t i = 0; i < effects_.size(); i++) {
		effects_[i]->Draw();
	}

	// 3Dオブジェクト後処理
	Model2::PostDraw();
}

void GameScene::SpawnStarEffect() {

	static std::mt19937 engine(std::random_device{}());

	std::uniform_real_distribution<float> posX(-20.0f, 20.0f);
	std::uniform_real_distribution<float> posY(0.0f, 10.0f);
	std::uniform_real_distribution<float> posZ(-20.0f, 20.0f);

	// 星全体のランダム位置
	Vector3 starPosition = {posX(engine), posY(engine), posZ(engine)};

	const float kPi = std::numbers::pi_v<float>;

	std::uniform_real_distribution<float> randomColor(0.3f, 1.0f);

	Vector4 starColor = {randomColor(engine), randomColor(engine), randomColor(engine), 1.0f};

	for (uint32_t i = 0; i < kCount; i++) {

		Effect* effect = new Effect();

		effect->Initialize(&camera_, starColor);

		// 放射状回転
		effect->AddRotationZ((2.0f * kPi / kCount) * i);

		// 最後に位置設定
		effect->SetPosition(starPosition);

		effects_.push_back(effect);
	}
}

GameScene::~GameScene() {
	delete model2_;
	Model2::StaticFinalize();
	for (uint32_t i = 0; i < effects_.size(); i++) {
		delete effects_[i];
	}
}