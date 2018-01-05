
/* Function for mixing up base stats */
void RandomizeBases(unsigned char *entrybuffer, unsigned char diffsetting)
{
  /* entrybuffer[0-7] here correspond to HP, Str, Mag, Skl, Spd, Def, Res, Lck */
  signed int basetotal = 0, rntotal = 0, i;
  
  /* Remember HP counts for half, and gains double */
  basetotal += entrybuffer[0]/2;
  /* Take out makeshift base HP of 16 */
  basetotal -= 8;
  entrybuffer[0] = rand() % 1000;
  rntotal += entrybuffer[0];
  
  for(i = 1; i < 8; i++)
  {
    basetotal += entrybuffer[i];
    entrybuffer[i] = rand() % 1000;
    rntotal += entrybuffer[i];
  }
  
  /* Take off points for difficulty. -0x30 makes an ASCII number into its int value.*/
  basetotal -= (diffsetting - 0x30)*2;
  if(basetotal < 0)
  {
    basetotal = 0;
  }
  
  for(i = 0; i < 8; i++)
  {
    /* Random number divided by rntotal is how big a slice of the basetotal pie that stat gets */
    entrybuffer[i] = (entrybuffer[i]*basetotal)/rntotal;
  }
  
  /* Remainders are dumped in HP */
  entrybuffer[0] += basetotal - (entrybuffer[0] + entrybuffer[1] + entrybuffer[2] + entrybuffer[3] + entrybuffer[4] + entrybuffer[5] + entrybuffer[6] + entrybuffer[7]);
  
  /* Re-add makeshift base HP */
  entrybuffer[0] += 8;
  /* HP is redoubled */
  entrybuffer[0] *= 2;

  return;
}