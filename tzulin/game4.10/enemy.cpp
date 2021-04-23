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
		floor = SIZE_Y - 60;
		IsMovingL = true;
		IsMovingR = false;
		IsFacingR = false;
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

	void enemy::SetHp(int input) {
		hp = input;
	}

	void enemy::Reset() {
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 1;
	}

	void enemy::OnShow()
	{
		if (IsFacingR) {
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

	void enemy::OnMove()
	{
		// set moving XY
		const int length = 2;

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

		MovingL.OnMove();
		MovingR.OnMove();
	}

	void enemy::LoadBitmap()
	{
		MovingR.AddBitmap(".\\res\\waddledee\\walk\\walkR1.bmp");
		MovingL.AddBitmap(".\\res\\waddledee\\walk\\walkL1.bmp");
	}
}
