/*
functions for holding the conditions of  different 
object interact
*/

#include <iostream>

#include "./kirby.h"
#include "./enemy.h"
// #include "./weapon.h"
// #include "./things.h"

template <class T, class U>

bool Meet(T a, U b) {
	int* aXy = a.GetXy();
	int* bXy = b.GetXy();

	// a 在 b 的右邊碰到 b
	if (aXy[0] > bXy[0] && aXy[0] < bXy[2]) {
		// a 在 b 的下面碰到 b
		if (aXy[1] > bXy[1] && aXy[1] < bXy[3]) {
			delete[] bXy;
			delete[] aXy;
			a.SetOtherFromL(false);
			b.SetOtherFromL(true);
			return true;
		}
		// a 在 b 的上面碰到 b
		else if (aXy[3] > bXy[1] && aXy[3] < bXy[3]) {
			delete[] bXy;
			delete[] aXy;
			a.SetOtherFromL(false);
			b.SetOtherFromL(true);
			return true;
		}
	}
	// a 在 b 的左邊碰到 b
	/*
	else if (aXy[2] > bXy[0] && aXy[2] < bXy[2]) {
		if (aXy[1] > bXy[1] && aXy[1] < bXy[3]) {
			delete[] bXy;
			delete[] aXy;
			a.SetOtherFromL(true);
			b.SetOtherFromL(false);
			return true;
		}
		else if (aXy[3] > bXy[1] && aXy[3] < bXy[3]) {
			delete[] bXy;
			delete[] aXy;
			a.SetOtherFromL(true);
			b.SetOtherFromL(false);
			return true;
		}
	}
	*/
	delete[] bXy;
	delete[] aXy;
	return false;
}