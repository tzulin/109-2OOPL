

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

	if (nChar == KEY_ESC) {						// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}
	else if (start_state == 1 && nChar == KEY_ENTER) {
		if (record == 1) {
			if (record_1 == 0) {
				record_1++;															// 切換至第一關
			}
			GotoGameState(GAME_STATE_RUN, record_1, record);						// 切換至GAME_STATE_RUN
		}
		else if (record == 2) {
			if (record_2 == 0) {
				record_2++;															// 切換至第一關
			}
			GotoGameState(GAME_STATE_RUN, record_2, record);						// 切換至GAME_STATE_RUN
		}
		else if (record == 3) {
			if (record_3 == 0) {
				record_3++;															// 切換至第一關
			}
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
			yellow_block.SetTopLeft(SIZE_X - yellow_block.Width(), 80-23);
			gray_block_1.SetTopLeft(SIZE_X - gray_block_1.Width(), 0);
			gray_block_2.SetTopLeft(SIZE_X - gray_block_2.Width(), 160);
			yellow_block.ShowBitmap();
			gray_block_1.ShowBitmap();
			gray_block_2.ShowBitmap();
		}
		else if (record == 3) {
			yellow_block.SetTopLeft(SIZE_X - yellow_block.Width(), 160-23);
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
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
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
	if (StarBlockList != nullptr) {
		for (int i = 0;i < number_of_star_blocks;i++) {
			delete[] StarBlockList[i];
		}
		delete[] StarBlockList;
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
	Kirby.StageReSet(Kirby.GetHp());
	Map.SetTopLeft(0, -480);
	Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());

	if (StarBlockList != nullptr) {
		for (int i = 0;i < number_of_star_blocks;i++) {
			delete[] StarBlockList[i];
		}
		delete[] StarBlockList;
	}

	StarBlockList = new starBlock*[38];
	number_of_star_blocks = 38;
	starBlock** blocks = StarBlockList;
	for (int i = 0;i < 5;i++) {
		for (int n = 0;n < 5;n++) {
			blocks[i * 5 + n] = new starBlock;
			blocks[i * 5 + n]->LoadBitmap();							// StarBlock LoadBitmap setTopLeft
			blocks[i * 5 + n]->SetXY(1020 + 32 * i, SIZE_Y - 32 - 32 * n - temp_floor);
		}
	}

	StarBlockList[25] = new starBlock;
	StarBlockList[25]->LoadBitmap();
	StarBlockList[25]->SetXY(620, SIZE_Y - 32 - temp_floor);

	for (int i = 0;i < 10;i++) {
		StarBlockList[26 + i] = new starBlock;
		StarBlockList[26 + i]->LoadBitmap();
		StarBlockList[26 + i]->SetXY(1330 + 32 * i, SIZE_Y - 32 - 200 - temp_floor);
	}

	StarBlockList[36] = new starBlock;
	StarBlockList[36]->LoadBitmap();
	StarBlockList[36]->SetXY(1650, SIZE_Y - 32 - temp_floor);

	StarBlockList[37] = new starBlock;
	StarBlockList[37]->LoadBitmap();
	StarBlockList[37]->SetXY(1950, SIZE_Y - 32 - temp_floor);

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
	EnemyVector[0]->SetMap(&Map);
	EnemyVector[0]->SetThings(StarBlockList, number_of_star_blocks);

	EnemyVector.push_back(new waddleDoo);
	EnemyVector[1]->LoadBitmap();
	EnemyVector[1]->Reset();
	EnemyVector[1]->SetXy(400, SIZE_Y - temp_floor - EnemyVector[1]->GetHeight());
	EnemyVector[1]->SetMap(&Map);
	EnemyVector[1]->SetThings(StarBlockList, number_of_star_blocks);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	counter++;

	Kirby.SetCounter(counter);							// kirby get counter
	Kirby.SetMap(&Map);									// kirby get map pointer
	Kirby.SetDoor(&Door);
	Kirby.SetThings(StarBlockList, number_of_star_blocks);					// kirby get things pointer 
	Kirby.SetEnemies(EnemyVector);

	if (!Kirby.IsAlive()) {								// Kirby dead
		GotoGameState(GAME_STATE_OVER, stage, record);
	}

	Kirby.OnMove();										// Kirby OnMove
	weapon* KirbyWeapon = Kirby.GetWeapon();

	if (!EnemyVector.empty()) {
		for (unsigned int i = 0; i < EnemyVector.size();i++) {
			EnemyVector[i]->OnMove();
			if (Meet(*EnemyVector[i], Kirby)) {
				Kirby.Hurt(EnemyVector[i]->GetPower(), counter);
				EnemyVector[i]->Hurt(1, counter);
			}
			if (Meet(*KirbyWeapon, *EnemyVector[i]) && KirbyWeapon->WeaponIsShow()) {			// kirby weapon hit enemy
				EnemyVector[i]->Hurt(1, counter);
				KirbyWeapon->SetShow(false);
			}
			if (EnemyVector[i]->EnemyHasWeapon()) {
				weapon EnemyWeapon = EnemyVector[i]->GetWeapon();
				if (EnemyCanAttack(*EnemyVector[i], Kirby)) {				// enemy weapon hit kirby
					EnemyVector[i]->OnMove();								    // WaddleDoo OnMove
					EnemyVector[i]->Attack(Kirby, counter);
					if (Meet(EnemyWeapon, Kirby) && EnemyWeapon.WeaponIsShow()) {
						Kirby.Hurt(EnemyVector[i]->GetPower(), counter);
					}
				}
			}
			if (EnemyVector[i]->GetHp() > 0) {												// waddle can attack check
				if (KirbyCanAttack(Kirby, EnemyVector[i])) {
					EnemyVector[i]->Hurt(10, counter);
					Kirby.SetEaten(true);
					Kirby.SetAttack(false);
				}
			}
			if (EnemyVector[i]->GetHp() <= 0) {
				delete EnemyVector[i];
				EnemyVector.erase(EnemyVector.begin() + i);
			}
		}
	}

	kirbyHpInt.SetInteger(Kirby.GetHp());				// set integer

	if (StarBlockList != nullptr) {							// starblock can attack or not
		for (int i = 0; i < number_of_star_blocks;i++) {
			if (StarBlockList[i] != nullptr && StarBlockList[i]->GetShow()) {
				if (Meet(*KirbyWeapon, *StarBlockList[i]) && KirbyWeapon->WeaponIsShow()) {			// kirby weapon hit enemy
					KirbyWeapon->SetShow(false);
				}
				if (KirbyCanAttack(Kirby, StarBlockList[i])) {
					StarBlockList[i]->SetShow(false);
					Kirby.SetEaten(true);
					Kirby.SetAttack(false);
				}
			}
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	Map.LoadBitmap(".\\res\\map_example.bmp");			// map load and set
	Door.LoadBitmap(IDB_DOOR, RGB(255, 255, 255));
	kirbyHp.LoadBitmap(".\\res\\kirby_hpPic.bmp", RGB(236, 28, 36));
	kirbyHpInt.LoadBitmap();
	Kirby.LoadBitmap();									// Kirby LoadBitmap
	
	Map.SetTopLeft(0, -480);
	Door.SetTopLeft(2560 - 50 - Door.Width(), SIZE_Y - temp_floor - Door.Height());
	kirbyHp.SetTopLeft(0, SIZE_Y  - kirbyHp.Height());											// kirbyHp load and set
	kirbyHpInt.SetDigits(2);
	kirbyHpInt.SetTopLeft(kirbyHp.Width(), SIZE_Y - kirbyHp.Height() + 5);						// kirbyHpInt load and set

	if (!EnemyVector.empty()) {
		for (auto n : EnemyVector) {
			delete n;
		}
		EnemyVector.clear();
	}

	StarBlockList = nullptr;

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25;	// keyboard左箭頭
	const char KEY_UP    = 0x26;	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;	// keyboard右箭頭
	const char KEY_DOWN  = 0x28;	// keyboard下箭頭
	const char KEY_ESC   = 0x1B;    // keyboard esc
	const char KEY_C     = 0x43;	// keyboard C
	const char KEY_W	 = 0x57;	// keyboard W
	const char KEY_S	 = 0X53;	// keyboard S
	const char KEY_SPACE = 0x20;	// keyboard space
	const char KEY_ENTER = 0x0D;	// keyboard enter

	if (nChar == KEY_ESC) {
		GotoGameState(GAME_STATE_OVER, stage, record);
	}

	if (nChar == KEY_LEFT) {
		if (counter - last_left <= 10) {
			Kirby.SetRun(true);
		}
		else {
			last_left = counter;
		}
		Kirby.SetMovingL(true);					// Kirby moving left
		Kirby.SetFacingL(true);					// Kirby facing left
	}

	if (nChar == KEY_RIGHT) {
		if (counter - last_right <= 10) {
			Kirby.SetRun(true);
		}
		else {
			last_right = counter;
		}
		Kirby.SetMovingR(true);					// Kirby moving right
		Kirby.SetFacingR(true);					// Kirby facing right
	}

	if (nChar == KEY_DOWN) {
		Kirby.SetDown(true);
	}

	if (nChar == KEY_C) {
		Kirby.SetAttack(true);
	}

	if (nChar == KEY_W) {

		
	}

	if (nChar == KEY_S) {
		if (StarBlockList != nullptr) {
			for (int i = 0;i < number_of_star_blocks;i++) {
				StarBlockList[i]->SetShow(false);
			}
		}
	}

	if (nChar == KEY_SPACE) {
		Kirby.SetJump(true);
	}

	if (nChar == KEY_UP) {
		if (Meet(Kirby, Door)) {
			GotoGameState(GAME_STATE_RUN, GetStage() + 1, record);
		}
		else {
			Kirby.SetFly(true);
		}
	}

	if (nChar == KEY_ENTER) {
		
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25;	// keyboard左箭頭
	const char KEY_UP    = 0x26;	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;	// keyboard右箭頭
	const char KEY_DOWN  = 0x28;	// keyboard下箭頭
	const char KEY_ESC   = 0x1B;	// keyboard esc
	const char KEY_C     = 0x43;	// keyboard C
	const char KEY_O	 = 0x57;	// keyboard W
	const char KEY_S	 = 0X53;	// keyboard S
	const char KEY_SPACE = 0x20;	// keyboard space
	const char KEY_ENTER = 0x0D;	// keyboard enter

	if (nChar == KEY_LEFT) {
		Kirby.SetMovingL(false);				// Kirby stop moving left
		Kirby.SetRun(false);
	}

	if (nChar == KEY_RIGHT) {
		Kirby.SetMovingR(false);				// Kirby stop moving right
		Kirby.SetRun(false);
	}

	if (nChar == KEY_DOWN) {
		Kirby.SetDown(false);
	}

	if (nChar == KEY_C) {
		Kirby.SetAttack(false);
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
	Map.ShowBitmap();
	Door.ShowBitmap();
	
	
	
	if (!EnemyVector.empty()) {
		for (auto n : EnemyVector) {
			n->OnShow();
		}
	}
	
	if (StarBlockList != nullptr) {
		for (int i = 0;i < number_of_star_blocks;i++) {
			if (StarBlockList[i] != nullptr) {
				if (StarBlockList[i]->GetShow()) {
					StarBlockList[i]->OnShow();							// StarBlock onShow
				}
			}
		}
	}

	Kirby.OnShow();									// Kirby OnShow
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