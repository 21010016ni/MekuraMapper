#include <DxLib.h>
#include "common.hpp"
#include "Input.hpp"
#include "Game.hpp"

#ifdef USE_RESOURCE
#include "resource.h"
#endif // USE_RESOURCE

HWND common::hwnd;
int common::width = 1024;
int common::height = 600;
int common::colorbit = 32;
int common::fps = 60;
bool common::windowmode = true;

int common::fc[8] = {0x3b7960,0x5a79ba,0x9370db,0xc0c0c0,0xbee0ce,0xfef263,0xf8b862,0xe95464};
int common::lc[2] = {0xc8c2be,0x302833};
int common::bc = 0x0b0b0b;

std::mt19937 common::engine(std::random_device{}());

#ifdef USE_RESOURCE
void MenuItemSelectCallBack(const TCHAR* ItemName, int ItemID)
{
	switch(ItemID)
	{
		// ここに項目
	}
}
#endif // USE_RESOURCE

#ifdef USE_CONSOLE
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
int main() { return WinMain(GetModuleHandle(0), NULL, NULL, _Notnull_ SW_SHOWDEFAULT); }
#endif // USE_CONSOLE

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// 初期化
	int count = 0;	// FPS調整用
	SetMainWindowText("Now Loading...");
	SetGraphMode(common::width, common::height, common::colorbit);
	// DxLib初期化ブロック
	//----------------------------------------------------------------<<
	// ウィンドウモードを設定
	ChangeWindowMode(common::windowmode);
#ifdef USE_RESOURCE
	// もしウィンドウモードなら
	if (common::windowmode)
	{
		// メニューのリソースを設定
		LoadMenuResource(IDR_MENU1);
		// メニューから呼び出すコールバック関数を設定
		SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
	}
#endif // USE_RESOURCE
	// 使用する文字コードをUTF-8に設定
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	// ファイルのドラッグ&ドロップを有効にする
	//SetDragFileValidFlag(TRUE);

	//---------------------------------------------------------------->>
	// 初期化
	if(DxLib_Init() == -1) return -1;
	common::hwnd = GetMainWindowHandle();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(false);
	// 初期化ブロック
	//----------------------------------------------------------------<<
	Game::preset();

	//---------------------------------------------------------------->>
	// タイトル表示
	SetMainWindowText((const char*)u8"\"Strings\"");
	// メインループ
	while(ProcessMessage() != -1)
	{
		// FPS
		count = GetNowCount();
		// キーボード入力状況更新
		Keyboard::update();
		Mouse::update();
		// 処理ブロック
		//----------------------------------------------------------------<<
		if (Game::update() == Game::Message::quit)
			break;

		//---------------------------------------------------------------->>
		// 描画ブロック
		//----------------------------------------------------------------<<
		Game::draw();

		//---------------------------------------------------------------->>
		// 画面表示
		ScreenFlip();
		// 画面消去
		ClearDrawScreen();
		WaitTimer(1000 / common::fps - GetNowCount() + count);
	}
	// 終了処理
	SetMainWindowText("Process Quitting...");
	DxLib_End();
	return 0;
}

