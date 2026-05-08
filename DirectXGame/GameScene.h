#pragma once
#include "KamataEngine.h"
#include "Model2/Model2.h"
#include "Effect.h"

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

private:
	// テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	// カメラ
	KamataEngine::Camera camera_;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model2* model2_ = nullptr;

	// エフェクト
	Effect* effect_ = nullptr;
};
