
/* Input: a char and an 0xFF terminated array of char */
/* Retuns: 1 if the supplied char is in the array, 0 if not */
int CharInArray(unsigned char id, const unsigned char *list)
{
  int i = 0;
  
  while(list[i] != 0xFF)
  {
    if(id == list[i])
    {
      return 1;
    }
    i++;
  }
  
  return 0;
}