#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Particle {
public:
	// 初期化
	void Initialize(Model* model,Vector3 pos,Vector3 velocity);
	
	// 更新
	void Update();

	// 描画
	void Draw(const Camera& camera);
	bool IsDead() const;

private:

	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// 色変更
	ObjectColor objectColor_;

	// 色の数値
	Vector4 color_;

	// 速度
	Vector3 velocity_;

	bool isDead_ = false;
};