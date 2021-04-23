#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "things.h"

namespace game_framework {
	void starBlock::LoadBitmap() {
		starBlockPic.LoadBitmap(IDB_STARBLOCK);
	}

	void starBlock::setXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	void starBlock::onShow() {
		starBlockPic.SetTopLeft(x, y);
		starBlockPic.ShowBitmap();
	}

	void blankBlock::setHW(int input_h, int input_w) {
		height = input_h;
		width = input_w;
	}

	void blankBlock::setXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}
}