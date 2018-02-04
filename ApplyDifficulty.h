
/* Function for applying difficulty when not randomizing. */
/* Takes an entrybuffer exerpt of the bases or growths, and a scale factor of 1 for bases or 50 for growths. */
void ApplyDifficulty(unsigned char *entrybuffer, int difficulty, int scale)
{
  int i, k, random;
  
  /* Workaround so having each difficulty point count for 20% wont break anything */
  /* Relies on the fact that these are call by values!!! */
  if(scale == 20)
  {
    scale /= 2;
    difficulty *= 2;
  }
  
  for(i = difficulty; i > 0; i--)
  {
    /* This is the reason for capping difficulty at 5: Any more and Deirdre would get stuck in this loop forever */
    do{
      random = rand() % 8;
      
      /* Let me just futureprove this for difficulties where characters can reach 0% growth */
      for(k = 0; k < 8; k++)
      {
        if(entrybuffer[k] >= scale)
        {
          break;
        }
      }
      
      /* If the for loop never broke, there is nothing left to break the while loop, so break it manually */
      if(k == 8)
      {
        break;
      }
      
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