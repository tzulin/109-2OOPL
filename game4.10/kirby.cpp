#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "kirby.h"

namespace game_framework {
	kirby::kirby()
	{
		const int origin_x = 5;
		const int origin_y = SIZE_Y - 5 - ImgH;
		x = origin_x;
		y = origin_y;
		IsMovingLeft = false;
		IsMovingRight = false;
		IsFacingRight = true;
		IsDown = false;
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

		KirbyDownR.LoadBitmap(IDB_1, RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(IDB_2, RGB(255, 255, 255));
		
	}

	void kirby::OnShow()
	{
		// facing right
		if (IsFacingRight) {
			if (IsDown) {
				KirbyDownR.SetTopLeft(x, y);
				KirbyDownR.ShowBitmap();
			}else
			// show walking right
			if (IsMovingRight) {
				KirbyMovingR.SetDelayCount(3);
				KirbyMovingR.SetTopLeft(x, y);
				KirbyMovingR.OnShow();
			}
			else {
				// show standing right
				KirbyStand.SetDelayCount(3);
				KirbyStand.SetTopLeft(x, y);
				KirbyStand.OnShow();
			}
		}
		else {
			// facing left
			if (IsDown) {
				KirbyDownL.SetTopLeft(x, y);
				KirbyDownL.ShowBitmap();
			}else
			if (IsMovingLeft) {
				// show walking left 
				KirbyMovingL.SetDelayCount(3);
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
		const int length = 3;

		if (IsMovingLeft && x > 5 && !IsDown) {
			x -= length;
		}
		if (IsMovingRight && x < SIZE_X - ImgW && !IsDown) {
			x += length;
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

	void  kirby::SetMovingLeft(bool input) {
		IsMovingLeft = input;
	}

	void kirby::SetMovingRight(bool input) {
		IsMovingRight = input;
	}

	void kirby::SetFacingRight(bool input) {
		IsFacingRight = true;
	}

	void kirby::SetFacingLeft(bool input) {
		IsFacingRight = false;
	}

	void kirby::SetDown(bool input) {
		IsDown = input;
	}
}