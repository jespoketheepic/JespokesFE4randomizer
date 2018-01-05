
/* Prototype */
void FillWeaponrankArray(int *weaponrankbuffer, int Swo, int Lan, int Axe, int Bow, int Fir, int Thu, int Wind, int Lig, int Sta);

/* Function for filling out an array with the weapon ranks of a given class */
/* Returns the highest weapon rank */
int ClassWeaponRanks(int *weaponrankbuffer, unsigned char class)
{
  int maxrank;
  
  switch(class)
  {
    case 0x00: /* Cavalier */
      FillWeaponrankArray(weaponrankbuffer,2,1,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x50:  /* Just in case i want to call this function from somewhere where 0x00 would be confused for a ' ' *//* Cavalier */
      FillWeaponrankArray(weaponrankbuffer,2,1,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x01: /* Lance Knight */
      FillWeaponrankArray(weaponrankbuffer,0,2,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x02: /* Arch Knight */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,2,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x03: /* Axe Knight */
      FillWeaponrankArray(weaponrankbuffer,0,0,2,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x04: /* Free Knight */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x05: /* Troubadour */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,0,0,0,0,1);
      maxrank = 2;
      break;
    case 0x06: /* Lord Knight */
      FillWeaponrankArray(weaponrankbuffer,3,2,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x07: /* Duke Knight */
      FillWeaponrankArray(weaponrankbuffer,0,3,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x08: /* Master Knight */
      FillWeaponrankArray(weaponrankbuffer,3,3,3,3,3,3,3,1,3);
      maxrank = 3;
      break;
    case 0x09: /* Paladin (M) */
      FillWeaponrankArray(weaponrankbuffer,2,2,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x0A: /* Paladin (F) */
      FillWeaponrankArray(weaponrankbuffer,2,1,0,0,0,0,0,0,1);
      maxrank = 2;
      break;
    case 0x0B: /* Bow Knight */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,3,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x0C: /* Forest Knight */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x0D: /* Mage Knight */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,2,2,2,0,0);
      maxrank = 2;
      break;
    case 0x0E: /* Great Knight */
      FillWeaponrankArray(weaponrankbuffer,0,0,3,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x10: /* Pegasus Knight */
      FillWeaponrankArray(weaponrankbuffer,2,2,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x11: /* Falcon Knight */
      FillWeaponrankArray(weaponrankbuffer,3,3,0,0,0,0,0,0,1);
      maxrank = 3;
      break;
    case 0x13: /* Dragon Knight */
      FillWeaponrankArray(weaponrankbuffer,2,2,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x14: /* Dragon Master */
      FillWeaponrankArray(weaponrankbuffer,3,3,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x16: /* Myrmidon */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x17: /* Swordmaster */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x18: /* Sniper */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,3,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x19: /* Hero */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x1A:  /* 1B would be Emperor, 1C would be Baron */ /* General */
      FillWeaponrankArray(weaponrankbuffer,3,3,2,2,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x15: /* Archer */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,3,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x25: /* Sword Armor */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x27: /* Axe Fighter */
      FillWeaponrankArray(weaponrankbuffer,0,0,3,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x29: /* Warrior */
      FillWeaponrankArray(weaponrankbuffer,0,0,3,2,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x2C: /* Junior Lord */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,0,0,0,0,0);
      maxrank = 2;
      break;
    case 0x2D:  /* Taking this one out since it is basically strictly worse than the (F) variant */ /* Mage Fighter (M) */
      FillWeaponrankArray(weaponrankbuffer,1,0,0,0,2,2,2,0,0);
      maxrank = 2;
      break;
    case 0x2E: /* Prince */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
    case 0x2F: /* Princess */
      FillWeaponrankArray(weaponrankbuffer,2,0,0,0,0,0,0,0,1);
      maxrank = 2;
      break;
    case 0x30: /* Mage Fighter (F) */
      FillWeaponrankArray(weaponrankbuffer,1,0,0,0,2,2,2,0,2);
      maxrank = 2;
      break;
    case 0x32: /* Here just in case i add Dancers */ /* Dancer */
      FillWeaponrankArray(weaponrankbuffer,1,0,0,0,0,0,0,0,0);
      maxrank = 1;
      break;
    case 0x33: /* Preist */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,0,0,0,0,2);
      maxrank = 2;
      break;
    case 0x34:  /* Plain Mage, just in case i re-add it */ /* Plain Mage */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,1,1,1,0,0);
      maxrank = 1;
      break;
    case 0x35: /* Fire Mage */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,2,0,0,0,0);
      maxrank = 2;
      break;
    case 0x36: /* Thunder Mage */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,0,2,0,0,0);
      maxrank = 2;
      break;
    case 0x37: /* Wind Mage */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,0,0,2,0,0);
      maxrank = 2;
      break;
    case 0x38: /* High Priest */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,1,1,1,0,3);
      maxrank = 3;
      break;
    case 0x3A: /* Sage */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,2,2,2,2,2);
      maxrank = 2;
      break;
    case 0x3B: /* Bard */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,1,1,1,1,0);
      maxrank = 1;
      break;
    case 0x3C: /* Shaman */
      FillWeaponrankArray(weaponrankbuffer,0,0,0,0,0,0,0,3,2);
      maxrank = 3;
      break;
    case 0x3F: /* Theif */
      FillWeaponrankArray(weaponrankbuffer,1,0,0,0,0,0,0,0,0);
      maxrank = 1;
      break;
    case 0x40: /* Rogue */
      FillWeaponrankArray(weaponrankbuffer,3,0,0,0,0,0,0,0,0);
      maxrank = 3;
      break;
  }
  return maxrank;
}


void FillWeaponrankArray(int *weaponrankbuffer, int Swo, int Lan, int Axe, int Bow, int Fir, int Thu, int Wind, int Lig, int Sta)
{
  weaponrankbuffer[0] = Swo;
  weaponrankbuffer[1] = Lan;
  weaponrankbuffer[2] = Axe;
  weaponrankbuffer[3] = Bow;
  weaponrankbuffer[4] = Fir;
  weaponrankbuffer[5] = Thu;
  weaponrankbuffer[6] = Wind;
  weaponrankbuffer[7] = Lig;
  weaponrankbuffer[8] = Sta;
  
  return;
}