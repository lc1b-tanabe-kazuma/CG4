#include "GameScene.h"
#include "MyMath.h"
#include <imgui.h>

using namespace KamataEngine;

void GameScene::Initialize() {
	// テクスチャーインスタンスの作成
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// モデルの初期化
	Model2::StaticInitialize();

	// カメラの初期化
	camera_.Initialize();

	//
	worldTransform_.Initialize();

	// モデルの生成
	model2_ = Model2::CreateRing(8, 5.0f, 10.0f);

	// エフェクトの初期化
	effect_ = new Effect();
	effect_->Initialize(&camera_);
}

void GameScene::Update() {

	effect_->Update();

	// ワールドトランスフォームの更新
	// WorldTransformUpdate(worldTransform_);

	// Imguiの表示
#ifdef _DEBUG
	/*ImGui::Begin("model");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::End();*/
#endif
}

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dオブジェクト描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	// モデルの描画
	//	model2_->Draw(worldTransform_, camera_, textureHandle_);
	effect_->Draw();

	// 3Dオブジェクト後処理
	Model2::PostDraw();
}

GameScene::~GameScene() {
	delete model2_;
	Model2::StaticFinalize();
	delete effect_;
}
