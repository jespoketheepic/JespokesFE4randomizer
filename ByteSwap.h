
/* Swaps the bytes in the specified file at the specified locations */
void ByteSwap(FILE *file, int loc1, int loc2)
{
  unsigned char buff1, buff2;
  
  fseek(file, loc1, SEEK_SET);
  buff1 = fgetc(file);
  fseek(file, loc2, SEEK_SET);
  buff2 = fgetc(file);
  fseek(file, loc2, SEEK_SET);
  fputc(buff1, file);
  fseek(file, loc1, SEEK_SET);
  fputc(buff2, file);
  
  return;
}