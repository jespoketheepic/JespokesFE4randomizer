#define SELIPHCLASSLOC 0x3B5F8
#define LEIFCLASSLOC 0x3B676
#define ALTENNACLASSLOC 0x3B896
#define FIRSTKIDCLASSLOC 0x3B960
#define VARIABLEKIDCOUNT 14

/* Prototype */
void PrintWeaponRanks(int *weaponrankbuffer, FILE *log);


void RandomizeChildClassAndPromo(FILE *rom, int header, char classsetting, char promosetting, FILE *names, FILE *log, FILE *superlog)
{
  unsigned char classbuffer, weaponID, gender;
  unsigned char spareweapons[] = {1,2};
  int weaponrankbuffer[9];    /* Sword, Lance, Axe, Bow, Fire, Thunder, Wind, Light, Staff */
  int i;
  /* Text as plain char */
  char textbuffer[TEXTBUFFERSIZE];
  
  if(classsetting == '1')
  {
    fprintf(superlog, "The following weapon ranks do not include Holy Blood bonuses, which ARE a factor in inheritance.\n");
  }
  
  
  /* Seliph */
  fgets(textbuffer, TEXTBUFFERSIZE, names);
  fprintf(log, "%s", textbuffer);
  if(classsetting == '1')
  {
    fprintf(superlog, "%s", textbuffer);
  }
  
  fseek(rom, SELIPHCLASSLOC + header, SEEK_SET);
  classbuffer = fgetc(rom);
  fseek(rom, SELIPHCLASSLOC + header + 8 , SEEK_SET);
  weaponID = fgetc(rom);
  fseek(rom, SELIPHCLASSLOC + header + 7, SEEK_SET);
  gender = fgetc(rom);  
  if(classsetting > '0')
  {
    RandomizeClass(&classbuffer, gender, log);
    MatchWeapon(rom, header, classbuffer, weaponID, spareweapons);
  }
  /* RandomizePromotion should be called either way because it is needed on class randomizing too, and this function is never called without either one or the other*/
  RandomizePromotion(rom, header, promosetting, log, classbuffer, gender, FIRSTGEN);
  fseek(rom, SELIPHCLASSLOC + header, SEEK_SET);
  fputc(classbuffer, rom);
  
  if(classsetting == '1')
  {
    /* Handle weapon ranks */
    /* We don't need the return value here */
    ClassWeaponRanks(weaponrankbuffer, classbuffer); 
    PrintWeaponRanks(weaponrankbuffer, superlog);
  }
  
  
  /* Leif */
  fgets(textbuffer, TEXTBUFFERSIZE, names);
  fprintf(log, "%s", textbuffer);
  if(classsetting == '1')
  {
    fprintf(superlog, "%s", textbuffer);
  }
  
  fseek(rom, LEIFCLASSLOC + header, SEEK_SET);
  classbuffer = fgetc(rom);
  fseek(rom, LEIFCLASSLOC + header + 8, SEEK_SET);
  weaponID = fgetc(rom);
  fseek(rom, LEIFCLASSLOC + header + 7, SEEK_SET);
  gender = fgetc(rom);
  if(classsetting > '0')
  {
    RandomizeClass(&classbuffer, gender, log);
    MatchWeapon(rom, header, classbuffer, weaponID, spareweapons);
  }
  RandomizePromotion(rom, header, promosetting, log, classbuffer, gender, FIRSTGEN + 4);
  fseek(rom, LEIFCLASSLOC + header, SEEK_SET);
  fputc(classbuffer, rom);
  
  if(classsetting == '1')
  {
    /* Handle weapon ranks */
    /* We don't need the return value here */
    ClassWeaponRanks(weaponrankbuffer, classbuffer); 
    PrintWeaponRanks(weaponrankbuffer, superlog);
  }
  
  
  /* Altenna */
  fgets(textbuffer, TEXTBUFFERSIZE, names);
  fprintf(log, "%s", textbuffer);
  if(classsetting == '1')
  {
    fprintf(superlog, "%s", textbuffer);
  }
  
  fseek(rom, ALTENNACLASSLOC + header, SEEK_SET);
  classbuffer = fgetc(rom);
  fseek(rom, ALTENNACLASSLOC + header + 8, SEEK_SET);
  weaponID = fgetc(rom);
  fseek(rom, ALTENNACLASSLOC + header + 7, SEEK_SET);
  gender = fgetc(rom);
  if(classsetting > '0')
  {
    RandomizeClass(&classbuffer, gender, log);
    MatchWeapon(rom, header, classbuffer, weaponID, spareweapons);
  }
  RandomizePromotion(rom, header, promosetting, log, classbuffer, gender, FIRSTGEN + 19);
  fseek(rom, ALTENNACLASSLOC + header, SEEK_SET);
  fputc(classbuffer, rom);
  
  if(classsetting == '1')
  {
    /* Handle weapon ranks */
    /* We don't need the return value here */
    ClassWeaponRanks(weaponrankbuffer, classbuffer); 
    PrintWeaponRanks(weaponrankbuffer, superlog);
  }
  
  
  /* The rest */
  for(i = 0; i < VARIABLEKIDCOUNT; i++)
  {
    fgets(textbuffer, TEXTBUFFERSIZE, names);
    fprintf(log, "%s", textbuffer);
    if(classsetting == '1')
    {
      fprintf(superlog, "%s", textbuffer);
    }
    
    fseek(rom, FIRSTKIDCLASSLOC + header + (0x0C * i), SEEK_SET);
    classbuffer = fgetc(rom);
    fseek(rom, FIRSTKIDCLASSLOC + header + (0x0C * i) + 8, SEEK_SET);
    weaponID = fgetc(rom);
    fseek(rom, FIRSTKIDCLASSLOC + header + (0x0C * i) + 7, SEEK_SET);
    gender = fgetc(rom);    
    if(classsetting > '0')
    {
      RandomizeClass(&classbuffer, gender, log);
      MatchWeapon(rom, header, classbuffer, weaponID, spareweapons);
    }
    RandomizePromotion(rom, header, promosetting, log, classbuffer, gender, FIRSTGEN + 25 + i);
    fseek(rom, FIRSTKIDCLASSLOC + header + (0x0C * i), SEEK_SET);
    fputc(classbuffer, rom);
    
    if(classsetting == '1')
    {
      /* Handle weapon ranks */
      /* We don't need the return value here */
      ClassWeaponRanks(weaponrankbuffer, classbuffer); 
      PrintWeaponRanks(weaponrankbuffer, superlog);
    }
  }
  
  
  return;
}


void PrintWeaponRanks(int *weaponrankbuffer, FILE *log)
{  
  if(weaponrankbuffer[0])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Sword %c, ", 68 - weaponrankbuffer[0]);
  }
  if(weaponrankbuffer[1])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Lance %c, ", 68 - weaponrankbuffer[1]);
  }
  if(weaponrankbuffer[2])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Axe %c, ", 68 - weaponrankbuffer[2]);
  }
  if(weaponrankbuffer[3])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Bow %c, ", 68 - weaponrankbuffer[3]);
  }
  if(weaponrankbuffer[4])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Fire %c, ", 68 - weaponrankbuffer[4]);
  }
  if(weaponrankbuffer[5])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Thunder %c, ", 68 - weaponrankbuffer[5]);
  }
  if(weaponrankbuffer[6])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Wind %c, ", 68 - weaponrankbuffer[6]);
  }
  if(weaponrankbuffer[7])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Light %c, ", 68 - weaponrankbuffer[7]);
  }
  if(weaponrankbuffer[8])
  {
    /* Print rank. 68 is 'D', subtracting weaponrank from that gives the right letter*/
    fprintf(log, "Staff %c, ", 68 - weaponrankbuffer[8]);
  }
  
  fputc('\n', log);
  fputc('\n', log);
  
  return;
}



