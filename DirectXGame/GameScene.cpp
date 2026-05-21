#include "GameScene.h"
#include "MyMath.h"
#include <imgui.h>
#include <numbers>
#include <random>

using namespace KamataEngine;

void GameScene::Initialize() {
	// テクスチャーインスタンスの作成
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// カメラの初期化
	camera_.Initialize();

	modelParticle_->StaticInitialize();
	modelParticle_ = Model::CreateSphere(4, 4);

	//
	worldTransform_.Initialize();

	// パーティクルの初期化
	particel_ = new Particle();
	particel_->Initialize(modelParticle_);
}

void GameScene::Update() { 
	
	// パーティクルの更新
	particel_->Update();
}

void GameScene::Draw() {

	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	// パーティクルの描画
	particel_->Draw(camera_);

	// 3Dオブジェクト後処理
	Model::PostDraw();
}

GameScene::~GameScene() { delete modelParticle_; }