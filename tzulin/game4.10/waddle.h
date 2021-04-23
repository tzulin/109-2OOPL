#ifndef WADDLE_H
#define WADDLE_H

#include "./enemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// class waddleDee and waddleDoo
	//
	/////////////////////////////////////////////////////////////////////////////

	class waddle : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class waddleDoo : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

}

#endif