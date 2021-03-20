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

	private:
		CAnimation KirbyMovingL;
		CAnimation KirbyMovingR;
		CAnimation KirbyStand;
		CAnimation KirbyStandL;
		CMovingBitmap KirbyDownR;
		CMovingBitmap KirbyDownL;
		CMovingBitmap KirbyDownAttackR;
		CMovingBitmap KirbyDownAttackL;

		int x, y;
		const int ImgW = 60, ImgH = 60;
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
		bool IsDown; 
		bool IsAttack;
	};
}