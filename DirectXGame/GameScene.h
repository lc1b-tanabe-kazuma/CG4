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

	void SpawnStarEffect();

private:
	// テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	// カメラ
	KamataEngine::Camera camera_;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model2* model2_ = nullptr;

	// 複数のエフェクト
	std::vector<Effect*> effects_;
	const uint32_t kCount = 8;
};
