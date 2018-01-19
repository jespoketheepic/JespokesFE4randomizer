
void MatchWeapon(FILE *rom, int header, unsigned char class, unsigned char weaponID, unsigned char *spareweapons)
{
  unsigned char weaponbuffer;
  int weaponrankbuffer[9], classrank, weaponrank, i, selectionbuffer[9], count;
  /* Gen 1 has 2 Slim Swords, and a Slim Lance to give out */
  /* Gen 2 has a Slim Sword, and 2 Slim Lances to give out */
  
  classrank = ClassWeaponRanks(weaponrankbuffer, class);
  
  fseek(rom, WEAPONENTRY + header + weaponID, SEEK_SET);
  weaponbuffer = fgetc(rom);
  
  /* Determine what rank the given weapon has (Bad blades are downgraded) */
  switch(weaponbuffer)
  {
    case 0xFF:  /* No weapon */
      return;
    
    case 0x00: /* C rank cases */
    /*case 0x03:*/
    case 0x1C:
    case 0x28:
    case 0x31:
    case 0x3E:
    case 0x43:
    case 0x48:
    case 0x58:

      weaponrank = 1;
      break;
    case 0x02:  /* A rank cases */
    case 0x05:
    case 0x1E:
    case 0x2A:
    case 0x33:
    case 0x40:
    case 0x45:
    case 0x4A:
    case 0x5A:

      weaponrank = 3;
      break;
    default : /* Any B rank weapon, slim weapon, and unaccounted for weapon gets a B */
      weaponrank = 2;
      break;
  }
  
  /* Tone down the weapon rank to the lower of the 2 */
  if(classrank < weaponrank)
  {
    weaponrank = classrank;
  }
  
  count = 0;
  /* Pick out options for what weapon to give */
  for(i = 0; i < 9; i++)
  {
    if(weaponrankbuffer[i] == classrank)
    {
      selectionbuffer[count] = i;
      count++;
    }
  }
  /* Pick out what weapon to give */
  /* The fixed value is the location of the iron variant of the weapontype */
  switch(selectionbuffer[rand() % count])
  {
    case 0: /* Sword */
      weaponbuffer = 0x00 + weaponrank - 1;
      break;
    case 1: /* Lance */
      weaponbuffer = 0x1C + weaponrank - 1;
      break;
    case 2: /* Axe */
      weaponbuffer = 0x28 + weaponrank - 1;
      break;
    case 3: /* Bow */
      weaponbuffer = 0x31 + weaponrank - 1;
      break;
    case 4: /* Fire */
      weaponbuffer = 0x3E + weaponrank - 1;
      break;
    case 5: /* Thunder */
      weaponbuffer = 0x43 + weaponrank - 1;
      break;
    case 6: /* Wind */
      weaponbuffer = 0x48 + weaponrank - 1;
      break;
    case 7: /* Light, there is no B rank light, and Lightning is better than Aura too */
      weaponbuffer = 0x4D;
      break;
    case 8: /* Staff */
      weaponbuffer = 0x58 + weaponrank - 1;
      break;
    
  }
  
  /* Reimbursement box */
  /* Slim Sword. There is almost inevitably someone who gets an Iron Sword, so no need to delete steel swords for this */
  /* Sylvia takes one if nobody else wants it */
  if(spareweapons[0] && (weaponbuffer == 0x00)) 
  {
    weaponbuffer = 0x0D;
    spareweapons[0]--;
  } 
  if(spareweapons[1] && (weaponbuffer == 0x1C || weaponbuffer == 0x1D)) /* Slim Lance, lances are less certain. And Slim Lance > Steel Lance is much more clear than with swords */
  {
    weaponbuffer = 0x22;
    spareweapons[1]--;
  }
  
  /* Write to file */
  fseek(rom, WEAPONENTRY + header + weaponID, SEEK_SET);
  fputc(weaponbuffer, rom);
  
  /* I don't feel like this needs to be printed to the log */
  
  return;
}







