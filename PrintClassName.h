
/* Function that prints the class whose id is given to the FILE given */
void PrintClassName(unsigned char id, FILE *file)
{
  /* Plain chars for text */
  char classnamebuffer[TEXTBUFFERSIZE];
  
  /* I don't feel like making another file for the class names right now NOTE: Maybe come back to this */
  switch(id)
  {
    case 0x00:
      strcpy(classnamebuffer, "Cavalier\0");
      break;
    case 0x50:  /* Just in case i want to call this function from somewhere where 0x00 would be confused for a '\0' */
      strcpy(classnamebuffer, "Cavalier\0");
      break;
    case 0x01:
      strcpy(classnamebuffer, "Lance Knight\0");
      break;
    case 0x02:
      strcpy(classnamebuffer, "Arch Knight\0");
      break;
    case 0x03:
      strcpy(classnamebuffer, "Axe Knight\0");
      break;
    case 0x04:
      strcpy(classnamebuffer, "Free Knight\0");
      break;
    case 0x05:
      strcpy(classnamebuffer, "Troubadour\0");
      break;
    case 0x06:
      strcpy(classnamebuffer, "Lord Knight\0");
      break;
    case 0x07:
      strcpy(classnamebuffer, "Duke Knight\0");
      break;
    case 0x08:
      strcpy(classnamebuffer, "Master Knight\0");
      break;
    case 0x09:
      strcpy(classnamebuffer, "Paladin (M)\0");
      break;
    case 0x0A:
      strcpy(classnamebuffer, "Paladin (F)\0");
      break;
    case 0x0B:
      strcpy(classnamebuffer, "Bow Knight\0");
      break;
    case 0x0C:
      strcpy(classnamebuffer, "Forest Knight\0");
      break;
    case 0x0D:
      strcpy(classnamebuffer, "Mage Knight\0");
      break;
    case 0x0E:
      strcpy(classnamebuffer, "Great Knight\0");
      break;
    case 0x10:
      strcpy(classnamebuffer, "Pegasus Knight\0");
      break;
    case 0x11:
      strcpy(classnamebuffer, "Falcon Knight\0");
      break;
    case 0x13:
      strcpy(classnamebuffer, "Dragon Knight\0");
      break;
    case 0x14:
      strcpy(classnamebuffer, "Dragon Master\0");
      break;
    case 0x16:
      strcpy(classnamebuffer, "Myrmidon\0");
      break;
    case 0x17:
      strcpy(classnamebuffer, "Swordmaster\0");
      break;
    case 0x18:
      strcpy(classnamebuffer, "Sniper\0");
      break;
    case 0x19:
      strcpy(classnamebuffer, "Hero\0");
      break;
    case 0x1A:  /* 1B would be Emperor, 1C would be Baron */
      strcpy(classnamebuffer, "General\0");
      break;
    case 0x15:
      strcpy(classnamebuffer, "Archer\0");
      break;
    case 0x25:
      strcpy(classnamebuffer, "Sword Armor\0");
      break;
    case 0x27:
      strcpy(classnamebuffer, "Axe Fighter\0");
      break;
    case 0x29:
      strcpy(classnamebuffer, "Warrior\0");
      break;
    case 0x2C:
      strcpy(classnamebuffer, "Junior Lord\0");
      break;
    case 0x2D:  /* Taking this one out since it is basically strictly worse than the (F) variant */
      strcpy(classnamebuffer, "Mage Fighter (M)\0");
      break;
    case 0x2E:
      strcpy(classnamebuffer, "Prince\0");
      break;
    case 0x2F:
      strcpy(classnamebuffer, "Princess\0");
      break;
    case 0x30:
      strcpy(classnamebuffer, "Mage Fighter (F)\0");
      break;
    case 0x32: /* Here just in case i add Dancers */
      strcpy(classnamebuffer, "Dancer\0");
      break;
    case 0x33:
      strcpy(classnamebuffer, "Preist\0");
      break;
    case 0x34:  /* Plain Mage, just in case i re-add it */
      strcpy(classnamebuffer, "Plain Mage\0");
      break;
    case 0x35:
      strcpy(classnamebuffer, "Fire Mage\0");
      break;
    case 0x36:
      strcpy(classnamebuffer, "Thunder Mage\0");
      break;
    case 0x37:
      strcpy(classnamebuffer, "Wind Mage\0");
      break;
    case 0x38:
      strcpy(classnamebuffer, "High Priest\0");
      break;
    case 0x3A:
      strcpy(classnamebuffer, "Sage\0");
      break;
    case 0x3B:
      strcpy(classnamebuffer, "Bard\0");
      break;
    case 0x3C:
      strcpy(classnamebuffer, "Shaman\0");
      break;
    case 0x3F:
      strcpy(classnamebuffer, "Theif\0");
      break;
    case 0x40:
      strcpy(classnamebuffer, "Rogue\0");
      break;
  }
  
  fprintf(file, "%s", classnamebuffer);
  
  return;
}