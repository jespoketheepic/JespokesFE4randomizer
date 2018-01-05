
/* Function for mixing up growths */
void RandomizeGrowths(unsigned char *entrybuffer, unsigned char diffsetting)
{
  /* entrybuffer[0-7] here correspond to HP, Str, Mag, Skl, Spd, Def, Res, Lck */
  signed int growthtotal = 0, rntotal = 0, i;
  
  /* Remember HP counts for half, and gains double */
  /* Everything is divided by 5 and re-multiplied at the end to get pretty numbers that are easier to process and memorize. It also eliminates 1% growths */
  growthtotal += entrybuffer[0]/10;
  entrybuffer[0] = rand() % 1000;
  rntotal += entrybuffer[0];
  
  for(i = 1; i < 8; i++)
  {
    growthtotal += entrybuffer[i]/5;
    entrybuffer[i] = rand() % 1000;
    rntotal += entrybuffer[i];
  }
  
  /* Take off points for difficulty. -0x30 makes an ASCII number into its int value. Since we divided by 5, 4 means 20% */
  growthtotal -= (diffsetting - 0x30) * 4;
  if(growthtotal < 0)
  {
    growthtotal = 0;
  }
  
  for(i = 0; i < 8; i++)
  {
    /* Random number divided by rntotal is how big a slice of the basetotal pie that stat gets */
    /* */
    entrybuffer[i] = (entrybuffer[i]*growthtotal)/rntotal;
    entrybuffer[i] *= 5;
  }
  
  /* Remainders are dumped randomly */
  while(growthtotal*5 > (entrybuffer[0] + entrybuffer[1] + entrybuffer[2] + entrybuffer[3] + entrybuffer[4] + entrybuffer[5] + entrybuffer[6] + entrybuffer[7]))
  {
    entrybuffer[(rand()%8)] += 5;
  }
  
  /* HP is redoubled */
  entrybuffer[0] *= 2;
  
  return;
}