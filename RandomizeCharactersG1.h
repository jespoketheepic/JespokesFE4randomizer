
/* Function that goes through each character entry and randomizes them based on the settings */
void RandomizeCharactersG1(FILE *rom, Settings *settings, unsigned char *entrybuffer, int header, FILE *names, FILE *log)
{
  /* Plain char for text */
  char textbuffer[TEXTBUFFERSIZE];
  unsigned char seliphbuffer, promo;
  unsigned char spareweapons[] = {1,1};
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
      RandomizeClass(&entrybuffer[CLASS], log);
      MatchWeapon(rom, header, entrybuffer[CLASS], entrybuffer[WEAPON1], spareweapons);
    }
    /* Go to the randomize promotion function if we want to do that, OR if classes were changed and the promotions need to match! */
    if(settings->promotion > '0' || settings->class > '0')
    {
      /* Remember this has nothing to do with the entrybuffer */
      promo = RandomizePromotion(rom, header, settings->promotion, log, entrybuffer[CLASS], i);
      /* Only neccessary with random class, but it is important that it happens AFTER the promotion is changed. */
      GenderMatch(&entrybuffer[GENDER], entrybuffer[CLASS], promo);
    }
    if(settings->bases > '0')
    {
      /* The bases are the very first thing in the buffer, so entrybuffer[BASES] is entrybuffer[0] */
      RandomizeBases(entrybuffer, settings->difficulty);
    }
    if(settings->growths > '0')
    {
      RandomizeGrowths(&entrybuffer[GROWTH], settings->difficulty);
    }
    if(settings->skills > '0')
    {
      RandomizeSkills(&entrybuffer[SKILL], settings->skills, settings->pursuit, log);
    }
    if(settings->bloodalloc > '0')
    {
      RandomizeCharacterHolyBlood(&entrybuffer[BLOOD], settings->bloodalloc, log);
    }
    /* Handle Seliph's holy blood while working on his parents */
    if(i == 0 && settings->bloodalloc > '0')
    { /* Father */
      fseek(rom, SELIPHBLOOD + header, SEEK_SET);
      fputc(entrybuffer[BLOOD], rom);
      fputc(entrybuffer[BLOOD+1], rom);
    }
    if(i == 15 && settings->bloodalloc > '0')
    { /* Mother */
      fseek(rom, SELIPHBLOOD + header, SEEK_SET);
      seliphbuffer = fgetc(rom);
      /* Long story short, this masks all her holy blood to minors, and & operates them into what was already there. */
      seliphbuffer &= (((entrybuffer[BLOOD] & 170 /*1010 1010*/)/2) & 85 /*0101 0101*/);
      fseek(rom, SELIPHBLOOD + header, SEEK_SET);
      fputc(seliphbuffer, rom);
      
      fseek(rom, SELIPHBLOOD + 1 + header, SEEK_SET);
      seliphbuffer = fgetc(rom);
      /* Long story short, this masks all her holy blood to minors, and & operates them into what was already there. */
      seliphbuffer &= (((entrybuffer[BLOOD+1] & 170 /*1010 1010*/)/2) & 85 /*0101 0101*/);
      fseek(rom, SELIPHBLOOD + 1 + header, SEEK_SET);
    }
    /* If either of these is active, we need to print stats to the log */
    if(settings->bases > '0' || settings->growths > '0')
    {
      PrintStats(log, entrybuffer, settings->bases, settings->growths, rom, header, entrybuffer[CLASS], &entrybuffer[BLOOD]);
    }
    
    
    /* Write to file */
    fseek(rom, CHARACTER + header + (CHARACTERSIZE * i), SEEK_SET);
    fwrite(entrybuffer, 1, 0x26, rom);
    
    fputc('\n', log);
  }
  
  
  return;
}