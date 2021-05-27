
#include "DxLib.h"
#define SCREEN_HEIGHT (480)
#define SCREEN_WIDTH (640)
#define MAPCHIP_SIZE (30)
#define MAP_HEIGHT (960)
#define MAP_WIDTH	(1280)
#define MAP_WINDOW_HEIGHT (MAP_HEIGHT/MAPCHIP_SIZE)
#define MAP_WINDOW_WIDTH  (MAP_WIDTH/MAPCHIP_SIZE)

int PlayerX, PlayerY;
int JumpPower;
int PlayerGraph;
int JumpFlag;
int Jump;

int g_CameraPosX =0;
int g_CameraPosY =0;

int CameraX, CameraY;
int CameraMoveX;
int CharX;

char MapData[MAP_WINDOW_HEIGHT][MAP_WINDOW_WIDTH] = {
		1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 1,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 1,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

		
};


 //WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)

{

	
	ChangeWindowMode(TRUE); // ウインドウモードに変更
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	/* 描画先画面を裏画面にセット*/

	PlayerGraph = LoadGraph("Player.png");

	PlayerX = -70,PlayerY = 300;//初期位置
	JumpPower = 0; //ジャンプの強さ


	JumpFlag = FALSE;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//これがないと動かない

	//----------------------------------------
	// キャラ移動(左右）
	//----------------------------------------

		DrawBox(1000 - g_CameraPosX, 90, 500 - g_CameraPosX, 800, GetColor(255, 255, 255), TRUE);


		{

			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {//右移動
				PlayerX += 10;

			}

			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {//左移動
				PlayerX -= 10;
			}


			if (PlayerX < -70) {
				PlayerX = -70;
			}
		}

		//----------------------------------------
		//キャラのジャンプ処理
		//----------------------------------------

		{

			if (JumpFlag == FALSE && CheckHitKey(KEY_INPUT_UP) == 1) { //ジャンプを押されたら

				//フラグを１にしてジャンプの強さを-15にする
				JumpPower -= 25;
				JumpFlag = 1;
			}

			if (JumpFlag == TRUE) {
				PlayerY += JumpPower;//上がる速さ　今いる場所から-15引く
				JumpPower += 1; //落ちる速さ　１ずつ引いていく



				if (PlayerY > 300) { //地面に落ちたら地面に戻す
					PlayerY = 300;
					JumpPower = 0;
					JumpFlag = 0;
				}
			}



		}


		//----------------------------------------
		//カメラ
		//----------------------------------------


			//

		if (PlayerX - g_CameraPosX > 230) {
			g_CameraPosX = PlayerX - 230;


		}

		else if (PlayerX - g_CameraPosX < 10) {
			g_CameraPosX = PlayerX - 10;
		}


		if (g_CameraPosX < -70) {
			g_CameraPosX = -70;
		}


		//----------------------------------------
		//map描画
		//----------------------------------------


		int i, j;
		/*for (i = 0; i <MAP_WINDOW_HEIGHT; i++) {
			for (j = 0; j<MAP_WINDOW_WIDTH; j++) {
				if (MapData[i][j] == 1)
				{
					DrawBox(j * MAPCHIP_SIZE- g_CameraPosX, i * MAPCHIP_SIZE,
						j * MAPCHIP_SIZE + MAPCHIP_SIZE - g_CameraPosX, i * MAPCHIP_SIZE + MAPCHIP_SIZE,
						GetColor(255, 255, 255), TRUE);
				}
			}
		}*/

	
	//----------------------------------------
	//キャラの描画
	//----------------------------------------

	DrawGraph(PlayerX-g_CameraPosX, PlayerY-g_CameraPosY, PlayerGraph, TRUE);

	

			 /*裏画面の内容を表画面に反映させる*/
		ScreenFlip();

		/* windows 特有の面倒な処理をＤＸライブラリにやらせる -1 が返ってきたらループを抜ける*/
		if (ProcessMessage() < 0) break;

		
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}


DxLib_End();				//

return 0;					// ソフトの終了
		}







