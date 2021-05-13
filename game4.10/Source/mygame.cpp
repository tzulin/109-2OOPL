

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


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
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(50,220,"Please press SPACE to begin.");
	pDC->TextOut(5,395,"Please make sure your typing mode is in English.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
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
	if (counter < 0)
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// esc 關閉遊戲		
}

void CGameStateOver::OnBeginState()
{
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
		for (int i = 0;i < 25;i++) {
			delete[] StarBlockList[i];
		}
		delete[] StarBlockList;
	}

	if (Waddle != nullptr) {
		delete Waddle;
	}
	if (WaddleDoo != nullptr) {
		delete WaddleDoo;
	}

	if (blockXys != nullptr) {				// delete blockXys
		for (int i = 0; i < 25;i++) {
			if (blockXys[i] != nullptr) {
				delete[] blockXys[i];
				blockXys[i] = nullptr;
			}
		}
		delete[] blockXys;
		blockXys = nullptr;
	}
}

void CGameStateRun::OnBeginState()
{	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	counter++;
	Kirby.SetCounter(counter);							// kirby get counter
	Kirby.SetMap(&Map);									// kirby get map pointer
	Kirby.SetThings(StarBlockTest);						// kirby get things pointer 
	Kirby.SetThings(StarBlockTest2);					// kirby get things pointer 
	if (!Kirby.IsAlive()) {								// Kirby dead
		GotoGameState(GAME_STATE_OVER);
	}

	Kirby.OnMove();										// Kirby OnMove
	weapon* KirbyWeapon = Kirby.GetWeapon();

	if (Waddle != nullptr) {
		Waddle->SetMap(&Map);
		if (Waddle->GetHp() > 0) {
			Waddle->OnMove();									// Waddle OnMove
			// kirby meet enemy
			if (Meet(*Waddle, Kirby)) {
				Kirby.Hurt(Waddle->GetPower(), counter);
				Waddle->Hurt(1, counter);
			}
			// kirby weapon hit enemy
			if (Meet(*KirbyWeapon, *Waddle) && KirbyWeapon->WeaponIsShow()) {
				Waddle->Hurt(1, counter);
				KirbyWeapon->SetShow(false);
			}
		}
	}
	if (WaddleDoo != nullptr) {
		WaddleDoo->SetMap(&Map);
		weapon WaddleDooWeapon = WaddleDoo->GetWeapon();
		if (WaddleDoo->GetHp() > 0) {
			WaddleDoo->OnMove();								    // WaddleDoo OnMove
			// kirby meet enemy
			if (Meet(*WaddleDoo, Kirby)) {
				Kirby.Hurt(WaddleDoo->GetPower(), counter);
				WaddleDoo->Hurt(1, counter);
			}
			// kirby weapon hit enemy
			if (Meet(*KirbyWeapon, *WaddleDoo) && KirbyWeapon->WeaponIsShow()) {
				WaddleDoo->Hurt(1, counter);
				KirbyWeapon->SetShow(false);
			}
			// enemy weapon hit kirby
			if (EnemyCanAttack(*WaddleDoo, Kirby)) {
				WaddleDoo->OnMove();								    // WaddleDoo OnMove
				WaddleDoo->Attack(Kirby, counter);
				if (Meet(WaddleDooWeapon, Kirby) && WaddleDooWeapon.WeaponIsShow()) {
					Kirby.Hurt(WaddleDoo->GetPower(), counter);
				}
			}
		}
	}

	kirbyHpInt.SetInteger(Kirby.GetHp());				// set integer

	// enemy block by  StarBlock
	if (Waddle != nullptr) {
		if (StarBlockTest != nullptr) {
			if (Meet(*Waddle, *StarBlockTest)) {
				Waddle->MeetBlock();
			}
		}
		if (StarBlockTest2 != nullptr) {
			if (Meet(*Waddle, *StarBlockTest2)) {
				Waddle->MeetBlock();
			}
		}
	}
	if (WaddleDoo != nullptr) {
		if (StarBlockTest != nullptr) {
			if (Meet(*WaddleDoo, *StarBlockTest)) {
				WaddleDoo->MeetBlock();
			}
		}
		if (StarBlockTest2 != nullptr) {
			if (Meet(*WaddleDoo, *StarBlockTest2)) {
				WaddleDoo->MeetBlock();
			}
		}
	}

	/*
	if (Waddle != nullptr) {
		if (StarBlockList != nullptr) {
			for (int i = 0; i < 25; i++) {
				if (StarBlockList[i] != nullptr) {
					if (Meet(*Waddle, *StarBlockList[i])) {
						Waddle->MeetBlock();
					}
				}
			}
		}
	}
	*/

	if (StarBlockList != nullptr) {							// starblock can attack or not
		for (int i = 0; i < 25;i++) {
			if (StarBlockList[i] != nullptr) {
				if (KirbyCanAttack(Kirby, StarBlockList[i])) {
					StarBlockList[i]->SetShow(false);
					Kirby.SetEaten(true);
					Kirby.SetAttack(false);
					delete[] StarBlockList[i];
					StarBlockList[i] = nullptr;
				}
				else {
					StarBlockList[i]->SetShow(true);
				}
			}
		}
	}


	
	if (StarBlockList != nullptr) {			// get blockXys
		blockXys = new int*[25];
		for (int i = 0; i < 25;i++) {
			if (StarBlockList[i] != nullptr) {
				blockXys[i] = StarBlockList[i]->GetXy();
			}
			else {
				blockXys[i] = nullptr;
			}
		}
	}

	Kirby.SetBlockers(blockXys, 25);

	if (blockXys != nullptr) {				// delete blockXys
		for (int i = 0; i < 25;i++) {
			if (blockXys[i] != nullptr) {
				delete[] blockXys[i];
				blockXys[i] = nullptr;
			}
		}
		delete[] blockXys;
		blockXys = nullptr;
	}
	

	if (Waddle != nullptr) {												// waddle can attack check
		if (KirbyCanAttack(Kirby, Waddle)) {
			Kirby.SetEaten(true);
			Kirby.SetAttack(false);
			delete Waddle;
			Waddle = nullptr;
		}
	}

	if (WaddleDoo != nullptr) {											// waddledoo can attack check
		if (KirbyCanAttack(Kirby, WaddleDoo)) {
			Kirby.SetEaten(true);
			Kirby.SetAttack(false);
			delete WaddleDoo;
			WaddleDoo = nullptr;
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	Map.LoadBitmap(".\\res\\map_example.bmp");			// map load and set
	Map.SetTopLeft(0, -480);
	kirbyHp.LoadBitmap(".\\res\\kirby_hpPic.bmp", RGB(236, 28, 36));
	kirbyHp.SetTopLeft(0, SIZE_Y  - kirbyHp.Height());											// kirbyHp load and set
	kirbyHpInt.LoadBitmap();
	kirbyHpInt.SetDigits(2);
	kirbyHpInt.SetTopLeft(kirbyHp.Width(), SIZE_Y - kirbyHp.Height() + 5);						// kirbyHpInt load and set
	Kirby.LoadBitmap();									// Kirby LoadBitmap
	
	StarBlockTest = new starBlock;
	StarBlockTest2 = new starBlock;
	StarBlockTest->LoadBitmap();
	StarBlockTest2->LoadBitmap();
	int* StarBlockTestHw = StarBlockTest->GetHw();
	int* StarBlockTestHw2 = StarBlockTest2->GetHw();
	StarBlockTest->SetXY(100, SIZE_Y - StarBlockTestHw[0] - temp_floor);
	StarBlockTest2->SetXY(100+SIZE_X/2, SIZE_Y - StarBlockTestHw2[0] -temp_floor);
	delete[] StarBlockTestHw;
	delete[] StarBlockTestHw2;

	Waddle = nullptr;
	WaddleDoo = nullptr;
	StarBlockList = nullptr;
	blockXys = nullptr;
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

	if (nChar == KEY_ESC) {
		GotoGameState(GAME_STATE_OVER);
	}

	if (nChar == KEY_LEFT) {
		Kirby.SetMovingL(true);					// Kirby moving left
		Kirby.SetFacingL(true);					// Kirby facing left
	}

	if (nChar == KEY_RIGHT) {
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
		if (Waddle != nullptr) {
			delete Waddle;
		}
		if (WaddleDoo != nullptr) {
			delete WaddleDoo;
		}
		Waddle = new waddle;
		WaddleDoo = new waddleDoo;
		Waddle->LoadBitmap();								// Waddle LoadBitmap
		WaddleDoo->LoadBitmap();							// WaddleDoo LoadBitmap
		Waddle->Reset();
		WaddleDoo->Reset();
	}

	if (nChar == KEY_S) {
		if (StarBlockList != nullptr) {
			for (int i = 0;i < 25;i++) {
				if (StarBlockList[i] != nullptr) {
					delete[] StarBlockList[i];
				}
			}
			delete[] StarBlockList;
		}
		StarBlockList = new starBlock*[25];
		starBlock** blocks = StarBlockList;
		for (int i = 0;i < 5;i++) {
			for (int n = 0;n < 5;n++) {
				blocks[i * 5 + n] = new starBlock;
				blocks[i * 5 + n]->LoadBitmap();							// StarBlock LoadBitmap setTopLeft
				blocks[i * 5 + n]->SetXY(SIZE_X/2 + 32*i, SIZE_Y - 32*n - temp_floor);
			}
		}
	}

	if (nChar == KEY_SPACE) {
		Kirby.SetJump(true);
	}

	if (nChar == KEY_UP) {
		Kirby.SetFly(true);
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
	const char KEY_S = 0X53;	// keyboard S
	const char KEY_SPACE = 0x20;	// keyboard space

	if (nChar == KEY_LEFT) {
		Kirby.SetMovingL(false);				// Kirby stop moving left
	}

	if (nChar == KEY_RIGHT) {
		Kirby.SetMovingR(false);				// Kirby stop moving right
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
	StarBlockTest->OnShow();
	StarBlockTest2->OnShow();
	kirbyHpInt.ShowBitmap();						// hp int show
	
	if (Waddle != nullptr) {
		if (Waddle->GetHp() > 0) {
			Waddle->OnShow();								// Waddle OnShow
		}
	}
	if (WaddleDoo != nullptr) {
		if (WaddleDoo->GetHp() > 0) {
			WaddleDoo->OnShow();								// WaddleDoo onshow
		}
	}
	
	Kirby.OnShow();									// Kirby OnShow
	kirbyHp.ShowBitmap();							// kibyHp show	

	
	if (StarBlockList != nullptr) {
		for (int i = 0;i < 25;i++) {
			if (StarBlockList[i] != nullptr) {
				if (StarBlockList[i]->GetShow()) {
					StarBlockList[i]->OnShow();							// StarBlock onShow
				}
			}
		}
	}
	
}
}//namespace end