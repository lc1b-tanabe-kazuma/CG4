#pragma once
#include "UI/Aim.h"
#include "UI/DrawNumber.h"
#include "Enemy/Enemy.h"
#include "KamataEngine.h"
#include "Player/Player.h"
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

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	GameScene(KamataEngine::Input* input) : SceneBase(input) {}

	void UpdateBG();

	void UpdateUI();

	KamataEngine::Vector3 GetMouseWorldPosition();

	// 敵の発生
	void SpawnEnemy();

	// 衝突判定
	void OnCollision();

private:
	// テクスチャーハンドル
	uint32_t textureHandle_ = 0;

	// カメラ
	KamataEngine::Camera camera_;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* modelParticle_ = nullptr;

	// ステージ
	Stage* stage_;

	// UI
	KamataEngine::Sprite* spriteHP_ = nullptr;

	// 敵
	std::list<Enemy*> enemies_;
	KamataEngine::Model* modelEnemy_ = nullptr;
	bool isSpawnEnemy_ = false;

	KamataEngine::Sprite* spriteHP2_ = nullptr;
	uint32_t HPTH_ = 0;
	KamataEngine::Vector2 posHP_ = {50, 50};
	KamataEngine::Vector2 sizeHP_ = {100.0f, 20.0f};

	// プレイヤー
	Player* player_ = nullptr;
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 数字描画
	DrawNumber* drawNumber_;
	uint32_t numberTH_ = 0;

	// タイマー
	float timer_ = 0.0f;

	// エイム
	Aim* aim_ = nullptr;

	KamataEngine::Model* modelBullet_ = nullptr;

	// 
	int score_ = 0;

	bool isGameClear_ = false;
};