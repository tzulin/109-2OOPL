namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// class waddleDee and waddleDoo
//
/////////////////////////////////////////////////////////////////////////////

	class waddle {
	public:
		waddle();
		~waddle();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		int* GetXy();
		int GetHp();
		int GetWeight();
		int GetHeight();
		void SetHp(int input);
		void Reset();

	private:
		CAnimation WaddleMovingL;
		CAnimation WaddleMovingR;
		CAnimation WaddleStand;
		CAnimation WaddleStandL;

		int x, y, hp;
		const int ImgW = 64, ImgH = 60;
		int floor;			// 地板y座標
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
	};


	class waddleDoo {
	public:
		waddleDoo();
		~waddleDoo();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		int* GetXy();
		int GetHp();
		int GetWeight();
		int GetHeight();
		void SetHp(int input);
		void Reset();

	private:
		CAnimation WaddleDooMovingL;
		CAnimation WaddleDooMovingR;
		CAnimation WaddleDooStand;
		CAnimation WaddleDooStandL;

		int x, y, hp;
		const int ImgW = 64, ImgH = 60;
		int floor;			// 地板y座標
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
	};
}