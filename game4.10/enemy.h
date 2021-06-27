#ifndef ENEMY_H
#define ENEMY_H

#include "./kirby.h"
#include "./things.h"
#include "./weapon.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// class enemy
	//
	/////////////////////////////////////////////////////////////////////////////
	class kirby;

	class enemy {
	public:
		enemy();
		virtual ~enemy();
		virtual void LoadBitmap();
		virtual void Reset();
		virtual void OnShow();
		virtual void Hurt(int input, int time);
		virtual void OnMove();
		int* GetXy();
		int GetHp();
		int GetWidth();
		int GetHeight();
		int GetPower();
		std::string GetKind();
		int Top();
		int Left();
		void SetXy(int input_x, int input_y);
		void SetThings(std::vector<thing*> input_ThingList);
		// void SetThings(starBlock** Blocks_input, int input_number);
		void BackX(bool fromL);
		void Attack(kirby k, int time);
		void YouAreLeft(bool YouAreLeft);
		bool EnemyFacingR();
		bool EnemyHasWeapon();
		bool GetCanAttack();
		void SetCounter(int input) {
			game_state_counter = input;
		}

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

		vector<thing*> StarBlockList;
		// starBlock ** StarBlockList = nullptr;
		// int number_of_star_blocks = 0;

		int x, y, hp;
		int power;			// §ðÀ»¤O
		int origin_x, origin_y;
		int ImgW = 64, ImgH = 60;
		int floor;			// ¦aªOy®y¼Ð
		bool IsFacingR;
		bool IsMovingL;
		bool IsMovingR;
		bool IsAttack;
		bool IsHurt;
		int LastHurt;
		int LastAttack;
		bool OtherFromL;
		bool HasWeapon;
		bool CanAttack;
		std::string kind;
		int game_state_counter, x_old = 0, y_old = 0, m_x_old = 0, m_y_old = 0;
	};
}

#endif