
/* There were more elegant ways to do this, if i had known in advance the kids and subs are in the same order, just with some fixed units inbetween */
void KidsMatch(FILE *rom, int header, int i, unsigned char class, unsigned char promo)
{
  int pos;
  
  /* Makes pos the place in the array that matches gen2 character i. */
  switch(i)
  {
    case 1:
      pos = 0;  /* Ulster */
      break;
    case 2:
      pos = 1;  /* Febail */
      break;
    case 4:
      pos = 2;  /* Ced */
      break;
    case 5:
      pos = 3;  /* Cairpre */
      break;
    case 6:
      pos = 4;  /* Diarmuid */
      break;
    case 8:
      pos = 5;  /* Lester */
      break;
    case 11:
      pos = 6;  /* Arthur */
      break;
    case 13:
      pos = 7;  /* Patty */
      break;
    case 14:
      pos = 8;  /* Larcey */
      break;
    case 15:
      pos = 9;  /* Lana */
      break;
    case 17:
      pos = 10; /* Fee */
      break;
    case 18:
      pos = 11; /* Tine */
      break;
    case 19:
      pos = 12; /* Lene */
      break;
    case 20:
      pos = 13; /* Nanna */
      break;
    default:
      return;
  }
  
  fseek(rom, FIRSTKIDCLASSLOC + header + (0x0C * pos), SEEK_SET);
  fputc(class, rom);
  fseek(rom, PROMOTION + header + FIRSTGEN + 25 + pos, SEEK_SET);
  fputc(promo, rom);
    
  return;
}