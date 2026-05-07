#include "GameScene.h"
#include "MyMath.h"

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

	model2_ = Model2::CreateSquare(5);
}

void GameScene::Update() { WorldTransformUpdate(worldTransform_); }

void GameScene::Draw() {
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 3Dオブジェクト描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());

	model2_->Draw(worldTransform_, camera_, textureHandle_);

	// 3Dオブジェクト後処理
	Model2::PostDraw();
}

GameScene::~GameScene() {
	delete model2_;
	Model2::StaticFinalize();
}
