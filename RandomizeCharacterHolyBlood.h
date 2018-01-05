
/* Prototype */
void RandomHolyBlood(unsigned char *entrybufferblood, int mode, FILE *log);


void RandomizeCharacterHolyBlood(unsigned char *entrybufferblood, char bloodsetting, FILE *log)
{
  int i;
  
  /* Wipe blood */
  for(i = 0; i < 4; i++)
  {
    entrybufferblood[i] = 0;
  }
  fprintf(log, "Holy Blood: Major ");
  /* Get a Major blood */
  RandomHolyBlood(entrybufferblood, 1, log);
  
  /* If in a high mode, add some minor blood*/
  if(bloodsetting > '1')
  {
    fprintf(log, ", Minor ");
    RandomHolyBlood(entrybufferblood, 2, log);
  }
  
  fputc('\n', log);
  
  return;
}


/* Function for handing out a random holy blood. */
/* Loops until it has given one. Won't pick an already given one. */
/* Call in mode 1 for Major blood, mode 2 for Minor */
void RandomHolyBlood(unsigned char *entrybufferblood, int mode, FILE *log)
{
  int done = 0;
  
  while(!done)
  {
    switch(rand() % 13)
    {
      case 0: /* Baldr, Set 1, 0000 0010 */
        if(entrybufferblood[0] & 3) /* If either minor or major is tripped, this will give true, and break the switch before it can reach "done" */
        {
          break;
        }
        entrybufferblood[0] += 2/mode;
        fprintf(log, "Baldr");
        done = 1;
        break;
      case 1: /* Naga, Set 1, 0000 1000 */
        if(entrybufferblood[0] & 12)
        {
          break;
        }
        entrybufferblood[0] += 8/mode;
        fprintf(log, "Naga");
        done = 1;
        break;
      case 2: /* Dain, Set 1, 0010 0000 */
        if(entrybufferblood[0] & 48)
        {
          break;
        }
        entrybufferblood[0] += 32/mode;
        fprintf(log, "Dain");
        done = 1;
        break;
      case 3: /* Noba, Set 1, 1000 0000 */
        if(entrybufferblood[0] & 192)
        {
          break;
        }
        entrybufferblood[0] += 128/mode;
        fprintf(log, "Nova");
        done = 1;
        break;
      case 4: /* Od, Set 2, 0000 0010 */
        if(entrybufferblood[1] & 3)
        {
          break;
        }
        entrybufferblood[1] += 2/mode;
        fprintf(log, "Od");
        done = 1;
        break;
      case 5: /* Ulir, Set 2, 0000 1000 */
        if(entrybufferblood[1] & 12)
        {
          break;
        }
        entrybufferblood[1] += 8/mode;
        fprintf(log, "Ulir");
        done = 1;
        break;
      case 6: /* Neir, Set 2, 0010 0000 */
        if(entrybufferblood[1] & 48)
        {
          break;
        }
        entrybufferblood[1] += 32/mode;
        fprintf(log, "Neir");
        done = 1;
        break;
      case 7: /* Fjalar, Set 2, 1000 0000 */
        if(entrybufferblood[1] & 192)
        {
          break;
        }
        entrybufferblood[1] += 128/mode;
        fprintf(log, "Fjalar");
        done = 1;
        break;
      case 8: /* Thrud, Set 3, 0000 0010 */
        if(entrybufferblood[2] & 3)
        {
          break;
        }
        entrybufferblood[2] += 2/mode;
        fprintf(log, "Thrud");
        done = 1;
        break;
      case 9: /* Forseti, Set 3, 0000 1000 */
        if(entrybufferblood[2] & 12)
        {
          break;
        }
        entrybufferblood[2] += 8/mode;
        fprintf(log, "Forseti");
        done = 1;
        break;
      case 10: /* Blagi, Set 3, 0010 0000 */
        if(entrybufferblood[2] & 48)
        {
          break;
        }
        entrybufferblood[2] += 32/mode;
        fprintf(log, "Blagi");
        done = 1;
        break;
      case 11: /* Hezul, Set 3, 1000 0000 */
        if(entrybufferblood[2] & 192)
        {
          break;
        }
        entrybufferblood[2] += 128/mode;
        fprintf(log, "Hezul");
        done = 1;
        break;
      case 12: /* Loptyr, Set 4, 0000 0010 */
        if(entrybufferblood[3] & 3)
        {
          break;
        }
        entrybufferblood[3] += 2/mode;
        fprintf(log, "Loptyr");
        done = 1;
        break;
    }
  }
  
  return;
}