
/* Function for applying difficulty when not randomizing. */
/* Takes an entrybuffer exerpt of the bases or growths, and a scale factor of 1 for bases or 10 for growths. */
void ApplyDifficulty(unsigned char *entrybuffer, int difficulty, int scale)
{
  int i, random;
  
  for(i = difficulty; i > 0; i--)
  {
    /* This is the reason for capping difficulty at 10: Any more and Deirdre would get stuck in this loop forever */
    do{
      random = rand() % 8;
    }
    while(entrybuffer[random] < scale);
    
    entrybuffer[random] -= scale;
    /* HP counts for half */
    if(random == 0 && entrybuffer[random] >= scale)
    {
      entrybuffer[random] -= scale;
    }
  }
  
  return;
}