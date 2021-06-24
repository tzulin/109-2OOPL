

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
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);		// 一開始的loading進度為0%
									//
									// 開始載入資料
									//
									//logo.LoadBitmap(IDB_BACKGROUND);
									//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
									//
									// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
		const char KEY_LEFT = 0x25;	// keyboard左箭頭
		const char KEY_UP = 0x26;	// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;	// keyboard下箭頭
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

		if (nChar == KEY_ESC) {						// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
		else if (start_state == 1 && nChar == KEY_W) {
			start_state_one_back.ResetLoad();
			start_state_one_back.LoadBitmap("./res/save_back_1.bmp", RGB(0, 0, 0));
		}
		else if (start_state == 1 && nChar == KEY_ENTER) {
			if (record == 1) {
				if (record_1 == 0) {
					record_1++;															// 切換至第一關
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_1, record);						// 切換至GAME_STATE_RUN
			}
			else if (record == 2) {
				if (record_2 == 0) {
					record_2++;															// 切換至第一關
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_2, record);						// 切換至GAME_STATE_RUN
			}
			else if (record == 3) {
				if (record_3 == 0) {
					record_3++;															// 切換至第一關
				}
				CAudio::Instance()->Stop(AUDIO_SELECT);
				GotoGameState(GAME_STATE_RUN, record_3, record);						// 切換至GAME_STATE_RUN
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
		//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		if (start_state == 0) {
			start_state_zero_back.ShowBitmap();
			//
			// 貼上logo
			//
			//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
			//logo.ShowBitmap();
			//
			// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
			//
			/*CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
			CFont f, *fp;
			f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			/*pDC->TextOut(50,220,"Please press SPACE to begin.");
			pDC->TextOut(5, 395, "Please make sure your typing mode is in English.");
			if (ENABLE_GAME_PAUSE)
				pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
			pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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

			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
			CFont f, *fp;
			f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f

			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			pDC->TextOut(460, 15, "Stage");
			pDC->TextOut(460, 95, "Stage");
			pDC->TextOut(460, 175, "Stage");
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "(%d)", record_1);
			pDC->TextOut(555, 15, str);
			sprintf(str, "(%d)", record_2);
			pDC->TextOut(555, 95, str);
			sprintf(str, "(%d)", record_3);
			pDC->TextOut(555, 175, str);

			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

			num_1.ShowBitmap();
			num_2.ShowBitmap();
			num_3.ShowBitmap();
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0) {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// esc 關閉遊戲		
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

		ofstream SaveFile("save_file.txt");
		if (SaveFile.is_open()) {
			SaveFile << record_1 << "\n" << record_2 << "\n" << record_3 << "\n";
		}
		SaveFile.close();
		counter = 30 * 1; // 1 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
								//
								// 開始載入資料
								//
								//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
								//
								// 最終進度為100%
								//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
		if (Map != nullptr) {
			delete[] Map;
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
				delete[] Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_example_cloud.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}
		
			for (int i = 0; i < 38; i++) {
				ThingVector.push_back(new starBlock);
			}

			for (int i = 0; i < 5;i++) {
				for (int n = 0; n < 5; n++) {
					ThingVector[i * 5 + n]->LoadBitmap();
					ThingVector[i * 5 + n]->SetXY(1020 + 32 * i, SIZE_Y - 32 - 32 * n - temp_floor);
				}
			}

			ThingVector[25]->LoadBitmap();
			ThingVector[25]->SetXY(620, SIZE_Y - 32 - temp_floor);


			for (int i = 0;i < 10;i++) {
				ThingVector[26 + i]->LoadBitmap();
				ThingVector[26 + i]->SetXY(1330 + 32 * i, SIZE_Y - 32 - 200 - temp_floor);
			}


			ThingVector[36]->LoadBitmap();
			ThingVector[36]->SetXY(1650, SIZE_Y - 32 - temp_floor);

			ThingVector[37]->LoadBitmap();
			ThingVector[37]->SetXY(1950, SIZE_Y - 32 - temp_floor);
			
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

			EnemyVector.push_back(new waddle);
			EnemyVector[2]->LoadBitmap();
			EnemyVector[2]->Reset();
			EnemyVector[2]->SetXy(650, SIZE_Y - temp_floor - EnemyVector[2]->GetHeight());
			EnemyVector[2]->SetMap(Map);
			EnemyVector[2]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(700, SIZE_Y - temp_floor - EnemyVector[3]->GetHeight());
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[4]->LoadBitmap();
			EnemyVector[4]->Reset();
			EnemyVector[4]->SetXy(1500, SIZE_Y - temp_floor - EnemyVector[4]->GetHeight());
			EnemyVector[4]->SetMap(Map);
			EnemyVector[4]->SetThings(ThingVector);
		}
		else if(stage == 2){
			CAudio::Instance()->Play(AUDIO_RAINBOWROUTE, true);
			if (Map != nullptr) {
				delete[] Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_example.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blocks
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

			// star blocks: 5 blocks
			for (int count_x = 0; count_x < 5; count_x++) {
				ThingVector.push_back(new starBlock);
				ThingVector.at(91 + count_x)->LoadBitmap();
				ThingVector.at(91 + count_x)->SetXY(1150 + 32 * count_x, SIZE_Y - 150 - temp_floor);
			} // last block: 95

			// enemys
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
			EnemyVector[3]->SetXy(1000, SIZE_Y - temp_floor - 80);
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);

			EnemyVector.push_back(new waddle);
			EnemyVector[4]->LoadBitmap();
			EnemyVector[4]->Reset();
			EnemyVector[4]->SetXy(650, SIZE_Y - temp_floor - EnemyVector[0]->GetHeight());
			EnemyVector[4]->SetMap(Map);
			EnemyVector[4]->SetThings(ThingVector);
		}
		else if (stage == 3) {
			CAudio::Instance()->Play(AUDIO_RAINBOWROUTE, true);
			if (Map != nullptr) {
				delete[] Map;
			}
			Map = new CMovingBitmap;
			Map->LoadBitmap(".\\res\\map_example.bmp");
			Map->SetTopLeft(0, -260);
			Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

			if (!ThingVector.empty()) {
				for (auto block : ThingVector) {
					delete block;
				}
				ThingVector.clear();
			}

			// blocks
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

			// star blocks: 5 blocks
			for (int count_x = 0; count_x < 5; count_x++) {
				ThingVector.push_back(new starBlock);
				ThingVector.at(91 + count_x)->LoadBitmap();
				ThingVector.at(91 + count_x)->SetXY(1150 + 32 * count_x, SIZE_Y - 150 - temp_floor);
			} // last block: 95

			// enemys
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

			EnemyVector.push_back(new hotHead);
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

			EnemyVector.push_back(new waddle);
			EnemyVector[3]->LoadBitmap();
			EnemyVector[3]->Reset();
			EnemyVector[3]->SetXy(1000, SIZE_Y - temp_floor - 80);
			EnemyVector[3]->SetMap(Map);
			EnemyVector[3]->SetThings(ThingVector);

			EnemyVector.push_back(new droppy);
			EnemyVector[4]->LoadBitmap();
			EnemyVector[4]->Reset();
			EnemyVector[4]->SetXy(700, SIZE_Y - temp_floor - EnemyVector[4]->GetHeight());
			EnemyVector[4]->SetMap(Map);
			EnemyVector[4]->SetThings(ThingVector);

			EnemyVector.push_back(new waddleDoo);
			EnemyVector[5]->LoadBitmap();
			EnemyVector[5]->Reset();
			EnemyVector[5]->SetXy(1500, SIZE_Y - temp_floor - EnemyVector[5]->GetHeight());
			EnemyVector[5]->SetMap(Map);
			EnemyVector[5]->SetThings(ThingVector);
		}
		else {
			CAudio::Instance()->Play(AUDIO_BOSS, true);
			if (Map != nullptr) {
				delete[] Map;
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

			Door.SetTopLeft(SIZE_X - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
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

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		counter++;

		Kirby->SetCounter(counter);							// kirby get counter
		Kirby->SetMap(Map);									// kirby get map pointer
		Kirby->SetDoor(&Door);
		Kirby->SetThings(ThingVector);						// kirby get things pointer 
		Kirby->SetEnemies(EnemyVector);

		if (!Kirby->IsAlive()) {								// Kirby dead
			GotoGameState(GAME_STATE_OVER, stage, record);
		}

		Kirby->OnMove();										// Kirby OnMove
		weapon* KirbyWeapon = Kirby->GetWeapon();

		if (!EnemyVector.empty()) {
			for (unsigned int i = 0; i < EnemyVector.size(); i++) {
				EnemyVector[i]->OnMove();
				if (Meet(*EnemyVector[i], *Kirby)) {
					EnemyVector[i]->Hurt(1, counter);
					Kirby->Hurt(EnemyVector[i]->GetPower(), counter);
					temp_kirby = new normal_kirby;
					if (Kirby != nullptr) {
						Kirby->KirbyCopy(temp_kirby);
						delete Kirby;
					}
					Kirby = temp_kirby;
					Kirby->LoadBitmap();
					Kirby->SetKindInit();
				}
				if (Meet(*KirbyWeapon, *EnemyVector[i]) && KirbyWeapon->WeaponIsShow()) {			// kirby weapon hit enemy
					EnemyVector[i]->Hurt(1, counter);
					KirbyWeapon->SetShow(false);
				}
				if (EnemyVector[i]->EnemyHasWeapon()) {
					weapon EnemyWeapon = EnemyVector[i]->GetWeapon();
					if (EnemyCanAttack(*EnemyVector[i], *Kirby)) {				// enemy weapon hit kirby
						EnemyVector[i]->OnMove();								    // WaddleDoo OnMove
						EnemyVector[i]->Attack(*Kirby, counter);
						if (Meet(EnemyWeapon, *Kirby) && EnemyWeapon.WeaponIsShow()) {
							Kirby->Hurt(EnemyVector[i]->GetPower(), counter);
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
				if (EnemyVector[i]->GetCanAttack()) {
					if (EnemyCanAttack(*EnemyVector[i], *Kirby)) {				// enemy weapon hit kirby
						EnemyVector[i]->OnMove();								    // WaddleDoo OnMove
						EnemyVector[i]->Attack(*Kirby, counter);
						if (Meet(*EnemyVector[i], *Kirby)) {
							Kirby->Hurt(EnemyVector[i]->GetPower(), counter);
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
				if (EnemyVector[i]->GetHp() > 0) {												// waddle can attack check
					if (KirbyCanAttack(*Kirby, EnemyVector[i]) && Kirby->GetKind() == "normal_kirby") {
						EnemyVector[i]->Hurt(10, counter);
						Kirby->SetEaten(true, EnemyVector[i]->GetKind());
						Kirby->SetAttack(false);
					}
				}
				if (EnemyVector[i]->GetHp() <= 0) {
					delete EnemyVector[i];
					EnemyVector.erase(EnemyVector.begin() + i);
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

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
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
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_UP = 0x26;		// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;		// keyboard下箭頭
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

		if (nChar == KEY_ESC) {
			GotoGameState(GAME_STATE_OVER, stage, record);
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
			GotoGameState(GAME_STATE_RUN, GetStage() + 1, record);
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
				GotoGameState(GAME_STATE_RUN, GetStage() + 1, record);
			}
			else {
				Kirby->SetFly(true);
			}
		}

		if (nChar == KEY_ENTER) {

		}

		if (nChar == NUM_KEY_1) {
			temp_kirby = new normal_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_2) {
			temp_kirby = new waddleDoo_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_3) {
			temp_kirby = new sparky_kirby;
			if (Kirby != nullptr) {
				Kirby->KirbyCopy(temp_kirby);
				delete Kirby;
			}
			Kirby = temp_kirby;
			Kirby->LoadBitmap();
			Kirby->SetKindInit();
		}

		if (nChar == NUM_KEY_4) {
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
		const char KEY_LEFT = 0x25;	// keyboard左箭頭
		const char KEY_UP = 0x26;	// keyboard上箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char KEY_DOWN = 0x28;	// keyboard下箭頭
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

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
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

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f

		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Stage : %d", stage);
		pDC->TextOut(SIZE_X - 107, SIZE_Y - 32, str);

		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	}
}