#ifndef SYSTEM_H
#define SYSTEM_H

#include "./kirby.h"
#include "./things.h"

namespace game_framework {
	/*bool CanMoveXy(int* wantToMoveXy, int* BlockXy) {
		bool result = true;
		if (wantToMoveXy[0] > BlockXy[0] && wantToMoveXy[0] < BlockXy[2] && wantToMoveXy[1] > BlockXy[1] && wantToMoveXy[1] < BlockXy[3]) {
			result = false;
		}
		return result;
	}*/

	template < class T >
	bool KirbyCanAttack(kirby & Kirby, T * t) {
		int* StarBlockXy = t->GetXy();
		int* KirbyXy = Kirby.GetXy();
		int for_count = 0;
		for (;for_count < 10;for_count++) {
			int x_different = StarBlockXy[0] - KirbyXy[2];
			int x_different2 = KirbyXy[0] - StarBlockXy[2];
			int y_different = StarBlockXy[1] - KirbyXy[1];
			int y_different2 = KirbyXy[3] - StarBlockXy[3];
			if (x_different > for_count && x_different < 60 && y_different < for_count * 8 && y_different2 < for_count * 8) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
			if (x_different2 > for_count && x_different2 < 60 && y_different < for_count * 8 && y_different2 < for_count * 8) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
		}
		delete[] StarBlockXy;
		delete[] KirbyXy;
		return false;
	}
	

	template <class T, class U>
	bool Meet(T & a, U & b) {
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
						// a在b左邊
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
						// b在a左邊
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
