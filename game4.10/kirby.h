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
		void DoAnimation();
		void OnMove();
		void OnShow();
		void SetXY(int x_in, int y_in);
		void SetMovingLeft(bool input);
		void SetMovingRight(bool input);
	private:
		CMovingBitmap now;
		CAnimation animation;
		int x, y;
		int img_w = 45, img_h = 40;
		bool IsMovingLeft;
		bool IsMovingRight;
	};
}