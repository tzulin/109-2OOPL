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
		void SetHp(int input);

		int GetCase();
		int GetHp();
		int* GetXy();
		int GetWidth();
		int GetHeight();
		bool IsAlive();

	private:
		CAnimation KirbyMovingL;
		CAnimation KirbyMovingR;
		CAnimation KirbyStand;
		CAnimation KirbyStandL;
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

		CMovingBitmap KirbyDownR;
		CMovingBitmap KirbyDownL;

		int x, y, hp;
		const int ImgW = 60, ImgH = 60;
		int sky_top;		// 天頂y座標
		int floor;			// 地板y座標
		int init_velocity;	// 初始速度
		int fly_velocity;	// kirby inAir 時的飛行速度
		int velocity;		// 目前速度
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
		// bool KeyPressed;								// 有按鍵被按下
	};
}