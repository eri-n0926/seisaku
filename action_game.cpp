#include "DxLib.h"

const int SCREEN_WIDTH = 640;  //< スクリーン横の大きさ
const int SCREEN_HEIGHT = 480;  //< スクリーン縦の大きさ

#define SCREEN_HEIGHT (480)
#define SCREEN_WIDTH (640)
#define MAPCHIP_SIZE (32)
#define MAP_HEIGHT (480)
#define MAP_WIDTH (2560)
#define MAP_WINDOW_HEIGHT (15)
#define MAP_WINDOW_WIDTH  (80)

int PlayerX, PlayerY;
int JumpPower;
int PlayerGraph, haikei;
int JumpFlag;
int Jump;

int CameraX, CameraY;
int CameraMoveX;
int CharX;
int View_charX;

const int SIZE_MAP_X = 32;  //< マップチップXサイズ
const int SIZE_MAP_Y = 32; //< マップチップYサイズ
const int NUM_CHIP_X = 10;  //< 横10種類
const int NUM_CHIP_Y = 4;   //< 縦4種類
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y; //< 40個
int chip[NUM_CHIP_ALL];

int p_chip[8];

int xCount = 0;
int result;
int ix, iy;//添え字

const int NUM_MAP_X = 80; // 32x80=2560
const int NUM_MAP_Y = 15; // 32x15=480

char MapData[MAP_WINDOW_HEIGHT][MAP_WINDOW_WIDTH] = {

    // 横80x20
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,23,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,4, 4,4,4,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,21,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 4,4,4,4,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,10,10,10, 10,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,7,7,

    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,10,10,10, 10,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,4,4,4,4, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,11,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10,  0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,4,4,4,4, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,11,11,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,10,10,10, 10,0,0,10,10, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,11,11,11,11, 11,0,0,7,7,

    0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 11,11,11,11,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,11, 11,11,11,11,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,10,10, 0,0,10,10,10, 10,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,11,11, 11,11,11,11,11, 11,0,0,7,7,
    0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,10,10, 0,0,10,10,10, 10,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,11,11,11, 11,11,11,11,11, 11,0,0,7,7,
    1,1,1,1,1, 1,1,1,1,1, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,10,10, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,

};

int titleback;
int mojicolor;
int menuNum = 0;
int iKeyFlg;
int s = 0;



int GameState;

void DrawGame();


struct Menusentaku_t {
    int x;
    int y;
    char name[128];

}Menusentaku;

void title() {


    DrawBox(0, 0, 640, 480, titleback, 1);
    SetFontSize(60);
    DrawString(240, 80, "title", GetColor(255, 255, 255), 1);
    SetFontSize(20);

}

void DrawGame() {

    //----------------------------------------
//map描画
//----------------------------------------
    DrawGraph(0 - CameraX, 0, haikei, true);

    int i, j;
    for (i = 0; i < MAP_WINDOW_HEIGHT; i++) {
        for (j = 0; j < MAP_WINDOW_WIDTH; j++) {

            if (MapData[i][j] == 1)
            {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[1], FALSE);
            }
            else if (MapData[i][j] == 2) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[2], FALSE);
            }
            else if (MapData[i][j] == 3) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[3], FALSE);
            }
            else if (MapData[i][j] == 4) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[4], FALSE);
            }
            else if (MapData[i][j] == 5) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[5], FALSE);
            }
            else if (MapData[i][j] == 6) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[6], FALSE);
            }
            else if (MapData[i][j] == 7) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[7], FALSE);
            }
            else if (MapData[i][j] == 8) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[8], FALSE);
            }
            else if (MapData[i][j] == 9) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[9], FALSE);
            }
            else if (MapData[i][j] == 10) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[10], FALSE);
            }
            else if (MapData[i][j] == 11) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[11], FALSE);
            }
            else if (MapData[i][j] == 35) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[35], FALSE);
            }
            else if (MapData[i][j] == 36) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[36], FALSE);
            }
            else if (MapData[i][j] == 37) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[37], FALSE);
            }
            else if (MapData[i][j] == 38) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[38], FALSE);
            }
            else if (MapData[i][j] == 21) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[21], FALSE);
            }
            else if (MapData[i][j] == 23) {
                DrawGraph(j * MAPCHIP_SIZE - CameraX, i * MAPCHIP_SIZE, chip[23], FALSE);
            }
        }

    }

    
//----------------------------------------
//	// キャラ移動(左右）
	//----------------------------------------


		{

			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {//右移動
			PlayerX += 8;
				if (xCount < 0) {
					xCount = 0;
				}
				++xCount;
			}

			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {//左移動
			PlayerX -= 8;
				if (xCount > 0) { //xCountがマイナスなら左、プラスなら右
					xCount = 0;
				}
				--xCount;
				
			}


			if (PlayerX < 0) {
				PlayerX = 0;
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



            if (PlayerY > 400) { //地面に落ちたら地面に戻す
                PlayerY = 400;
                JumpPower = 0;
                JumpFlag = 0;
            }
        }



    }


    		//----------------------------------------
    		//
    		//----------------------------------------
    
    		ix = abs(xCount) %40 / 10;//％４０で３９までのあまりを取得、それを１０でわると、0～9は０，１０～１９は１というように増える
    
    		if (xCount > 0)//右向きなら。。
    		{
    			ix += 4;
    			result = ix;
    		}
    		else if (xCount < 0)//左向きなら。。
    		{
    			ix += 0;
    			result = ix;
    		}


    //----------------------------------------
    //カメラ
    //----------------------------------------

    CharX = PlayerX;
    CameraX = CharX - SCREEN_WIDTH / 2; //カメラの左上座標

    if (CameraX < 0) CameraX = 0;//左上座標を無理やり０にしてうｒ
    if (CameraX > (MAP_WIDTH - SCREEN_WIDTH)) CameraX = MAP_WIDTH - SCREEN_WIDTH; //スクリーンを超えてしまったら６４０にもどす


    View_charX = CharX - CameraX;//この座標に描画


    //※６４０を超えるとキャラが止まったような挙動を起こすのは仕様




    //----------------------------------------
    //キャラの描画
    //----------------------------------------
    DrawGraph(View_charX, PlayerY, p_chip[result], TRUE);

}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    SetMainWindowText("DanmakuShooting");   // タイトルを設定
    ChangeWindowMode(TRUE);             // ウィンドウモード変更
    DxLib_Init();                       // DXライブラリ初期化
    SetDrawScreen(DX_SCREEN_BACK);      // 裏画面設定

    LoadDivGraph("images/mapchip.png", NUM_CHIP_ALL,
        NUM_CHIP_X, NUM_CHIP_Y,
        SIZE_MAP_X, SIZE_MAP_Y,
        chip);

    LoadDivGraph("images/Player1.png", 8, 4, 2, 57, 54, p_chip);

   
    haikei = LoadGraph("images/haikei1.jpg");//仮

    PlayerX = 71, PlayerY = 400;//初期位置
    JumpPower = 0; //ジャンプの強さ


    JumpFlag = FALSE;

    Menusentaku_t Menusentaku[2]{   //menu moji
      {320,300,"Start"},
      {320,330,"Exit"},
    };

    DrawBox(0, 0, 640, 480, titleback, 1);//title 背景

    titleback = GetColor(0, 0, 0);//titlecolor
    mojicolor = GetColor(254, 254, 254);//mojicolor

    while (ProcessMessage() == 0) {    // メッセージ処理


        ClearDrawScreen(); // 画面消去

        //DrawGraph(0 - CameraX, 0, haikei, true);

        switch (GameState) {
        case 0:
        {//メニュー画面
            title();
            DrawCircle(Menusentaku[s].x - 20, Menusentaku[s].y + 5, 5, mojicolor, TRUE);
            for (int i = 0; i < 2; i++) {
                DrawFormatString(Menusentaku[i].x, Menusentaku[i].y, GetColor(255, 255, 255), Menusentaku[i].name);
            }
            break;
        }
        case 1:
        { //ゲーム画面
            DrawGame();
            break;
        }
        case 2:
        {//ゴール画面

        }
        }

        if (CheckHitKey(KEY_INPUT_DOWN) != 0) {
            menuNum = 1;
            s = 1;
        }
        if (CheckHitKey(KEY_INPUT_UP) != 0) {
            menuNum = 0;
            s = 0;
        }

        if (CheckHitKey(KEY_INPUT_Z) != 0) {
            if (menuNum == 0) {
                GameState = 1;
            }
            else if (menuNum = 1) {
                break;
            }
        }

        ScreenFlip();     // 画面更新
    }
    DxLib_End(); // DXライブラリ終了処理
    return 0;
}