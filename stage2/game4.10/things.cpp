#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
//#include "things.h"
#include "Header.h"

namespace game_framework {

	thing::thing() {
		IsShow = true;
	}

	void thing::LoadBitmap(){}

	void thing::SetXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	void thing::YouAreLeft(bool input) {

	}

	int* thing::GetHw() {
		return new int[2]{ blockPic.Height(), blockPic.Width() };
	}

	int* thing::GetXy() {
		return new int[4]{ x, y , x + blockPic.Width(), y + blockPic.Height() };
	}

	bool thing::GetShow() {
		return IsShow;
	}

	void thing::OnShow() {
		blockPic.SetTopLeft(x, y);
		blockPic.ShowBitmap();
	}

	void thing::SetShow(bool input) {
		IsShow = input;
	}

	int thing::Top() {
		return y;
	}

	int thing::Left() {
		return x;
	}

	bool thing::isStarBlock() {
		return false;
	}

	void starBlock::LoadBitmap() {
		blockPic.LoadBitmap(IDB_STARBLOCK);
	}

	bool starBlock::isStarBlock() {
		return true;
	}

	void blankBlock::LoadBitmap() {
		blockPic.LoadBitmap(".\\res\\blankBlock.bmp", RGB(0, 0, 0));
	}

	bool blankBlock::isStarBlock() {
		return false;
	}

	/*
	starBlock::starBlock() {
		IsShow = true;
	}

	void starBlock::LoadBitmap() {
		starBlockPic.LoadBitmap(IDB_STARBLOCK);
	}

	void starBlock::SetXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	void starBlock::YouAreLeft(bool input) {

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

	int starBlock::Top() {
		return y;
	}

	int starBlock::Left() {
		return x;
	}

	void blankBlock::SetHW(int input_h, int input_w) {
		height = input_h;
		width = input_w;
	}

	void blankBlock::SetXY(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}
	*/

}