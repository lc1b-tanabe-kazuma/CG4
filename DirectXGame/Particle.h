#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Particle {
public:
	// 初期化
	void Initialize(Model* model);
	
	// 更新
	void Update();

	// 描画
	void Draw(const Camera& camera);
	bool IsDead() const { return isDead_; }
private:

	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// 色変更
	ObjectColor objectColor_;

	// 色の数値
	Vector4 color_;

	bool isDead_ = false;
};