#ifndef THINGS_H
#define THINGS_H

namespace game_framework {
	class starBlock {
	public:
		void LoadBitmap();
		void OnShow();
		void SetShow(bool);
		void SetXy(int, int);
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
		void SetXy(int, int);
		void SetHw(int, int);
	private:
		int x, y;
		int height, width;
	};
}

#endif
