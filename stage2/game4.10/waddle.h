#ifndef WADDLE_H
#define WADDLE_H

#include "./enemy.h"
#include "./weapon.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// class waddleDee and waddleDoo
	//
	/////////////////////////////////////////////////////////////////////////////

	class waddle : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
		//bool SeeKirby(kirby k) override;
	};

	class waddleDoo : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

}

#endif