
void RandomizeWeapons(FILE *rom, int header, Weapons *weapons)
{
  signed int i, randomnessbuffer;
  unsigned char weaponentrybuffer[3];
  
  for(i = 0; i < WEAPONSTATSCOUNT; i++)
  {
    fseek(rom, WEAPONSTATS + header + (WEAPONSTATSSIZE * i), SEEK_SET);
    fread(weaponentrybuffer, 1, 3, rom);
    
    /* Balance Melee */
    if(weapons->balancemelee){
      /* If sword */
      if(i < 0x18){
        if(weapons->balancemelee == 1){
          weaponentrybuffer[2] -= 3;
        }
      }
      /* If axe */
      if(i > 0x27 && i < 0x2E){
        if(weapons->balancemelee == 1){
          weaponentrybuffer[0] += 2;
          weaponentrybuffer[2] -= 2;
        }
      }
    }
    
    
    /* Balance Magic */
    if(weapons->balancemagic){
      /* If Fire */ /* Excludes Valflame to not make that boss even harder */
      if(i > 0x3D && i < 0x41){
        /* If might */
        if(weapons->balancemagic == 1 || weapons->balancemagic == 3){
          weaponentrybuffer[0] += 2;
        }
        /* If weight */
        if(weapons->balancemagic == 2 || weapons->balancemagic == 3){
          weaponentrybuffer[2] -= 2;
        }
      }
      /* If Wind */
      if(i > 0x47 && i < 0x4C){
      /* If might */
        if(weapons->balancemelee == 1 || weapons->balancemelee == 3){
          weaponentrybuffer[0] -= 2;
        }
        /* If weight */
        if(weapons->balancemelee == 2 || weapons->balancemelee == 3){
          weaponentrybuffer[2] += 2;
        }
      }
    }
    
    
    if(weapons->might > 0)
    {
      /* Might */
      /* The thing with all the parenthesies makes a span of 2x the variance, and then subtracts the variance to make it +-variance */
      randomnessbuffer = (rand() % (((weapons->might)*2)-(weapons->might)));
      /* Stop underflow */
      ((weaponentrybuffer[0] + randomnessbuffer) > 0) ? (weaponentrybuffer[0] += randomnessbuffer) : (weaponentrybuffer[0] = 0);
    }
    if(weapons->hit > 0)
    {
      /* Hit */
      /* The thing with all the parenthesies makes a span of 2x the variance, and then subtracts the variance to make it +-variance */
      randomnessbuffer = (rand() % (((weapons->hit)*2)-(weapons->hit)));
      /* Stop underflow */
      ((weaponentrybuffer[1] + randomnessbuffer) > 0) ? (weaponentrybuffer[1] += randomnessbuffer) : (weaponentrybuffer[1] = 0);
    }
    if(weapons->weight > 0)
    {
      /* Weight */
      /* The thing with all the parenthesies makes a span of 2x the variance, and then subtracts the variance to make it +-variance */
      randomnessbuffer = (rand() % (((weapons->weight)*2)-(weapons->weight)));
      /* Stop underflow */
      ((weaponentrybuffer[2] + randomnessbuffer) > 0) ? (weaponentrybuffer[2] += randomnessbuffer) : (weaponentrybuffer[2] = 0);
    }
    
    /* Write to file */
    fseek(rom, WEAPONSTATS + header + (WEAPONSTATSSIZE * i), SEEK_SET);
    fwrite(weaponentrybuffer, 1, 3, rom);
  }
  
 
  return;
}