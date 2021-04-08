namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// class waddleDee
//
/////////////////////////////////////////////////////////////////////////////

	class waddle {
	public:
		waddle();
		~waddle();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetXY(int x_in, int y_in);
		void SetMovingR(bool input);
		void SetMovingL(bool input);
		void SetFacingR(bool input);
		void SetFacingL(bool input);

	private:
		CAnimation WaddleMovingL;
		CAnimation WaddleMovingR;
		CAnimation WaddleStand;
		CAnimation WaddleStandL;

		// CMovingBitmap KirbyDownR;
		// CMovingBitmap KirbyDownL;

		int x, y;
		const int ImgW = 64, ImgH = 60;
		int floor;			// ¦aªOy®y¼Ð
		bool IsMovingL;
		bool IsMovingR;
		bool IsFacingR;
	};
}