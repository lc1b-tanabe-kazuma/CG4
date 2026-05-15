#pragma once
#include "KamataEngine.h"
#include "Model2/Model2.h"

class Effect {
public:
	// 初期化
	void Initialize(KamataEngine::Camera* camera, const KamataEngine::Vector4& color);

	// 更新
	void Update();

	// 描画
	void Draw();

	// 座標設定
	void SetPosition(const KamataEngine::Vector3& position);

	void AddRotationZ(float angle);

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model2* model_ = nullptr;

	// 色
	KamataEngine::ObjectColor color_;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	float alpha_ = 1.0f;

	float lifeTimer_ = 0.0f;

	float lifeTime_ = 1.0f;

	bool isDead_ = false;
};