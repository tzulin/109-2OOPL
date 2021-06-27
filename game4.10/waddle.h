#ifndef WADDLE_H
#define WADDLE_H

#include "./enemy.h"
#include "./weapon.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// class enemies
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

	class sparky : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class hotHead : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class droppy : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class bigWaddle : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
	};

	class kingDedede : public enemy {
	public:
		void LoadBitmap() override;
		void Reset() override;
		void OnShow() override;
		void Hurt(int input, int time) override;
		void OnMove() override;
	protected:
		CAnimation HurtR, HurtL;
	};
}

#endif