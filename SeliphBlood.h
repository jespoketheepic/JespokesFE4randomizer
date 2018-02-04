

void WriteSeliphBlood(FILE *superlog, unsigned char *seliphblood);

/* I must have been drunk when programming this. The formatting has been even worse, half the comments are "This makes sense i swear", and half the things did the opposite of what they were supposed to */
void SeliphBlood(FILE *rom, int header, unsigned char *parentbloodreal, unsigned char *seliphblood, int parent, FILE *superlog)
{  
  int random;
  unsigned char parentblood[4];
  
  /* Some stuff could have been better if i made this immediately, but now i NEEDED it, so here it is */
  parentblood[0] = parentbloodreal[0];
  parentblood[1] = parentbloodreal[1];
  parentblood[2] = parentbloodreal[2];
  parentblood[3] = parentbloodreal[3];
  
  /* Handle Seliph's holy blood while working on his parents */
  /* NOTE: This function is currently the limiting factor on how much holy blood could theorectally be allocated, since it gets stuck if Seliph inherits 9+ holy bloods */
    if(parent == 0)
    { /* Father */
      seliphblood[0] = parentblood[0];
      seliphblood[1] = parentblood[1];
      if((parentblood[2] & 192 /*1100 0000*/) > 0)  /* If Hezul, prioritize swords */
      {
        if((seliphblood[0] & 3 /*0000 0011*/) == 0)  /* If Baldr or Od is available, take them */
        {
          seliphblood[0] &= (parentblood[2] >> 6);
        }
        else if((seliphblood[1] & 3 /*0000 0011*/) == 0)
        {
          seliphblood[1] &= (parentblood[2] >> 6);
        }
        else
        {
          do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2] >> 6) & 3 /*0000 0011*/) << ((random%4)*2);
        }
      }
      if((parentblood[2] & 48 /*0011 0000*/) > 0) /* Blagi */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2] >> 4) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[2] & 12 /*0000 1100*/) > 0) /* Forseti */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* Picks out a holy blood Seliph doesn't have yet */
          
          seliphblood[random/4] &= ((parentblood[2] >> 2) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[2] & 3 /*0000 0011*/) > 0) /* Thurd */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2]) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[3] & 3 /*0000 0011*/) > 0) /* Loptyr */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[3]) & 3 /*0000 0011*/) << ((random%4)*2);
      }
    }
    
    
    
    if(parent == 15)
    { /* Mother */  
      if((parentblood[0] & 3 /*0000 0011*/) > 0)
      {
        if((seliphblood[0] & 1 /*0000 0001*/) > 0)
        {
          seliphblood[0] &= 2 /*0000 0010*/;
        }
        else
        {
          seliphblood[0] &= 1 /*0000 0001*/;
        }
      }
      if((parentblood[0] & 12 /*0000 1100*/) > 0)
      {
        if((seliphblood[0] & 4 /*0000 0100*/) > 0)
        {
          seliphblood[0] &= 8 /*0000 1000*/;
        }
        else
        {
          seliphblood[0] &= 4 /*0000 0100*/;
        }
      }
      if((parentblood[0] & 48 /*0011 0000*/) > 0)
      {
        if((seliphblood[0] & 16 /*0001 0000*/) > 0)
        {
          seliphblood[0] &= 32 /*0010 0000*/;
        }
        else
        {
          seliphblood[0] &= 64 /*0100 0000*/;
        }
      }
      if((parentblood[0] & 192 /*1100 0000*/) > 0)
      {
        if((seliphblood[0] & 64 /*0100 0000*/) > 0)
        {
          seliphblood[0] &= 128 /*1000 0000*/;
        }
        else
        {
          seliphblood[0] &= 64 /*0100 0000*/;
        }
      }
      if((parentblood[1] & 3 /*0000 0011*/) > 0)
      {
        if((seliphblood[1] & 1 /*0000 0001*/) > 0)
        {
          seliphblood[1] &= 2 /*0000 0010*/;
        }
        else
        {
          seliphblood[1] &= 1 /*0000 0001*/;
        }
      }
      if((parentblood[1] & 12 /*0000 1100*/) > 0)
      {
        if((seliphblood[1] & 4 /*0000 0100*/) > 0)
        {
          seliphblood[1] &= 8 /*0000 1000*/;
        }
        else
        {
          seliphblood[1] &= 4 /*0000 0100*/;
        }
      }
      if((parentblood[1] & 48 /*0011 0000*/) > 0)
      {
        if((seliphblood[1] & 16 /*0001 0000*/) > 0)
        {
          seliphblood[1] &= 32 /*0010 0000*/;
        }
        else
        {
          seliphblood[1] &= 64 /*0100 0000*/;
        }
      }
      if((parentblood[1] & 192 /*1100 0000*/) > 0)
      {
        if((seliphblood[1] & 64 /*0100 0000*/) > 0)
        {
          seliphblood[1] &= 128 /*1000 0000*/;
        }
        else
        {
          seliphblood[1] &= 64 /*0100 0000*/;
        }
      }
        
      /* All minors */
      parentblood[2] = (parentblood[2] && 0x55 /*0101 0101*/) | ((parentblood[2] & 0xAA /*1010 1010*/) >> 1);
      parentblood[3] = (parentblood[3] && 0x55 /*0101 0101*/) | ((parentblood[3] & 0xAA /*1010 1010*/) >> 1);
        
      /* The holy bloods Seliph cant get are randomly relocated */
      if((parentblood[2] & 192 /*1100 0000*/) > 0) /* Hezul */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2] >> 6) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[2] & 48 /*0011 0000*/) > 0) /* Blagi */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2] >> 4) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[2] & 12 /*0000 1100*/) > 0) /* Forseti */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* Picks out a holy blood Seliph doesn't have yet */
          
          seliphblood[random/4] &= ((parentblood[2] >> 2) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[2] & 3 /*0000 0011*/) > 0) /* Thurd */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[2]) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      if((parentblood[3] & 3 /*0000 0011*/) > 0) /* Loptyr */
      {
        do{
            random = rand() % 8;
          }
          while(((seliphblood[random/4] >> ((random%4)*2)) & 3 /*0000 0011*/) != 0);  /* It makes sense i swear */
          
          seliphblood[random/4] &= ((parentblood[3]) & 3 /*0000 0011*/) << ((random%4)*2);
      }
      
      /* Write to file */
      fseek(rom, SELIPHBLOOD + header, SEEK_SET);
      fwrite(seliphblood, 1, 2, rom);
      WriteSeliphBlood(superlog, seliphblood);
    }
  
  return;
}

void WriteSeliphBlood(FILE *superlog, unsigned char *seliphblood)
{
  int number;

  number = ((seliphblood[0] >> 0) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Baldr, ");
  }
  
  number = ((seliphblood[0] >> 2) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Naga, ");
  }
  
  number = ((seliphblood[0] >> 4) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Dain, ");
  }
  
  number = ((seliphblood[0] >> 6) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Nova, ");
  }
  
    number = ((seliphblood[1] >> 0) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Od, ");
  }
  
  number = ((seliphblood[1] >> 2) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Ulir, ");
  }
  
  number = ((seliphblood[1] >> 4) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Neir, ");
  }
  
  number = ((seliphblood[1] >> 6) & 3);
  if(number > 0)
  {
    if(number > 1)
      fprintf(superlog, "Major ");
    else
      fprintf(superlog, "Minor ");
    
    fprintf(superlog, "Vala, ");
  }

  return;
}
