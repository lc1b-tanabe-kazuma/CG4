#include "GameScene.h"
#include <imgui.h>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device rd;
std::mt19937 randomEngine(rd());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

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
		Vector3 pos = {0.0f, 0.0f, 0.0f};

		// 速度
		Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0.0f};
		Normalize(velocity);
		velocity *= distribution(randomEngine);
		velocity *= 0.1f;

		// 初期化
		particle->Initialize(modelParticle_, pos, velocity);

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