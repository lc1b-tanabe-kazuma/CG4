#pragma once
#include "KamataEngine.h"
#include "SceneBase.h"

class Title : public SceneBase {
public:
	Title(KamataEngine::Input* input) : SceneBase(input) {}

	// 初期化
	void Initialize() override;

	// 更新
	void Update() override;

	void Finalize() override;

	// 描画
	void Draw() override;

	~Title() override;

private:
	
};