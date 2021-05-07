#ifndef ENEMY_H
#define ENEMY_H

#include "./kirby.h"
#include "./weapon.h"

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
		bool MeetKirby(kirby & k);
		virtual bool SeeKirby(kirby k);
		void Attack(kirby k, int time);
		// virtual void SetAttack();

	protected:
		CAnimation MovingL;
		CAnimation MovingR;
		CAnimation AttackR;
		CAnimation AttackL;
		CAnimation Stand;
		CAnimation StandL;
		weapon wL;
		weapon wR;

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
		int LastAttack;
		bool KirbyFromL;
	};
}

#endif