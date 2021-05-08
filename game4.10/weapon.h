#ifndef WEAPON_H
#define WEAPON_H

namespace game_framework {
	class weapon {
	public:
		weapon();
		~weapon();
		void LoadBitmap(char** pic, int* rgb, int n);
		void LoadBitmap(int IDB_INPUT, int* rgb, int n);
		void OnShow();
		void OnMove();
		void AnimationReset();
		void SetShow(bool);
		void SetWeapon(int enemyX, int enemyY, bool enemyFaceR);
		void SetXy(int, int);
		void SetAttackState(int attack_time, bool IsFacingR, int* input_Xy);
		int GetAttackTime();
		int* GetXy();
		bool GetAttackFacingR();
	protected:
		CAnimation PlayAttack;
		int x, y;
		int ImgW = 75, ImgH = 128;
		int enemyImgH = 60, enemyImgW = 60;
		int attack_time;
		bool IsShow;
		bool AttackIsFacingR;
	};
}

#endif