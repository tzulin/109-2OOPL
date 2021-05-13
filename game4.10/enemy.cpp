#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "enemy.h"

namespace game_framework {
	const int frame_of_test = 5;
	enemy::enemy()
	{
		// enemy constructor
		/*
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		*/
		const int INIT_HP = 0;
		hp = INIT_HP;
		x = origin_x;
		y = origin_y;
		power = 1;
		floor = SIZE_Y - 60;
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		LastAttack = 0;
	}

	enemy::~enemy()
	{
	}

	int* enemy::GetXy() {
		return new int[4]{ x, y, x + ImgW, y + ImgH };
	}

	int enemy::GetHp() {
		return hp;
	}

	int enemy::GetWidth() {
		return ImgW;
	}

	int enemy::GetHeight() {
		return ImgH;
	}

	int enemy::GetPower() {
		return power;
	}

	void enemy::BackX(bool fromL) {
		if (fromL) {
			x += 60;
		}
		else {
			x -= 60;
		}
	}

	void enemy::Hurt(int input, int time) {
		if (abs(LastHurt - time) < 30) {
			return;
		}
		BackX(OtherFromL);
		LastHurt = time;
		hp -= input;
	}

	void enemy::Reset() {
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		wL.SetShow(false);
		wR.SetShow(false);
		hp = 1;
	}

	void enemy::Attack(kirby k, int time) {
		if (abs(LastAttack - time) < 30) {
			return;
		}
		LastAttack = time;
		IsAttack = true;
	}

	void enemy::YouAreLeft(bool YouAreLeft) {
		OtherFromL = !YouAreLeft;
	}

	void enemy::OnShow()
	{
		if (!IsAttack) {
			if (IsMovingR) {
				MovingR.SetDelayCount(3);
				MovingR.SetTopLeft(x, y);
				MovingR.OnShow();
			}
			else {
				MovingL.SetDelayCount(3);
				MovingL.SetTopLeft(x, y);
				MovingL.OnShow();
			}
		}
		else {
			if (OtherFromL) {
				AttackL.SetDelayCount(5);
				AttackL.SetTopLeft(x, y);
				AttackL.OnShow();
				wL.SetWeapon(x, y, IsFacingR);
				wL.SetShow(true);
				wL.OnMove();
				wL.OnShow();
				if (AttackL.IsFinalBitmap()) {
					AttackL.Reset();
					wL.AnimationReset();
					IsAttack = false;
					wL.SetShow(false);
				}
			}
			else {
				AttackR.SetDelayCount(5);
				AttackR.SetTopLeft(x, y);
				AttackR.OnShow();
				wR.SetWeapon(x, y, IsFacingR);
				wR.SetShow(true);
				wR.OnMove();
				wR.OnShow();
				if (AttackR.IsFinalBitmap()) {
					AttackR.Reset();
					wR.AnimationReset();
					IsAttack = false;
					wR.SetShow(false);
				}
			}
		}

	}

	void enemy::OnMove()
	{
		
		// set moving XY
		const int length = 2;

		SetXy(x - Map->GetXChange(), y - Map->GetYChange());
		Map->ResetChange();

		if (!IsAttack) {
			MovingL.OnMove();
			MovingR.OnMove();
			// set moving XY and frame of test 
			if (IsMovingL && x > frame_of_test) {
				if (IsFacingR) {
					IsFacingR = false;
				}
				x -= length;
			}
			else if (x <= frame_of_test) {
				IsMovingL = false;
				IsMovingR = true;
			}

			if (IsMovingR && x < SIZE_X - ImgW) {
				if (!IsFacingR) {
					IsFacingR = true;
				}
				x += length;
			}
			else if (x >= SIZE_X - ImgW) {
				IsMovingR = false;
				IsMovingL = true;
			}
		}
		else {
			AttackR.OnMove();
			AttackL.OnMove();
		}
	}

	void enemy::LoadBitmap(){}

	void enemy::SetMap(CMovingBitmap * input) {
		Map = input;
	}

	bool enemy::EnemyFacingR() {
		return IsFacingR;
	}

	void enemy::SetXy(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	weapon enemy::GetWeapon() {
		if (IsFacingR) {
			return wR;
		}
		else {
			return wL;
		}
	}
}
