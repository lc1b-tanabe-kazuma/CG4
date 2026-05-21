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
	for (int i = 0; i < 150; i++) {

		// 生成
		Particle* particle = new Particle();

		// 位置
		Vector3 pos = {0.5f * i, 0.0f, 0.0f};

		// 初期化
		particle->Initialize(modelParticle_, pos);

		// リストに追加
		particles_.push_back(particle);
	}
}

void GameScene::Update() {

	// パーティクルの更新
	for (Particle* particle : particles_) {
		particle->Update();
	}
}

void GameScene::Draw() {

	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	// パーティクルの描画
	for (Particle* particle : particles_) {
		particle->Draw(camera_);
	}

	// 3Dオブジェクト後処理
	Model::PostDraw();
}

GameScene::~GameScene() {
	delete modelParticle_;

	// パーティクルの解放
	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
}