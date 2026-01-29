#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;
#include "scene/GameScene.h"
#include "scene/TitleScene.h"

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,

};

Scene scene = Scene::kTitle;

void ChangeScene() {

	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
		case Scene::kGame:
		    if (gameScene->IsFinished()) {

		        scene = Scene::kTitle;
		        delete gameScene;
		        gameScene = nullptr;
		        titleScene = new TitleScene;
		        titleScene->Initialize();
		    }
		    break;
		}
	}

	void UpdateScene() {

		switch (scene) {
		case Scene::kTitle:
			titleScene->Update();

			break;

		case Scene::kGame:
			gameScene->Update();
			break;
		}
	}

	void DrawScene() {

		switch (scene) {
		case Scene::kTitle:
			titleScene->Draw();

			break;

		case Scene::kGame:
			gameScene->Draw();
			break;
		}
	}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_11_ハギワラ_ケンタ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームシーンのインスタンス生成
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();

	// メインループ
	while (true) {

		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}
		// ゲームシーンの更新
		gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScene->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	KamataEngine::Finalize();

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	return 0;
}
