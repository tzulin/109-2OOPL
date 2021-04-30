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
		int GetPower();
		void BackX(bool fromL);
		void Hurt(int input, int time);
		virtual void Reset();
		// virtual void SetAttack();

	protected:
		CAnimation MovingL;
		CAnimation MovingR;
		CAnimation Stand;
		CAnimation StandL;

		int x, y, hp;
		int power;			// §ðÀ»¤O
		int origin_x, origin_y;
		const int ImgW = 64, ImgH = 60;
		int floor;			// ¦aªOy®y¼Ð
		bool IsFacingR;
		bool IsMovingL;
		bool IsMovingR;
		bool IsAttack;
		bool IsHurt;
		int LastHurt;
	};
}

#endif