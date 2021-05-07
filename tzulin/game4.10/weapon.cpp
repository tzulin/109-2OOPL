#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "weapon.h"
#include "enemy.h"

namespace game_framework {

	weapon::weapon() {
		IsShow = false;
	}

	void weapon::LoadBitmap(char** pic, int* rgb, int n) {
		for (int i = 0; i < n; i++) {
			PlayAttack.AddBitmap(pic[i], RGB(rgb[0], rgb[1], rgb[2]));
		}
	}

	void weapon::OnShow() {
		if (IsShow) {
			PlayAttack.SetDelayCount(3);
			PlayAttack.SetTopLeft(x, y);
			PlayAttack.OnShow();
			if (PlayAttack.IsFinalBitmap()) {
				PlayAttack.Reset();
				IsShow = false;
			}
		}
	}

	void weapon::OnMove() {
		PlayAttack.OnMove();
	}

	void weapon::SetShow(bool input) {
		if (input) {
			IsShow = true;
		}
		else {
			IsShow = false;
		}
	}
	void weapon::SetXy(int enemyX, int enemyY, bool enemyFaceL) {
		if (enemyFaceL) {
			x = enemyX - ImgW;
			y = enemyY - (ImgH - enemyImgH);
		}
	}

	int* weapon::GetXy() {
		return new int[4]{ x, y, x + ImgW, y + ImgH };
	}


}