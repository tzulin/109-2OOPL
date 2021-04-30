#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "kirby.h"

namespace game_framework {
	const int frame_of_test = 5;
	const int temp_floor = 60;
	kirby::kirby()
	{
		// kirby constructor
		const int origin_x = frame_of_test;
		const int origin_y = SIZE_Y - temp_floor - ImgH;
		const int INIT_VELOCITY = 18;
		const int INIT_FLY_VELOCITY = 9;
		const int INIT_HP = 5;
		init_velocity = INIT_VELOCITY;
		velocity = INIT_VELOCITY;
		init_fly_velocity = INIT_FLY_VELOCITY;
		fly_velocity = INIT_FLY_VELOCITY;
		hp = INIT_HP;
		x = origin_x;
		y = origin_y;
		sky_top = 0;
		floor = SIZE_Y - temp_floor;
		IsMovingL = false;
		IsMovingR = false;
		IsFacingR = true;
		IsDown = false;
		IsAttack = false;
		InAir = false;
		IsRising = true;
		IsJumping = false;
		IsFlying = false;
		IsFat = false;
		FlyUp = false;
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
		char *jump_right[10] = { ".\\res\\jump\\jumpR1.bmp", ".\\res\\jump\\jumpR2.bmp", ".\\res\\jump\\jumpR3.bmp", ".\\res\\jump\\jumpR4.bmp", ".\\res\\jump\\jumpR5.bmp", ".\\res\\jump\\jumpR6.bmp", ".\\res\\jump\\jumpR7.bmp", ".\\res\\jump\\jumpR8.bmp", ".\\res\\jump\\jumpR9.bmp", ".\\res\\jump\\jumpR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpR.AddBitmap(jump_right[i], RGB(255, 0, 0));
		}

		// load jump left
		char *jump_left[10] = { ".\\res\\jump\\jumpL1.bmp", ".\\res\\jump\\jumpL2.bmp", ".\\res\\jump\\jumpL3.bmp", ".\\res\\jump\\jumpL4.bmp", ".\\res\\jump\\jumpL5.bmp", ".\\res\\jump\\jumpL6.bmp", ".\\res\\jump\\jumpL7.bmp", ".\\res\\jump\\jumpL8.bmp", ".\\res\\jump\\jumpL9.bmp", ".\\res\\jump\\jumpL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpL.AddBitmap(jump_left[i], RGB(255, 0, 0));
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

		// load flyR
		KirbyFlyR.AddBitmap(".\\res\\fly\\flyR1.bmp", RGB(255, 0, 0));
		KirbyFlyR.AddBitmap(".\\res\\fly\\flyR2.bmp", RGB(255, 0, 0));
		KirbyFlyR.AddBitmap(".\\res\\fly\\flyR3.bmp", RGB(255, 0, 0));
		count = 3;
		while (count-- > 0) {
			KirbyFlyR.AddBitmap(".\\res\\fly\\flyR4.bmp", RGB(255, 0, 0));
		}
		KirbyFlyR.AddBitmap(".\\res\\fly\\flyR4.bmp", RGB(255, 0, 0));
		KirbyFlyR.AddBitmap(".\\res\\fly\\flyR5.bmp", RGB(255, 0, 0));

		// load flyingR
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR6.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR7.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR8.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR9.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR10.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR9.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR8.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR7.bmp", RGB(255, 0, 0));
		KirbyFlyingR.AddBitmap(".\\res\\fly\\flyR6.bmp", RGB(255, 0, 0));

		// load flyL
		KirbyFlyL.AddBitmap(".\\res\\fly\\flyL1.bmp", RGB(255, 0, 0));
		KirbyFlyL.AddBitmap(".\\res\\fly\\flyL2.bmp", RGB(255, 0, 0));
		KirbyFlyL.AddBitmap(".\\res\\fly\\flyL3.bmp", RGB(255, 0, 0));
		count = 3;
		while (count-- > 0) {
			KirbyFlyL.AddBitmap(".\\res\\fly\\flyL4.bmp", RGB(255, 0, 0));
		}
		KirbyFlyL.AddBitmap(".\\res\\fly\\flyL5.bmp", RGB(255, 0, 0));

		// load flyingL
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL6.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL7.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL8.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL9.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL10.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL9.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL8.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL7.bmp", RGB(255, 0, 0));
		KirbyFlyingL.AddBitmap(".\\res\\fly\\flyL6.bmp", RGB(255, 0, 0));
	}

	void kirby::OnShow()
	{
		switch (GetCase()) {
		// case jump up right
		case 1:
			KirbyJumpR.SetDelayCount(4);
			KirbyJumpR.SetTopLeft(x, y);
			KirbyJumpR.OnMove();
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
			KirbyScreamR.SetDelayCount(3);
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

		// case fly up right
		case 7:
			KirbyFlyR.SetDelayCount(5);
			KirbyFlyR.SetTopLeft(x, y);
			KirbyFlyR.OnMove();
			KirbyFlyR.OnShow();
			if (KirbyFlyR.IsFinalBitmap()) {
				KirbyFlyR.Reset();
			}
			break;

		// case flying right
		case 8:
			KirbyFlyingR.SetDelayCount(3);
			KirbyFlyingR.SetTopLeft(x, y);
			KirbyFlyingR.OnMove();
			KirbyFlyingR.OnShow();
			if (KirbyFlyingR.IsFinalBitmap()) {
				KirbyFlyingR.Reset();
			}
			break;

		// case jump up left
		case 9:
			KirbyJumpL.SetDelayCount(4);
			KirbyJumpL.SetTopLeft(x, y);
			KirbyJumpL.OnMove();
			KirbyJumpL.OnShow();
			break;

		// case down attack left
		case 10:
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
		case 11:
			KirbyDownL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
			KirbyDownL.ShowBitmap();
			break;

		// case scream left 
		case 12:
			KirbyScreamL.SetDelayCount(3);
			KirbyScreamL.SetTopLeft(x, y + ImgH - KirbyScreamL.Height());
			KirbyScreamL.OnMove();
			KirbyScreamL.OnShow();
			if (KirbyScreamL.IsFinalBitmap()) {
				IsAttack = false;
				KirbyScreamL.Reset();
			}
			break;

		// case walking left
		case 13:
			KirbyMovingL.SetDelayCount(2);
			KirbyMovingL.SetTopLeft(x, y);
			KirbyMovingL.OnShow();
			break;

		// case standing left
		case 14:
			KirbyStandL.SetDelayCount(3);
			KirbyStandL.SetTopLeft(x, y);
			KirbyStandL.OnShow();
			break;

		// case fly up left
		case 15:
			KirbyFlyL.SetDelayCount(5);
			KirbyFlyL.SetTopLeft(x, y);
			KirbyFlyL.OnMove();
			KirbyFlyL.OnShow();
			if (KirbyFlyL.IsFinalBitmap()) {
				KirbyFlyL.Reset();
			}
			break;

		// case flying left
		case 16:
			KirbyFlyingL.SetDelayCount(3);
			KirbyFlyingL.SetTopLeft(x, y);
			KirbyFlyingL.OnMove();
			KirbyFlyingL.OnShow();
			if (KirbyFlyingL.IsFinalBitmap()) {
				KirbyFlyingL.Reset();
			}
			break;
		}
	}

	void kirby::OnMove()
	{
		// set moving XY
		const int length = 4;

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

		// set jump and fly
		if (IsRising && InAir && !IsAttack && !IsDown) {
			if (y < sky_top) {		// �I��Ѫ�O
				IsRising = false;
			}
			if (IsJumping) {
				if (velocity > 0) {
					y -= velocity;
					velocity--;
				}
				else {
					IsRising = false;
					velocity = 1;
				}
			}
			else if (FlyUp && IsFat) {
				if (fly_velocity > 0) {
					y -= fly_velocity;
					fly_velocity--;
				}
				else {
					IsRising = false;
					FlyUp = false;
					fly_velocity = init_fly_velocity;
				}
			}
		}
		else {											// falling
			if (y < floor - frame_of_test - ImgH) {
				if (IsJumping || !IsFlying) {
					y += velocity;
					velocity++;
				}
				else if (IsFlying) {
					y++;
				}
			}
			else {
				y = floor - frame_of_test - ImgH;
				velocity = init_velocity;
				InAir = false;
				IsRising = true;
				IsJumping = false;
				KirbyJumpR.Reset();
				KirbyJumpL.Reset();
				KirbyFlyR.Reset();
				KirbyFlyL.Reset();
			}
		}

		// animation OnMove
		KirbyMovingL.OnMove();
		KirbyMovingR.OnMove();
		KirbyStand.OnMove();
		KirbyStandL.OnMove();
	}

	bool kirby::MeetEnemy(enemy e) {
		int* KirbyXy = GetXy();
		int* enemyXY = e.GetXy();

		if (enemyXY[0] > KirbyXy[0] && enemyXY[0] < KirbyXy[2]) {					// kirby meet enemy from left
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				return true;
			}
		}
		else if (enemyXY[2] > KirbyXy[0] && enemyXY[2] < KirbyXy[2]) {			// kirby meet enemy from right
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				return true;
			}
		}

		delete[] KirbyXy;
		delete[] enemyXY;
		return false;
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
		if (!IsAttack && !InAir) {
			IsDown = input;
		}
	}

	void kirby::SetAttack(bool input) {
		IsAttack = input;
		if (IsFlying) {
			SetFly(false);
		}
	}

	void kirby::SetJump(bool input) {
		if (IsJumping) {
			SetFly(true);
		}
		if (!IsFlying) {
			InAir = input;
			IsJumping = input;
		}
		else {
			SetFly(true);
		}
	}

	void kirby::SetFly(bool input) {
		if (!IsDown) {
			InAir = input;
			IsFat = input;
			FlyUp = input;
			IsRising = input;
			IsFlying = input;
		}
		if (IsJumping) {
			IsJumping = false;
		}
	}

	void kirby::SetHp(int input) {
		hp = input;
	}

	int kirby::GetCase() {
		if (IsFacingR) {
			if (IsJumping && !IsFat && !IsAttack) {
				// case jump up right
				return 1;
			}
			else if (IsDown && !IsJumping && !IsFlying && !IsFat) {
				if (IsAttack) {
					// case down attack right
					return 2;
				}
				else {
					// case down right
					return 3;
				}
			}
			else if (IsAttack && !IsJumping) {
				// case scream right
				return 4;
			}
			else if (FlyUp && !IsFat && !IsAttack && !IsDown) {
				// case fly up right
				return 7;
			}
			else if (IsFat && IsFlying && !IsAttack) {
				// case flying right
				return 8;
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
			if (IsJumping && !IsFat && !IsAttack) {
				// case jump up left
				return 9;
			}
			else if (IsDown && !IsJumping && !IsFlying) {
				if (IsAttack) {
					// case down attack left
					return 10;
				}
				else {
					// case down left
					return 11;
				}
			}
			else if (IsAttack && !IsJumping) {
				// case scream left 
				return 12;
			}
			else if (FlyUp && !IsFat && !IsAttack && !IsDown) {
				// case fly up left
				return 15;
			}
			else if (IsFat && IsFlying && !IsAttack) {
				// case flying left
				return 16;
			}
			else if (IsMovingL) {
				// case walking left 
				return 13;
			}
			else {
				// case standing left
				return 14;
			}
		}
	}

	int kirby::GetHp() {
		return hp;
	}

	int* kirby::GetXy() {
		return new int[4]{ x, y , x+ImgW, y+ImgH };
	}

	int kirby::GetWidth() {
		return ImgW;
	}

	int kirby::GetHeight() {
		return ImgH;
	}

	bool kirby::IsAlive() {
		if (hp > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool kirby::IsScreamR() {
		return IsAttack && IsFacingR && !IsDown;
	}

	bool kirby::IsScreamL() {
		return IsAttack && !IsFacingR && !IsDown;
	}
}