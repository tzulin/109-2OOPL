#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "kirby.h"

namespace game_framework {
	kirby::kirby()
	{
		const int origin_x = 5;
		const int origin_y = SIZE_Y - 5 - img_h;
		x = origin_x;
		y = origin_y;
		IsMovingLeft = false;
		IsMovingRight = false;
	}

	kirby::~kirby()
	{
	}

	void kirby::LoadBitmap()
	{
		// now.LoadBitmap(IDB_KIRBY);
		char *filename[10] = { ".\\res\\walkL1.bmp", ".\\res\\walkL2.bmp", ".\\res\\walkL3.bmp", ".\\res\\walkL4.bmp", ".\\res\\walkL5.bmp", ".\\res\\walkL6.bmp", ".\\res\\walkL7.bmp", ".\\res\\walkL8.bmp", ".\\res\\walkL9.bmp", ".\\res\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			animation.AddBitmap(filename[i], RGB(255, 255, 255));
		}
	}

	void kirby::OnShow()
	{
		// now.SetTopLeft(x, y);
		// now.ShowBitmap();
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

	void kirby::OnMove()
	{
		const int length = 3;

		if (IsMovingLeft && x > 0) {
			x -= length;
		}
		if (IsMovingRight && x < SIZE_X - img_w) {
			x += length;
		}
		animation.OnMove();
	}

	void kirby::SetXY(int x_in, int y_in) {
		x = x_in;
		y = y_in;
	}

	void  kirby::SetMovingLeft(bool input) {
		IsMovingLeft = input;
	}

	void kirby::SetMovingRight(bool input) {
		IsMovingRight = input;
	}
}