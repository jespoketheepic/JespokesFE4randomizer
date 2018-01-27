
/* Prototypes */
void DoHolyBloodGrowth(FILE *rom, int header, FILE *log, FILE *superlog, unsigned char *growthbuffer, char *textbuffer, int BBsetting, int i);
void BloodBonus(FILE *rom, int header, unsigned char *growthbuffer, int BBsetting, int i);
void PrintGrowthLine(FILE *log, unsigned char *growthbuffer);


void RandomizeBloodBonus(FILE *rom, int header, int BBsetting, FILE *log, FILE *superlog)
{
  unsigned char growthbuffer[8];
  char textbuffer[10];
 
  fprintf(log, "Holy Blood growth bonuses:\n"
               "        |  HP | Str | Mag | Skl | Spd | Def | Res | Lck |\n");
  fprintf(superlog, "Holy Blood growth bonuses:\n"
               "        |  HP | Str | Mag | Skl | Spd | Def | Res | Lck |\n");
               
  strcpy(textbuffer, "Baldr:  \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 0);
                 
  strcpy(textbuffer, "Naga:   \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 1); 
  
  strcpy(textbuffer, "Dain:   \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 2); 
  
  strcpy(textbuffer, "Noba:   \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 3); 
  
  strcpy(textbuffer, "Od:     \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 4); 
  
  strcpy(textbuffer, "Ulir:   \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 5); 
  
  strcpy(textbuffer, "Neir:   \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 6); 
  
  strcpy(textbuffer, "Fjalar: \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 7); 
  
  strcpy(textbuffer, "Thurd:  \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 8); 
  
  strcpy(textbuffer, "Forseti:\0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 9); 
  
  strcpy(textbuffer, "Blagi:  \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 10); 
  
  strcpy(textbuffer, "Hezul:  \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 11); 
  
  strcpy(textbuffer, "Loptyr: \0");
  DoHolyBloodGrowth(rom, header, log, superlog, growthbuffer, textbuffer, BBsetting, 12);
  
    
  fputc('\n', log);
  fputc('\n', superlog);
  
  return;
}

void DoHolyBloodGrowth(FILE *rom, int header, FILE *log, FILE *superlog, unsigned char *growthbuffer, char *textbuffer, int BBsetting, int i)
{
  BloodBonus(rom, header, growthbuffer, BBsetting, i);
  fprintf(log, "%s", textbuffer);
  fprintf(superlog, "%s", textbuffer);
  PrintGrowthLine(log, growthbuffer);
  PrintGrowthLine(superlog, growthbuffer);
  
  return;
}

void BloodBonus(FILE *rom, int header, unsigned char *growthbuffer, int BBsetting, int i)
{
  int rn1, k;
    
  /* Clear */
  memset(growthbuffer, 0x00, 8);
  
  switch(BBsetting)
  {
    case 1: /* 20 HP, 30 spread */
      growthbuffer[0] = 20;
      for(k = 0; k < 3; k++)
      {
        rn1 = (rand()%7)+1;
        growthbuffer[rn1] += 10;
      }
      break;
    case 2: /* 20, 20 */
      growthbuffer[0] = 20;
      for(k = 0; k < 2; k++)
      {
        rn1 = (rand()%7)+1;
        growthbuffer[rn1] += 10;
      }
      break;
    case 3: /* 10, 20 */
      growthbuffer[0] = 10;
      for(k = 0; k < 2; k++)
      {
        rn1 = (rand()%7)+1;
        growthbuffer[rn1] += 10;
      }
      break;
    case 4: /* 10, 10 */
      growthbuffer[0] = 10;
      for(k = 0; k < 1; k++)
      {
        rn1 = (rand()%7)+1;
        growthbuffer[rn1] += 10;
      }
      break;
    default:;
  }
  
  if(i == 12) /* Loptyr bonus */
  {
    rn1 = (rand()%7)+1;
    growthbuffer[rn1] += 10;
  }
  
  /* Write to file */
  fseek(rom, HOLYBLOOD + (HOLYBLOODSIZE * i) + header, SEEK_SET);
  fwrite(growthbuffer, 1, 8, rom);
  
  return;
}


/* Function for printing a line of growths to log */
void PrintGrowthLine(FILE *log, unsigned char *growthbuffer)
{
  int i, k, statsclone, length;
  
  for(i = 0; i < 8; i++)
  {
    length = 1;
    
    // Determining nr of digits
    statsclone = growthbuffer[i];
    while(statsclone /= 10)
    {
      length++;
    }
    fputc('|', log);
    for(k = 0; k < (4 - length); k++)
    {
      fputc(' ', log);
    }
    fprintf(log, "%d", growthbuffer[i]);
    fputc('%', log);
  }
  fputc('|', log);
  fputc('\n', log);
  
  return;
}