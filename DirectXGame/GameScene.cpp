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

	// 乱数の初期化
	srand((unsigned int)time(nullptr));
}

void GameScene::Update() {

	// パーティクルの削除
	particles_.remove_if([](Particle* particle) {
		if (particle->IsDead()) {
			delete particle;
			return true;
		}
		return false;
	});

	// 確率でパーティクル発生
	if (rand() % 20 == 0) {

		// 発生位置は乱数で
		Vector3 pos = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0.0f};

		// パーティクルの発生
		SpawnParticle(pos);
	}

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

void GameScene::SpawnParticle(Vector3 pos) {

	// パーティクルの初期化
	for (int i = 0; i < 150; i++) {

		// 生成
		Particle* particle = new Particle();

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