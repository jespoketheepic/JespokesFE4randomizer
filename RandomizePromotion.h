
/* Prototype */
void PromotionFinder(unsigned char *promo, unsigned char class, int mode);

/* Function that randomizes promotions */
/* OBS: characternr here is their nr within their generation */ 
/* Offset for gen 1 is their number, gen 2 is FIRSTGEN + their nr + the offset for skipping kids, and gen 3(kids) it is FIRSTGEN + a number that has to be found manually */
/* Returns the class they promote to for use in the gender swapping function */
unsigned char RandomizePromotion(FILE *rom, int header, unsigned char promosetting, FILE *log, unsigned char class, int offset)    
{
  /* Beware of this function, the character order is freaky */
  
  const unsigned char promoted[] = {0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x11, 0x14, 0x17, 0x18, 0x19, 0x1A, 0x29, 0x30, 0x38, 0x3A, 0x40, 0xFF};
  unsigned char promotionbuffer, genderdecoy = 0x00;
  
  /* If not promoted, do stuff */
  if(!CharInArray(class, promoted))
  {
    /* If crazy, just give them a random promotion (That matches their gender)*/
    if(promosetting == '2')
    {
      do
      {
        promotionbuffer = promoted[rand() % PROMOTEDCLASSCOUNT];
      } /* GenderMatch returns 1 if they are incompatible, causing a reroll. Genderdecoy is just there to catch and discard its output so the compiler doesn't complain */
      while(GenderMatch(&genderdecoy, class, promotionbuffer));
    }
    else if(promosetting == '0')   /* else if simple, find the right promotion by calling PromotionFinder in fixed mode */
    {
      PromotionFinder(&promotionbuffer, class, 0);
    }
    else      /* else we are looking for a random out of a selection, by calling PromotionFinder in random mode */
    {
      PromotionFinder(&promotionbuffer, class, 1);
    }
    
    /* Write to file */
    fseek(rom, PROMOTION + header + offset, SEEK_SET);
    fputc(promotionbuffer, rom);
    
    /* Log */
    fprintf(log, "Promotion: ");
    PrintClassName(promotionbuffer, log);
    fprintf(log, "\n");
  }
  
  
  return promotionbuffer;
}


/* Function for setting a given char "promo" to a class ID that is a valid promotion for given class ID "class" */
/* In mode fixed mode (0), a random appropriate class is picked. In random mode (1), any random valid class is picked */
void PromotionFinder(unsigned char *promo, unsigned char class, int mode)
{
  unsigned char choicebuffer[MAXPROMOOPTIONS];
  int i = 0;
  
  /* If they hit the Master Knight jackpot */
  if(!(rand()%20))
  {
    choicebuffer[i] = 0x08;
    i++;
  }
  else  /* else get going */
  {
    switch(class)
    {
      case 0x00:  /* Cavalier */
        choicebuffer[i] = 0x09; /* Paladin (M) */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0A;  /* Paladin (F) */
          i++;
        }
        break;
      case 0x50:  /* Just in case i want to call this function from somewhere where i swapped 0x00 for 0x50. OUTDATED, but just in case i missed one */
        choicebuffer[i] = 0x09; /* Paladin (M) */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0A;  /* Paladin (F) */
          i++;
        }
        break;
      case 0x01: /* Lance Knight */
        choicebuffer[i] = 0x07;  /* Duke Knight */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x09;  /* Paladin (M) */
          i++;
        }
        break;
      case 0x02: /* Arch Knight */
        choicebuffer[i] = 0x0B;  /* Bow Knight */
        i++;
        break;
      case 0x03: /* Axe Knight */
        choicebuffer[i] = 0x0E;  /* Great Knight */
        i++;
        break;
      case 0x04: /* Free Knight */
        choicebuffer[i] = 0x0C;  /* Forest Knight */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x09;  /* Paladin (M) */  /* Paladin (F) removed for gender conflict */
          i++;
          choicebuffer[i] = 0x0D;  /* Mage Knight */
          i++;
        }
        break;
      case 0x05: /* Troubadour */
        choicebuffer[i] = 0x0A;  /* Paladin (F) */
        i++;
        break;
      case 0x10: /* Pegasus Knight */
        choicebuffer[i] = 0x11;  /* Falcon Knight */
        i++;
        break;
      case 0x13: /* Dragon Knight */
        choicebuffer[i] = 0x14;  /* Dragon Master */
        i++;
        break;
      case 0x16: /* Myrmidon */
        choicebuffer[i] = 0x17;  /* Swordmaster */
        i++;
        choicebuffer[i] = 0x19;  /* Hero */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0C;  /* Forest Knight */
          i++;
          choicebuffer[i] = 0x11;  /* Falcon Knight */
          i++;
          choicebuffer[i] = 0x14;  /* Dragon Master */
          i++;
          choicebuffer[i] = 0x40;  /* Rogue */ /* NOTE: Should this be here? */
          i++;
        }
        break;
      case 0x15: /* Archer */
        choicebuffer[i] = 0x18;  /* Sniper */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0B;  /* Bow Knight */
          i++;
        }
        break;
      case 0x25: /* Sword Armor */
        choicebuffer[i] = 0x1A;  /* General */
        i++;
        /*if(mode)
        {
          choicebuffer[i] =  THIS IS WHERE TO PUT BARON!;
          i++;
        }*/
        break;
      case 0x27: /* Axe Fighter */
        choicebuffer[i] = 0x29;  /* Warrior */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0E;  /* Great Knight */
          i++;
        }
        break;
      case 0x2C: /* Junior Lord */
        choicebuffer[i] = 0x06;  /* Lord Knight */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x09;  /* Paladin (M) */ /* Paladin (F) removed for gender conflict */
          i++;
          choicebuffer[i] = 0x0C;  /* Forest Knight */
          i++;
          choicebuffer[i] = 0x0D;  /* Mage Knight */
          i++;
          /* Falcon Knight removed for gender conflict */
          choicebuffer[i] = 0x14;  /* Dragon Master */
          i++;
          choicebuffer[i] = 0x17;  /* Swordmaster */
          i++;
          choicebuffer[i] = 0x19;  /* Hero */
          i++;
          choicebuffer[i] = 0x40;  /* Rogue */
          i++;
        }
        break;
      case 0x2E: /* Prince */
        choicebuffer[i] = 0x08;  /* Master Knight */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x17;  /* Swordmaster */
          i++;
          choicebuffer[i] = 0x19;  /* Hero */
          i++;
          choicebuffer[i] = 0x0C;  /* Forest Knight */
          i++;
          /* Falcon Knight removed for gender conflict */
          choicebuffer[i] = 0x14;  /* Dragon Master */
          i++;
          choicebuffer[i] = 0x40;  /* Rogue */ /* NOTE: Should this be here? */
          i++;
        }
        break;
      case 0x2F: /* Princess */
        choicebuffer[i] = 0x08;  /* Master Knight */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x0A;  /* Paladin (F) */
          i++;
          choicebuffer[i] = 0x11;  /* Falcon Knight */
          i++;
        }
        break;
/*      case 0x32:  Dancer. Here just in case i add Dancers. note that it needs some tweaks because it shouldn't be able to promote
        choicebuffer[i] = 0xFF;
        i++;
        if(mode)
        {
          choicebuffer[i] = 0xFF;
          i++;
        }
        break;*/
      case 0x33: /* Preist */
        choicebuffer[i] = 0x38;  /* High Priest */
        i++;
        if(mode)
        {
          choicebuffer[i] = 0x3A;  /* Sage */
          i++;
          choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
          i++;
        }
        break;
      case 0x34:  /* Plain Mage, just in case i re-add it */
        choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
        i++;
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        choicebuffer[i] = 0x0D;  /* Mage Knight */
        i++;
        
        if(mode)
        {
          choicebuffer[i] = 0x38;  /* High Priest */
          i++;
        }
        break;
      case 0x35: /* Fire Mage */
        choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
        i++;
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        choicebuffer[i] = 0x0D;  /* Mage Knight */
        i++;
        break;
      case 0x36: /* Thunder Mage */
        choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
        i++;
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        choicebuffer[i] = 0x0D;  /* Mage Knight */
        i++;
        break;
      case 0x37: /* Wind Mage */
        choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
        i++;
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        choicebuffer[i] = 0x0D;  /* Mage Knight */
        i++;
        break;
      case 0x3B: /* Bard */
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        break;
      case 0x3C: /* Shaman */
        choicebuffer[i] = 0x3A;  /* Sage */
        i++;
        break;
      case 0x3F: /* Theif */
        choicebuffer[i] = 0x40;  /* Rogue */
        i++;
        if(mode)
        {
          choicebuffer[i] = (rand() % 2) ? 0x09 : 0x0A;  /* Paladin (M/F) */
          i++;
          choicebuffer[i] = 0x0C;  /* Forest Knight */
          i++;
          choicebuffer[i] = 0x0D;  /* Mage Knight */
          i++;
          choicebuffer[i] = 0x11;  /* Falcon Knight */
          i++;
          choicebuffer[i] = 0x14;  /* Dragon Master */
          i++;
          choicebuffer[i] = 0x17;  /* Swordmaster */
          i++;
          choicebuffer[i] = 0x19;  /* Hero */
          i++;
          choicebuffer[i] = 0x30;  /* Mage Fighter (F) */
          i++;
        }
        break;
    }
  }
  
  /* Safety check in case we call this function on a non-promoting class (Dancer comes to mind as a risk) */
  if(i > 0){
    /* Set the promotion to a random id*/
    *promo = choicebuffer[rand() % i];
  }
  else{
    *promo = 0xFF;
  }
  
  
  return;
}