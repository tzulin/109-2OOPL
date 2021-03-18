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
		void SetMovingLeft(bool input);
		void SetMovingRight(bool input);
	private:
		CMovingBitmap now;
		int x, y;
		bool IsMovingLeft;
		bool IsMovingRight;
	};
}