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
		count = 3;
		while (count-- > 0) {
			KirbyDownAttackR.AddBitmap(IDB_DOWNR2, RGB(255, 255, 255));
			KirbyDownAttackL.AddBitmap(IDB_DOWNL2, RGB(255, 255, 255));
		}

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

		// load scream right and left
		KirbyScreamR.AddBitmap(IDB_SCREAMR1, RGB(255, 255, 255));
		count = 6;
		while (count-- > 0) {
			KirbyScreamR.AddBitmap(IDB_SCREAMR2, RGB(255, 255, 255));
		}
		count = 6;
		while (count-- > 0) {
			KirbyScreamR.AddBitmap(IDB_SCREAMR3, RGB(255, 255, 255));
			KirbyScreamR.AddBitmap(IDB_SCREAMR4, RGB(255, 255, 255));
		}
		count = 5;
		while (count-- > 0) {
			KirbyScreamR.AddBitmap(IDB_SCREAMR2, RGB(255, 255, 255));
		}
		KirbyScreamR.AddBitmap(IDB_SCREAMR5, RGB(255, 255, 255));

		KirbyScreamL.AddBitmap(IDB_SCREAML1, RGB(255, 255, 255));
		count = 6;
		while (count-- > 0) {
			KirbyScreamL.AddBitmap(IDB_SCREAML2, RGB(255, 255, 255));
		}
		count = 6;
		while (count-- > 0) {
			KirbyScreamL.AddBitmap(IDB_SCREAML3, RGB(255, 255, 255));
			KirbyScreamL.AddBitmap(IDB_SCREAML4, RGB(255, 255, 255));
		}
		count = 5;
		while (count-- > 0) {
			KirbyScreamL.AddBitmap(IDB_SCREAML2, RGB(255, 255, 255));
		}
		KirbyScreamL.AddBitmap(IDB_SCREAML5, RGB(255, 255, 255));
	}

	void kirby::OnShow()
	{
		/*
        //facing right
		if (IsFacingR) {
			if (IsDown) {
				if (IsAttack) {
					// show down attack right
					KirbyDownAttackR.SetDelayCount(5);
					KirbyDownAttackR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
					KirbyDownAttackR.OnMove();
					KirbyDownAttackR.OnShow();
					if (KirbyDownAttackR.IsFinalBitmap()) {
						IsAttack = false;
						KirbyDownAttackR.Reset();
					}
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
			else if (IsAttack) {
				// show scream right
				KirbyScreamR.SetDelayCount(5);
				KirbyScreamR.SetTopLeft(x, y + ImgH - KirbyScreamR.Height());
				KirbyScreamR.OnMove();
				KirbyScreamR.OnShow();
				if (KirbyScreamR.IsFinalBitmap()) {
					IsAttack = false;
					KirbyScreamR.Reset();
				}
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
					KirbyDownAttackL.SetDelayCount(5);
					KirbyDownAttackL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
					KirbyDownAttackL.OnMove();
					KirbyDownAttackL.OnShow();
					if (KirbyDownAttackL.IsFinalBitmap()) {
						IsAttack = false;
						KirbyDownAttackL.Reset();
					}
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
			else if (IsAttack) {
				// show scream left
				KirbyScreamL.SetDelayCount(5);
				KirbyScreamL.SetTopLeft(x, y + ImgH - KirbyScreamR.Height());
				KirbyScreamL.OnMove();
				KirbyScreamL.OnShow();
				if (KirbyScreamL.IsFinalBitmap()) {
					IsAttack = false;
					KirbyScreamL.Reset();
				}
			}
			else if (IsMovingL) {
				// show walking left 
				KirbyMovingL.SetDelayCount(2);
				KirbyMovingL.SetTopLeft(x, y);
				KirbyMovingL.OnShow();
			}
			else {
				// show standing left
				KirbyStandL.SetDelayCount(3);
				KirbyStandL.SetTopLeft(x, y);
				KirbyStandL.OnShow();
			}
		}*/
		switch (GetCase()) {
		// case jump up right
		case 1:
			KirbyJumpR.SetTopLeft(x, y);
			KirbyJumpR.OnShow();
			break;

		// case down attack right
		case 2:
			KirbyDownAttackR.SetDelayCount(5);
			KirbyDownAttackR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
			KirbyDownAttackR.OnMove();
			KirbyDownAttackR.OnShow();
			if (KirbyDownAttackR.IsFinalBitmap()) {
				IsAttack = false;
				KirbyDownAttackR.Reset();
			}
			break;

		// case down right
		case 3:
			KirbyDownR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
			KirbyDownR.ShowBitmap();
			break;

		// case scream right
		case 4:
			KirbyScreamR.SetDelayCount(5);
			KirbyScreamR.SetTopLeft(x, y + ImgH - KirbyScreamR.Height());
			KirbyScreamR.OnMove();
			KirbyScreamR.OnShow();
			if (KirbyScreamR.IsFinalBitmap()) {
				IsAttack = false;
				KirbyScreamR.Reset();
			}
			break;

		// case walking right
		case 5:
			KirbyMovingR.SetDelayCount(2);
			KirbyMovingR.SetTopLeft(x, y);
			KirbyMovingR.OnShow();
			break;

		// case standing right
		case 6:
			KirbyStand.SetDelayCount(3);
			KirbyStand.SetTopLeft(x, y);
			KirbyStand.OnShow();
			break;

		// case jump up left
		case 7:
			KirbyJumpL.SetTopLeft(x, y);
			KirbyJumpL.OnShow();
			break;

		// case down attack left
		case 8:
			KirbyDownAttackL.SetDelayCount(5);
			KirbyDownAttackL.SetTopLeft(x, y + ImgH - KirbyDownAttackL.Height());
			KirbyDownAttackL.OnMove();
			KirbyDownAttackL.OnShow();
			if (KirbyDownAttackL.IsFinalBitmap()) {
				IsAttack = false;
				KirbyDownAttackL.Reset();
			}
			break;

		// case down left
		case 9:
			KirbyDownL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
			KirbyDownL.ShowBitmap();
			break;

		// case scream left 
		case 10:
			KirbyScreamL.SetDelayCount(5);
			KirbyScreamL.SetTopLeft(x, y + ImgH - KirbyScreamL.Height());
			KirbyScreamL.OnMove();
			KirbyScreamL.OnShow();
			if (KirbyScreamL.IsFinalBitmap()) {
				IsAttack = false;
				KirbyScreamL.Reset();
			}
			break;

		// case walking left
		case 11:
			KirbyMovingL.SetDelayCount(2);
			KirbyMovingL.SetTopLeft(x, y);
			KirbyMovingL.OnShow();
			break;

		// case standing left
		case 12:
			KirbyStandL.SetDelayCount(3);
			KirbyStandL.SetTopLeft(x, y);
			KirbyStandL.OnShow();
			break;
		}
	}

	void kirby::OnMove()
	{
		// set moving XY
		const int length = 2;

		// set moving XY and frame of test 
		if (IsMovingL && !IsDown && !IsAttack && x > frame_of_test) {
			if (IsFacingR) {
				IsFacingR = false;
			}
			x -= length;
		}

		if (IsMovingR && !IsDown && !IsAttack && x < SIZE_X - ImgW - frame_of_test) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			x += length;
		}

		// set down attack right and left
		if (IsDown && IsAttack) {
			if (IsFacingR && x < SIZE_X - ImgW - frame_of_test) {
				x += length * 3;
			}
			else if (x > frame_of_test) {
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
		/*KirbyScreamR.OnMove();
		KirbyScreamL.OnMove();
		KirbyDownAttackR.OnMove();
		KirbyDownAttackL.OnMove();
		*/
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

	int kirby::GetCase() {
		if (IsFacingR) {
			if (InAir) {
				// case jump up right
				return 1;
			}
			else if (IsDown) {
				if (IsAttack) {
					// case down attack right
					return 2;
				}
				else {
					// case down right
					return 3;
				}
			}
			else if (IsAttack) {
				// case scream right
				return 4;
			}
			else if (IsMovingR) {
				// case walking right
				return 5;
			}
			else {
				// case standing right
				return 6;
			}
		}
		else {
			// facing left
			if (InAir) {
				// case jump up left
				return 7;
			}
			else if (IsDown) {
				if (IsAttack) {
					// case down attack left
					return 8;
				}
				else {
					// case down left
					return 9;
				}
			}
			else if (IsAttack) {
				// case scream left 
				return 10;
			}
			else if (IsMovingL) {
				// case walking left 
				return 11;
			}
			else {
				// case standing left
				return 12;
			}
		}
	}
}