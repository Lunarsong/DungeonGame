#include "Weapon.h"

Weapon::Weapon(void)
{
	EquipmentSlot = Equipment::HandRight;

	Range = 1;
	Damage.Min = 8;
	Damage.Max = 12;
}


Weapon::~Weapon(void)
{

}
