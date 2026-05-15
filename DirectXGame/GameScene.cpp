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
	SpawnStarEffect(50);
}

void GameScene::Update() {

	for (auto starIt = effects_.begin(); starIt != effects_.end();) {

		// 棒更新
		for (auto effectIt = starIt->effects.begin(); effectIt != starIt->effects.end();) {

			// 棒の更新
			(*effectIt)->Update();

			// 棒死亡
			if ((*effectIt)->IsDead()) {

				delete *effectIt;

				// 死亡した棒をリストから削除
				effectIt = starIt->effects.erase(effectIt);
			} else {

				// 棒が生きている場合は次の棒へ
				++effectIt;
			}
		}

		// 星の棒が全部消えた
		if (starIt->effects.empty()) {

			// 星をリストから削除
			starIt = effects_.erase(starIt);

			// 新しい星を生成
			SpawnStarEffect(1);
		} else {

			// 星がまだ生きている場合は次の星へ
			++starIt;
		}
	}
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dオブジェクト描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	// モデルの描画
	for (uint32_t i = 0; i < effects_.size(); i++) {
		for (uint32_t j = 0; j < effects_[i].effects.size(); j++) {
			effects_[i].effects[j]->Draw();
		}
	}

	// 3Dオブジェクト後処理
	Model2::PostDraw();
}

void GameScene::SpawnStarEffect(int starCount) {

	// 乱数エンジン
	static std::mt19937 engine(std::random_device{}());

	// 位置の乱数範囲
	std::uniform_real_distribution<float> posX(-20.0f, 20.0f);
	std::uniform_real_distribution<float> posY(-10.0f, 10.0f);
	std::uniform_real_distribution<float> posZ(-20.0f, 20.0f);
	std::uniform_real_distribution<float> randomColor(0.5f, 1.0f);
	std::uniform_real_distribution<float> randomLife(1.0f, 5.0f);
	std::uniform_real_distribution<float> delayDist(0.0f, 2.0f);

	const float kPi = std::numbers::pi_v<float>;

	for (int s = 0; s < starCount; s++) {

		// 星エフェクトの初期化
		StarEffect star;
		Vector3 starPosition = {posX(engine), posY(engine), posZ(engine)};
		Vector4 starColor = {randomColor(engine), randomColor(engine), randomColor(engine), 1.0f};
		
		star.lifeTime = randomLife(engine);

		star.spawnDelay = delayDist(engine);

		// 位置と寿命をランダムに設定
		for (uint32_t i = 0; i < kCount; i++) {

			Effect* effect = new Effect();
			effect->Initialize(&camera_, starColor);

			effect->AddRotationZ((2.0f * kPi / kCount) * i);
			effect->SetPosition(starPosition);

			star.effects.push_back(effect);
		}

		effects_.push_back(star);
	}
}

GameScene::~GameScene() {

	delete model2_;
	model2_ = nullptr;

	Model2::StaticFinalize();

	for (auto& star : effects_) {

		for (Effect* e : star.effects) {
			delete e;
		}

		star.effects.clear();
	}

	effects_.clear();
}