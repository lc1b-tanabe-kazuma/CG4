#pragma once
#include "KamataEngine.h"

class Player {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);
	void Update();
	void Draw();

	void Move();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition() const;
private:
	KamataEngine::Model* model_;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;

	// キーボード入力
	KamataEngine::Input* input_ = nullptr;

	float moveSpeed_ = 0.1f;
};