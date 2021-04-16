

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

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
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	//logo.LoadBitmap(IDB_BACKGROUND);
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	//logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	//logo.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(50,220,"Please press SPACE to begin.");
	pDC->TextOut(5,395,"Please make sure your typing mode is in English.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
	if (counter < 0)
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// esc �����C��		
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
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
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
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
}

void CGameStateRun::OnBeginState()
{	
}

void CGameStateRun::OnMove()							// ���ʹC������
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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
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
	const char KEY_LEFT  = 0x25;	// keyboard���b�Y
	const char KEY_UP    = 0x26;	// keyboard�W�b�Y
	const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
	const char KEY_DOWN  = 0x28;	// keyboard�U�b�Y
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
	const char KEY_LEFT  = 0x25;	// keyboard���b�Y
	const char KEY_UP    = 0x26;	// keyboard�W�b�Y
	const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
	const char KEY_DOWN  = 0x28;	// keyboard�U�b�Y
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