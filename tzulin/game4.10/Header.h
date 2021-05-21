#ifndef HEADER_H
#define HEADER_H

namespace game_framework {
	class starBlock {
	public:
		void LoadBitmap();
		void OnShow();
		void SetShow(bool);
		void SetXY(int, int);
		starBlock();
		int* GetHw();
		int* GetXy();
		bool GetShow();
		void YouAreLeft(bool);
		int Top();
		int Left();
	private:
		CMovingBitmap starBlockPic;
		int x, y;
		bool IsShow;
	};

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
		void YouAreLeft(bool YouAreLeft);
		bool GetAttackFacingR();
		bool WeaponIsShow();
	protected:
		CAnimation PlayAttack;
		int x, y;
		int ImgW = 75, ImgH = 128;
		int enemyImgH = 60, enemyImgW = 60;
		int attack_time;
		bool IsShow;
		bool AttackIsFacingR;
		bool OtherFromL;
	};

	class blankBlock {
	public:
		void SetXY(int, int);
		void SetHW(int, int);
	private:
		int x, y;
		int height, width;
	};

	class kirby;

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
		int Top();
		int Left();
		void SetXy(int input_x, int input_y);
		void SetThings(starBlock** Blocks_input, int input_number);
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

		starBlock ** StarBlockList = nullptr;
		int number_of_star_blocks = 0;

		int x, y, hp;
		int power;			// �����O
		int origin_x, origin_y;
		const int ImgW = 64, ImgH = 60;
		int floor;			// �a�Oy�y��
		bool IsFacingR;
		bool IsMovingL;
		bool IsMovingR;
		bool IsAttack;
		bool IsHurt;
		int LastHurt;
		int LastAttack;
		bool OtherFromL;
	};

	class waddle : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
		//bool SeeKirby(kirby k) override;
	};

	class waddleDoo : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

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

		void SetMap(CMovingBitmap* Map);
		void SetDoor(CMovingBitmap* door);
		void SetThings(starBlock** Blocks_input, int input_number);
		void SetWaddles(waddle** waddles_input, int input_number);
		void SetWaddleDoos(waddleDoo** waddle_doos_input, int input_number);
		void SetRun(bool input);
		void Hurt(int input, int time);
		void ThrowStar();
		void YouAreLeft(bool YouAreLeft);
		weapon* GetWeapon();

		int GetCase();
		int GetHp();
		int* GetXy();
		int GetWidth();
		int GetHeight();
		bool IsAlive();
		bool IsScreamR();
		bool IsScreamL();
		bool GetUpKey();

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
		CMovingBitmap * Map;
		CMovingBitmap * Door;

		waddle** WaddleList;
		waddleDoo** WaddleDooList;
		starBlock ** StarBlockList;
		int number_of_star_blocks, number_of_waddles, number_of_waddle_doos;
		weapon StarThrow;


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
		bool IsRising;		// true���ܤW��
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
	};

	inline bool EnemyCanAttack(enemy & e, kirby & k) {
		int* kirbyXy = k.GetXy();
		int* enemyXY = e.GetXy();
		// enemy �b kirby �k��
		if (enemyXY[0] - 80 > kirbyXy[0] && enemyXY[0] - 80 < kirbyXy[2] && !e.EnemyFacingR()) {
			if (enemyXY[1] > kirbyXy[1] && enemyXY[1] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(false);
				return true;
			}
			else if (enemyXY[3] > kirbyXy[1] && enemyXY[3] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(false);
				return true;
			}
		}
		// enemy �b kirby ����
		else if (enemyXY[2] + 80 > kirbyXy[0] && enemyXY[2] + 80 < kirbyXy[2] && e.EnemyFacingR()) {				// enemy meet kirby from right
			if (enemyXY[1] > kirbyXy[1] && enemyXY[1] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(true);
				return true;
			}
			else if (enemyXY[3] > kirbyXy[1] && enemyXY[3] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(true);
				return true;
			}
		}
		delete[] kirbyXy;
		delete[] enemyXY;
		return false;
	}

	template < class T >
	bool KirbyCanAttack(kirby & Kirby, T * t) {
		int* StarBlockXy = t->GetXy();
		int* KirbyXy = Kirby.GetXy();
		int for_count = 0;
		for (;for_count < 10;for_count++) {
			int x_different = StarBlockXy[0] - KirbyXy[2];
			int x_different2 = KirbyXy[0] - StarBlockXy[2];
			int y_different = StarBlockXy[1] - KirbyXy[1];
			int y_different2 = KirbyXy[3] - StarBlockXy[3];
			if (x_different > for_count && x_different < 60 && y_different < for_count * 8 && y_different2 < for_count * 8 && Kirby.IsScreamR()) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
			if (x_different2 > for_count && x_different2 < 60 && y_different < for_count * 8 && y_different2 < for_count * 8 && Kirby.IsScreamL()) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
		}
		delete[] StarBlockXy;
		delete[] KirbyXy;
		return false;
	}

	template <class T, class U>
	bool Meet(T & a, U & b) {
		int* aXy = a.GetXy();
		int* bXy = b.GetXy();

		int i = 0, n = 1;
		for (int count = 0; count < 2; count++) {
			for (int _count = 0; _count < 2; _count++) {
				if (aXy[i] > bXy[0] && aXy[i] < bXy[2] && aXy[n] > bXy[1] && aXy[n] < bXy[3]) {
					delete[] aXy;
					delete[] bXy;
					if (i == 0) {
						// b�bA����
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					else {
						// a�bb����
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					return true;
				}
				n += 2;
			}
			n = 1;
			i += 2;
		}

		i = 0, n = 1;
		for (int count = 0; count < 2; count++) {
			for (int _count = 0; _count < 2; _count++) {
				if (bXy[i] > aXy[0] && bXy[i] < aXy[2] && bXy[n] > aXy[1] && bXy[n] < aXy[3]) {
					delete[] aXy;
					delete[] bXy;
					if (i == 0) {
						// a�bb����
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					else {
						// b�ba����
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					return true;
				}
				n += 2;
			}
			n = 1;
			i += 2;
		}
		// �S�I��
		delete[] aXy;
		delete[] bXy;
		return false;
	}
}

#endif