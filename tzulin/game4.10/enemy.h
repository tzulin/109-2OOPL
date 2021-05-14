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
		void SetXy(int input_x, int input_y);
		void BackX(bool fromL);
		void Hurt(int input, int time);
		virtual void Reset();
		void Attack(kirby k, int time);
		void YouAreLeft(bool YouAreLeft);
		bool EnemyFacingR();
		void SetMap(CMovingBitmap * Map);
		weapon GetWeapon();

	protected:
		CAnimation MovingL;
		CAnimation MovingR;
		CAnimation AttackR;
		CAnimation AttackL;
		CAnimation Stand;
		CAnimation StandL;
		weapon wL;
		weapon wR;

		CMovingBitmap* Map;

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
		bool OtherFromL;
	};
}

#endif