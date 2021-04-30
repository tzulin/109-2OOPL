#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "enemy.h"
#include "waddle.h"

namespace game_framework {
	const int frame_of_test = 5;

	void waddle::LoadBitmap()
	{
		// load walk right
		char *walk_right[10] = { ".\\res\\waddledee\\walk\\walkR1.bmp", ".\\res\\waddledee\\walk\\walkR2.bmp", ".\\res\\waddledee\\walk\\walkR3.bmp", ".\\res\\waddledee\\walk\\walkR4.bmp", ".\\res\\waddledee\\walk\\walkR5.bmp", ".\\res\\waddledee\\walk\\walkR6.bmp", ".\\res\\waddledee\\walk\\walkR7.bmp", ".\\res\\waddledee\\walk\\walkR8.bmp", ".\\res\\waddledee\\walk\\walkR9.bmp", ".\\res\\waddledee\\walk\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 0, 0));
		}

		// load walk left
		char *walk_left[10] = { ".\\res\\waddledee\\walk\\walkL1.bmp", ".\\res\\waddledee\\walk\\walkL2.bmp", ".\\res\\waddledee\\walk\\walkL3.bmp", ".\\res\\waddledee\\walk\\walkL4.bmp", ".\\res\\waddledee\\walk\\walkL5.bmp", ".\\res\\waddledee\\walk\\walkL6.bmp", ".\\res\\waddledee\\walk\\walkL7.bmp", ".\\res\\waddledee\\walk\\walkL8.bmp", ".\\res\\waddledee\\walk\\walkL9.bmp", ".\\res\\waddledee\\walk\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 0, 0));
		}
	}

	void waddle::Reset() {
		const int origin_x = (SIZE_X - ImgW - frame_of_test) / 2;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 10;
		power = 1;
	}

	void waddleDoo::LoadBitmap()
	{
		// load walk right
		char *walk_right[9] = { ".\\res\\waddledoo\\walk\\walkR1.bmp", ".\\res\\waddledoo\\walk\\walkR2.bmp", ".\\res\\waddledoo\\walk\\walkR3.bmp", ".\\res\\waddledoo\\walk\\walkR4.bmp", ".\\res\\waddledoo\\walk\\walkR5.bmp", ".\\res\\waddledoo\\walk\\walkR6.bmp", ".\\res\\waddledoo\\walk\\walkR7.bmp", ".\\res\\waddledoo\\walk\\walkR8.bmp", ".\\res\\waddledoo\\walk\\walkR9.bmp" };
		for (int i = 0; i < 9; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(84, 109, 142));
		}

		// load walk left
		char *walk_left[9] = { ".\\res\\waddledoo\\walk\\walkL1.bmp", ".\\res\\waddledoo\\walk\\walkL2.bmp", ".\\res\\waddledoo\\walk\\walkL3.bmp", ".\\res\\waddledoo\\walk\\walkL4.bmp", ".\\res\\waddledoo\\walk\\walkL5.bmp", ".\\res\\waddledoo\\walk\\walkL6.bmp", ".\\res\\waddledoo\\walk\\walkL7.bmp", ".\\res\\waddledoo\\walk\\walkL8.bmp", ".\\res\\waddledoo\\walk\\walkL9.bmp" };
		for (int i = 0; i < 9; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(84, 109, 142));
		}
	}

	void waddleDoo::Reset() {
		const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;
		hp = 10;
		power = 2;
	}

}