
#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
//#include "kirby.h"
#include "Header.h"

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
		const int INIT_HP = 10;
		BoundaryTop = SIZE_Y / 2;
		BoundaryLeft = SIZE_X / 2;
		BoundaryRight = 2560 - BoundaryLeft;
		now_img_h = ImgH;
		now_img_w = ImgW;
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
		LastHurt = 0;
		IsHurt = false;
		IsEaten = false;
		OtherFromL = false;
		YouAreGround = true;
		StarBlockList = nullptr;
		IsRun = false;
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

		// load fat walk left
		char *fat_walk_left[8] = { ".\\res\\walk\\fat_walkL1.bmp", ".\\res\\walk\\fat_walkL2.bmp", ".\\res\\walk\\fat_walkL3.bmp", ".\\res\\walk\\fat_walkL4.bmp", ".\\res\\walk\\fat_walkL5.bmp", ".\\res\\walk\\fat_walkL6.bmp", ".\\res\\walk\\fat_walkL7.bmp", ".\\res\\walk\\fat_walkL8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			KirbyFatMovingL.AddBitmap(fat_walk_left[i], RGB(255, 255, 255));
		}

		// load fat walk right
		char *fat_walk_right[8] = { ".\\res\\walk\\fat_walkR1.bmp", ".\\res\\walk\\fat_walkR2.bmp", ".\\res\\walk\\fat_walkR3.bmp", ".\\res\\walk\\fat_walkR4.bmp", ".\\res\\walk\\fat_walkR5.bmp", ".\\res\\walk\\fat_walkR6.bmp", ".\\res\\walk\\fat_walkR7.bmp", ".\\res\\walk\\fat_walkR8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			KirbyFatMovingR.AddBitmap(fat_walk_right[i], RGB(255, 255, 255));
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

		// load fat stand and wink right
		count = 12;
		while (count-- > 0) {
			KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR2.bmp", RGB(255, 255, 255));

		count = 12;
		while (count-- > 0) {
			KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR1.bmp", RGB(255, 255, 255));

		}
		KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR2.bmp", RGB(255, 255, 255));
		KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR1.bmp", RGB(255, 255, 255));
		KirbyFatStand.AddBitmap(".\\res\\basic\\fat_basicR2.bmp", RGB(255, 255, 255));

		// load fat stand and wink left
		count = 12;
		while (count-- > 0) {
			KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL2.bmp", RGB(255, 255, 255));

		count = 12;
		while (count-- > 0) {
			KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL1.bmp", RGB(255, 255, 255));

		}
		KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL2.bmp", RGB(255, 255, 255));
		KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL1.bmp", RGB(255, 255, 255));
		KirbyFatStandL.AddBitmap(".\\res\\basic\\fat_basicL2.bmp", RGB(255, 255, 255));

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

		// load hurtR
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR1.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR2.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR3.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR5.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR6.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR7.bmp", RGB(255, 255, 255));
		KirbyHurtR.AddBitmap(".\\res\\hurt\\hurtR8.bmp", RGB(255, 255, 255));

		// load hurtL
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL1.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL2.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL3.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL5.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL6.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL7.bmp", RGB(255, 255, 255));
		KirbyHurtL.AddBitmap(".\\res\\hurt\\hurtL8.bmp", RGB(255, 255, 255));

		// load Star Throw
		int rgb[3] = {0, 0, 0};
		StarThrow.LoadBitmap(IDB_STARTHROW, rgb, 100);
}

	void kirby::OnShow()
	{
		if (StarThrow.WeaponIsShow()) {
			StarThrow.OnShow();
		}
		
		switch (GetCase()) {
		// case jump up right
		case 1:
			KirbyJumpR.SetDelayCount(4);
			now_img_h = KirbyJumpR.Height();
			now_img_w = KirbyJumpR.Width();
			KirbyJumpR.SetTopLeft(x, y);
			KirbyJumpR.OnMove();
			KirbyJumpR.OnShow();
			break;

		// case down attack right
		case 2:
			KirbyDownAttackR.SetDelayCount(5);
			now_img_h = KirbyDownAttackR.Height();
			now_img_w = KirbyDownAttackR.Width();
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
			now_img_h = KirbyDownR.Height();
			now_img_w = KirbyDownR.Width();
			KirbyDownR.SetTopLeft(x, y + ImgH - KirbyDownR.Height());
			KirbyDownR.ShowBitmap();
			break;

		// case scream right
		case 4:
			KirbyScreamR.SetDelayCount(3);
			now_img_h = KirbyScreamR.Height();
			now_img_w = KirbyScreamR.Width();
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
			now_img_h = KirbyMovingR.Height();
			now_img_w = KirbyMovingR.Width();
			KirbyMovingR.SetTopLeft(x, y);
			KirbyMovingR.OnShow();
			break;

		// case standing right
		case 6:
			KirbyStand.SetDelayCount(3);
			now_img_h = KirbyStand.Height();
			now_img_w = KirbyStand.Width();
			KirbyStand.SetTopLeft(x, y);
			KirbyStand.OnShow();
			break;

		// case fly up right
		case 7:
			KirbyFlyR.SetDelayCount(5);
			now_img_h = KirbyFlyR.Height();
			now_img_w = KirbyFlyR.Width();
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
			now_img_h = KirbyFlyingR.Height();
			now_img_w = KirbyFlyingR.Width();
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
			now_img_h = KirbyJumpL.Height();
			now_img_w = KirbyJumpL.Width();
			KirbyJumpL.SetTopLeft(x, y);
			KirbyJumpL.OnMove();
			KirbyJumpL.OnShow();
			break;

		// case down attack left
		case 10:
			KirbyDownAttackL.SetDelayCount(5);
			now_img_h = KirbyDownAttackL.Height();
			now_img_w = KirbyDownAttackL.Width();
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
			now_img_h = KirbyDownL.Height();
			now_img_w = KirbyDownL.Width();
			KirbyDownL.SetTopLeft(x, y + ImgH - KirbyDownL.Height());
			KirbyDownL.ShowBitmap();
			break;

		// case scream left 
		case 12:
			KirbyScreamL.SetDelayCount(3);
			now_img_h = KirbyScreamL.Height();
			now_img_w = KirbyScreamL.Width();
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
			now_img_h = KirbyMovingL.Height();
			now_img_w = KirbyMovingL.Width();
			KirbyMovingL.SetTopLeft(x, y);
			KirbyMovingL.OnShow();
			break;

		// case standing left
		case 14:
			KirbyStandL.SetDelayCount(3);
			now_img_h = KirbyStandL.Height();
			now_img_w = KirbyStandL.Width();
			KirbyStandL.SetTopLeft(x, y);
			KirbyStandL.OnShow();
			break;

		// case fly up left
		case 15:
			KirbyFlyL.SetDelayCount(5);
			now_img_h = KirbyFlyL.Height();
			now_img_w = KirbyFlyL.Width();
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
			now_img_h = KirbyFlyingL.Height();
			now_img_w = KirbyFlyingL.Width();
			KirbyFlyingL.SetTopLeft(x, y);
			KirbyFlyingL.OnMove();
			KirbyFlyingL.OnShow();
			if (KirbyFlyingL.IsFinalBitmap()) {
				KirbyFlyingL.Reset();
			}
			break;

		// case hurt right
		case 17: 
			KirbyHurtR.SetDelayCount(2);
			now_img_h = KirbyHurtR.Height();
			now_img_w = KirbyHurtR.Width();
			KirbyHurtR.SetTopLeft(x, y);
			KirbyHurtR.OnMove();
			KirbyHurtR.OnShow();
			if (KirbyHurtR.IsFinalBitmap()) {
				IsHurt = false;
				KirbyHurtR.Reset();
			}
			break;

		// case hurt left
		case 18:
			KirbyHurtL.SetDelayCount(2);
			now_img_h = KirbyHurtL.Height();
			now_img_w = KirbyHurtL.Width();
			KirbyHurtL.SetTopLeft(x, y);
			KirbyHurtL.OnMove();
			KirbyHurtL.OnShow();
			if (KirbyHurtL.IsFinalBitmap()) {
				IsHurt = false;
				KirbyHurtL.Reset();
			}
			break;

		// case IsEaten standing right
		case 19:
			KirbyFatStand.SetDelayCount(3);
			KirbyFatStand.SetTopLeft(x, y);
			KirbyFatStand.OnMove();
			KirbyFatStand.OnShow();
			break;

		// case IsEaten standing left
		case 20:
			KirbyFatStandL.SetDelayCount(3);
			KirbyFatStandL.SetTopLeft(x, y);
			KirbyFatStandL.OnMove();
			KirbyFatStandL.OnShow();
			break;

		// case fat walk right 21
		case 21:
			KirbyFatMovingR.SetDelayCount(2);
			KirbyFatMovingR.SetTopLeft(x, y);
			KirbyFatMovingR.OnMove();
			KirbyFatMovingR.OnShow();
			break;

		// case fat walk left 22
		case 22:
			KirbyFatMovingL.SetDelayCount(2);
			KirbyFatMovingL.SetTopLeft(x, y);
			KirbyFatMovingL.OnMove();
			KirbyFatMovingL.OnShow();
			break;

		default:
			CMovingBitmap temp;
			temp.LoadBitmap(IDB_KIRBY);
			temp.ShowBitmap();
			break;
		}
	}

	void kirby::OnMove()
	{
		// set moving XY
		const int length = 4;

		// set moving XY and frame of test 
		if (IsMovingL && !IsDown && !IsAttack && !IsHurt && x > frame_of_test) {
			if (IsFacingR) {
				IsFacingR = false;
			}
			if (IsRun && !InAir) {
				SetXY(x - length * 3, y);
			}
			else {
				// x -= length;
				SetXY(x - length, y);
			}
		}

		if (IsMovingR && !IsDown && !IsAttack && !IsHurt && x < SIZE_X - ImgW - frame_of_test) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			if (IsRun && !InAir) {
				SetXY(x + length * 3, y);
			}
			else {
				// x += length;
				SetXY(x + length, y);
			}
		}

		// set down attack right and left
		if (IsDown && IsAttack && !IsHurt) {
			if (IsFacingR && x < SIZE_X - ImgW - frame_of_test) {
				// x += length * 3;
				SetXY(x + length * 3, y);
			}
			else if (x > frame_of_test) {
				// x -= length * 3;
				SetXY(x - length * 3, y);
			}
		}

		// set jump and fly
		if (IsRising && InAir && !IsAttack && !IsDown && !IsHurt) {
			if (y < sky_top) {		// ¸I¨ì¤ÑªáªO
				IsRising = false;
			}
			if (IsJumping) {
				if (velocity > 0) {
					// y -= velocity;
					SetXY(x, y - velocity);
					velocity--;
				}
				else {
					IsRising = false;
					velocity = 1;
				}
			}
			else if (FlyUp && IsFat) {
				if (fly_velocity > 0) {
					// y -= fly_velocity;
					SetXY(x, y - fly_velocity);
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
					// y += velocity;
					SetXY(x, y + velocity);
					velocity++;
				}
				else if (IsFlying) {
					// y++;
					SetXY(x, y + 1);
				}
				if (YouAreGround) {
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

		// kirby is hurt
		if (IsHurt) {
			if (!OtherFromL && x - 4 > 0) {
				// x -= 2;
				SetXY(x - 4, y);
			} else if(x + 4 < SIZE_X - now_img_w){
				// x += 2;
				SetXY(x + 4, y);
			} 
		}

		// kirby throw star
		if (IsEaten && IsAttack) {
			ThrowStar();
		}

		StarThrow.OnMove();
		if (StarThrow.GetAttackTime() > 0 && game_state_counter - StarThrow.GetAttackTime() < 100) {
			int* temp = StarThrow.GetXy();
			if (StarThrow.GetAttackFacingR()) {
				StarThrow.SetXy(temp[0] + 10, temp[1]);
			}
			else {
				StarThrow.SetXy(temp[0] - 10, temp[1]);
			}
			delete[] temp;
		}
		else {
			StarThrow.SetShow(false);
		}

		// animation OnMove
		KirbyMovingL.OnMove();
		KirbyMovingR.OnMove();
		KirbyStand.OnMove();
		KirbyStandL.OnMove();
	}

	void kirby::SetXY(int x_in, int y_in) {
		int aXy[4] = { x_in, y_in, x_in + now_img_w, y_in + now_img_h};
		bool result = true;
		if (StarBlockList != nullptr) {
			for (int k = 0;k < number_of_star_blocks;k++) {
				if (StarBlockList[k] != nullptr) {
					int* bXy = StarBlockList[k]->GetXy();
					int i = 0, n = 1;
					for (int count = 0; count < 2; count++) {
						for (int _count = 0; _count < 2; _count++) {
							if (aXy[i] > bXy[0] && aXy[i] < bXy[2] && aXy[n] > bXy[1] && aXy[n] < bXy[3]) {
								result = false;
								if (y_in - y > 0) {
									// go down
									YouAreGround = true;
								}
							}
							n += 2;
						}
						n = 1;
						i += 2;
					}

					i = 0, n = 1;
					for (int count = 0; count < 2; count++) {
						for (int _count = 0; _count < 2; _count++) {
							if (bXy[i] > aXy[0] && bXy[i] < aXy[2] && bXy[n] > aXy[1] && bXy[n] < aXy[3]) {
								result = false;
								if (y_in - y > 0) {
									// go down
									YouAreGround = true;
								}
							}
							n += 2;
						}
						n = 1;
						i += 2;
					}
					delete[] bXy;
				}
			}
		}
		
		
		if (result) {
			if (x_in - x > 0) {
				// right
				if (x_in > BoundaryLeft - now_img_w && Map->Left() > -(BoundaryRight - SIZE_X / 2)) {
					Map->SetTopLeft(Map->Left() - (x_in - x), Map->Top());
					Door->SetTopLeft(Door->Left() - (x_in - x), Door->Top());
					if (StarBlockList != nullptr) {
						for (int i = 0;i < number_of_star_blocks;i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left() - (x_in - x), StarBlockList[i]->Top());
							}
						}
					}
					if (WaddleList != nullptr) {
						for (int i = 0;i < number_of_waddles;i++) {
							if (WaddleList[i] != nullptr) {
								WaddleList[i]->SetXy(WaddleList[i]->Left() - (x_in - x), WaddleList[i]->Top());
							}
						}
					}
					if (WaddleDooList != nullptr) {
						for (int i = 0;i < number_of_waddle_doos;i++) {
							if (WaddleDooList[i] != nullptr) {
								WaddleDooList[i]->SetXy(WaddleDooList[i]->Left() - (x_in - x), WaddleDooList[i]->Top());
							}
						}
					}
					return;
				}
			}
			else if (x_in - x < 0) {
				// left
				if (x_in < BoundaryLeft && Map->Left() < 0) {
					Map->SetTopLeft(Map->Left() - (x_in - x), Map->Top());
					Door->SetTopLeft(Door->Left() - (x_in - x), Door->Top());
					if (StarBlockList != nullptr) {
						for (int i = 0;i < number_of_star_blocks;i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left() - (x_in - x), StarBlockList[i]->Top());
							}
						}
					}
					if (WaddleList != nullptr) {
						for (int i = 0;i < number_of_waddles;i++) {
							if (WaddleList[i] != nullptr) {
								WaddleList[i]->SetXy(WaddleList[i]->Left() - (x_in - x), WaddleList[i]->Top());
							}
						}
					}
					if (WaddleDooList != nullptr) {
						for (int i = 0;i < number_of_waddle_doos;i++) {
							if (WaddleDooList[i] != nullptr) {
								WaddleDooList[i]->SetXy(WaddleDooList[i]->Left() - (x_in - x), WaddleDooList[i]->Top());
							}
						}
					}
					return;
				}
			}

			if (y_in - y > 0) {
				// go down
				if (y_in > BoundaryTop && Map->Top() > -480) {
					Map->SetTopLeft(Map->Left(), Map->Top() - (y_in - y));
					Door->SetTopLeft(Door->Left(), Door->Top() - (y_in - y));
					if (StarBlockList != nullptr) {
						for (int i = 0;i < number_of_star_blocks;i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left(), StarBlockList[i]->Top() - (y_in - y));
							}
						}
					}
					if (WaddleList != nullptr) {
						for (int i = 0;i < number_of_waddles;i++) {
							if (WaddleList[i] != nullptr) {
								WaddleList[i]->SetXy(WaddleList[i]->Left(), WaddleList[i]->Top() - (y_in - y));
							}
						}
					}
					if (WaddleDooList != nullptr) {
						for (int i = 0;i < number_of_waddle_doos;i++) {
							if (WaddleDooList[i] != nullptr) {
								WaddleDooList[i]->SetXy(WaddleDooList[i]->Left(), WaddleDooList[i]->Top() - (y_in - y));
							}
						}
					}
					return;
				}
			}
			else if (y_in - y < 0) {
				// go up
				if (y_in < BoundaryTop && Map->Top() < 0) {
					Map->SetTopLeft(Map->Left(), Map->Top() - (y_in - y));
					Door->SetTopLeft(Door->Left(), Door->Top() - (y_in - y));
					if (StarBlockList != nullptr) {
						for (int i = 0;i < number_of_star_blocks;i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left(), StarBlockList[i]->Top() - (y_in - y));
							}
						}
					}
					if (WaddleList != nullptr) {
						for (int i = 0;i < number_of_waddles;i++) {
							if (WaddleList[i] != nullptr) {
								WaddleList[i]->SetXy(WaddleList[i]->Left(), WaddleList[i]->Top() - (y_in - y));
							}
						}
					}
					if (WaddleDooList != nullptr) {
						for (int i = 0;i < number_of_waddle_doos;i++) {
							if (WaddleDooList[i] != nullptr) {
								WaddleDooList[i]->SetXy(WaddleDooList[i]->Left(), WaddleDooList[i]->Top() - (y_in - y));
							}
						}
					}
					return;
				}
			}
			x = x_in;
			y = y_in;
		}
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
		if (!IsAttack && !InAir && !IsHurt) {
			IsDown = input;
		}
	}

	void kirby::SetAttack(bool input) {
		if (!IsHurt) {
			IsAttack = input;
		}
		if (IsFlying) {
			SetFly(false);
		}
	}

	void kirby::SetJump(bool input) {
		YouAreGround = false;
		if (IsJumping && !IsHurt) {
			SetFly(true);
		}
		if (!IsFlying && !IsHurt) {
			InAir = input;
			IsJumping = input;
		}
		else {
			SetFly(true);
		}
	}

	void kirby::SetFly(bool input) {
		YouAreGround = false;
		if (!IsDown || !IsHurt) {
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

	void kirby::SetEaten(bool input) {
		IsEaten = input;
	}

	void kirby::YouAreLeft(bool YouAreLeft) {
		OtherFromL = !YouAreLeft;
	}

	void kirby::SetUpKey(bool input) {
		PressUpKey = input;
	}

	void kirby::SetCounter(int input_counter) {
		game_state_counter = input_counter;
	}

	void kirby::SetMap(CMovingBitmap* input_Map) {
		Map = input_Map;
	}

	void kirby::SetDoor(CMovingBitmap* input_door) {
		Door = input_door;
	}

	void kirby::SetThings(starBlock ** input, int number_input) {
		StarBlockList = input;
		number_of_star_blocks = number_input;
	}

	void kirby::SetWaddles(waddle** input, int number_input) {
		WaddleList = input;
		number_of_waddles = number_input;
	}

	void kirby::SetWaddleDoos(waddleDoo** input, int number_input) {
		WaddleDooList = input;
		number_of_waddle_doos = number_input;
	}

	void kirby::SetRun(bool input) {
		IsRun = input;
	}
	
	void kirby::Hurt(int input, int time) {
		if (abs(LastHurt - time) < 30) {
			return;
		}
		LastHurt = time;
		hp -= input;
		IsHurt = true;
		SetDown(false);
		SetAttack(false);
		SetJump(false);
		SetFly(false);
	}

	void kirby::ThrowStar() {
		int* temp = GetXy();
		StarThrow.SetAttackState(game_state_counter, IsFacingR, temp);
		delete[] temp;
		StarThrow.SetShow(true);
		IsEaten = false;
		IsAttack = false;
	}

	int kirby::GetCase() {
		if (IsHurt) {
			if (OtherFromL) {
				if (IsFacingR) {
					IsFacingR = false;
				}
				return 18;
			}
			else {
				if (!IsFacingR) {
					IsFacingR = true;
				}
				return 17;
			}
		}
		else {
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
				else if (IsMovingR && !IsEaten) {
					// case walking right
					return 5;
				}
				else if (IsEaten && IsMovingR) {
					// case IsEaten  walking right
					return 21;
				}
				else if (IsEaten) {
					// case IsEaten standing right
					return 19;
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
				else if (IsMovingL && !IsEaten) {
					// case walking left 
					return 13;
				}
				else if (IsEaten && IsMovingL) {
					// case IsEaten walking left
					return 22;
				}
				else if (IsEaten) {
					// case IsEaten standing left
					return 20;
				}
				else {
					// case standing left
					return 14;
				}
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

	bool kirby::GetUpKey() {
		return PressUpKey;
	}


	weapon* kirby::GetWeapon() {
		return &StarThrow;
	}
}
