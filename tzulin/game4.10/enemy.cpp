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
		LastHurt = time;
		hp -= input;
	}

	void enemy::Reset() {
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 1;
	}

	bool enemy::MeetKirby(kirby & k) {
		int* KirbyXy = k.GetXy();
		int* enemyXY = GetXy();

		if (enemyXY[0] > KirbyXy[0] && enemyXY[0] < KirbyXy[2]) {					// kirby meet enemy from left
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				BackX(true);
				k.SetEnemyFromL(false);
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				BackX(true);
				k.SetEnemyFromL(false);
				return true;
			}
		}
		else if (enemyXY[2] > KirbyXy[0] && enemyXY[2] < KirbyXy[2]) {			// kirby meet enemy from right
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				BackX(false);
				k.SetEnemyFromL(true);
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				BackX(false);
				k.SetEnemyFromL(true);
				return true;
			}
		}
		delete[] KirbyXy;
		delete[] enemyXY;
		return false;
	}

	bool enemy::SeeKirby(kirby k) {
		int* KirbyXy = k.GetXy();
		int* enemyXY = GetXy();

		if (enemyXY[0]-ImgW > KirbyXy[0] && enemyXY[0]-ImgW < KirbyXy[2]) {					// enemy meet kirby from left
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				KirbyFromL = true;
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				KirbyFromL = true;
				return true;
			}
		}
		else if (enemyXY[2]+ImgW> KirbyXy[0] && enemyXY[2]+ImgW < KirbyXy[2]) {				// enemy meet kirby from right
			if (enemyXY[1] > KirbyXy[1] && enemyXY[1] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				KirbyFromL = false;
				return true;
			}
			else if (enemyXY[3] > KirbyXy[1] && enemyXY[3] < KirbyXy[3]) {
				delete[] KirbyXy;
				delete[] enemyXY;
				KirbyFromL = false;
				return true;
			}
		}

		delete[] KirbyXy;
		delete[] enemyXY;
		return false;
	}

	void enemy::Attack(kirby k, int time) {
		if (abs(LastAttack - time) < 30) {
			return;
		}
		LastAttack = time;
		IsAttack = true;
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
			if (KirbyFromL) {
				AttackL.SetDelayCount(10);
				AttackL.SetTopLeft(x-68, y-68);
				AttackL.OnShow();
				if (AttackL.IsFinalBitmap()) {
					AttackL.Reset();
					IsAttack = false;
				}
			}
			else {
				AttackR.SetDelayCount(3);
				AttackR.SetTopLeft(x, y);
				AttackR.OnShow();
				if (AttackR.IsFinalBitmap()) {
					AttackR.Reset();
					IsAttack = false;
				}
			}
		}

	}

	void enemy::OnMove()
	{
		// set moving XY
		const int length = 2;

		if (!IsAttack) {
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

		MovingL.OnMove();
		MovingR.OnMove();
		AttackR.OnMove();
		AttackL.OnMove();
	}

	void enemy::LoadBitmap()
	{
		MovingR.AddBitmap(".\\res\\waddledee\\walk\\walkR1.bmp");
		MovingL.AddBitmap(".\\res\\waddledee\\walk\\walkL1.bmp");
	}
}
