
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
		StageReSet(10, "normal");
	}

	void kirby::StageReSet(int hp_left, std::string kind) {
		const int origin_x = frame_of_test;
		const int origin_y = SIZE_Y - temp_floor - ImgH;
		const int INIT_VELOCITY = 18;
		const int INIT_FLY_VELOCITY = 9;
		const int INIT_HP = hp_left;
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
		// StarBlockList = nullptr;
		IsRun = false;
		IsHack = false;
		EatenEnemy = "";
		kirby_kind = kind;
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
		int rgb[3] = { 0, 0, 0 };
		StarThrow.LoadBitmap(IDB_STARTHROW, rgb, 100);
	}

	void kirby::OnShow()
	{
		if (StarThrow.WeaponIsShow()) {
			StarThrow.OnShow();
		}

		if (kirby_kind == "waddleKirby") {
			TRACE("waddle\n");
		}
		else if (kirby_kind == "bigWaddleKirby") {
			TRACE("bigWaddle\n");
		}
		else if (kirby_kind == "droppyKirby") {
			TRACE("droppy\n");
		}
		else if (kirby_kind == "waddleDooKirby") {
			TRACE("waddleDoo\n");
		}
		else if (kirby_kind == "sparkyKirby") {
			TRACE("sparky\n");
		}
		else if (kirby_kind == "hotHeadKirby") {
			TRACE("hotHead\n");
		}
		

		switch (GetCase()) {
			// case jump up right
		case 1:
			KirbyJumpR.SetDelayCount(4);
			now_img_h = KirbyJumpR.Height();
			now_img_w = KirbyJumpR.Width();
			KirbyJumpR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyJumpR.OnMove();
			KirbyJumpR.OnShow();
			break;

			// case down attack right
		case 2:
			KirbyDownAttackR.SetDelayCount(5);
			now_img_h = KirbyDownAttackR.Height();
			now_img_w = KirbyDownAttackR.Width();
			KirbyDownAttackR.SetTopLeft(x, y + KirbyStand.Height() - KirbyDownR.Height());
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
			KirbyDownR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyDownR.ShowBitmap();
			break;

			// case scream right
		case 4:
			KirbyScreamR.SetDelayCount(3);
			now_img_h = KirbyScreamR.Height();
			now_img_w = KirbyScreamR.Width();
			KirbyScreamR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyMovingR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyMovingR.OnShow();
			break;

			// case standing right
		case 6:
			KirbyStand.SetDelayCount(3);
			now_img_h = KirbyStand.Height();
			now_img_w = KirbyStand.Width();
			KirbyStand.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyStand.OnShow();
			break;

			// case fly up right
		case 7:
			KirbyFlyR.SetDelayCount(5);
			now_img_h = KirbyFlyR.Height();
			now_img_w = KirbyFlyR.Width();
			KirbyFlyR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyFlyingR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyJumpL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyJumpL.OnMove();
			KirbyJumpL.OnShow();
			break;

			// case down attack left
		case 10:
			KirbyDownAttackL.SetDelayCount(5);
			now_img_h = KirbyDownAttackL.Height();
			now_img_w = KirbyDownAttackL.Width();
			KirbyDownAttackL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyDownL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyDownL.ShowBitmap();
			break;

			// case scream left 
		case 12:
			KirbyScreamL.SetDelayCount(3);
			now_img_h = KirbyScreamL.Height();
			now_img_w = KirbyScreamL.Width();
			KirbyScreamL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyMovingL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyMovingL.OnShow();
			break;

			// case standing left
		case 14:
			KirbyStandL.SetDelayCount(3);
			now_img_h = KirbyStandL.Height();
			now_img_w = KirbyStandL.Width();
			KirbyStandL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyStandL.OnShow();
			break;

			// case fly up left
		case 15:
			KirbyFlyL.SetDelayCount(5);
			now_img_h = KirbyFlyL.Height();
			now_img_w = KirbyFlyL.Width();
			KirbyFlyL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyFlyingL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyHurtR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			KirbyHurtL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			now_img_h = KirbyFatStand.Height();
			now_img_w = KirbyFatStand.Width();
			KirbyFatStand.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyFatStand.OnMove();
			KirbyFatStand.OnShow();
			break;

			// case IsEaten standing left
		case 20:
			KirbyFatStandL.SetDelayCount(3);
			now_img_h = KirbyFatStandL.Height();
			now_img_w = KirbyFatStandL.Width();
			KirbyFatStandL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyFatStandL.OnMove();
			KirbyFatStandL.OnShow();
			break;

			// case fat walk right 21
		case 21:
			KirbyFatMovingR.SetDelayCount(2);
			now_img_h = KirbyFatMovingR.Height();
			now_img_w = KirbyFatMovingR.Width();
			KirbyFatMovingR.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
			KirbyFatMovingR.OnMove();
			KirbyFatMovingR.OnShow();
			break;

			// case fat walk left 22
		case 22:
			KirbyFatMovingL.SetDelayCount(2);
			now_img_h = KirbyFatMovingL.Height();
			now_img_w = KirbyFatMovingL.Width();
			KirbyFatMovingL.SetTopLeft(x, y + KirbyStand.Height() - now_img_h);
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
			else if (IsRun && IsHack) {
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
			else if (IsRun && IsHack) {
				SetXY(x + length * 3, y);
			}
			else {
				// x += length;
				SetXY(x + length, y);
			}
		}

		// set down attack right and left
		/*if (IsDown && IsAttack && !IsHurt) {
			if (IsFacingR && x < SIZE_X - ImgW - frame_of_test) {
				// x += length * 3;
				SetXY(x + length * 3, y);
			}
			else if (x > frame_of_test) {
				// x -= length * 3;
				SetXY(x - length * 3, y);
			}
		}*/

		// set down attack right and left
		if (IsDown && IsAttack) {
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
			}
			else if (x + 4 < SIZE_X - now_img_w) {
				// x += 2;
				SetXY(x + 4, y);
			}
		}

		// kirby throw star
		if (IsEaten && IsAttack) {
			ThrowStar();
		}

		if (IsEaten && IsDown) {
			SetChange();
		}

		StarThrow.OnMove();
		if (StarThrow.GetAttackTime() > 0 && game_state_counter - StarThrow.GetAttackTime() < 50) {
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
		int aXy[4] = { x_in, y_in, x_in + now_img_w, y_in + now_img_h };
		bool result = true;
		if (!StarBlockList.empty()) {
			for (int k = 0; k < int(StarBlockList.size()); k++) {
				if (StarBlockList[k] != nullptr && StarBlockList[k]->GetShow()) {
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
					int* temp = StarThrow.GetXy();
					StarThrow.SetXy(temp[0] - (x_in - x), temp[1]);
					delete[] temp;
					if (!StarBlockList.empty()) {
						/*for (int i = 0; i < int(StarBlockList.size()); i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left() - (x_in - x), StarBlockList[i]->Top());
							}
						}*/
						for (auto n : StarBlockList) {
							n->SetXY(n->Left() - (x_in - x), n->Top());
						}
					}
					if (!EnemyList.empty()) {
						for (auto n : EnemyList) {
							n->SetXy(n->Left() - (x_in - x), n->Top());
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
					int* temp = StarThrow.GetXy();
					StarThrow.SetXy(temp[0] - (x_in - x), temp[1]);
					delete[] temp;
					if (!StarBlockList.empty()) {
						/*for (int i = 0; i < int(StarBlockList.size()); i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left() - (x_in - x), StarBlockList[i]->Top());
							}
						}*/
						for (auto n : StarBlockList) {
							n->SetXY(n->Left() - (x_in - x), n->Top());
						}
					}
					if (!EnemyList.empty()) {
						for (auto n : EnemyList) {
							n->SetXy(n->Left() - (x_in - x), n->Top());
						}
					}
					return;
				}
			}

			if (y_in - y > 0) {
				// go down
				if (y_in > BoundaryTop && Map->Top() > -260) {
					Map->SetTopLeft(Map->Left(), Map->Top() - (y_in - y));
					Door->SetTopLeft(Door->Left(), Door->Top() - (y_in - y));
					int* temp = StarThrow.GetXy();
					StarThrow.SetXy(temp[0], temp[1] - (y_in - y));
					delete[] temp;
					if (!StarBlockList.empty()) {
						/*for (int i = 0; i < int(StarBlockList.size()); i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left(), StarBlockList[i]->Top() - (y_in - y));
							}
						}*/
						for (auto n : StarBlockList) {
							n->SetXY(n->Left(), n->Top() - (y_in - y));
						}
					}
					if (!EnemyList.empty()) {
						for (auto n : EnemyList) {
							n->SetXy(n->Left(), n->Top() - (y_in - y));
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
					int* temp = StarThrow.GetXy();
					StarThrow.SetXy(temp[0], temp[1] - (y_in - y));
					delete[] temp;
					if (!StarBlockList.empty()) {
						/*for (int i = 0; i < int(StarBlockList.size()); i++) {
							if (StarBlockList[i] != nullptr) {
								StarBlockList[i]->SetXY(StarBlockList[i]->Left(), StarBlockList[i]->Top() - (y_in - y));
							}
						}*/
						for (auto n : StarBlockList) {
							n->SetXY(n->Left(), n->Top() - (y_in - y));
						}
					}
					if (!EnemyList.empty()) {
						for (auto n : EnemyList) {
							n->SetXy(n->Left(), n->Top() - (y_in - y));
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

	void kirby::SetEaten(bool input, std::string name) {
		IsEaten = input;
		EatenEnemy = name;
	}

	void kirby::SetChange() {
		if (EatenEnemy == "waddle") {
			TRACE("waddle eaten\n");
		}
		else if (EatenEnemy == "bigWaddle") {
			TRACE("bigWaddle eaten\n");
		}
		else if (EatenEnemy == "droppy") {
			TRACE("droppy eaten\n");
		}
		else if (EatenEnemy == "waddleDoo") {
			TRACE("waddleDoo eaten\n");
			kirby_kind = "waddleDooKirby";
		}
		else if (EatenEnemy == "sparky") {
			TRACE("sparky eaten\n");
			kirby_kind = "sparkyKirby";
		}
		else if (EatenEnemy == "hotHead") {
			TRACE("hotHead eaten\n");
			kirby_kind = "hotHeadKirby";
		}
		else {
			TRACE("other eaten\n");
		}
		SetEaten(false, "");
	}

	void kirby::YouAreLeft(bool YouAreLeft) {
		OtherFromL = !YouAreLeft;
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

	void kirby::SetThings(vector<thing*> input) {
		StarBlockList = input;
	}

	void kirby::SetEnemies(vector<enemy*> input_EnemyList) {
		EnemyList = input_EnemyList;
	}

	void kirby::SetRun(bool input) {
		IsRun = input;
	}

	void kirby::SetHack(bool input) {
		IsHack = input;
	}

	void kirby::Hurt(int input, int time) {
		if (IsHack) {
			return;
		}
		if (abs(LastHurt - time) < 30) {
			return;
		}
		if (IsDown && IsAttack) {
			return;
		}
		kirby_kind = "normal";
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
		return new int[4]{ x, y , x + ImgW, y + ImgH };
	}

	int kirby::GetWidth() {
		return ImgW;
	}

	int kirby::GetHeight() {
		return ImgH;
	}

	std::string kirby::GetKind() {
		return kirby_kind;
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

	weapon* kirby::GetWeapon() {
		return &StarThrow;
	}

	void sparky_kirby::SetEaten(bool input) {}

	void sparky_kirby::SetEaten(bool input, std::string name) {}

	void sparky_kirby::ThrowStar() {}

	void sparky_kirby::LoadBitmap()
	{
		// load walk left
		char *walk_left[10] = { ".\\res\\kirby_sparky\\walk\\walkL1.bmp", ".\\res\\kirby_sparky\\walk\\walkL2.bmp", ".\\res\\kirby_sparky\\walk\\walkL3.bmp", ".\\res\\kirby_sparky\\walk\\walkL4.bmp", ".\\res\\kirby_sparky\\walk\\walkL5.bmp", ".\\res\\kirby_sparky\\walk\\walkL6.bmp", ".\\res\\kirby_sparky\\walk\\walkL7.bmp", ".\\res\\kirby_sparky\\walk\\walkL8.bmp", ".\\res\\kirby_sparky\\walk\\walkL9.bmp", ".\\res\\kirby_sparky\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load walk right
		char *walk_right[10] = { ".\\res\\kirby_sparky\\walk\\walkR1.bmp", ".\\res\\kirby_sparky\\walk\\walkR2.bmp", ".\\res\\kirby_sparky\\walk\\walkR3.bmp", ".\\res\\kirby_sparky\\walk\\walkR4.bmp", ".\\res\\kirby_sparky\\walk\\walkR5.bmp", ".\\res\\kirby_sparky\\walk\\walkR6.bmp", ".\\res\\kirby_sparky\\walk\\walkR7.bmp", ".\\res\\kirby_sparky\\walk\\walkR8.bmp", ".\\res\\kirby_sparky\\walk\\walkR9.bmp", ".\\res\\kirby_sparky\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load stand and wink right
		int count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR3.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR3.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR1.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_sparky\\basic\\basicR3.bmp", RGB(255, 255, 255));

		// load stand and wink left
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL3.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL3.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL1.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_sparky\\basic\\basicL3.bmp", RGB(255, 255, 255));

		

		// load down right and left
		KirbyDownR.LoadBitmap(".\\res\\kirby_sparky\\down\\downR1.bmp", RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(".\\res\\kirby_sparky\\down\\downL1.bmp", RGB(255, 255, 255));

		// load down attack right and left
		count = 3;
		while (count-- > 0) {
			KirbyDownAttackR.AddBitmap(".\\res\\kirby_sparky\\down\\downR2.bmp", RGB(255, 255, 255));
			KirbyDownAttackL.AddBitmap(".\\res\\kirby_sparky\\down\\downL2.bmp", RGB(255, 255, 255));
		}

		// load jump right
		char *jump_right[10] = { ".\\res\\kirby_sparky\\jump\\jumpR1.bmp", ".\\res\\kirby_sparky\\jump\\jumpR2.bmp", ".\\res\\kirby_sparky\\jump\\jumpR3.bmp", ".\\res\\kirby_sparky\\jump\\jumpR4.bmp", ".\\res\\kirby_sparky\\jump\\jumpR5.bmp", ".\\res\\kirby_sparky\\jump\\jumpR6.bmp", ".\\res\\kirby_sparky\\jump\\jumpR7.bmp", ".\\res\\kirby_sparky\\jump\\jumpR8.bmp", ".\\res\\kirby_sparky\\jump\\jumpR9.bmp", ".\\res\\kirby_sparky\\jump\\jumpR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpR.AddBitmap(jump_right[i], RGB(255, 255, 255));
		}

		// load jump left
		char *jump_left[10] = { ".\\res\\kirby_sparky\\jump\\jumpL1.bmp", ".\\res\\kirby_sparky\\jump\\jumpL2.bmp", ".\\res\\kirby_sparky\\jump\\jumpL3.bmp", ".\\res\\kirby_sparky\\jump\\jumpL4.bmp", ".\\res\\kirby_sparky\\jump\\jumpL5.bmp", ".\\res\\kirby_sparky\\jump\\jumpL6.bmp", ".\\res\\kirby_sparky\\jump\\jumpL7.bmp", ".\\res\\kirby_sparky\\jump\\jumpL8.bmp", ".\\res\\kirby_sparky\\jump\\jumpL9.bmp", ".\\res\\kirby_sparky\\jump\\jumpL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpL.AddBitmap(jump_left[i], RGB(255, 255, 255));
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
		KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR1.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR2.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR4.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR5.bmp", RGB(255, 255, 255));

		// load flyingR
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR6.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR10.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_sparky\\fly\\flyR6.bmp", RGB(255, 255, 255));

		// load flyL
		KirbyFlyL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL1.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL2.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL5.bmp", RGB(255, 255, 255));

		// load flyingL
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL6.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL10.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_sparky\\fly\\flyL6.bmp", RGB(255, 255, 255));

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
		int rgb[3] = { 0, 0, 0 };
		StarThrow.LoadBitmap(IDB_STARTHROW, rgb, 100);
	}

	void hotHead_kirby::SetEaten(bool input) {}

	void hotHead_kirby::SetEaten(bool input, std::string name) {}

	void hotHead_kirby::ThrowStar(){}

	void hotHead_kirby::LoadBitmap()
	{
		// load walk left
		char *walk_left[10] = { ".\\res\\kirby_hotHead\\walk\\walkL1.bmp", ".\\res\\kirby_hotHead\\walk\\walkL2.bmp", ".\\res\\kirby_hotHead\\walk\\walkL3.bmp", ".\\res\\kirby_hotHead\\walk\\walkL4.bmp", ".\\res\\kirby_hotHead\\walk\\walkL5.bmp", ".\\res\\kirby_hotHead\\walk\\walkL6.bmp", ".\\res\\kirby_hotHead\\walk\\walkL7.bmp", ".\\res\\kirby_hotHead\\walk\\walkL8.bmp", ".\\res\\kirby_hotHead\\walk\\walkL9.bmp", ".\\res\\kirby_hotHead\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load walk right
		char *walk_right[10] = { ".\\res\\kirby_hotHead\\walk\\walkR1.bmp", ".\\res\\kirby_hotHead\\walk\\walkR2.bmp", ".\\res\\kirby_hotHead\\walk\\walkR3.bmp", ".\\res\\kirby_hotHead\\walk\\walkR4.bmp", ".\\res\\kirby_hotHead\\walk\\walkR5.bmp", ".\\res\\kirby_hotHead\\walk\\walkR6.bmp", ".\\res\\kirby_hotHead\\walk\\walkR7.bmp", ".\\res\\kirby_hotHead\\walk\\walkR8.bmp", ".\\res\\kirby_hotHead\\walk\\walkR9.bmp", ".\\res\\kirby_hotHead\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load stand and wink right
		int count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR3.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR3.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR1.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicR3.bmp", RGB(255, 255, 255));

		// load stand and wink left
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL3.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL3.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL1.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_hotHead\\basic\\basicL3.bmp", RGB(255, 255, 255));



		// load down right and left
		KirbyDownR.LoadBitmap(".\\res\\kirby_hotHead\\down\\downR1.bmp", RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(".\\res\\kirby_hotHead\\down\\downL1.bmp", RGB(255, 255, 255));

		// load down attack right and left
		count = 3;
		while (count-- > 0) {
			KirbyDownAttackR.AddBitmap(".\\res\\kirby_hotHead\\down\\downR3.bmp", RGB(255, 255, 255));
			KirbyDownAttackL.AddBitmap(".\\res\\kirby_hotHead\\down\\downL3.bmp", RGB(255, 255, 255));
		}

		// load jump right
		char *jump_right[10] = { ".\\res\\kirby_hotHead\\jump\\jumpR1.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR2.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR3.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR4.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR5.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR6.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR7.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR8.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR9.bmp", ".\\res\\kirby_hotHead\\jump\\jumpR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpR.AddBitmap(jump_right[i], RGB(255, 255, 255));
		}

		// load jump left
		char *jump_left[10] = { ".\\res\\kirby_hotHead\\jump\\jumpL1.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL2.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL3.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL4.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL5.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL6.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL7.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL8.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL9.bmp", ".\\res\\kirby_hotHead\\jump\\jumpL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpL.AddBitmap(jump_left[i], RGB(255, 255, 255));
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
		KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR1.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR2.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR4.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR5.bmp", RGB(255, 255, 255));

		// load flyingR
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR6.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR10.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyR6.bmp", RGB(255, 255, 255));

		// load flyL
		KirbyFlyL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL1.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL2.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL5.bmp", RGB(255, 255, 255));

		// load flyingL
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL6.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL10.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_hotHead\\fly\\flyL6.bmp", RGB(255, 255, 255));

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
		int rgb[3] = { 0, 0, 0 };
		StarThrow.LoadBitmap(IDB_STARTHROW, rgb, 100);
	}

	void waddleDoo_kirby::SetEaten(bool input) {}

	void waddleDoo_kirby::SetEaten(bool input, std::string name) {}

	void waddleDoo_kirby::ThrowStar() {}

	void waddleDoo_kirby::LoadBitmap()
	{
		// load walk left
		char *walk_left[10] = { ".\\res\\kirby_waddleDoo\\walk\\walkL1.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL2.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL3.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL4.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL5.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL6.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL7.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL8.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL9.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load walk right
		char *walk_right[10] = { ".\\res\\kirby_waddleDoo\\walk\\walkR1.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR2.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR3.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR4.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR5.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR6.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR7.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR8.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR9.bmp", ".\\res\\kirby_waddleDoo\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyMovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load stand and wink right
		int count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR2.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR1.bmp", RGB(255, 255, 255));
		}
		KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR2.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR1.bmp", RGB(255, 255, 255));
		KirbyStand.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicR2.bmp", RGB(255, 255, 255));

		// load stand and wink left
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL2.bmp", RGB(255, 255, 255));
		count = 12;
		while (count-- > 0) {
			KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL1.bmp", RGB(255, 255, 255));
		}
		KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL2.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL1.bmp", RGB(255, 255, 255));
		KirbyStandL.AddBitmap(".\\res\\kirby_waddleDoo\\basic\\basicL2.bmp", RGB(255, 255, 255));



		// load down right and left
		KirbyDownR.LoadBitmap(".\\res\\kirby_waddleDoo\\down\\downR1.bmp", RGB(255, 255, 255));
		KirbyDownL.LoadBitmap(".\\res\\kirby_waddleDoo\\down\\downL1.bmp", RGB(255, 255, 255));

		// load down attack right and left
		count = 3;
		while (count-- > 0) {
			KirbyDownAttackR.AddBitmap(".\\res\\kirby_waddleDoo\\down\\downR2.bmp", RGB(255, 255, 255));
			KirbyDownAttackL.AddBitmap(".\\res\\kirby_waddleDoo\\down\\downL2.bmp", RGB(255, 255, 255));
		}

		// load jump right
		char *jump_right[10] = { ".\\res\\kirby_waddleDoo\\jump\\jumpR1.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR2.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR3.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR4.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR5.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR6.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR7.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR8.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR9.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpR.AddBitmap(jump_right[i], RGB(255, 255, 255));
		}

		// load jump left
		char *jump_left[10] = { ".\\res\\kirby_waddleDoo\\jump\\jumpL1.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL2.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL3.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL4.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL5.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL6.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL7.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL8.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL9.bmp", ".\\res\\kirby_waddleDoo\\jump\\jumpL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			KirbyJumpL.AddBitmap(jump_left[i], RGB(255, 255, 255));
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
		KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR1.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR2.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR4.bmp", RGB(255, 255, 255));
		KirbyFlyR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR5.bmp", RGB(255, 255, 255));

		// load flyingR
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR6.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR9.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR8.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR7.bmp", RGB(255, 255, 255));
		KirbyFlyingR.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyR6.bmp", RGB(255, 255, 255));

		// load flyL
		KirbyFlyL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL1.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL2.bmp", RGB(255, 255, 255));
		KirbyFlyL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL3.bmp", RGB(255, 255, 255));
		count = 3;
		while (count-- > 0) {
			KirbyFlyL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL4.bmp", RGB(255, 255, 255));
		}
		KirbyFlyL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL5.bmp", RGB(255, 255, 255));

		// load flyingL
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL6.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL9.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL8.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL7.bmp", RGB(255, 255, 255));
		KirbyFlyingL.AddBitmap(".\\res\\kirby_waddleDoo\\fly\\flyL6.bmp", RGB(255, 255, 255));

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
		int rgb[3] = { 0, 0, 0 };
		StarThrow.LoadBitmap(IDB_STARTHROW, rgb, 100);
	}
}
