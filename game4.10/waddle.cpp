#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "waddle.h"

namespace game_framework {
	const int frame_of_test = 5;
	waddle::waddle()
	{
		// waddle constructor
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - frame_of_test - ImgH;
		x = origin_x;
		y = origin_y;
		floor = SIZE_Y;
		IsMovingL = true;
		IsMovingR = false;
		IsFacingR = false;
	}

	waddle::~waddle()
	{
	}

	void waddle::LoadBitmap()
	{
		// load walk right
		char *walk_right[10] = { ".\\res\\waddledee\\walk\\walkR1.bmp", ".\\res\\waddledee\\walk\\walkR2.bmp", ".\\res\\waddledee\\walk\\walkR3.bmp", ".\\res\\waddledee\\walk\\walkR4.bmp", ".\\res\\waddledee\\walk\\walkR5.bmp", ".\\res\\waddledee\\walk\\walkR6.bmp", ".\\res\\waddledee\\walk\\walkR7.bmp", ".\\res\\waddledee\\walk\\walkR8.bmp", ".\\res\\waddledee\\walk\\walkR9.bmp", ".\\res\\waddledee\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			WaddleMovingR.AddBitmap(walk_right[i], RGB(255, 0, 0));
		}

		// load walk left
		char *walk_left[10] = { ".\\res\\waddledee\\walk\\walkL1.bmp", ".\\res\\waddledee\\walk\\walkL2.bmp", ".\\res\\waddledee\\walk\\walkL3.bmp", ".\\res\\waddledee\\walk\\walkL4.bmp", ".\\res\\waddledee\\walk\\walkL5.bmp", ".\\res\\waddledee\\walk\\walkL6.bmp", ".\\res\\waddledee\\walk\\walkL7.bmp", ".\\res\\waddledee\\walk\\walkL8.bmp", ".\\res\\waddledee\\walk\\walkL9.bmp", ".\\res\\waddledee\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			WaddleMovingL.AddBitmap(walk_left[i], RGB(255, 0, 0));
		}
	}

	void waddle::OnShow()
	{
		if (IsFacingR) {
			WaddleMovingR.SetDelayCount(3);
			WaddleMovingR.SetTopLeft(x, y);
			WaddleMovingR.OnShow();
		}
		else {
			WaddleMovingL.SetDelayCount(3);
			WaddleMovingL.SetTopLeft(x, y);
			WaddleMovingL.OnShow();
		}
	}

	void waddle::OnMove()
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

		if (IsMovingR && x < SIZE_X - ImgW - frame_of_test) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			x += length;
		}
		else if (x >=  SIZE_X - ImgW - frame_of_test) {
			IsMovingR = false;
			IsMovingL = true;
		}

		WaddleMovingL.OnMove();
		WaddleMovingR.OnMove();
		// WaddleStand.OnMove();
		// WaddleStandL.OnMove();
	}

	void waddle::SetXY(int x_in, int y_in) {
		x = x_in;
		y = y_in;
	}
}