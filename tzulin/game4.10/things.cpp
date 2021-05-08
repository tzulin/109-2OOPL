#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "things.h"

namespace game_framework {

	starBlock::starBlock() {
		IsShow = true;
	}

	void starBlock::LoadBitmap() {
		starBlockPic.LoadBitmap(IDB_STARBLOCK);
	}

	void starBlock::SetXy(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	int* starBlock::GetHw() {
		return new int[2]{ starBlockPic.Height(), starBlockPic.Width() };
	}

	int* starBlock::GetXy() {
		return new int[4]{ x, y , x + starBlockPic.Width(), y + starBlockPic.Height() };
	}

	bool starBlock::GetShow() {
		return IsShow;
	}

	void starBlock::OnShow() {
		starBlockPic.SetTopLeft(x, y);
		starBlockPic.ShowBitmap();
	}

	void starBlock::SetShow(bool input) {
		IsShow = input;
	}

	void blankBlock::SetHw(int input_h, int input_w) {
		height = input_h;
		width = input_w;
	}

	void blankBlock::SetXy(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}
}