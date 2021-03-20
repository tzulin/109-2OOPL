#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "kirby.h"

namespace game_framework {
	const int frame_of_test = 5;
	kirby::kirby()
	{
		// kirby constructor
		const int origin_x = frame_of_test;
		const int origin_y = SIZE_Y - frame_of_test - ImgH;
		x = origin_x;
		y = origin_y;
		IsMovingL = false;
		IsMovingR = false;
		IsFacingR = true;
		IsDown = false;
		IsAttack = false;
	}

	kirby::~kirby()
	{
	}

	void kirby::LoadBitmap()
	{	
		// load walk left
		char *filename[10] = { ".\\res\\walkL1.bmp", ".\\res\\walkL2.bmp", ".\\res\\walkL3.bmp", ".\\res\\walkL4.bmp", ".\\res\\walkL5.bmp", ".\\res\\walkL6.bmp", ".\\res\\walkL7.bmp", ".\\res\\walkL8.bmp", ".\\res\\walkL9.bmp", ".\\res\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingL.AddBitmap(filename[i], RGB(255, 255, 255));
		}
		
		// load walk right
		KirbyMovingR.AddBitmap(IDB_WALKR1, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR2, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR3, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR4, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR5, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR6, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR7, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR8, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR9, RGB(255, 255, 255));
		KirbyMovingR.AddBitmap(IDB_WALKR10, RGB(255, 255, 255));	
		
		// load stand and wink right
		int count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(IDB_STAND, RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(IDB_STAND, RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 255, 255));
		KirbyStand.AddBitmap(IDB_STAND, RGB(255, 255, 255));
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 255, 255));	

		// load stand left
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 255, 255));
		KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 255, 255));
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 255, 255));	

		// load down right and left
		KirbyDownR.LoadBitmap(IDB_DOWNR1, RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(IDB_DOWNL1, RGB(255, 255, 255));

		// load down attack right and left
		KirbyDownAttackR.LoadBitmap(IDB_DOWNR2, RGB(255, 255, 255));
		KirbyDownAttackL.LoadBitmap(IDB_DOWNL2, RGB(255, 255, 255));
	}

	void kirby::OnShow()
	{
		// facing right
		if (IsFacingR) {
			if (IsDown) {
				if (IsAttack) {
					// show down attack right
					KirbyDownAttackR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
					KirbyDownAttackR.ShowBitmap();
				}
				else {			
					// show down
					KirbyDownR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
					KirbyDownR.ShowBitmap();
				}
			}else if (IsMovingR) {		
				// show walking right
				KirbyMovingR.SetDelayCount(2);
				KirbyMovingR.SetTopLeft(x, y);
				KirbyMovingR.OnShow();
			}
			else {
				// show standing right
				KirbyStand.SetDelayCount(3);
				KirbyStand.SetTopLeft(x, y);
				KirbyStand.OnShow();
			}
		}else {
			// facing left
			if (IsDown) {
				if (IsAttack) {
					// show down attack left
					KirbyDownAttackL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
					KirbyDownAttackL.ShowBitmap();
				}
				else {
					// show down
					KirbyDownL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
					KirbyDownL.ShowBitmap();
				}
			}else if (IsMovingL) {
				// show walking left 
				KirbyMovingL.SetDelayCount(2);
				KirbyMovingL.SetTopLeft(x, y);
				KirbyMovingL.OnShow();
			}
			else {
				// show standing right
				KirbyStandL.SetDelayCount(3);
				KirbyStandL.SetTopLeft(x, y);
				KirbyStandL.OnShow();
			}
		}
	}

	void kirby::OnMove()
	{
		// set moving XY
		const int length = 2;

		// set moving XY and frame of test 
		if (IsMovingL && !IsDown && x > frame_of_test) {
			if (IsFacingR) {
				IsFacingR = false;
			}
			x -= length;
		}

		if (IsMovingR && !IsDown && x < SIZE_X - ImgW - frame_of_test) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			x += length;
		}

		if (IsDown && IsAttack) {
			if (IsFacingR) {
				x += length * 3;
			}
			else {
				x -= length * 3;
			}
		}

		// animation OnMove
		KirbyMovingL.OnMove();
		KirbyMovingR.OnMove();
		KirbyStand.OnMove();
		KirbyStandL.OnMove();
	}

	void kirby::SetXY(int x_in, int y_in) {
		x = x_in;
		y = y_in;
	}

	void  kirby::SetMovingL(bool input) {
		IsMovingL = input;
	}

	void kirby::SetMovingR(bool input) {
		IsMovingR = input;
	}

	void kirby::SetFacingR(bool input) {
		IsFacingR = input;
	}

	void kirby::SetFacingL(bool input) {
		IsFacingR = !input;
	}

	void kirby::SetDown(bool input) {
		IsDown = input;
	}

	void kirby::SetAttack(bool input) {
		IsAttack = input;
	}
}