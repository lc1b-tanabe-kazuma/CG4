#pragma once
#include "Effect.h"
#include "KamataEngine.h"
#include "Model2/Model2.h"

// ゲームシーン
class GameScene {

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();
	~GameScene();

	void SpawnStarEffect(int starCount);

private:
	// テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	// カメラ
	KamataEngine::Camera camera_;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model2* model2_ = nullptr;

	// 複数のエフェクト
	struct StarEffect {

		std::vector<Effect*> effects;

		KamataEngine::Vector3 position; // 星の中心位置

		float timer = 0.0f;

		float lifeTime = 3.0f;

		float spawnDelay = 0.0f;

		bool active = true;
	};

	std::vector<StarEffect> effects_;

	const uint32_t kCount = 10;
};
