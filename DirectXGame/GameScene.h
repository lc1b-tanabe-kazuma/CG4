#pragma once
#include "KamataEngine.h"
#include "Particle.h"
#include "SceneBase.h"
#include "Stage.h"
#include <cassert>
#include <sstream>

// ゲームシーン
class GameScene : public SceneBase {
public:
	~GameScene() override;

	// 初期化
	void Initialize() override;

	void Finalize() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// パーティクルの発生
	void SpawnParticle(KamataEngine::Vector3 pos);

	GameScene(KamataEngine::Input* input) : SceneBase(input) {}

	void UpdateBG();

private:
	// テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	// カメラ
	KamataEngine::Camera camera_;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* modelParticle_ = nullptr;

	// パーティクル
	std::list<Particle*> particles_;

	// ステージ
	Stage* stage_;
};
