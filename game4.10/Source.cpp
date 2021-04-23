#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "things.h"

namespace game_framework {
	starBlock::LoadBitmap() {
		starBlockPic.LoadBitmap(IDB_STARBLOCK);
	}

	starBlock::setXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	starBlock::onShow() {
		starBockPic.setTopLeft(x, y);
		starBlockPic.onShow();
	}

	starBlock::onMove() {
		starBlockPic.onMove();
	}
}