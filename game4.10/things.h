#ifndef THINGS_H
#define THINGS_H

namespace game_framework {
	class thing {
	public:
		thing();
		virtual ~thing();
		virtual void LoadBitmap();
		virtual bool isStarBlock();
		void OnShow();
		void SetShow(bool);
		void SetXY(int, int);
		int* GetHw();
		int* GetXy();
		bool GetShow();
		void YouAreLeft(bool);
		int Top();
		int Left();
		std::string GetKind();
		void SetKind(std::string input);
	protected:
		CMovingBitmap blockPic;
		int x, y;
		bool IsShow;
		std::string name = "";
	};

	class starBlock : public thing {
		void LoadBitmap() override;
		bool isStarBlock() override;
	};

	class blankBlock : public thing {
		void LoadBitmap() override;
		bool isStarBlock() override;
	};
}

#endif
