#ifndef SYSTEM_H
#define SYSTEM_H

#include "./kirby.h"
#include "./enemy.h"

namespace game_framework {
	inline bool EnemyCanAttack(enemy & e, kirby & k) {
		int* kirbyXy = k.GetXy();
		int* enemyXY = e.GetXy();
		// enemy �b kirby �k��
		if (enemyXY[0] - 80 > kirbyXy[0] && enemyXY[0] - 80 < kirbyXy[2] && !e.EnemyFacingR()) {
			if (enemyXY[1] > kirbyXy[1] && enemyXY[1] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(false);
				return true;
			}
			else if (enemyXY[3] > kirbyXy[1] && enemyXY[3] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(false);
				return true;
			}
		}
		// enemy �b kirby ����
		else if (enemyXY[2] + 80 > kirbyXy[0] && enemyXY[2] + 80 < kirbyXy[2] && e.EnemyFacingR()) {				// enemy meet kirby from right
			if (enemyXY[1] > kirbyXy[1] && enemyXY[1] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(true);
				return true;
			}
			else if (enemyXY[3] > kirbyXy[1] && enemyXY[3] < kirbyXy[3]) {
				delete[] kirbyXy;
				delete[] enemyXY;
				e.YouAreLeft(true);
				return true;
			}
		}
		delete[] kirbyXy;
		delete[] enemyXY;
		return false;
	}

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
			if (x_different > for_count && x_different < 60 && y_different < for_count * 8 && y_different2 < for_count * 8 && Kirby.IsScreamR()) {
				delete[] StarBlockXy;
				delete[] KirbyXy;
				return true;
			}
			if (x_different2 > for_count && x_different2 < 60 && y_different < for_count * 8 && y_different2 < for_count * 8 && Kirby.IsScreamL()) {
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
						// b�bA����
						a.YouAreLeft(false);
						b.YouAreLeft(true);
					}
					else {
						// a�bb����
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
						// a�bb����
						a.YouAreLeft(true);
						b.YouAreLeft(false);
					}
					else {
						// b�ba����
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
		// �S�I��
		delete[] aXy;
		delete[] bXy;
		return false;
	}
}


#endif