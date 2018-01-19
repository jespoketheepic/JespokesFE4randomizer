
/* Takes care of the groundwork editing the rom needs */
void FixedStuff(FILE *rom, int header)
{
  int i;
  
  fseek(rom, SELLHOLYWEAPON + header, SEEK_SET);
  fputc(0x00, rom);
  
  fseek(rom, SEIZEFIX1 + header, SEEK_SET);
  fprintf(rom, "%c%c%c%c", 0x22, 0x33, 0xA3, 0x84);
  
  fseek(rom, SEIZEFIX2 + header, SEEK_SET);
  fputc(0x01, rom);
  
  fseek(rom, SEIZEFIX3 + header, SEEK_SET);
  fputc(0x19, rom);
  
  for(i = 0; i < INHERITCOUNT; i++)
  {
    fseek(rom, SWORDSKILLINHERIT + (INHERITSIZE * i) + header, SEEK_SET);
    fputc(0xFF, rom);
  }
  
  /* Swords Skills for everyone */
  SwordSkillsPatch(rom, header);
  
  fseek(rom, JULIUSSKILLS + header, SEEK_SET);
  fputc(0x42, rom);
  fseek(rom, JULIUSDEF + header, SEEK_SET);
  fputc(0x0A, rom);
  fputc(0x05, rom);
  
  fseek(rom, INHERITHOLYWEAPON + header, SEEK_SET);
  fputc(0x05, rom);
  
  /* Chapter 7 enemies */
  fseek(rom, 0x1D9EF + header, SEEK_SET);
  fputc(0x03, rom);
  fseek(rom, 0x1D9F7 + header, SEEK_SET);
  fputc(0x04, rom);
  
  /* Altenna in case she cant cross mountains */
  fseek(rom, 0x1DE0E + header, SEEK_SET);
  fputc(0x17, rom);
  fputc(0x3E, rom);
  fseek(rom, 0x6F8FE + header, SEEK_SET);
  fputc(0x2B, rom);
  
  
  return;
}