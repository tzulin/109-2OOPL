

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
	counter = 30 * 5; // 5 seconds
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
}

void CGameStateRun::OnBeginState()
{	
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	Kirby.OnMove();										// Kirby OnMove
	Waddle.OnMove();									// Waddle OnMove
	WaddleDoo.OnMove();								    // WaddleDoo OnMove
	if (!Kirby.IsAlive()) {								// Kirby dead
		GotoGameState(GAME_STATE_OVER);
	}
	if (Waddle.GetHp() > 0) {
		int* KirbyXy = Kirby.GetXy();
		int* WaddleXy = Waddle.GetXy();
		int x1 = KirbyXy[0], y1 = KirbyXy[1];
		int x2 = x1 + Kirby.GetWeight();
		int y2 = y1 + Kirby.GetHeight();
		int wx1 = WaddleXy[0], wy1 = WaddleXy[1];
		int wx2 = wx1 + Waddle.GetWeight();
		int wy2 = wy1 + Waddle.GetHeight();
		if (wx1 > x1 && wx1 < x2) {
			if (wy1 > y1 && wy1 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				Waddle.SetHp(Waddle.GetHp() - 1);
			}
		}else if (wx1 > x1 && wx1 < x2) {
			if (wy2 > y1 && wy2 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				Waddle.SetHp(Waddle.GetHp() - 1);
			}
		}else if (wx2 > x1 && wx2 < x2) {
			if (wy1 > y1 && wy1 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				Waddle.SetHp(Waddle.GetHp() - 1);
			}
		}else if (wx2 > x1 && wx2 < x2) {
			if (wy2 > y1 && wy2 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				Waddle.SetHp(Waddle.GetHp() - 1);
			}
		}
		delete [] KirbyXy;
		delete [] WaddleXy;
	}
	if (WaddleDoo.GetHp() > 0) {
		int* KirbyXy = Kirby.GetXy();
		int* WaddleDooXy = WaddleDoo.GetXy();
		int x1 = KirbyXy[0], y1 = KirbyXy[1];
		int x2 = x1 + Kirby.GetWeight();
		int y2 = y1 + Kirby.GetHeight();
		int wx1 = WaddleDooXy[0], wy1 = WaddleDooXy[1];
		int wx2 = wx1 + WaddleDoo.GetWeight();
		int wy2 = wy1 + WaddleDoo.GetHeight();
		if (wx1 >= x1 && wx1 <= x2) {
			if (wy1 > y1 && wy1 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				WaddleDoo.SetHp(WaddleDoo.GetHp() - 1);
			}
		}else if (wx1 > x1 && wx1 < x2) {
			if (wy2 > y1 && wy2 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				WaddleDoo.SetHp(WaddleDoo.GetHp() - 1);
			}
		}else if (wx2 > x1 && wx2 < x2) {
			if (wy1 > y1 && wy1 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				WaddleDoo.SetHp(WaddleDoo.GetHp() - 1);
			}
		}else if (wx2 > x1 && wx2 < x2) {
			if (wy2 > y1 && wy2 < y2) {
				Kirby.SetHp(Kirby.GetHp() - 1);
				WaddleDoo.SetHp(WaddleDoo.GetHp() - 1);
			}
		}
		delete [] KirbyXy;
		delete [] WaddleDooXy;
	}
	kirbyHpInt.SetInteger(Kirby.GetHp());				// set integer
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	Map.LoadBitmap(".\\res\\map_example.bmp");			// map load and set
	Map.SetTopLeft(0, 0);
	kirbyHp.LoadBitmap(".\\res\\kirby_hpPic.bmp", RGB(236, 28, 36));
	kirbyHp.SetTopLeft(0, SIZE_Y  - kirbyHp.Height());							// kirbyHp load and set
	kirbyHpInt.LoadBitmap();
	kirbyHpInt.SetDigits(2);
	kirbyHpInt.SetTopLeft(kirbyHp.Width(), SIZE_Y - kirbyHp.Height() + 5);						// kirbyHpInt load and set
	Kirby.LoadBitmap();									// Kirby LoadBitmap
	Waddle.LoadBitmap();								// Waddle LoadBitmap
	WaddleDoo.LoadBitmap();								// WaddleDoo LoadBitmap
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
		Waddle.Reset();
		WaddleDoo.Reset();
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
	kirbyHpInt.ShowBitmap();						// hp int show
	if (Waddle.GetHp() > 0) {
		Waddle.OnShow();								// Waddle OnShow
	}
	if (WaddleDoo.GetHp() > 0) {
		WaddleDoo.OnShow();								// WaddleDoo onshow
	}
	Kirby.OnShow();									// Kirby OnShow
	kirbyHp.ShowBitmap();							// kibyHp show						
}
}//namespace end