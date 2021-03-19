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
		void SetFacingRight(bool input);
		void SetFacingLeft(bool input);
		void SetDown(bool input);
	private:
		CAnimation KirbyMovingL;
		CAnimation KirbyMovingR;
		CAnimation KirbyStand;
		CAnimation KirbyStandL;
		CMovingBitmap KirbyDownR;
		CMovingBitmap KirbyDownL;

		int x, y;
		int ImgW = 60, ImgH = 60;
		bool IsMovingLeft;
		bool IsMovingRight;
		bool IsFacingRight;
		bool IsDown; 
	};
}