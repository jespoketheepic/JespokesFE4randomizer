
/* Prototypes */
void WeaponBonus(FILE *rom, int header, unsigned char *statbuffer, char WBsetting, int i);
void PrintStatLine(FILE *log, unsigned char *statbuffer);


void RandomizeWeaponBonus(FILE *rom, int header, unsigned char WBsetting, FILE *log)
{
  unsigned char statbuffer[6];
  
  fprintf(log, "Holy Weapon stat bonuses:\n"
               "            | Str | Mag | Skl | Spd | Def | Res |\n");
               
  fprintf(log, "Tyrfing:    ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 0);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Naga:       ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 1);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Gungnir:    ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 2);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Gae Bolg:   ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 3);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Balmung:    ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 4);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Yewfelle:   ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 5);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Helswath:   ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 6);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Valflame:   ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 7);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Mjolnir:    ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 8);
  PrintStatLine(log, statbuffer);
  
  fprintf(log, "Forseti:    ");
  WeaponBonus(rom, header, statbuffer, WBsetting, 9);
  PrintStatLine(log, statbuffer);
  
  /* 10 is Valkyrie */
  
  fprintf(log, "Mystletainn:");
  WeaponBonus(rom, header, statbuffer, WBsetting, 11);
  PrintStatLine(log, statbuffer);
  
  /* Edit Loptyr manually */
  memset(statbuffer, 0x00, 6);
  statbuffer[1] = 5;
  fseek(rom, HOLYBLOOD + HOLYWEAPONBONUS + (HOLYBLOODSIZE * 12) + header, SEEK_SET);
  fwrite(statbuffer, 1, 6, rom);
  
  fputc('\n', log);
  
  return;
}


void WeaponBonus(FILE *rom, int header, unsigned char *statbuffer, char WBsetting, int i)
{
  int rn1, rn2, k;
  
  /* Clear */
  memset(statbuffer, 0x00, 6);
  
  switch(WBsetting)
  {
    case '2': /* 20 to one, 10 to another */
      rn1 = (rand()%6);
      do
      {
        rn2 = (rand()%6);
      }
      while(rn1 == rn2);
      statbuffer[rn1] = 20;
      statbuffer[rn2] = 10;
      break;
    case '1': /* rounds of 10 */
      for(k = 0; k < 3; k++)
      {
        rn1 = (rand()%6);
        statbuffer[rn1] += 10;
      }
      break;
/*    case '3':  30 to one 
      rn1 = (rand()%6);
      statbuffer[rn1] = 30;
      break;*/
  }
  
  /*if(i == 0) Tyrfing bonus 
  {
    rn1 = (rand()%6);
    statbuffer[rn1] += 10;
  }*/
  if(i == 1) /* Naga bonus */
  {
    for(k = 0; k < 5; k++)
    {
      rn1 = (rand()%6);
      statbuffer[rn1] += 10;
    }
  }
  
  /* Write to file */
  fseek(rom, HOLYBLOOD + HOLYWEAPONBONUS + (HOLYBLOODSIZE * i) + header, SEEK_SET);
  fwrite(statbuffer, 1, 6, rom);
  
  return;
}


/* Function for printing a line of growths to log */
void PrintStatLine(FILE *log, unsigned char *statbuffer)
{
  int i, k, statsclone, length;
  
  for(i = 0; i < 6; i++)
  {
    length = 1;
    
    // Determining nr of digits
    statsclone = statbuffer[i];
    while(statsclone /= 10)
    {
      length++;
    }
    fputc('|', log);
    for(k = 0; k < (4 - length); k++)
    {
      fputc(' ', log);
    }
    fprintf(log, "%d", statbuffer[i]);
    fputc(' ', log);
  }
  fputc('|', log);
  fputc('\n', log);
  
  return;
}
