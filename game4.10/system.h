#ifndef SYSTEM_H
#define SYSTEM_H

#include "./kirby.h"
#include "./things.h"

namespace game_framework {

	template <class T, class U>
	bool Meet(T a, U b) {
		int* aXy = a.GetXy();
		int* bXy = b.GetXy();
		
		int i = 0, n = 1;
		for (int count = 0; count < 2; count++) {
			for (int _count = 0; _count < 2; _count++) {
				if (aXy[i] > bXy[0] && aXy[i] < bXy[2] && aXy[n] > bXy[1] && aXy[n] < bXy[3]) {
					delete[] aXy;
					delete[] bXy;
					if (i == 0) {
						// b在A左邊
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					else {
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					return true;
				}
				n += 2;
			}
			n = 1;
			i += 2;
		}

		i = 0, n = 1;
		for (int count = 0; count < 2; count++) {
			for (int _count = 0; _count < 2; _count++) {
				if (bXy[i] > aXy[0] && bXy[i] < aXy[2] && bXy[n] > aXy[1] && bXy[n] < aXy[3]) {
					delete[] aXy;
					delete[] bXy;
					if (i == 0) {
						// a在b左邊
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					else {
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					return true;
				}
				n += 2;
			}
			n = 1;
			i += 2;
		}
		
		
		// 沒碰到
		delete[] aXy;
		delete[] bXy;
 		return false;
	}

}


#endif
