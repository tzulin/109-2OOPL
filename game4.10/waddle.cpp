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
		const int origin_x = (SIZE_X - ImgW - frame_of_test) / 2;
		const int origin_y = SIZE_Y - 60 - ImgH;
		const int INIT_HP = 0;
		hp = INIT_HP;
		x = origin_x;
		y = origin_y;
		floor = SIZE_Y - 60;
		IsMovingL = true;
		IsMovingR = false;
		IsFacingR = false;
	}

	waddle::~waddle()
	{
	}

	int* waddle::GetXy() {
		return new int[2]{ x, y };
	}

	int waddle::GetHp() {
		return hp;
	}

	int waddle::GetWeight() {
		return ImgW;
	}

	int waddle::GetHeight() {
		return ImgH;
	}

	void waddle::SetHp(int input) {
		hp = input;
	}

	void waddle::Reset() {
		const int origin_x = (SIZE_X - ImgW - frame_of_test) / 2;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 1;
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

		if (IsMovingR && x < SIZE_X/2 - ImgW ) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			x += length;
		}
		else if (x >=  SIZE_X/2 - ImgW) {
			IsMovingR = false;
			IsMovingL = true;
		}

		WaddleMovingL.OnMove();
		WaddleMovingR.OnMove();
	}

	waddleDoo::waddleDoo()
	{
		// waddle constructor
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		const int INIT_HP = 0;
		hp = INIT_HP;
		x = origin_x;
		y = origin_y;
		floor = SIZE_Y - 60;
		IsMovingL = true;
		IsMovingR = false;
		IsFacingR = false;
	}

	waddleDoo::~waddleDoo()
	{
	}

	int* waddleDoo::GetXy() {
		return new int[2]{ x, y };
	}

	int waddleDoo::GetHp() {
		return hp;
	}

	int waddleDoo::GetWeight() {
		return ImgW;
	}

	int waddleDoo::GetHeight() {
		return ImgH;
	}

	void waddleDoo::SetHp(int input) {
		hp = input;
	}

	void waddleDoo::Reset() {
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 1;
	}

	void waddleDoo::LoadBitmap()
	{
		// load walk right
		char *walk_right[9] = { ".\\res\\waddledoo\\walk\\walkR1.bmp", ".\\res\\waddledoo\\walk\\walkR2.bmp", ".\\res\\waddledoo\\walk\\walkR3.bmp", ".\\res\\waddledoo\\walk\\walkR4.bmp", ".\\res\\waddledoo\\walk\\walkR5.bmp", ".\\res\\waddledoo\\walk\\walkR6.bmp", ".\\res\\waddledoo\\walk\\walkR7.bmp", ".\\res\\waddledoo\\walk\\walkR8.bmp", ".\\res\\waddledoo\\walk\\walkR9.bmp" };
		for (int i = 0; i < 9; i++)
		{
			WaddleDooMovingR.AddBitmap(walk_right[i], RGB(84, 109, 142));
		}

		// load walk left
		char *walk_left[9] = { ".\\res\\waddledoo\\walk\\walkL1.bmp", ".\\res\\waddledoo\\walk\\walkL2.bmp", ".\\res\\waddledoo\\walk\\walkL3.bmp", ".\\res\\waddledoo\\walk\\walkL4.bmp", ".\\res\\waddledoo\\walk\\walkL5.bmp", ".\\res\\waddledoo\\walk\\walkL6.bmp", ".\\res\\waddledoo\\walk\\walkL7.bmp", ".\\res\\waddledoo\\walk\\walkL8.bmp", ".\\res\\waddledoo\\walk\\walkL9.bmp" };
		for (int i = 0; i < 9; i++)
		{
			WaddleDooMovingL.AddBitmap(walk_left[i], RGB(84, 109, 142));
		}
	}

	void waddleDoo::OnShow()
	{
		if (IsFacingR) {
			WaddleDooMovingR.SetDelayCount(3);
			WaddleDooMovingR.SetTopLeft(x, y);
			WaddleDooMovingR.OnShow();
		}
		else {
			WaddleDooMovingL.SetDelayCount(3);
			WaddleDooMovingL.SetTopLeft(x, y);
			WaddleDooMovingL.OnShow();
		}
	}

	void waddleDoo::OnMove()
	{
		// set moving XY
		const int length = 2;

		// set moving XY and frame of test 
		if (IsMovingL && x > SIZE_X / 2) {
			if (IsFacingR) {
				IsFacingR = false;
			}
			x -= length;
		}
		else if (x <= SIZE_X / 2) {
			IsMovingL = false;
			IsMovingR = true;
		}

		if (IsMovingR && x < SIZE_X - ImgW - frame_of_test) {
			if (!IsFacingR) {
				IsFacingR = true;
			}
			x += length;
		}
		else if (x >= SIZE_X - ImgW - frame_of_test) {
			IsMovingR = false;
			IsMovingL = true;
		}

		WaddleDooMovingR.OnMove();
		WaddleDooMovingL.OnMove();
	}
}