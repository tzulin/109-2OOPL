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
		const int origin_y = SIZE_Y - 5 - 150;
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
		now.LoadBitmap(IDB_KIRBY);
	}

	void kirby::OnShow()
	{
		now.SetTopLeft(x, y);
		now.ShowBitmap();
	}

	void kirby::OnMove()
	{
		const int lenth = 3;

		if (IsMovingLeft && x > 0) {
			x -= lenth;
		}
		if (IsMovingRight && x < SIZE_X - 200) {
			x += lenth;
		}
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