#pragma once
#include "KamataEngine.h"

class Enemy {
public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Vector3 position);
	void Update();
	void Draw(const KamataEngine::Camera& camera);

	// 敵の位置を取得
	KamataEngine::Vector3 GetPosition() const;

	// 敵の半径を取得
	const float& GetRadius() const { return kRadius; }

	// 敵が死んでいるかどうかを取得
	bool IsDead() const { return isDead_; }

	// 敵が弾に当たったときの処理
	void OnCollision();
private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// 半径
	const float kRadius = 1.25f;
	// デスフラグ
	bool isDead_ = false;
};