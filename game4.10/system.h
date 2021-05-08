#ifndef SYSTEM_H
#define SYSTEM_H

#include "./kirby.h"
#include "./things.h"

namespace game_framework {
	template <class T, class U>
	bool Meet(T a, U b) {
		int* aXy = a.GetXy();
		int* bXy = b.GetXy();

		// a�bb������A���I��
		if (aXy[2] > bXy[0] && aXy[2] < bXy[2] && bXy[0] > aXy[0]) {
			// a�bb���W���A���I��
			if (aXy[3] > bXy[1] && aXy[3] < bXy[3] && bXy[1] > aXy[1]) {
				delete[] aXy;
				delete[] bXy;
				return true;
			}
			// a�bb���U���A���I��
			else if (aXy[1] > bXy[1] && aXy[1] < bXy[3] && bXy[3] < aXy[3]) {
				delete[] aXy;
				delete[] bXy;
				return true;
			}
		}
		// a�bb���k��A���I��
		else if (aXy[0] > bXy[0] && aXy[0] < bXy[2] && aXy[2] > bXy[2]) {
			// a�bb���W���A���I��
			if (aXy[3] > bXy[1] && aXy[3] < bXy[3] && bXy[1] > aXy[1]) {
				delete[] aXy;
				delete[] bXy;
				return true;
			}
			// a�bb���U���A���I��
			else if (aXy[1] > bXy[1] && aXy[1] < bXy[3] && bXy[3] < aXy[3]) {
				delete[] aXy;
				delete[] bXy;
				return true;
			}
		}

		// �S�I��
		delete[] aXy;
		delete[] bXy;
 		return false;
	}
}


#endif
