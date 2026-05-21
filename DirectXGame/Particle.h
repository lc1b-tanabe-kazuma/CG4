#pragma once
#include <KamataEngine.h>

class Particle {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 pos, KamataEngine::Vector3 velocity);

	// 更新
	void Update();

	// 描画
	void Draw(const KamataEngine::Camera& camera);
	bool IsDead() const;

private:
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 色変更
	KamataEngine::ObjectColor objectColor_;

	// 色の数値
	KamataEngine::Vector4 color_;

	// 速度
	KamataEngine::Vector3 velocity_;

	// 死亡フラグ
	bool isDead_ = false;

	// 経過時間
	float counter_ = 0.0f;

	// 持続時間
	float lifeTime_ = 1.0f;
};