
/* Function for randomizing a unit's class, keeping promoted and unpromoted classes as such */
/* Returns 0 for unpromoted units, 1 for promoted */
void RandomizeClass(unsigned char *class, FILE *log)
{
  /* Don't randomize Dancers. NOTE: should i change that? */
  if(*class == 0x32)
  {
    return;
  }
  
  /* 0xFF terminated arrays */
  const unsigned char unpromoted[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x13, 0x16, 0x15, 0x25, 0x27, 0x2C, 0x2E, 0x2F, 0x33, 0x35, 0x36, 0x37, 0x3B, 0x3c, 0x3F, 0xFF};
  const unsigned char promoted[] = {0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x11, 0x14, 0x17, 0x18, 0x19, 0x1A, 0x29, 0x30, 0x38, 0x3A, 0x40, 0xFF}; /* NOTE: Ask lektor: Speed comparison between re-declaring every time, or passing by reference */
  
  /* If promoted */
  if(CharInArray(*class, promoted))    
  {
    *class = promoted[rand() % PROMOTEDCLASSCOUNT]; /* NOTE: Ask lektor: should i EVER worry about sizeof failing? */
  }  
  else /* if unpromoted */
  {
    *class = unpromoted[rand() % UNPROMOTEDCLASSCOUNT];
  }
  
  fprintf(log, "Class: ");
  PrintClassName(*class, log);
  fprintf(log, "\n");
  
  return;
}