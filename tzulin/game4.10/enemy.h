#ifndef ENEMY_H
#define ENEMY_H

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// class enemy
	//
	/////////////////////////////////////////////////////////////////////////////

	class enemy {
	public:
		enemy();
		~enemy();
		virtual void LoadBitmap();
		void OnMove();
		void OnShow();
		int* GetXy();
		int GetHp();
		int GetWidth();
		int GetHeight();
		void SetHp(int input);
		virtual  void Reset();

	protected:
		CAnimation MovingL;
		CAnimation MovingR;
		CAnimation Stand;
		CAnimation StandL;

		int x, y, hp;
		int origin_x, origin_y;
		const int ImgW = 64, ImgH = 60;
		int floor;			// ¦aªOy®y¼Ð
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
	};
}

#endif