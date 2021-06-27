#ifndef HEADER_H
#define HEADER_H

namespace game_framework {

	class thing {
	public:
		virtual void LoadBitmap();
		virtual bool isStarBlock();
		void OnShow();
		void SetShow(bool);
		void SetXY(int, int);
		thing();
		virtual ~thing();
		int* GetHw();
		int* GetXy();
		bool GetShow();
		void YouAreLeft(bool);
		int Top();
		int Left();
		std::string GetKind();
		void SetKind(std::string input);
	protected:
		CMovingBitmap blockPic;
		int x, y;
		bool IsShow;
		std::string name = "";
	};

	class starBlock : public thing {
		void LoadBitmap() override;
		bool isStarBlock() override;
	};

	class blankBlock : public thing {
		void LoadBitmap() override;
		bool isStarBlock() override;
	};

	class weapon {
	public:
		weapon();
		~weapon();
		void LoadBitmap(char** pic, int* rgb, int n);
		void LoadBitmap(int IDB_INPUT, int* rgb, int n);
		void LoadBitmap(char* pic, int* rgb, int n);
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
		bool IsFinalBitmap();
		void SetOwner(std::string which_enemy);
		int Width();
		int Height();
	protected:
		CAnimation PlayAttack;
		int x, y;
		int ImgW = 75, ImgH = 128;
		int enemyImgH = 60, enemyImgW = 60;
		int attack_time;
		bool IsShow;
		bool AttackIsFacingR;
		bool OtherFromL;
		std::string owner;
	};

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
		void SetThings(vector<thing*> input_ThingList);
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
		int power;			// 攻擊力
		int origin_x, origin_y;
		int ImgW = 64, ImgH = 60;
		int floor;			// 地板y座標
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

	class sparky : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class hotHead : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class droppy : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class bigWaddle : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class kingDedede : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
		void OnShow() override;
		void Hurt(int input, int time) override;
		void OnMove() override;
	protected:
		CAnimation HurtR, HurtL;
	};

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

		void SetEnemies(vector<enemy*> input_EnemyList);
		void SetThings(vector<thing*> input_ThingList);
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

		vector<enemy*> EnemyList;
		vector<thing*> StarBlockList;
		// starBlock ** StarBlockList;
		// int number_of_star_blocks;
		weapon StarThrow;

		std::string EatenEnemy = "";
		std::string kirby_kind;
		int x, y, hp;
		const int ImgW = 60, ImgH = 60;
		int now_img_w, now_img_h;
		int sky_top;		// 天頂y座標
		int floor;			// 地板y座標
		int init_velocity;	// 初始速度
		int velocity;		// 目前速度
		int init_fly_velocity;	// 初始飛行速度
		int fly_velocity;	// kirby inAir 時的飛行速度
		int game_state_counter;		// game state counter
		int LastHurt;				// last hurt time 初始為零
		int BoundaryTop, BoundaryRight, BoundaryLeft; // boundary 
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

	inline bool EnemyCanAttack(enemy & e, kirby & k) {
		int* kirbyXy = k.GetXy();
		int* enemyXY = e.GetXy();
		// enemy 在 kirby 右邊
		if (enemyXY[0] - e.GetWidth() - 10 < kirbyXy[2] && enemyXY[0]  > kirbyXy[2] && !e.EnemyFacingR()) {
			if (kirbyXy[1] - enemyXY[1] < 150) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(false);
				return true;
			}
		}
		// enemy 在 kirby 左邊
		else if (enemyXY[2] + e.GetWidth() + 10 > kirbyXy[0] && enemyXY[2] < kirbyXy[0] && e.EnemyFacingR()) {				// enemy meet kirby from right
			if (kirbyXy[1] - enemyXY[1] < 150) {
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
		for (; for_count < 10; for_count++) {
			int x_different = (StarBlockXy[0] + StarBlockXy[2]) / 2 - (KirbyXy[0] + KirbyXy[2]) / 2;
			int x_different2 = (KirbyXy[0] + KirbyXy[2]) / 2 - (StarBlockXy[0] + StarBlockXy[2]) / 2;
			int y_different = StarBlockXy[1] - KirbyXy[1];
			int y_different2 = KirbyXy[3] - StarBlockXy[3];
			if (x_different >= for_count && x_different <= 150 && y_different <= for_count * 8 && y_different2 <= for_count * 8 && Kirby.IsScreamR()) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
			if (x_different2 >= for_count && x_different2 <= 150 && y_different <= for_count * 8 && y_different2 <= for_count * 8 && Kirby.IsScreamL()) {
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
						// b在A左邊
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					else {
						// a在b左邊
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
						// a在b左邊
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					else {
						// b在a左邊
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
		// 沒碰到
		delete[] aXy;
		delete[] bXy;
		return false;
	}

}

#endif
