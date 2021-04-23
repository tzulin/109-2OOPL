namespace game_framework {
	class starBlock {
	public:
		void LoadBitmap();
		void onShow();
		void setXY(int, int);
	private:
		CMovingBitmap starBlockPic;
		int x, y;
	};

	class blankBlock {
	public:
		void setXY(int, int);
		void setHW(int, int);
	private:
		int x, y;
		int height, width;
	};
}
