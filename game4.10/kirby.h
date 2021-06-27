#ifndef KIRBY_H
#define KIRBY_H

#include <vector>
#include "./enemy.h"
#include "./weapon.h"
#include "./things.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// class kirby
//
/////////////////////////////////////////////////////////////////////////////
	
	class kirby {
	public:
		virtual void SetAttack(bool input);
		virtual void SetKindInit();
		virtual void SetEaten(bool input);
		virtual void SetEaten(bool input, std::string name);
		virtual void LoadBitmap();
		virtual void ThrowStar();
		virtual void OnMove();
		virtual void OnShow();
		virtual weapon* GetWeapon();

		kirby();
		virtual ~kirby();
		void kirby::StageReSet(int hp_left, std::string kind);
		void SetXY(int x_in, int y_in);
		void SetMovingL(bool input);
		void SetMovingR(bool input);
		void SetFacingR(bool input);
		void SetFacingL(bool input);
		void SetDown(bool input);
		void SetJump(bool input);
		void SetFly(bool input);
		void SetCounter(int);
		void SetHack(bool input);
		void SetKind(std::string input);

		void SetEnemies(std::vector<enemy*> input_EnemyList);
		void SetThings(std::vector<thing*> input_ThingList);
		void SetMap(CMovingBitmap* Map);
		void SetDoor(CMovingBitmap* door);
		void SetRun(bool input);
		bool Hurt(int input, int time);
		void YouAreLeft(bool YouAreLeft);

		std::string GetKind();
		int GetCase();
		int GetHp();
		int* GetXy();
		int GetWidth();
		int GetHeight();
		std::string GetEatenEnemy();
		bool GetEaten();
		bool GetIsGround();
		bool IsAlive();
		bool IsScreamR();
		bool IsScreamL();
		bool GetFacingR() {
			return IsFacingR;
		}
		//bool GetUpKey();

		void KirbyCopy(kirby* new_kirby);

	protected:
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
		CMovingBitmap * Map;
		CMovingBitmap * Door;

		std::vector<enemy*> EnemyList;
		std::vector<thing*> StarBlockList;
		// starBlock ** StarBlockList;
		// int number_of_star_blocks;
		weapon StarThrow;

		std::string EatenEnemy = "";
		std::string kirby_kind;
		int x, y, hp;
		const int ImgW = 60, ImgH = 60;
		int now_img_w, now_img_h;
		int sky_top;		// �ѳ�y�y��
		int floor;			// �a�Oy�y��
		int init_velocity;	// ��l�t��
		int velocity;		// �ثe�t��
		int init_fly_velocity;	// ��l����t��
		int fly_velocity;	// kirby inAir �ɪ�����t��
		int game_state_counter;		// game state counter
		int LastHurt;				// last hurt time ��l���s
		int BoundaryTop, BoundaryRight, BoundaryLeft; // boundary 
		bool IsRising;		// true��ܤW��
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
		bool YouAreGround;
		bool IsRun;
		bool IsHack;
	};

	class normal_kirby : public kirby {};

	class sparky_kirby : public kirby {
	public:
		void SetEaten(bool input) override;
		void SetEaten(bool input, std::string name) override;
		void LoadBitmap() override;
		void OnMove() override;
		void ThrowStar() override;
		void SetKindInit() override;
	};

	class hotHead_kirby : public kirby {
	public:
		void SetEaten(bool input) override;
		void SetEaten(bool input, std::string name) override;
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;
		void ThrowStar() override;
		void SetKindInit() override;
		weapon* GetWeapon() override;
	protected:
		weapon left_side;
	};

	class waddleDoo_kirby : public kirby {
	public:
		void SetEaten(bool input) override;
		void SetEaten(bool input, std::string name) override;
		void LoadBitmap() override;
		void OnMove() override;
		void OnShow() override;
		void ThrowStar() override;
		void SetKindInit() override;
		void SetAttack(bool input) override;
	protected:
		weapon left_side;
	};
}

#endif