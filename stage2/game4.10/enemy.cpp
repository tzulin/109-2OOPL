#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
//#include "enemy.h"
#include "Header.h"

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

	std::string enemy::GetKind() {
		return kind;
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

	int enemy::Top() {
		return y;
	}

	int enemy::Left() {
		return x;
	}

	void enemy::BackX(bool fromL) {
		if (fromL) {
			SetXy(x + 60, y);
		}
		else {
			SetXy(x - 60, y);
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
				wL.SetOwner(kind);
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
				wR.SetOwner(kind);
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

		/*
		SetXy(x - Map->GetXChange(), y - Map->GetYChange());
		Map->ResetChange();
		*/

		if (!IsAttack) {
			MovingL.OnMove();
			MovingR.OnMove();
			// set moving XY and frame of test 
			if (IsMovingL && x >= Map->Left()) {
				if (IsFacingR) {
					IsFacingR = false;
				}
				SetXy(x - length, y);
			}
			else if (x <= Map->Left()) {
				IsMovingL = false;
				IsMovingR = true;
			}

			if (IsMovingR && x <= Map->Left() + Map->Width() - ImgW) {
				if (!IsFacingR) {
					IsFacingR = true;
				}
				SetXy(x + length, y);
			}
			else if (x >= Map->Left() + Map->Width() - ImgW) {
				IsMovingR = false;
				IsMovingL = true;
			}
		}
		else {
			AttackR.OnMove();
			AttackL.OnMove();
		}
	}

	void enemy::LoadBitmap() {}

	void enemy::SetMap(CMovingBitmap * input) {
		Map = input;
	}

	void enemy::SetThings(vector<thing*> input) {
		StarBlockList = input;
	}

	bool enemy::EnemyFacingR() {
		return IsFacingR;
	}

	void enemy::SetXy(int x_in, int y_in) {
		int aXy[4] = { x_in, y_in, x_in + MovingR.Width(), y_in + MovingR.Height() };
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
								IsMovingL = !IsMovingL;
								IsMovingR = !IsMovingR;
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
								IsMovingL = !IsMovingL;
								IsMovingR = !IsMovingR;
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
			x = x_in;
			y = y_in;
		}
	}

	weapon enemy::GetWeapon() {
		if (IsFacingR) {
			return wR;
		}
		else {
			return wL;
		}
	}

	bool enemy::EnemyHasWeapon() {
		return HasWeapon;
	}
}
