
/* Function that goes through each character entry and randomizes them based on the settings */
void RandomizeCharactersG1(FILE *rom, Settings *settings, unsigned char *entrybuffer, int header, FILE *names, FILE *log, FILE *superlog)
{
  /* Plain char for text */
  char textbuffer[TEXTBUFFERSIZE];
  unsigned char seliphblood[2];
  unsigned char spareweapons[] = {2,1};
  int i;
  
  rewind(names); /* This is here in case of a rerun */
  
  for(i = 0; i < FIRSTGEN; i++)
  {
    fseek(rom, CHARACTER + header + (CHARACTERSIZE * i), SEEK_SET);
    fread(entrybuffer, 1, 0x26, rom);
    
    fgets(textbuffer, TEXTBUFFERSIZE, names);
    fprintf(log, "%s", textbuffer);
    
    if(settings->class > '0')
    {
      printf("Class");
      RandomizeClass(&entrybuffer[CLASS], entrybuffer[GENDER], log);
      MatchWeapon(rom, header, entrybuffer[CLASS], entrybuffer[WEAPON1], spareweapons);
    }
    /* Go to the randomize promotion function if we want to do that, OR if classes were changed and the promotions need to match! */
    if(settings->promotion > '0' || settings->class > '0')
    {
      printf("Promotion");
      /* Remember this has nothing to do with the entrybuffer */
      RandomizePromotion(rom, header, settings->promotion, log, entrybuffer[CLASS], entrybuffer[GENDER], i);
    }
    if(settings->bases > '0')
    {
      printf("Bases");
      /* The bases are the very first thing in the buffer, so entrybuffer[BASES] is entrybuffer[0] */
      RandomizeBases(&entrybuffer[0], settings->difficulty);
    }
    else if(settings->difficulty > 0) /* Apply difficulty even when not random */
    {
      printf("Difficulty(Bases)");
      ApplyDifficulty(&entrybuffer[0], settings->difficulty, 1);
    }
    if(settings->growths > '0')
    {
      printf("Growth");
      RandomizeGrowths(&entrybuffer[GROWTH], settings->difficulty);
    }
    else if(settings->difficulty > 0) /* Apply difficulty even when not random */
    {
      printf("Difficulty(Growth)");
      ApplyDifficulty(&entrybuffer[GROWTH], settings->difficulty, 20);
    }
    if(settings->skills > '0')
    {
      printf("RandomSkills");
      RandomizeSkills(&entrybuffer[SKILL], settings->skills, settings->pursuit, log);
    }
    if(settings->bloodalloc > 0)
    {
      printf("BloodAlloc");
      RandomizeCharacterHolyBlood(&entrybuffer[BLOOD], settings->bloodalloc, log);
      if(i == 0 || i == 15)
      {
        SeliphBlood(rom, header, &entrybuffer[BLOOD], seliphblood, i, superlog);
      }
    }
    /* If either of these is active, we need to print stats to the log */
    if(settings->bases > '0' || settings->growths > '0')
    {
      printf("PrintStats");
      PrintStats(log, entrybuffer, settings->bases, settings->growths, rom, header, entrybuffer[CLASS], &entrybuffer[BLOOD]);
    }
    
    printf("Write\n");
    /* Write to file */
    fseek(rom, CHARACTER + header + (CHARACTERSIZE * i), SEEK_SET);
    fwrite(entrybuffer, 1, 0x26, rom);
    
    fputc('\n', log);
  }
  
  
  return;
}