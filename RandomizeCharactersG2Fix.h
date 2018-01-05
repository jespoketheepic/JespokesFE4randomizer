
#define FINNCLASS 0x3B308
#define FINNGROWTH 0x3B313
#define FINNEXTENT 0x0F

/* Function that goes through each character entry and randomizes them based on the settings */
void RandomizeCharactersG2Fix(FILE *rom, Settings *settings, unsigned char *entrybuffer, int header, FILE *names, FILE *log)
{
  /* Plain char for text */
  unsigned char promo, spareweapons[] = {0,0};
  char textbuffer[TEXTBUFFERSIZE];
  int i, k;
  /* Offset for skipping over child entries, starts ready to skip Seliph */
  int offset = 0x0C;
  
  /* Edit all fixed and replacement units */
  for(i = 0; i < SECONDGENFIX; i++)
  {
    /* Skip over Leif and Altenna's child entries */
    if(i == 3 || i == 17)
    {
      offset += 0x0C;
    }
    
    fseek(rom, CHARACTER + header + offset + (CHARACTERSIZE * FIRSTGEN) + (CHARACTERSIZE * i), SEEK_SET);
    fread(entrybuffer, 1, 0x26, rom);
    
    /* Finn fetches what he needs from his old (young) entry */
    if(i == 7)
    {
      fseek(rom, FINNCLASS, SEEK_SET);
      entrybuffer[CLASS] = fgetc(rom);
      fseek(rom, FINNGROWTH, SEEK_SET);
      for(k = 0; k < FINNEXTENT; k++)
      {
        entrybuffer[GROWTH+k] = fgetc(rom);
      }
      fseek(rom, CHARACTER + header + offset + (CHARACTERSIZE * FIRSTGEN) + (CHARACTERSIZE * i), SEEK_SET);
      fwrite(entrybuffer, 1, 0x26, rom);
      continue; /* Skip everything else in the loop for this entry */
    }
    
    fgets(textbuffer, TEXTBUFFERSIZE, names);
    fprintf(log, "%s", textbuffer);
    
    if(settings->class > '0')
    {
      RandomizeClass(&entrybuffer[CLASS], log);
      /* Remember to add the setting check for logging here for the kids, not the fixed. */
      /* Doing it for the subs is fine, they will be overwritten by the kids anyway. Might downgrade one here and there, but thats fine. */
      MatchWeapon(rom, header, entrybuffer[CLASS], entrybuffer[WEAPON1], spareweapons);
    }
    /* Go to the randomize promotion function if we want to do that, OR if classes were changed and the promotions need to match! */
    if(settings->promotion > '0' || settings->class > '0')
    {
      /* Remember this has nothing to do with the entrybuffer */
      promo = RandomizePromotion(rom, header, settings->promotion, log, entrybuffer[CLASS], FIRSTGEN + i + offset/0x0C);
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
    /* If either of these is active, we need to print stats to the log */
    if(settings->bases > '0' || settings->growths > '0')
    {
      PrintStats(log, entrybuffer, settings->bases, settings->growths, rom, header, entrybuffer[CLASS], &entrybuffer[BLOOD]);
    }
  
    /* Write to file */
    fseek(rom, CHARACTER + header + offset + (CHARACTERSIZE * FIRSTGEN) + (CHARACTERSIZE * i), SEEK_SET);
    fwrite(entrybuffer, 1, 0x26, rom);
    
    fputc('\n', log);
  }
  
  return;
}