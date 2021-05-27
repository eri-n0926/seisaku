
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


 //WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)

{

	
	ChangeWindowMode(TRUE); // �E�C���h�E���[�h�ɕύX
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	/* �`����ʂ𗠉�ʂɃZ�b�g*/

	PlayerGraph = LoadGraph("Player.png");

	PlayerX = -70,PlayerY = 300;//�����ʒu
	JumpPower = 0; //�W�����v�̋���


	JumpFlag = FALSE;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//���ꂪ�Ȃ��Ɠ����Ȃ�

	//----------------------------------------
	// �L�����ړ�(���E�j
	//----------------------------------------

		DrawBox(1000 - g_CameraPosX, 90, 500 - g_CameraPosX, 800, GetColor(255, 255, 255), TRUE);


		{

			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {//�E�ړ�
				PlayerX += 10;

			}

			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {//���ړ�
				PlayerX -= 10;
			}


			if (PlayerX < -70) {
				PlayerX = -70;
			}
		}

		//----------------------------------------
		//�L�����̃W�����v����
		//----------------------------------------

		{

			if (JumpFlag == FALSE && CheckHitKey(KEY_INPUT_UP) == 1) { //�W�����v�������ꂽ��

				//�t���O���P�ɂ��ăW�����v�̋�����-15�ɂ���
				JumpPower -= 25;
				JumpFlag = 1;
			}

			if (JumpFlag == TRUE) {
				PlayerY += JumpPower;//�オ�鑬���@������ꏊ����-15����
				JumpPower += 1; //�����鑬���@�P�������Ă���



				if (PlayerY > 300) { //�n�ʂɗ�������n�ʂɖ߂�
					PlayerY = 300;
					JumpPower = 0;
					JumpFlag = 0;
				}
			}



		}


		//----------------------------------------
		//�J����
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
		//map�`��
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
	//�L�����̕`��
	//----------------------------------------

	DrawGraph(PlayerX-g_CameraPosX, PlayerY-g_CameraPosY, PlayerGraph, TRUE);

	

			 /*����ʂ̓��e��\��ʂɔ��f������*/
		ScreenFlip();

		/* windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点�� -1 ���Ԃ��Ă����烋�[�v�𔲂���*/
		if (ProcessMessage() < 0) break;

		
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}


DxLib_End();				//

return 0;					// �\�t�g�̏I��
		}







