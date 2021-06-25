

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

#include <iostream>
#include <fstream>
#include <string>


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);		// �@�}�l��loading�i�׬�0%
									//
									// �}�l���J���
									//
									//logo.LoadBitmap(IDB_BACKGROUND);
									//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
									//
									// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
									//
		start_state_zero_back.LoadBitmap(IDB_STARTBACK, RGB(0, 0, 0));
		start_state_one_back.LoadBitmap(IDB_SAVEBACK, RGB(0, 0, 0));
		gray_block_1.LoadBitmap(IDB_GRAY_BLOCK, RGB(255, 255, 255));
		gray_block_2.LoadBitmap(IDB_GRAY_BLOCK, RGB(255, 255, 255));
		yellow_block.LoadBitmap(IDB_YELLOW_BLOCK, RGB(255, 255, 255));

		num_1.LoadBitmap(IDB_1, RGB(255, 255, 255));
		num_2.LoadBitmap(IDB_2, RGB(255, 255, 255));
		num_3.LoadBitmap(IDB_3, RGB(255, 255, 255));

		CAudio::Instance()->Load(AUDIO_TITLE, "sounds\\title.mp3");
		CAudio::Instance()->Load(AUDIO_SELECT, "sounds\\selection.mp3");

		CAudio::Instance()->Play(AUDIO_TITLE, true);

		num_1.SetTopLeft(270, 20);
		num_2.SetTopLeft(270, 100);
		num_3.SetTopLeft(270, 180);

		string line;
		ifstream saveFile("save_file.txt");
		if (saveFile.is_open())
		{
			getline(saveFile, line);
			record_1 = stoi(line);
			getline(saveFile, line);
			record_2 = stoi(line);
			getline(saveFile, line);
			record_3 = stoi(line);
			saveFile.close();
		}
		else {
			ofstream firstSaveFile("save_file.txt");
			firstSaveFile << "0\n0\n0\n";
			record_1 = 0; record_2 = 0; record_3 = 0;
			firstSaveFile.close();
		}
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;	// keyboard���b�Y
		const char KEY_UP = 0x26;	// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;	// keyboard�U�b�Y
		const char KEY_ESC = 0x1B;    // keyboard esc
		const char KEY_C = 0x43;	// keyboard C
		const char KEY_W = 0x57;	// keyboard W
		const char KEY_S = 0X53;	// keyboard S
		const char KEY_SPACE = 0x20;	// keyboard space
		const char KEY_ENTER = 0x0D;	// keyboard enter


		if (nChar == KEY_ENTER) {
			CAudio::Instance()->Stop(AUDIO_TITLE);
			CAudio::Instance()->Play(AUDIO_SELECT, true);
		}

		if (nChar == KEY_ESC) {						// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		}
		else if (start_state == 1 && nChar == KEY_W) {
			start_state_one_back.ResetLoad();
			start_state_one_back.LoadBitmap("./res/save_back_1.bmp", RGB(0, 0, 0));
		}
		else if (start_state == 1 && nChar == KEY_ENTER) {
			if (record == 1) {
				if (record_1 == 0) {
					record_1++;															// �����ܲĤ@��
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_1, record, false);						// ������GAME_STATE_RUN
			}
			else if (record == 2) {
				if (record_2 == 0) {
					record_2++;															// �����ܲĤ@��
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_2, record, false);						// ������GAME_STATE_RUN
			}
			else if (record == 3) {
				if (record_3 == 0) {
					record_3++;															// �����ܲĤ@��
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_3, record, false);						// ������GAME_STATE_RUN
			}
		}
		else if (start_state == 0 && nChar == KEY_ENTER) {
			start_state = 1;
		}
		else if (start_state == 1 && nChar == KEY_UP) {
			if (record == 2 || record == 3) {
				SetRecord(GetRecord() - 1);
			}
		}
		else if (start_state == 1 && nChar == KEY_DOWN) {
			if (record == 1 || record == 2) {
				SetRecord(GetRecord() + 1);
			}
		}
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		if (start_state == 0) {
			start_state_zero_back.ShowBitmap();
			//
			// �K�Wlogo
			//
			//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
			//logo.ShowBitmap();
			//
			// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
			//
			/*CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
			CFont f, *fp;
			f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			/*pDC->TextOut(50,220,"Please press SPACE to begin.");
			pDC->TextOut(5, 395, "Please make sure your typing mode is in English.");
			if (ENABLE_GAME_PAUSE)
				pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
			pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
			*/
		}
		else {
			start_state_one_back.ShowBitmap();
			if (record == 1) {
				yellow_block.SetTopLeft(SIZE_X - yellow_block.Width(), -23);
				gray_block_1.SetTopLeft(SIZE_X - gray_block_1.Width(), 80);
				gray_block_2.SetTopLeft(SIZE_X - gray_block_2.Width(), 160);
				yellow_block.ShowBitmap();
				gray_block_1.ShowBitmap();
				gray_block_2.ShowBitmap();
			}
			else if (record == 2) {
				yellow_block.SetTopLeft(SIZE_X - yellow_block.Width(), 80 - 23);
				gray_block_1.SetTopLeft(SIZE_X - gray_block_1.Width(), 0);
				gray_block_2.SetTopLeft(SIZE_X - gray_block_2.Width(), 160);
				yellow_block.ShowBitmap();
				gray_block_1.ShowBitmap();
				gray_block_2.ShowBitmap();
			}
			else if (record == 3) {
				yellow_block.SetTopLeft(SIZE_X - yellow_block.Width(), 160 - 23);
				gray_block_1.SetTopLeft(SIZE_X - gray_block_1.Width(), 0);
				gray_block_2.SetTopLeft(SIZE_X - gray_block_2.Width(), 80);
				yellow_block.ShowBitmap();
				gray_block_1.ShowBitmap();
				gray_block_2.ShowBitmap();
			}

			CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
			CFont f, *fp;
			f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f

			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			pDC->TextOut(460, 15, "Stage");
			pDC->TextOut(460, 95, "Stage");
			pDC->TextOut(460, 175, "Stage");
			char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
			sprintf(str, "(%d)", record_1);
			pDC->TextOut(555, 15, str);
			sprintf(str, "(%d)", record_2);
			pDC->TextOut(555, 95, str);
			sprintf(str, "(%d)", record_3);
			pDC->TextOut(555, 175, str);

			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

			num_1.ShowBitmap();
			num_2.ShowBitmap();
			num_3.ShowBitmap();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0) {
			CAudio::Instance()->Stop(AUDIO_SELECT);
			GotoGameState(GAME_STATE_INIT, stage, record, false);
			// PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// esc �����C��		
		}
	}

	void CGameStateOver::OnBeginState()
	{
		CAudio::Instance()->Stop(AUDIO_TITLE);
		CAudio::Instance()->Stop(AUDIO_SELECT);
		CAudio::Instance()->Stop(AUDIO_STARTING);
		CAudio::Instance()->Stop(AUDIO_RAINBOWROUTE);
		CAudio::Instance()->Stop(AUDIO_BOSS);

		string line;
		int record_1 = 0, record_2 = 0, record_3 = 0;
		ifstream oldSaveFile("save_file.txt");
		if (oldSaveFile.is_open()) {
			getline(oldSaveFile, line);
			record_1 = stoi(line);
			getline(oldSaveFile, line);
			record_2 = stoi(line);
			getline(oldSaveFile, line);
			record_3 = stoi(line);
			oldSaveFile.close();
		}

		if (record == 1) {
			record_1 = stage;
		}
		else if (record == 2) {
			record_2 = stage;

		}
		else if (record == 3) {
			record_3 = stage;
		}
		counter = 30 * 3; // 1 seconds

		if (pass) {
			record_1 = 0; record_2 = 0; record_3 = 0; counter = 5 * 30;
		}

		ofstream SaveFile("save_file.txt");
		if (SaveFile.is_open()) {
			SaveFile << record_1 << "\n" << record_2 << "\n" << record_3 << "\n";
		}
		SaveFile.close();
		
	}

	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
								//
								// �}�l���J���
								//
								//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
								//
								// �̲׶i�׬�100%
								//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		if (pass) {
			sprintf(str, "Game Pass ! (%d)", counter / 30);
		}
		else {
			sprintf(str, "Game Over ! (%d)", counter / 30);
		}
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
		if (Map != nullptr) {
			delete Map;
		}

		if (Kirby != nullptr) {
			delete Kirby;
		}

		if (!ThingVector.empty()) {
			for (auto block : ThingVector) {
				delete block;
			}
			ThingVector.clear();
		}

		if (!EnemyVector.empty()) {
			for (auto n : EnemyVector) {
				delete n;
			}
			EnemyVector.clear();
		}
	}

	void CGameStateRun::OnBeginState()
	{
		Kirby->StageReSet(Kirby->GetHp(), Kirby->GetKind());
		if (stage == 1) {
			CAudio::Instance()->Play(AUDIO_STARTING, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_cloud1.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blankBlocks
			// hill: 9 blocks
			for (int i = 0; i < 3; i++) {
				for (int n = 0; n < 3; n++) {
					ThingVector.push_back(new blankBlock);
					ThingVector[i * 3 + n]->LoadBitmap();
					ThingVector[i * 3 + n]->SetXY(960 + 32 * i, SIZE_Y - 32 - 32 * n - temp_floor);
				}
			} // last block: 8
			// platform: 18 blocks
			for (int count_x = 0; count_x < 9; count_x++) {
				for (int count_y = 0; count_y < 2; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(9 + count_x * 2 + count_y)->LoadBitmap();
					ThingVector.at(9 + count_x * 2 + count_y)->SetXY(1365 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - 260);
				}
			} // last block: 26

			// starBlocks
			ThingVector.push_back(new starBlock);
			ThingVector[27]->LoadBitmap();
			ThingVector[27]->SetXY(620, SIZE_Y - 32 - temp_floor);

			ThingVector.push_back(new starBlock);
			ThingVector[28]->LoadBitmap();
			ThingVector[28]->SetXY(1650, SIZE_Y - 32 - temp_floor);

			ThingVector.push_back(new starBlock);
			ThingVector[29]->LoadBitmap();
			ThingVector[29]->SetXY(1950, SIZE_Y - 32 - temp_floor);

			// enemies
			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}
			EnemyVector.push_back(new waddle);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(700, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[1]->LoadBitmap();
			EnemyVector[1]->Reset();
			EnemyVector[1]->SetXy(1400, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
			EnemyVector[1]->SetMap(Map);
			EnemyVector[1]->SetThings(ThingVector);

			EnemyVector.push_back(new waddle);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(2200, SIZE_Y - temp_floor - EnemyVector[2]->GetHeight());
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);
		}
		else if (stage == 2) {
			CAudio::Instance()->Play(AUDIO_STARTING, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_cloud1.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blankBlocks
			// hill: 9 blocks
			for (int i = 0; i < 3; i++) {
				for (int n = 0; n < 3; n++) {
					ThingVector.push_back(new blankBlock);
					ThingVector[i * 3 + n]->LoadBitmap();
					ThingVector[i * 3 + n]->SetXY(960 + 32 * i, SIZE_Y - 32 - 32 * n - temp_floor);
				}
			} // last block: 8
			// platform: 18 blocks
			for (int count_x = 0; count_x < 9; count_x++) {
				for (int count_y = 0; count_y < 2; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(9 + count_x * 2 + count_y)->LoadBitmap();
					ThingVector.at(9 + count_x * 2 + count_y)->SetXY(1365 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - 260);
				}
			} // last block: 26

			// starBlocks
			ThingVector.push_back(new starBlock);
			ThingVector[27]->LoadBitmap();
			ThingVector[27]->SetXY(200, SIZE_Y - 32 - temp_floor);

			for (int i = 0; i < 3; i++) {
				ThingVector.push_back(new starBlock);
				ThingVector[28 + i]->LoadBitmap();
				ThingVector[28 + i]->SetXY(700 + 32 * i, SIZE_Y - 250);
			}

			ThingVector.push_back(new starBlock);
			ThingVector[31]->LoadBitmap();
			ThingVector[31]->SetXY(1950, SIZE_Y - 32 - temp_floor);

			// enemies
			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}
			EnemyVector.push_back(new droppy);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(300, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[1]->LoadBitmap();
			EnemyVector[1]->Reset();
			EnemyVector[1]->SetXy(1400, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
			EnemyVector[1]->SetMap(Map);
			EnemyVector[1]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(2200, SIZE_Y - temp_floor - EnemyVector[2]->GetHeight());
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);

			EnemyVector.push_back(new waddle);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(1200, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);
		}
		else if (stage == 3) {
			CAudio::Instance()->Play(AUDIO_STARTING, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_cloud2.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - 350 - Door.Height());
			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blankBlocks
			// 1st hill: 24 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 8; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(count_x * 8 + count_y)->LoadBitmap();
					ThingVector.at(count_x * 8 + count_y)->SetXY(685 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor + 10);
				}
			} // last block: 23
			// 1st hill_up: 39 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 13; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(24 + count_x * 13 + count_y)->LoadBitmap();
					ThingVector.at(24 + count_x * 13 + count_y)->SetXY(690 + 32 * count_x, -320 + 32 * count_y);
				}
			} // last block: 62
			// 1st hill_up_left: 15 blocks
			for (int count_x = 0; count_x < 5; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(63 + count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(63 + count_x * 3 + count_y)->SetXY(790 + 32 * count_x, 32 * count_y);
				}
			} // last block: 77
			// 2nd hill: 8 blocks
			for (int count_x = 0; count_x < 4; count_x++) {
				for (int count_y = 0; count_y < 2; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(78 + count_x * 2 + count_y)->LoadBitmap();
					ThingVector.at(78 + count_x * 2 + count_y)->SetXY(1420 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor + 5);
				}
			} // last block: 85
			// 3rd hill: 15 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 5; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(86 + count_x * 5 + count_y)->LoadBitmap();
					ThingVector.at(86 + count_x * 5 + count_y)->SetXY(1945 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor + 15);
				}
			} // last block: 100
			// platform: 16 blocks
			for (int count_x = 0; count_x < 8; count_x++) {
				for (int count_y = 0; count_y < 2; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(101 + count_x * 2 + count_y)->LoadBitmap();
					ThingVector.at(101 + count_x * 2 + count_y)->SetXY(2300 + 32 * count_x, SIZE_Y - 360 + 32 * count_y);
				}
			} // last block: 116

			//starBlocks: 3
			for (int count_x = 0; count_x < 3; count_x++) {
				ThingVector.push_back(new starBlock);
				ThingVector[117 + count_x]->LoadBitmap();
				ThingVector[117 + count_x]->SetXY(800 + 32 * count_x, -40);
			} // last block: 119

			// enemies
			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}

			EnemyVector.push_back(new waddle);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(350, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[1]->LoadBitmap();
			EnemyVector[1]->Reset();
			EnemyVector[1]->SetXy(1010, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
			EnemyVector[1]->SetMap(Map);
			EnemyVector[1]->SetThings(ThingVector);

			EnemyVector.push_back(new waddle);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(1600, SIZE_Y - temp_floor - EnemyVector[2]->GetHeight());
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(1850, SIZE_Y - temp_floor - EnemyVector[3]->GetHeight());
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[4]->LoadBitmap();
			EnemyVector[4]->Reset();
			EnemyVector[4]->SetXy(2200, SIZE_Y - temp_floor - EnemyVector[4]->GetHeight());
			EnemyVector[4]->SetMap(Map);
			EnemyVector[4]->SetThings(ThingVector);
			
		}
		else if (stage == 4) {
			CAudio::Instance()->Play(AUDIO_RAINBOWROUTE, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_forest1.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blankBlocks
			// first hill: 9 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(count_x * 3 + count_y)->SetXY(360 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 8
			// second hill: 32 blocks
			for (int count_x = 0; count_x < 4; count_x++) {
				for (int count_y = 0; count_y < 8; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(9 + count_x * 8 + count_y)->LoadBitmap();
					ThingVector.at(9 + count_x * 8 + count_y)->SetXY(770 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 40
			// 3rd hill: 9 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(41 + count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(41 + count_x * 3 + count_y)->SetXY(1580 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 49
			// 4th hill: 32 blocks
			for (int count_x = 0; count_x < 4; count_x++) {
				for (int count_y = 0; count_y < 8; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(50 + count_x * 8 + count_y)->LoadBitmap();
					ThingVector.at(50 + count_x * 8 + count_y)->SetXY(1790 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 81
			// 5th hill: 9 blocks
			for (int count_x = 0; count_x < 3; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(82 + count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(82 + count_x * 3 + count_y)->SetXY(2310 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 90

			// starBlocks: 5 blocks
			for (int count_x = 0; count_x < 5; count_x++) {
				ThingVector.push_back(new starBlock);
				ThingVector.at(91 + count_x)->LoadBitmap();
				ThingVector.at(91 + count_x)->SetXY(1150 + 32 * count_x, SIZE_Y - 150 - temp_floor);
			} // last block: 95

			// enemies
			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}

			EnemyVector.push_back(new waddle);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(200, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[1]->LoadBitmap();
			EnemyVector[1]->Reset();
			EnemyVector[1]->SetXy(2000, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
			EnemyVector[1]->SetMap(Map);
			EnemyVector[1]->SetThings(ThingVector);

			EnemyVector.push_back(new sparky);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(600, SIZE_Y - temp_floor - EnemyVector[2]->GetHeight());
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);

			EnemyVector.push_back(new hotHead);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(1400, SIZE_Y - temp_floor - 80);
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[4]->LoadBitmap();
			EnemyVector[4]->Reset();
			EnemyVector[4]->SetXy(2500, SIZE_Y - temp_floor - EnemyVector[4]->GetHeight());
			EnemyVector[4]->SetMap(Map);
			EnemyVector[4]->SetThings(ThingVector);
		}
		else if (stage == 5) {
		CAudio::Instance()->Play(AUDIO_RAINBOWROUTE, true);
		if (Map != nullptr) {
			delete Map;
		}
		Map = new CMovingBitmap;
		Map->LoadBitmap(".\\res\\map_forest1.bmp");
		Map->SetTopLeft(0, -260);
		Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

		if (!ThingVector.empty()) {
			for (auto block : ThingVector) {
				delete block;
			}
			ThingVector.clear();
		}

		// blankBlocks
		// first hill: 9 blocks
		for (int count_x = 0; count_x < 3; count_x++) {
			for (int count_y = 0; count_y < 3; count_y++) {
				ThingVector.push_back(new blankBlock);
				ThingVector.at(count_x * 3 + count_y)->LoadBitmap();
				ThingVector.at(count_x * 3 + count_y)->SetXY(360 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
			}
		} // last block: 8
		// second hill: 32 blocks
		for (int count_x = 0; count_x < 4; count_x++) {
			for (int count_y = 0; count_y < 8; count_y++) {
				ThingVector.push_back(new blankBlock);
				ThingVector.at(9 + count_x * 8 + count_y)->LoadBitmap();
				ThingVector.at(9 + count_x * 8 + count_y)->SetXY(770 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
			}
		} // last block: 40
		// 3rd hill: 9 blocks
		for (int count_x = 0; count_x < 3; count_x++) {
			for (int count_y = 0; count_y < 3; count_y++) {
				ThingVector.push_back(new blankBlock);
				ThingVector.at(41 + count_x * 3 + count_y)->LoadBitmap();
				ThingVector.at(41 + count_x * 3 + count_y)->SetXY(1580 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
			}
		} // last block: 49
		// 4th hill: 32 blocks
		for (int count_x = 0; count_x < 4; count_x++) {
			for (int count_y = 0; count_y < 8; count_y++) {
				ThingVector.push_back(new blankBlock);
				ThingVector.at(50 + count_x * 8 + count_y)->LoadBitmap();
				ThingVector.at(50 + count_x * 8 + count_y)->SetXY(1790 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
			}
		} // last block: 81
		// 5th hill: 9 blocks
		for (int count_x = 0; count_x < 3; count_x++) {
			for (int count_y = 0; count_y < 3; count_y++) {
				ThingVector.push_back(new blankBlock);
				ThingVector.at(82 + count_x * 3 + count_y)->LoadBitmap();
				ThingVector.at(82 + count_x * 3 + count_y)->SetXY(2310 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
			}
		} // last block: 90

		// starBlocks: 5 blocks
		for (int count_x = 0; count_x < 5; count_x++) {
			ThingVector.push_back(new starBlock);
			ThingVector.at(91 + count_x)->LoadBitmap();
			ThingVector.at(91 + count_x)->SetXY(1150 + 32 * count_x, SIZE_Y - 150 - temp_floor);
		} // last block: 95

		// enemies
		if (!EnemyVector.empty()) {
			for (auto n : EnemyVector) {
				delete n;
			}
			EnemyVector.clear();
		}

		EnemyVector.push_back(new bigWaddle);
		EnemyVector[0]->LoadBitmap();
		EnemyVector[0]->Reset();
		EnemyVector[0]->SetXy(200, SIZE_Y - temp_floor - 120);
		EnemyVector[0]->SetMap(Map);
		EnemyVector[0]->SetThings(ThingVector);

		EnemyVector.push_back(new waddleDoo);
		EnemyVector[1]->LoadBitmap();
		EnemyVector[1]->Reset();
		EnemyVector[1]->SetXy(2200, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
		EnemyVector[1]->SetMap(Map);
		EnemyVector[1]->SetThings(ThingVector);

		EnemyVector.push_back(new hotHead);
		EnemyVector[2]->LoadBitmap();
		EnemyVector[2]->Reset();
		EnemyVector[2]->SetXy(600, SIZE_Y - temp_floor - 80);
		EnemyVector[2]->SetMap(Map);
		EnemyVector[2]->SetThings(ThingVector);

		EnemyVector.push_back(new sparky);
		EnemyVector[3]->LoadBitmap();
		EnemyVector[3]->Reset();
		EnemyVector[3]->SetXy(1400, SIZE_Y - temp_floor - EnemyVector[3]->GetHeight());
		EnemyVector[3]->SetMap(Map);
		EnemyVector[3]->SetThings(ThingVector);

		EnemyVector.push_back(new droppy);
		EnemyVector[4]->LoadBitmap();
		EnemyVector[4]->Reset();
		EnemyVector[4]->SetXy(900, SIZE_Y - temp_floor - EnemyVector[4]->GetHeight());
		EnemyVector[4]->SetMap(Map);
		EnemyVector[4]->SetThings(ThingVector);
		}
		else if (stage == 6) {
			CAudio::Instance()->Play(AUDIO_RAINBOWROUTE, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_forest2.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blankBlocks
			// first hill: 45 blocks
			for (int count_x = 0; count_x < 15; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(count_x * 3 + count_y)->SetXY(710 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 44
			// 2nd hill: 32 blocks
			for (int count_x = 0; count_x < 4; count_x++) {
				for (int count_y = 0; count_y < 8; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(45 + count_x * 8 + count_y)->LoadBitmap();
					ThingVector.at(45 + count_x * 8 + count_y)->SetXY(1480 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor + 10);
				}
			} // last block: 76
			// 3rd hill: 45 blocks
			for (int count_x = 0; count_x < 15; count_x++) {
				for (int count_y = 0; count_y < 3; count_y++) {
					ThingVector.push_back(new blankBlock);
					ThingVector.at(77 + count_x * 3 + count_y)->LoadBitmap();
					ThingVector.at(77 + count_x * 3 + count_y)->SetXY(1620 + 32 * count_x, SIZE_Y - 32 - 32 * count_y - temp_floor);
				}
			} // last block: 121

			// starBlocks
			ThingVector.push_back(new starBlock);
			ThingVector[122]->LoadBitmap();
			ThingVector[122]->SetXY(2020, SIZE_Y - 140 - temp_floor);

			// enemyies
			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}
			EnemyVector.push_back(new bigWaddle);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(400, SIZE_Y - temp_floor - 120);
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);

			EnemyVector.push_back(new hotHead);
			EnemyVector[1]->LoadBitmap();
			EnemyVector[1]->Reset();
			EnemyVector[1]->SetXy(1300, SIZE_Y - temp_floor - 80);
			EnemyVector[1]->SetMap(Map);
			EnemyVector[1]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(1700, 300);
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);

			EnemyVector.push_back(new sparky);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(2000, SIZE_Y - temp_floor - EnemyVector[3]->GetHeight());
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);
		}
		else {
			CAudio::Instance()->Play(AUDIO_BOSS, true);
			if (Map != nullptr) {
				delete Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_example_cloud.bmp");
			Map->SetTopLeft(0, -260);

			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			Door.ResetLoad();
			Door.LoadBitmap(".\\res\\weapon\\1.bmp", RGB(255, 255, 255));

			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}
			EnemyVector.push_back(new kingDedede);
			EnemyVector[0]->LoadBitmap();
			EnemyVector[0]->Reset();
			EnemyVector[0]->SetXy(SIZE_X - 200, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[0]->SetMap(Map);
			EnemyVector[0]->SetThings(ThingVector);
		}
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		counter++;

		Kirby->SetCounter(counter);							// kirby get counter
		Kirby->SetMap(Map);									// kirby get map pointer
		Kirby->SetDoor(&Door);
		Kirby->SetThings(ThingVector);						// kirby get things pointer 
		Kirby->SetEnemies(EnemyVector);

		if (!Kirby->IsAlive()) {								// Kirby dead
			GotoGameState(GAME_STATE_OVER, stage, record, false);
		}

		Kirby->OnMove();										// Kirby OnMove
		weapon* KirbyWeapon = Kirby->GetWeapon();

		if (!EnemyVector.empty()) {
			for (unsigned int i = 0; i < EnemyVector.size(); i++) {
				EnemyVector[i]->OnMove();
				EnemyVector[i]->SetCounter(counter);
				if (Meet(*EnemyVector[i], *Kirby)) {
					/*ThingVector.push_back(new starBlock);
					int * temp = Kirby->GetXy();
					ThingVector[ThingVector.size() - 1]->LoadBitmap();
					if (Kirby->GetFacingR()) {
						ThingVector[ThingVector.size() - 1]->SetXY(temp[0] - 100, temp[1] - 50);
					}
					else {
						ThingVector[ThingVector.size() - 1]->SetXY(temp[0] + 100, temp[1] - 50);
					}
					ThingVector[ThingVector.size() - 1]->SetShow(true);
					ThingVector[ThingVector.size() - 1]->SetKind(Kirby->GetKind());
					delete[] temp;*/
					EnemyVector[i]->Hurt(1, counter);
					if (Kirby->Hurt(EnemyVector[i]->GetPower(), counter)) {
						temp_kirby = new normal_kirby;
						if (Kirby != nullptr) {
							Kirby->KirbyCopy(temp_kirby);
							delete Kirby;
						}
						Kirby = temp_kirby;
						Kirby->LoadBitmap();
						Kirby->SetKindInit();
					}
				}
				if (Meet(*KirbyWeapon, *EnemyVector[i]) && KirbyWeapon->WeaponIsShow()) {			// kirby weapon hit enemy
					EnemyVector[i]->Hurt(1, counter);
					if (Kirby->GetKind() == "normal_kirby") {
						KirbyWeapon->SetShow(false);
					}
				}
				if (EnemyVector[i]->EnemyHasWeapon()) {
					weapon EnemyWeapon = EnemyVector[i]->GetWeapon();
					if (EnemyCanAttack(*EnemyVector[i], *Kirby)) {				// enemy weapon hit kirby
						EnemyVector[i]->OnMove();								    // WaddleDoo OnMove
						EnemyVector[i]->Attack(*Kirby, counter);
						if (Meet(EnemyWeapon, *Kirby) && EnemyWeapon.WeaponIsShow()) {
							if (Kirby->Hurt(EnemyVector[i]->GetPower(), counter)) {
								temp_kirby = new normal_kirby;
								if (Kirby != nullptr) {
									Kirby->KirbyCopy(temp_kirby);
									delete Kirby;
								}
								Kirby = temp_kirby;
								Kirby->LoadBitmap();
								Kirby->SetKindInit();
							}
						}
					}
				}
				if (EnemyVector[i]->GetHp() > 0) {												// waddle can attack check
					if (KirbyCanAttack(*Kirby, EnemyVector[i]) && Kirby->GetKind() == "normal_kirby" &&  !(EnemyVector[i]->GetKind() == "kingDedede")) {
						EnemyVector[i]->Hurt(10, counter);
						Kirby->SetEaten(true, EnemyVector[i]->GetKind());
						Kirby->SetAttack(false);
					}
				}
				if (EnemyVector[i]->GetHp() <= 0) {
					if (EnemyVector[i]->GetKind() == "kingDedede") {
						delete EnemyVector[i];
						EnemyVector.erase(EnemyVector.begin() + i);
						GotoGameState(GAME_STATE_OVER, stage, record, true);
					}
					else {
						delete EnemyVector[i];
						EnemyVector.erase(EnemyVector.begin() + i);
					}
				}
			}
		}

		kirbyHpInt.SetInteger(Kirby->GetHp());				// set integer
		if (!ThingVector.empty()) {							// starblock can attack or not
			for (auto block : ThingVector) {
				if (block != nullptr && block->GetShow()) {
					if (Meet(*KirbyWeapon, *block) && KirbyWeapon->WeaponIsShow() && Kirby->GetKind() == "normal_kirby") {			// kirby weapon hit enemy
						KirbyWeapon->SetShow(false);
					}
					if (KirbyCanAttack(*Kirby, block) && block->isStarBlock() && Kirby->GetKind() == "normal_kirby") {
						block->SetShow(false);
						Kirby->SetEaten(true);
						Kirby->SetAttack(false);
					}
				}
			}
		}
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		//Map->LoadBitmap(".\\res\\map_example.bmp");			// map load and set
		Door.LoadBitmap(IDB_DOOR, RGB(255, 255, 255));
		kirbyHp.LoadBitmap(".\\res\\kirby_hpPic.bmp", RGB(236, 28, 36));
		kirbyHpInt.LoadBitmap();
		Kirby = new normal_kirby;
		Kirby->LoadBitmap();									// Kirby LoadBitmap
		Kirby->SetKindInit();
		
		// load audio
		CAudio::Instance()->Load(AUDIO_STARTING, "sounds\\starting_stage.mp3");
		CAudio::Instance()->Load(AUDIO_RAINBOWROUTE, "sounds\\forest_and_natural_area.mp3");
		CAudio::Instance()->Load(AUDIO_BOSS, "sounds\\boss.mp3");

		//Map->SetTopLeft(0, -260);
		Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
		kirbyHp.SetTopLeft(0, SIZE_Y - kirbyHp.Height());											// kirbyHp load and set
		kirbyHpInt.SetDigits(2);
		kirbyHpInt.SetTopLeft(kirbyHp.Width(), SIZE_Y - kirbyHp.Height() + 5);						// kirbyHpInt load and set

		Map = nullptr;

		if (!EnemyVector.empty()) {
			for (auto n : EnemyVector) {
				delete n;
			}
			EnemyVector.clear();
		}

		if (!ThingVector.empty()) {
			for (auto block : ThingVector) {
				delete block;
			}
			ThingVector.clear();
		}
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard���b�Y
		const char KEY_UP = 0x26;		// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;		// keyboard�U�b�Y
		const char KEY_ESC = 0x1B;	    // keyboard esc
		const char KEY_C = 0x43;		// keyboard C
		const char KEY_W = 0x57;		// keyboard W
		const char KEY_S = 0X53;		// keyboard S
		const char KEY_N = 0x4E;		// keyboard N
		const char KEY_P = 0x50;		// keyboard P
		const char KEY_SPACE = 0x20;	// keyboard space
		const char KEY_ENTER = 0x0D;	// keyboard enter
		const char NUM_KEY_1 = 0x61;	// number keyboard 1
		const char NUM_KEY_2 = 0x62;	// number keyboard 2
		const char NUM_KEY_3 = 0x63;	// number keyboard 3
		const char NUM_KEY_4 = 0x64;	// number keyboard 4
		const char KEY_1 = 0x31;		// keyboard 1
		const char KEY_2 = 0x32;		// keyboard 2
		const char KEY_3 = 0x33;		// keyboard 3
		const char KEY_4 = 0x34;		// keyboard 4

		if (nChar == KEY_ESC) {
			GotoGameState(GAME_STATE_OVER, stage, record, false);
		}

		if (nChar == KEY_LEFT) {
			if (counter - last_left <= 10) {
				Kirby->SetRun(true);
			}
			else {
				last_left = counter;
			}
			Kirby->SetMovingL(true);					// Kirby moving left
			Kirby->SetFacingL(true);					// Kirby facing left
		}

		if (nChar == KEY_RIGHT) {
			if (counter - last_right <= 10) {
				Kirby->SetRun(true);
			}
			else {
				last_right = counter;
			}
			Kirby->SetMovingR(true);					// Kirby moving right
			Kirby->SetFacingR(true);					// Kirby facing right
		}

		if (nChar == KEY_DOWN) {
			Kirby->SetDown(true);

			if (Kirby->GetEatenEnemy() == "waddleDoo") {
				temp_kirby = new waddleDoo_kirby;
				if (Kirby != nullptr) {
					Kirby->KirbyCopy(temp_kirby);
					delete Kirby;
				}
				Kirby = temp_kirby;
				Kirby->LoadBitmap();
				Kirby->SetKindInit();
			}
			else if (Kirby->GetEatenEnemy() == "sparky") {
				temp_kirby = new sparky_kirby;
				if (Kirby != nullptr) {
					Kirby->KirbyCopy(temp_kirby);
					delete Kirby;
				}
				Kirby = temp_kirby;
				Kirby->LoadBitmap();
				Kirby->SetKindInit();
			}
			else if (Kirby->GetEatenEnemy() == "hotHead") {
				temp_kirby = new hotHead_kirby;
				if (Kirby != nullptr) {
					Kirby->KirbyCopy(temp_kirby);
					delete Kirby;
				}
				Kirby = temp_kirby;
				Kirby->LoadBitmap();
				Kirby->SetKindInit();
			}
			else if (Kirby->GetEaten()) {
				Kirby->SetEaten(false);
			}
		}

		if (nChar == KEY_C) {
			Kirby->SetAttack(true);
		}

		if (nChar == KEY_P) {
			CAudio::Instance()->Stop(AUDIO_STARTING);
			CAudio::Instance()->Stop(AUDIO_RAINBOWROUTE);
			CAudio::Instance()->Stop(AUDIO_BOSS);
			if (stage != 7) {
				GotoGameState(GAME_STATE_RUN, GetStage() + 1, record, false);
			}
		}

		if (nChar == KEY_S) {
			Kirby->SetHack(true);
		}

		if (nChar == KEY_N) {
			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					block->SetShow(false);
					delete block;
				}
				ThingVector.clear();
			}

			if (!EnemyVector.empty()) {
				for (auto n : EnemyVector) {
					delete n;
				}
				EnemyVector.clear();
			}
		}

		if (nChar == KEY_SPACE) {
			Kirby->SetJump(true);
		}

		if (nChar == KEY_UP) {
			if (Meet(*Kirby, Door)) {
				CAudio::Instance()->Stop(AUDIO_STARTING);
				CAudio::Instance()->Stop(AUDIO_RAINBOWROUTE);
				CAudio::Instance()->Stop(AUDIO_BOSS);
				GotoGameState(GAME_STATE_RUN, GetStage() + 1, record, false);
			}
			else {
				Kirby->SetFly(true);
			}
		}

		if (nChar == KEY_ENTER) {

		}

		if (nChar == NUM_KEY_1 || nChar == KEY_1) {
			temp_kirby = new normal_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_2 || nChar == KEY_2) {
			temp_kirby = new waddleDoo_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_3 || nChar == KEY_3) {
			temp_kirby = new sparky_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_4 || nChar == KEY_4) {
			temp_kirby = new hotHead_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;	// keyboard���b�Y
		const char KEY_UP = 0x26;	// keyboard�W�b�Y
		const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
		const char KEY_DOWN = 0x28;	// keyboard�U�b�Y
		const char KEY_ESC = 0x1B;    // keyboard esc
		const char KEY_C = 0x43;	// keyboard C
		const char KEY_W = 0x57;	// keyboard W
		const char KEY_S = 0X53;	// keyboard S
		const char KEY_N = 0x4E;		// keyboard N
		const char KEY_SPACE = 0x20;	// keyboard space
		const char KEY_ENTER = 0x0D;	// keyboard enter

		if (nChar == KEY_LEFT) {
			Kirby->SetMovingL(false);				// Kirby stop moving left
			Kirby->SetRun(false);
		}

		if (nChar == KEY_RIGHT) {
			Kirby->SetMovingR(false);				// Kirby stop moving right
			Kirby->SetRun(false);
		}

		if (nChar == KEY_DOWN) {
			Kirby->SetDown(false);
		}

		if (nChar == KEY_C) {
			Kirby->SetAttack(false);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
	}

	void CGameStateRun::OnShow()
	{
		Map->ShowBitmap();
		Door.ShowBitmap();

		if (!EnemyVector.empty()) {
			for (auto n : EnemyVector) {
				n->OnShow();
			}
		}
		if (!ThingVector.empty()) {
			for (int i = 0; i < int(ThingVector.size()); i++) {
				if (ThingVector.at(i) != nullptr) {
					if (ThingVector.at(i)->GetShow()) {
						ThingVector.at(i)->OnShow();							// StarBlock onShow
					}
				}
			}
		}

		Kirby->OnShow();									// Kirby OnShow
		kirbyHpInt.ShowBitmap();						// hp int show
		kirbyHp.ShowBitmap();							// kibyHp show	

		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f

		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Stage : %d", stage);
		pDC->TextOut(SIZE_X - 107, SIZE_Y - 32, str);

		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

	}
}