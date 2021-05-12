#ifndef KIRBY_H
#define KIRBY_H

// #include "./enemy.h"
#include "./weapon.h"
#include "./things.h"


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// class kirby
//
/////////////////////////////////////////////////////////////////////////////

	
	class kirby {
	public:
		kirby();
		~kirby();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetXY(int x_in, int y_in);
		void SetMovingL(bool input);
		void SetMovingR(bool input);
		void SetFacingR(bool input);
		void SetFacingL(bool input);
		void SetDown(bool input);
		void SetAttack(bool input);
		void SetJump(bool input);
		void SetFly(bool input);
		void SetEaten(bool input);
		void SetCounter(int);
		void SetBlockers(int** input_blockers);
		void Hurt(int input, int time);
		void ThrowStar();
		void YouAreLeft(bool YouAreLeft);
		weapon GetWeapon();

		int GetCase();
		int GetHp();
		int* GetXy();
		int GetWidth();
		int GetHeight();
		bool IsAlive();
		bool IsScreamR();
		bool IsScreamL();

	private:
		CAnimation KirbyMovingL;
		CAnimation KirbyMovingR;
		CAnimation KirbyFatMovingL;
		CAnimation KirbyFatMovingR;
		CAnimation KirbyStand;
		CAnimation KirbyStandL;
		CAnimation KirbyFatStand;
		CAnimation KirbyFatStandL;
		CAnimation KirbyJumpR;
		CAnimation KirbyJumpL;
		CAnimation KirbyScreamR;
		CAnimation KirbyScreamL;
		CAnimation KirbyDownAttackR;
		CAnimation KirbyDownAttackL;
		CAnimation KirbyFlyR;
		CAnimation KirbyFlyingR;
		CAnimation KirbyFlyL;
		CAnimation KirbyFlyingL;
		CAnimation KirbyHurtR;
		CAnimation KirbyHurtL;

		CMovingBitmap KirbyDownR;
		CMovingBitmap KirbyDownL;

		weapon StarThrow;

		int** blockerXys;

		int x, y, hp;
		const int ImgW = 60, ImgH = 60;
		int sky_top;		// 天頂y座標
		int floor;			// 地板y座標
		int init_velocity;	// 初始速度
		int velocity;		// 目前速度
		int init_fly_velocity;	// 初始飛行速度
		int fly_velocity;	// kirby inAir 時的飛行速度
		int game_state_counter;		// game state counter
		int LastHurt;				// last hurt time 初始為零
		bool IsRising;		// true表示上升
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
		bool IsDown; 
		bool IsAttack;
		bool InAir;
		bool IsJumping;
		bool IsFlying;
		bool IsFat;
		bool FlyUp;
		bool OtherFromL;
		bool IsHurt;
		bool IsEaten;
	};
}

#endif