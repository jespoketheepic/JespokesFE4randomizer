
/* Function for determining if a given class is compatible with a characters gender */
/* Returns 0 if the class is compatible with the gender, 1 if they are incompatible */
int GenderMatch(unsigned char gender, unsigned char class)
{
  /* NOTE: REMEMBER TO MAKE SURE THE PROMO OPTIONS ADHERE TO THIS! 
     They can both be on the list, just not separate sides. */
  
  switch(class)
  {
    /*case 0x04:*/  /* Im accepting Free- and Forest Knight in the pool, because i want them there. It is only invisible weapons anyway */
    case 0x06:
    case 0x09:
    /*case 0x0C:*/
    case 0x25:  
    case 0x2C:
    case 0x2E:
    case 0x27:
    case 0x29:
    case 0x2D:
      if (gender == 0x00){  /* Male only */
        return 0; /* For male this is fine */
      }
      else{
        return 1; /* For female this is not fine */
      }
      break;
    case 0x05:
    case 0x0A:
    case 0x10:
    case 0x11:
    case 0x32:
    case 0x2F:
    case 0x30:
    case 0x3C:
      if (gender == 0x01){  /* Female only */
        return 0; /* For female this is fine */
      }
      else{
        return 1; /* For male this is not fine */
      }
      break;
    default:;         /* Works either way */
  }

  return 0;
}

/* Classes confirmed to be unisex: 
* Marks classes that i didn't test because i know they exist in both genders in vanilla.
0x00, Cavalier
0x01, Lance Knight
0x02, Arch Knight
0x03, Axe Knight
0x07, Duke Knight
0x08, Master Knight*
0x0B, Bow Knight
0x0D, Mage Knight, unique map sprite and everything
0x0E, Great Knight
0x13, Dragon Knight*
0x14, Dragonmaster*
0x15, Archer(Bow Fighter)
0x16, Swordfighter*
0x17, Swordmaster*
0x18, Sniper*
0x19, Hero, unique sprites. ah, Creidne/Radney.
0x1A, General, holy crap Sigurds palete is hideous on a General though
0x33, Priest*
0x34, Plain Mage*
0x35, Fire Mage
0x36, Thunder Mage
0x37, Wind Mage, all of the elemental mages have unique sprites, for both genders.
0x38, High Priest*
0x3A, Sage*
0x3B, Bard
0x3F, Theif*
0x40, Rogue*

*/

/* Classes that "work" unisex: 
0x04, Free Knight, Weapon is invisible
0x0C, Forest Knight, Invisible Weapon

0x25, Sword Armor, Invisible Weapon
0x2C, Junior Lord, Surprisingly only invisible weapon, considering how badly its promotion broke
0x2E, Prince, Invisible Weapon
0x32, Dancer, Invisible Weapon

*/

/* Classes that break in unisex: 
0x06, Lord Knight, Animations totally break but work, however it uses Duke Knight sprites, so it is out.
0x05, Troubador, Animations go to shit, but somehow works as intended.
0x09, Paladin (M), Animations break
0x0A, Paladin (F), Game Crash
0x10, Pegasus Knight, Surprisingly passed the first test, but softlocked on the second. Moving all other classes that break animations to "break" to be safe.
0x11, Falcon Knight, immediatly blinked out of existence.
0x27, Axe Fighter, Animations break.
0x29, Warrior, Softlock.
0x2D, Mage Fighter (M), Used magic fine, but swords softlocked
0x2F, Princess, Seizure inducing crash
0x30, Mage Fighter (F), Like the male version, magic worked, swords and staves softlocked
0x3C, Shaman, Game Crash. It managed to crash the game on a magic animation, a new record!

*/


















