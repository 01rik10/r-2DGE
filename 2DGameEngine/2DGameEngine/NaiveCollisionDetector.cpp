#include "NaiveCollisionDetector.h"

void NaiveCollisionDetector::checkCollisions(std::vector<Unit*> units)
{
	for (int i = 0;i < units.size();i++) {
		for (int j = 0; j < units.size();j++) {
			if (i != j);
				//units.at(i)->solve(units.at(j));
		}
	}
}
