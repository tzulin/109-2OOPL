#include "stdafx.h"
#include "source/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "source/audio.h"
#include "source/gamelib.h"
/*
#include "enemy.h"
#include "waddle.h"
*/
#include "Header.h"

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

		// load attack right
		for (int i = 0; i < 5; i++) {
			AttackR.AddBitmap(".\\res\\waddledee\\walk\\walkR1.bmp");
		}

		// load attack left
		for (int i = 0; i < 5; i++) {
			AttackL.AddBitmap(".\\res\\waddledee\\walk\\walkL1.bmp");
		}
	}

	void waddle::Reset() {
		/*const int origin_x = (SIZE_X - ImgW - frame_of_test) / 2;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;*/
		hp = 1;
		power = 1;
		kind = "waddle";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = false;
	}

	/*
	bool waddle::SeeKirby(kirby k) {
		return false;
	}
	*/
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

		// load attack right
		for (int i = 0; i < 10; i++) {
			AttackR.AddBitmap(".\\res\\waddledoo\\walk\\walkR1.bmp");
		}

		// load attack left
		for (int i = 0; i < 10; i++) {
			AttackL.AddBitmap(".\\res\\waddledoo\\walk\\walkL5.bmp");
		}

		// load weapon bitmap
		char* weapon_left[10] = { ".\\res\\weapon\\waddledoo\\attackL1.bmp", ".\\res\\weapon\\waddledoo\\attackL2.bmp", ".\\res\\weapon\\waddledoo\\attackL3.bmp", ".\\res\\weapon\\waddledoo\\attackL4.bmp", ".\\res\\weapon\\waddledoo\\attackL5.bmp", ".\\res\\weapon\\waddledoo\\attackL6.bmp", ".\\res\\weapon\\waddledoo\\attackL7.bmp", ".\\res\\weapon\\waddledoo\\attackL8.bmp", ".\\res\\weapon\\waddledoo\\attackL9.bmp", ".\\res\\weapon\\waddledoo\\attackL10.bmp" };
		char* weapon_right[10] = { ".\\res\\weapon\\waddledoo\\attackR1.bmp", ".\\res\\weapon\\waddledoo\\attackR2.bmp", ".\\res\\weapon\\waddledoo\\attackR3.bmp", ".\\res\\weapon\\waddledoo\\attackR4.bmp", ".\\res\\weapon\\waddledoo\\attackR5.bmp", ".\\res\\weapon\\waddledoo\\attackR6.bmp", ".\\res\\weapon\\waddledoo\\attackR7.bmp", ".\\res\\weapon\\waddledoo\\attackR8.bmp", ".\\res\\weapon\\waddledoo\\attackR9.bmp", ".\\res\\weapon\\waddledoo\\attackR10.bmp" };
		int rgb[3] = { 255, 255, 255 };
		wL.LoadBitmap(weapon_left, rgb, 10);
		wR.LoadBitmap(weapon_right, rgb, 10);
	}

	void waddleDoo::Reset() {
		/*const int origin_x = SIZE_X - ImgW - frame_of_test;
		const int origin_y = SIZE_Y - 60 - ImgH;
		x = origin_x;
		y = origin_y;*/
		hp = 2;
		power = 1;
		kind = "waddleDoo";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = true;
	}

	void sparky::LoadBitmap()
	{
		// load walk right
		char *walk_right[6] = { ".\\res\\sparky\\R1.bmp", ".\\res\\sparky\\R2.bmp", ".\\res\\sparky\\R3.bmp", ".\\res\\sparky\\R4.bmp", ".\\res\\sparky\\R5.bmp", ".\\res\\sparky\\R6.bmp" };
		for (int i = 0; i < 6; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(0, 0, 255));
		}

		// load walk left
		char *walk_left[6] = { ".\\res\\sparky\\L1.bmp", ".\\res\\sparky\\L2.bmp", ".\\res\\sparky\\L3.bmp", ".\\res\\sparky\\L4.bmp", ".\\res\\sparky\\L5.bmp", ".\\res\\sparky\\L6.bmp" };
		for (int i = 0; i < 6; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(0, 0, 255));
		}

		// load attack right
		for (int i = 0; i < 2; i++) {
			AttackR.AddBitmap(".\\res\\sparky\\attack1.bmp", RGB(0, 0, 255));
			AttackR.AddBitmap(".\\res\\sparky\\attack2.bmp", RGB(0, 0, 255));
		}

		// load attack left
		for (int i = 0; i < 2; i++) {
			AttackL.AddBitmap(".\\res\\sparky\\attack1.bmp", RGB(0, 0, 255));
			AttackL.AddBitmap(".\\res\\sparky\\attack2.bmp", RGB(0, 0, 255));
		}

		// load weapon bitmap
		char* weapon[4] = { ".\\res\\weapon\\sparky\\attack1.bmp", ".\\res\\weapon\\sparky\\attack2.bmp", ".\\res\\weapon\\sparky\\attack3.bmp", ".\\res\\weapon\\sparky\\attack4.bmp" };
		int rgb[3] = { 0, 0, 255 };
		wL.LoadBitmap(weapon, rgb, 4);
		wR.LoadBitmap(weapon, rgb, 4);
	}

	void sparky::Reset() {
		hp = 1;
		power = 1;
		kind = "sparky";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = true;
	}

	void hotHead::LoadBitmap()
	{
		// load walk right
		char *walk_right[8] = { ".\\res\\hotHead\\walkR1.bmp", ".\\res\\hotHead\\walkR2.bmp", ".\\res\\hotHead\\walkR3.bmp", ".\\res\\hotHead\\walkR4.bmp", ".\\res\\hotHead\\walkR5.bmp", ".\\res\\hotHead\\walkR6.bmp", ".\\res\\hotHead\\walkR7.bmp", ".\\res\\hotHead\\walkR8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load walk left
		char *walk_left[8] = { ".\\res\\hotHead\\walkL1.bmp", ".\\res\\hotHead\\walkL2.bmp", ".\\res\\hotHead\\walkL3.bmp", ".\\res\\hotHead\\walkL4.bmp", ".\\res\\hotHead\\walkL5.bmp", ".\\res\\hotHead\\walkL6.bmp", ".\\res\\hotHead\\walkL7.bmp", ".\\res\\hotHead\\walkL8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load attack right
		for (int i = 0; i < 3; i++) {
			AttackR.AddBitmap(".\\res\\hotHead\\attackR1.bmp", RGB(255, 255, 255));
			AttackR.AddBitmap(".\\res\\hotHead\\attackR2.bmp", RGB(255, 255, 255));
			AttackR.AddBitmap(".\\res\\hotHead\\attackR3.bmp", RGB(255, 255, 255));
		}

		// load attack left
		for (int i = 0; i < 3; i++) {
			AttackL.AddBitmap(".\\res\\hotHead\\attackL1.bmp", RGB(255, 255, 255));
			AttackL.AddBitmap(".\\res\\hotHead\\attackL2.bmp", RGB(255, 255, 255));
			AttackL.AddBitmap(".\\res\\hotHead\\attackL3.bmp", RGB(255, 255, 255));
		}

		// load weapon bitmap
		char* weapon_left[4] = { ".\\res\\weapon\\hotHead\\attackL1.bmp", ".\\res\\weapon\\hotHead\\attackL2.bmp", ".\\res\\weapon\\hotHead\\attackL3.bmp", ".\\res\\weapon\\hotHead\\attackL4.bmp" };
		char* weapon_right[4] = { ".\\res\\weapon\\hotHead\\attackR1.bmp", ".\\res\\weapon\\hotHead\\attackR2.bmp", ".\\res\\weapon\\hotHead\\attackR3.bmp", ".\\res\\weapon\\hotHead\\attackR4.bmp" };
		int rgb[3] = { 255, 255, 255 };
		wL.LoadBitmap(weapon_left, rgb, 4);
		wR.LoadBitmap(weapon_right, rgb, 4);
	}

	void hotHead::Reset() {
		hp = 1;
		power = 1;
		kind = "hotHead";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = true;
	}

	void droppy::LoadBitmap()
	{
		// load walk right
		char *walk_right[8] = { ".\\res\\droppy\\walkR1.bmp", ".\\res\\droppy\\walkR2.bmp", ".\\res\\droppy\\walkR3.bmp", ".\\res\\droppy\\walkR4.bmp", ".\\res\\droppy\\walkR5.bmp", ".\\res\\droppy\\walkR6.bmp", ".\\res\\droppy\\walkR7.bmp", ".\\res\\droppy\\walkR8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}
		for (int i = 6; i >= 0; i--)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load walk left
		char *walk_left[8] = { ".\\res\\droppy\\walkL1.bmp", ".\\res\\droppy\\walkL2.bmp", ".\\res\\droppy\\walkL3.bmp", ".\\res\\droppy\\walkL4.bmp", ".\\res\\droppy\\walkL5.bmp", ".\\res\\droppy\\walkL6.bmp", ".\\res\\droppy\\walkL7.bmp", ".\\res\\droppy\\walkL8.bmp" };
		for (int i = 0; i < 8; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}
		for (int i = 6; i >= 0; i--)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load attack right
		for (int i = 0; i < 5; i++) {
			AttackR.AddBitmap(".\\res\\droppy\\walkR1.bmp");
		}

		// load attack left
		for (int i = 0; i < 5; i++) {
			AttackL.AddBitmap(".\\res\\droppy\\walkL1.bmp");
		}
	}

	void droppy::Reset() {
		hp = 1;
		power = 1;
		kind = "droppy";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = false;
	}

	void bigWaddle::LoadBitmap() {
		// load walk right
		char *walk_right[10] = { ".\\res\\bigwaddledee\\walkR1.bmp", ".\\res\\bigwaddledee\\walkR2.bmp", ".\\res\\bigwaddledee\\walkR3.bmp", ".\\res\\bigwaddledee\\walkR4.bmp", ".\\res\\bigwaddledee\\walkR5.bmp", ".\\res\\bigwaddledee\\walkR6.bmp", ".\\res\\bigwaddledee\\walkR7.bmp", ".\\res\\bigwaddledee\\walkR8.bmp", ".\\res\\bigwaddledee\\walkR9.bmp", ".\\res\\bigwaddledee\\walkR10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 0, 0));
		}

		// load walk left
		char *walk_left[10] = { ".\\res\\bigwaddledee\\walkL1.bmp", ".\\res\\bigwaddledee\\walkL2.bmp", ".\\res\\bigwaddledee\\walkL3.bmp", ".\\res\\bigwaddledee\\walkL4.bmp", ".\\res\\bigwaddledee\\walkL5.bmp", ".\\res\\bigwaddledee\\walkL6.bmp", ".\\res\\bigwaddledee\\walkL7.bmp", ".\\res\\bigwaddledee\\walkL8.bmp", ".\\res\\bigwaddledee\\walkL9.bmp", ".\\res\\bigwaddledee\\walkL10.bmp" };
		for (int i = 0; i < 10; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 0, 0));
		}

		// load attack right
		for (int i = 0; i < 5; i++) {
			AttackR.AddBitmap(".\\res\\bigwaddledee\\walkR1.bmp");
		}

		// load attack left
		for (int i = 0; i < 5; i++) {
			AttackL.AddBitmap(".\\res\\bigwaddledee\\walkL1.bmp");
		}
	}

	void bigWaddle::Reset() {
		hp = 1;
		power = 1;
		kind = "bigWaddle";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		LastHurt = 0;
		HasWeapon = false;
	}

	void kingDedede::LoadBitmap() {
		// load walk right
		char *walk_right[7] = { ".\\res\\king_dedede\\walk\\walkR1.bmp", ".\\res\\king_dedede\\walk\\walkR2.bmp", ".\\res\\king_dedede\\walk\\walkR3.bmp", ".\\res\\king_dedede\\walk\\walkR4.bmp", ".\\res\\king_dedede\\walk\\walkR5.bmp", ".\\res\\king_dedede\\walk\\walkR6.bmp", ".\\res\\king_dedede\\walk\\walkR7.bmp"};
		for (int i = 0; i < 7; i++)
		{
			MovingR.AddBitmap(walk_right[i], RGB(255, 255, 255));
		}

		// load walk left
		char *walk_left[7] = { ".\\res\\king_dedede\\walk\\walkL1.bmp", ".\\res\\king_dedede\\walk\\walkL2.bmp", ".\\res\\king_dedede\\walk\\walkL3.bmp", ".\\res\\king_dedede\\walk\\walkL4.bmp", ".\\res\\king_dedede\\walk\\walkL5.bmp", ".\\res\\king_dedede\\walk\\walkL6.bmp", ".\\res\\king_dedede\\walk\\walkL7.bmp" };
		for (int i = 0; i < 7; i++)
		{
			MovingL.AddBitmap(walk_left[i], RGB(255, 255, 255));
		}

		// load attack right
		char *attack_right[8] = { ".\\res\\king_dedede\\attack\\attackR1.bmp", ".\\res\\king_dedede\\attack\\attackR2.bmp", ".\\res\\king_dedede\\attack\\attackR3.bmp", ".\\res\\king_dedede\\attack\\attackR4.bmp", ".\\res\\king_dedede\\attack\\attackR5.bmp", ".\\res\\king_dedede\\attack\\attackR6.bmp", ".\\res\\king_dedede\\attack\\attackR7.bmp", ".\\res\\king_dedede\\attack\\attackR8.bmp" };
		for (int i = 0; i < 8; i++) {
			AttackR.AddBitmap(attack_right[i], RGB(255, 255, 255));
		}

		// load attack left
		char *attack_left[8] = { ".\\res\\king_dedede\\attack\\attackL1.bmp", ".\\res\\king_dedede\\attack\\attackL2.bmp", ".\\res\\king_dedede\\attack\\attackL3.bmp", ".\\res\\king_dedede\\attack\\attackL4.bmp", ".\\res\\king_dedede\\attack\\attackL5.bmp", ".\\res\\king_dedede\\attack\\attackL6.bmp", ".\\res\\king_dedede\\attack\\attackL7.bmp", ".\\res\\king_dedede\\attack\\attackL8.bmp" };
		for (int i = 0; i < 8; i++) {
			AttackL.AddBitmap(attack_left[i], RGB(255, 255, 255));
		}

		// Load hurt right
		for (int i = 0;i < 5;i++) {
			HurtR.AddBitmap(".\\res\\king_dedede\\hurt\\hurtR1.bmp", RGB(255, 255, 255));
		}
		for (int i = 0;i < 5;i++) {
			HurtR.AddBitmap(".\\res\\king_dedede\\hurt\\hurtR2.bmp", RGB(255, 255, 255));
		}

		// Load hurt left
		for (int i = 0;i < 2;i++) {
			HurtL.AddBitmap(".\\res\\king_dedede\\hurt\\hurtL1.bmp", RGB(255, 255, 255));
		}
		for (int i = 0;i < 2;i++) {
			HurtL.AddBitmap(".\\res\\king_dedede\\hurt\\hurtL2.bmp", RGB(255, 255, 255));
		}
		
		char* weapon_left = { ".\\res\\weapon\\1.bmp" };
		int rgb[3] = { 255, 255, 255 };
		wL.LoadBitmap(weapon_left, rgb, 100);
		wR.LoadBitmap(weapon_left, rgb, 100);
	}

	void kingDedede::Reset() {
		hp = 10;
		power = 2;
		ImgH = MovingL.Height();
		ImgW = MovingL.Width();
		kind = "kingDedede";
		IsFacingR = false;
		IsMovingL = true;
		IsMovingR = false;
		IsAttack = false;
		IsHurt = false;
		LastHurt = 0;
		HasWeapon = true;
		CanAttack = false;
	}

	void kingDedede::OnShow()
	{
		if (IsHurt) {
			if (!IsFacingR) {
				HurtL.SetDelayCount(3);
				HurtL.SetTopLeft(x, y);
				HurtL.OnMove();
				HurtL.OnShow();
				if (HurtL.IsFinalBitmap()) {
					IsHurt = false;
					HurtL.Reset();
				}
			}
			else {
				HurtR.SetDelayCount(3);
				HurtR.SetTopLeft(x, y);
				HurtR.OnMove();
				HurtR.OnShow();
				if (HurtR.IsFinalBitmap()) {
					IsHurt = false;
					HurtR.Reset();
				}
			}
		}
		else if (!IsAttack) {
			if (IsMovingR) {
				MovingR.SetDelayCount(3);
				MovingR.SetTopLeft(x, y);
				MovingR.OnShow();
				ImgH = MovingR.Height();
				ImgW = MovingL.Width();
			}
			else {
				MovingL.SetDelayCount(3);
				MovingL.SetTopLeft(x, y);
				MovingL.OnShow();
				ImgH = MovingL.Height();
				ImgW = MovingL.Width();
			}
		}
		else {
			if (OtherFromL) {
				AttackL.SetDelayCount(5);
				AttackL.SetTopLeft(x, y - 50);
				AttackL.OnShow();
				wL.SetOwner(kind);
				wL.SetWeapon(x, y - 50, IsFacingR);
				wL.SetShow(true);
				wL.OnMove();
				wL.OnShow();
				if (AttackL.IsFinalBitmap()) {
					AttackL.Reset();
					wL.AnimationReset();
					IsAttack = false;
					wL.SetShow(true);
				}
				ImgH = AttackL.Height();
				ImgW = AttackL.Width();
			}
			else {
				AttackR.SetDelayCount(5);
				AttackR.SetTopLeft(x, y - 50);
				AttackR.OnShow();
				wR.SetOwner(kind);
				wR.SetWeapon(x, y - 50, IsFacingR);
				wR.SetShow(true);
				wR.OnMove();
				wR.OnShow();
				if (AttackR.IsFinalBitmap()) {
					AttackR.Reset();
					wR.AnimationReset();
					IsAttack = false;
					wR.SetShow(true);
				}
				ImgH = AttackR.Height();
				ImgW = AttackR.Width();
			}
		}

	}

	void kingDedede::OnMove()
	{

		// set moving XY
		const int length = 2;

		if (!IsAttack && !IsHurt) {
			MovingL.OnMove();
			MovingR.OnMove();
			// set moving XY and frame of test 
			if (IsMovingL && x >= Map->Left()) {
				if (IsFacingR) {
					IsFacingR = false;
				}
				SetXy(x - length, y);
			}
			else if (x <= Map->Left()) {
				IsMovingL = false;
				IsMovingR = true;
			}

			if (IsMovingR && x <= Map->Left() + Map->Width() - ImgW) {
				if (!IsFacingR) {
					IsFacingR = true;
				}
				SetXy(x + length, y);
			}
			else if (x >= Map->Left() + Map->Width() - ImgW) {
				IsMovingR = false;
				IsMovingL = true;
			}
		}
		else {
			AttackR.OnMove();
			AttackL.OnMove();
		}
	}

	void kingDedede::Hurt(int input, int time) {
		if (abs(LastHurt - time) < 30) {
			return;
		}
		if (IsAttack) {
			return;
		}
		IsHurt = true;
		BackX(OtherFromL);
		LastHurt = time;
		hp -= input;
	}
}