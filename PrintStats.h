
/* Prototype */
void FindHolyBloodGrowth(FILE *rom, int header, unsigned char *blood, int *holybloodgrowth);


/* Funtion for printing stats to a file */
void PrintStats(FILE *log, unsigned char *entrybuffer, unsigned char basesetting, unsigned char growthsetting, FILE *rom, int header, unsigned char class, unsigned char *blood)
{
  int length = 1, statsclone, i, k, classbase, holybloodgrowth[8] = {0};
  
  /* Find the combined growths for this character's holy blood */
  FindHolyBloodGrowth(rom, header, blood, holybloodgrowth);
  
  fprintf(log, "Stats:\n");
  fprintf(log, "|  HP | Str | Mag | Skl | Spd | Def | Res | Lck |\n");
  if(basesetting > '0')
  {
    for(i = 0; i < 8; i++)
    {
      length = 1;
      /* Get the relevant class base */
      if(i > 0 && i < 7)  
      {
        fseek(rom, CLASSBASE + header + i-1 + (class*CLASSSIZE), SEEK_SET);
        classbase = fgetc(rom);
      }
      else
      {
        /* HP and Luck excluded */
        classbase = 0;
      }
      
      /* Determining nr of digits */
      statsclone = entrybuffer[i] + classbase;
      while(statsclone /= 10)
      {
        length++;
      }
      fputc('|', log);
      for(k = 0; k < (4 - length); k++)
      {
        fputc(' ', log);
      }
      fprintf(log, "%d", entrybuffer[i] + classbase);
      fputc(' ', log);
    }
    fputc('|', log);
    fputc('\n', log);
  }
  if(growthsetting > '0')
  {
    for(i = 0; i < 8; i++)
    {
      length = 1;
      /* Determining nr of digits */
      statsclone = entrybuffer[i+GROWTH]+holybloodgrowth[i];
      while(statsclone /= 10)
      {
        length++;
      }
      fputc('|', log);
      for(k = 0; k < (3 - length); k++)
      {
        fputc(' ', log);
      }
      fprintf(log, "%d", entrybuffer[i+GROWTH]+holybloodgrowth[i]);
      fputc('%', log);
      fputc(' ', log);
    }
    fputc('|', log);
    fputc('\n', log);
    fputc('\n', log);
  }
  
  return;
}

void FindHolyBloodGrowth(FILE *rom, int header, unsigned char *blood, int *holybloodgrowth)
{
  int stat, bloodslot, internal;
  
  for(stat = 0; stat < 8; stat++)
  {
    for(bloodslot = 0; bloodslot < 4; bloodslot++)
    {
      for(internal = 0; internal < 4; internal++)
      {
        if((blood[bloodslot] >> (internal*2)) & 2/*0000 0010 */)  /* If Major */
        {
          fseek(rom, HOLYBLOOD + header + stat + (HOLYBLOODSIZE*internal) + (HOLYBLOODSIZE*bloodslot*4), SEEK_SET);
          holybloodgrowth[stat] += (fgetc(rom)*2);
        }
        else if((blood[bloodslot] >> (internal*2)) & 1/*0000 0001 */)  /* same thing but Minor. Skipped if there is a Major since they dont stack */
        {
          fseek(rom, HOLYBLOOD + header + stat + (HOLYBLOODSIZE*internal) + (HOLYBLOODSIZE*bloodslot*4), SEEK_SET);
          holybloodgrowth[stat] += fgetc(rom);
        }
      }
    }
  }
  
  return;
}






