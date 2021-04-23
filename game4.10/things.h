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
	private:
		CMovingBitmap starBlockPic;
		int x, y;
		bool IsShow;
	};

	class blankBlock {
	public:
		void SetXY(int, int);
		void SetHW(int, int);
	private:
		int x, y;
		int height, width;
	};
}
