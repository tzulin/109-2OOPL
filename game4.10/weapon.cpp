#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
#include "Header.h"

namespace game_framework {

	weapon::weapon() {
		IsShow = false;
		attack_time = 0;
	}

	weapon::~weapon() {}

	void weapon::LoadBitmap(char** pic, int* rgb, int n) {
		for (int i = 0; i < n; i++) {
			PlayAttack.AddBitmap(pic[i], RGB(rgb[0], rgb[1], rgb[2]));
		}
	}

	void weapon::LoadBitmap(char* pic, int* rgb, int n) {
		for (int i = 0; i < n;i++) {
			PlayAttack.AddBitmap(pic, RGB(rgb[0], rgb[1], rgb[2]));
		}
	}

	void weapon::LoadBitmap(int IDB_INPUT, int* rgb, int n) {
		for (int i = 0; i < n; i++) {
			PlayAttack.AddBitmap(IDB_INPUT, RGB(rgb[0], rgb[1], rgb[2]));
		}
	}

	void weapon::OnShow() {
		if (IsShow) {
			PlayAttack.SetDelayCount(5);
			PlayAttack.SetTopLeft(x, y);
			PlayAttack.OnShow();
		}
	}

	void weapon::AnimationReset() {
		PlayAttack.Reset();
	}

	void weapon::OnMove() {
		PlayAttack.OnMove();
		ImgW = PlayAttack.Width();
		ImgH = PlayAttack.Height();
	}

	void weapon::SetShow(bool input) {
		if (input) {
			IsShow = true;
		}
		else {
			IsShow = false;
		}
	}

	void weapon::SetOwner(std::string input) {
		owner = input;
	}

	void weapon::SetWeapon(int enemyX, int enemyY, bool enemyFaceR) {
		if (owner == "waddleDoo") {
			if (enemyFaceR) {
				x = enemyX + enemyImgW;
				y = enemyY - (ImgH - enemyImgH);
			}
			else {
				x = enemyX - ImgW;
				y = enemyY - (ImgH - enemyImgH);
			}
		}
		else if (owner == "sparky") {
			x = enemyX - 20;
			y = enemyY - 20;
		}
		else if (owner == "hotHead") {
			if (enemyFaceR) {
				x = enemyX + enemyImgW + 15;
				y = enemyY + 15;
			}
			else {
				x = enemyX - ImgW;
				y = enemyY + 15;
			}
		}
	}

	void weapon::SetXy(int input_x, int input_y) {
		x = input_x;
		y = input_y;
	}

	void weapon::SetAttackState(int input_attack_time, bool IsFacingR, int* input_Xy) {
		x = input_Xy[0];
		y = input_Xy[1];
		attack_time = input_attack_time;
		AttackIsFacingR = IsFacingR;
	}

	int* weapon::GetXy() {
		return new int[4]{ x, y, x +ImgW, y + ImgW };
	}

	int weapon::GetAttackTime() {
		return attack_time;
	}

	bool weapon::GetAttackFacingR() {
		return AttackIsFacingR;
	}

	bool weapon::WeaponIsShow() {
		return IsShow;
	}

	bool weapon::IsFinalBitmap() {
		return PlayAttack.IsFinalBitmap();
	}

	void weapon::YouAreLeft(bool YouAreLeft) {
		OtherFromL = !YouAreLeft;
	}

	int weapon::Width() {
		return PlayAttack.Width();
	}

	int weapon::Height() {
		return PlayAttack.Height();
	}
}