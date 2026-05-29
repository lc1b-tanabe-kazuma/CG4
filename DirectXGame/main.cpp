#include "GameScene.h"
#include "KamataEngine.h"
#include "SceneManager.h"
#include <Windows.h>
#include <imgui.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"CG4_LE3D_16タナベ_カズマ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// scnenマネージャーの作成
	SceneManager::GetInstance()->Initialize();

#ifdef _DEBUG
	// ImguiManagerのインスタンスを取得
	ImGuiManager* imguiManager_ = ImGuiManager::GetInstance();
#endif

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

#ifdef _DEBUG
		// Imgui受付開始
		imguiManager_->Begin();
#endif

		// シーンマネージャーの更新
		SceneManager::GetInstance()->Update();

#ifdef _DEBUG
		// Imgui受付終了
		imguiManager_->End();
#endif

		// 描画開始
		dxCommon->PreDraw();

		// シーンマネージャーの描画
		SceneManager::GetInstance()->Draw();

#ifdef _DEBUG
		// Imguiの描画
		imguiManager_->Draw();
#endif

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	SceneManager::GetInstance()->Finalize();

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
