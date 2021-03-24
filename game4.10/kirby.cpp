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
		const int INIT_VELOCITY = 18;
		init_velocity = INIT_VELOCITY;
		x = origin_x;
		y = origin_y;
		floor = SIZE_Y;
		IsMovingL = false;
		IsMovingR = false;
		IsFacingR = true;
		IsDown = false;
		IsAttack = false;
		InAir = false;
		IsRising = true;
	}

	kirby::~kirby()
	{
	}

	void kirby::LoadBitmap()
	{	
		// load walk left
		char *walk_left[10] = { ".\\res\\walk\\walkL1.bmp", ".\\res\\walk\\walkL2.bmp", ".\\res\\walk\\walkL3.bmp", ".\\res\\walk\\walkL4.bmp", ".\\res\\walk\\walkL5.bmp", ".\\res\\walk\\walkL6.bmp", ".\\res\\walk\\walkL7.bmp", ".\\res\\walk\\walkL8.bmp", ".\\res\\walk\\walkL9.bmp", ".\\res\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingL.AddBitmap(walk_left[i], RGB(255, 0, 0));
		}

		// load walk right
		char *walk_right[10] = { ".\\res\\walk\\walkR1.bmp", ".\\res\\walk\\walkR2.bmp", ".\\res\\walk\\walkR3.bmp", ".\\res\\walk\\walkR4.bmp", ".\\res\\walk\\walkR5.bmp", ".\\res\\walk\\walkR6.bmp", ".\\res\\walk\\walkR7.bmp", ".\\res\\walk\\walkR8.bmp", ".\\res\\walk\\walkR9.bmp", ".\\res\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingR.AddBitmap(walk_right[i], RGB(255, 0, 0));
		}

		// load stand and wink right
		int count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(IDB_STAND, RGB(255, 0, 0));
		}
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 0, 0));
		count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(IDB_STAND, RGB(255, 0, 0));
		}
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 0, 0));
		KirbyStand.AddBitmap(IDB_STAND, RGB(255, 0, 0));
		KirbyStand.AddBitmap(IDB_CLOSE_EYES, RGB(255, 0, 0));	

		// load stand and wink left
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 0, 0));
		}
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 0, 0));
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 0, 0));
		}
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 0, 0));
		KirbyStandL.AddBitmap(IDB_STANDL, RGB(255, 0, 0));
		KirbyStandL.AddBitmap(IDB_CLOSE_EYES_L, RGB(255, 0, 0));	

		// load down right and left
		KirbyDownR.LoadBitmap(IDB_DOWNR1, RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(IDB_DOWNL1, RGB(255, 255, 255));

		// load down attack right and left
		KirbyDownAttackR.LoadBitmap(IDB_DOWNR2, RGB(255, 255, 255));
		KirbyDownAttackL.LoadBitmap(IDB_DOWNL2, RGB(255, 255, 255));

		// load jump right
		for (int i = 0; i < 5; i++)
		{
			KirbyJumpR.AddBitmap(".\\res\\jump\\jumpR1.bmp", RGB(255, 0, 0));
		}
		// 空中翻滾 先不要
		// char *jump_right[10] = { ".\\res\\jump\\jumpR1.bmp", ".\\res\\jump\\jumpR2.bmp", ".\\res\\jump\\jumpR3.bmp", ".\\res\\jump\\jumpR4.bmp", ".\\res\\jump\\jumpR5.bmp", ".\\res\\jump\\jumpR6.bmp", ".\\res\\jump\\jumpR7.bmp", ".\\res\\jump\\jumpR8.bmp", ".\\res\\jump\\jumpR9.bmp", ".\\res\\jump\\jumpR10.bmp"};
		// for (int i = 0; i < 10; i++)
		// {
		// 	KirbyJumpR.AddBitmap(jump_right[i], RGB(255, 0, 0));
		// }

		// load jump left
		for (int i = 0; i < 5; i++)
		{
			KirbyJumpL.AddBitmap(".\\res\\jump\\jumpL1.bmp", RGB(255, 0, 0));
		}
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
			}
			else if (InAir) {
				// show jump up
				KirbyJumpR.SetTopLeft(x, y);
				KirbyJumpR.OnShow();
			}
			else if (IsMovingR) {
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
			}
			else if (InAir) {
				// show jump up
				KirbyJumpL.SetTopLeft(x, y);
				KirbyJumpL.OnShow();
			}
			else if (IsMovingL) {
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

		if (IsRising && InAir) {
			if (velocity > 0) {
				y -= velocity;
				velocity--;
			}
			else {
				IsRising = false;
				velocity = 1;
			}
		}
		else {
			if (y < floor - frame_of_test - ImgH) {
				y += velocity;
				velocity++;
			}
			else {
				y = floor - frame_of_test - ImgH;
				velocity = init_velocity;
				IsRising = true;
				InAir = false;
				KirbyJumpR.Reset();
				KirbyJumpL.Reset();
			}
		}

		// animation OnMove
		KirbyJumpR.OnMove();
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

	void kirby::SetJump(bool input) {
		InAir = input;
	}

}