#include "GameScene.h"
#include "MyMath.h"
#include "SceneManager.h"
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

	// プレイヤーの初期化
	player_ = new Player();
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	modelBullet_ = Model::CreateFromOBJ("playerBullet", true);
	player_->Initialize(modelPlayer_, &camera_, modelBullet_);

	// 敵の初期化
	modelEnemy_ = Model::CreateFromOBJ("enemy", true);

	// エイムの初期化
	aim_ = new Aim();
	aim_->Initialize(&camera_);

	// 乱数の初期化
	srand((unsigned int)time(nullptr));

	// ステージの初期化
	stage_ = new Stage();
	stage_->Initialize();

	// UIの初期化
	HPTH_ = TextureManager::Load("white1x1.png");
	spriteHP_ = Sprite::Create(HPTH_, posHP_);
	spriteHP2_ = Sprite::Create(HPTH_, posHP_);
	spriteHP_->SetSize(sizeHP_);
	spriteHP2_->SetSize(sizeHP_);
	spriteHP_->SetColor({1.0f, 0.0f, 0.0f, 0.5f});  // 赤色で半透明
	spriteHP2_->SetColor({0.0f, 1.0f, 0.0f, 0.5f}); // 緑色で半透明

	// 数字描画の初期化
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(TextureManager::Load("number.png"));
}

void GameScene::Update() {

	if (isGameClear_) {
		return;
	}

	// 敵の消去
	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});

	// タイマーの更新
	timer_ += 1.0f / 60.0f;

	if (timer_ >= 2.0f) {
		isSpawnEnemy_ = true;
	}

	if (isSpawnEnemy_) {
		for (int i = 0; i < 3; i++) {
			SpawnEnemy();
		}
		isSpawnEnemy_ = false;
		timer_ = 0.0f;
	}

	// ステージの更新
	stage_->Update();

	// エイムの更新
	aim_->Updeta();

	if (aim_->IsAttac()) {
		Vector3 worldPos = GetMouseWorldPosition();

		player_->Attack({worldPos.x, worldPos.y});
	}

	// プレイヤーの更新
	player_->Update();

	// 敵の更新
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	// 衝突判定
	OnCollision();

	// UIの更新
	UpdateUI();

	// 数字描画の更新
	drawNumber_->Update(static_cast<int>(score_));
}

void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ステージの描画
	stage_->Draw();

	// UIの描画
	spriteHP_->Draw();
	spriteHP2_->Draw();

	// 数字描画
	drawNumber_->Draw();

	aim_->Draw();

	// 画像描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	// プレイヤーの描画
	player_->Draw();

	// 敵の描画
	for (Enemy* enemy : enemies_) {
		enemy->Draw(camera_);
	}

	// 3Dオブジェクト後処理
	Model::PostDraw();
}

void GameScene::UpdateUI() {

	// 徐々にHPが減るように
	static float hp = 1.0f;                                  // HPの割合（0.0f～1.0f）
	hp -= 0.0005f;                                            // HPを減らす
	spriteHP2_->SetSize(Vector2(sizeHP_.x * hp, sizeHP_.y)); // HPバーのサイズを更新
	if (hp <= 0.0f) {
		
		// ゲームをクリアしたらシーンを"GameClear"に変更
		SceneManager::GetInstance()->ChangeScene("GameClear");

		hp = 1.0f; // HPが0になったらリセット

		isGameClear_ = true;
	}
}

KamataEngine::Vector3 GameScene::GetMouseWorldPosition() {
	Ray ray = aim_->GetRayFromMouse();

	// z = 0 の平面との交点
	float t = -ray.origin.z / ray.direction.z;

	return {ray.origin.x + ray.direction.x * t, ray.origin.y + ray.direction.y * t, 0.0f};
}

void GameScene::SpawnEnemy() {
	Enemy* newEnemies = new Enemy();
	Vector3 spawnPos = {distribution(randomEngine) * 10.0f + 20.0f, distribution(randomEngine) * 30.0f, 0.0f};
	newEnemies->Initialize(modelEnemy_, spawnPos);
	enemies_.push_back(newEnemies);
}

void GameScene::OnCollision() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自機の弾リスト取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

#pragma region プレイヤーの弾と敵の当たり判定
	// ボスの座標を取得
	for (Enemy* enemy : enemies_) {
		posA = enemy->GetPosition();

		// プレイヤーの弾の座標を取得
		for (PlayerBullet* bullet : playerBullets) {
			posB = bullet->GetPosition();
			if (IsCollision(posA, enemy->GetRadius(), posB, bullet->GetRadius())) {

				// ---- 通常弾 ----
				bullet->Oncollosion();
				enemy->OnCollision();

				score_ += 100;
			}
		}
	}
#pragma endregion
}

GameScene::~GameScene() {

	// ステージの解放
	if (stage_) {
		delete stage_;
	}

	delete player_;

	delete modelPlayer_;

	delete aim_;

	delete drawNumber_;

	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}