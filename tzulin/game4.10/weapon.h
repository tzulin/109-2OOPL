#ifndef WEAPON_H
#define WEAPON_H

namespace game_framework {
	class weapon {
	public:
		weapon();
		void LoadBitmap(char** pic, int* rgb, int n);
		void OnShow();
		void OnMove();
		void SetShow(bool);
		void SetXy(int enemyX, int enemyY, bool enemyFaceL);
		int* GetXy();
	protected:
		CAnimation PlayAttack;
		int x, y;
		int ImgW = 75, ImgH = 128;
		int enemyImgH = 60;
		bool IsShow;
	};
}

#endif