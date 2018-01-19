
/* Prototype */
int SkillAlloc(unsigned char *skillslot, int skillID, int *skillcount);

void RandomizeSkills(unsigned char *entrybufferskill, unsigned char skillsetting, int pursuitsetting, FILE *log)
{
  int skillcount = (skillsetting - 0x30);
  /* There are 14 skills aside from Pursuit, and the number in pursuitsetting corresponds to how many instances of Pursuit to add to the raffle */
  int optioncount = 14 + (pursuitsetting - 0x30);
  int i;
  
  /* Wipe skills */
  for(i = 0; i < 3; i++)
  {
    entrybufferskill[i] = 0;
  }
  
  fprintf(log, "Skills: ");
  
  /* If everyone gets pursuit, do that */
  if(pursuitsetting == '0')
  {
    entrybufferskill[0] = 2;
    skillcount--;
    fprintf(log, "Pursuit%s", skillcount ? ", " : "\n");
  }
  
  /* While we still want more skills, give them */
  while(skillcount)
  {
    switch(rand() % optioncount)
    {
      case 0: /* Wrath (Skillset 1, 0000 0001) */
        if(SkillAlloc(&entrybufferskill[0], 1, &skillcount))
        {
          fprintf(log, "Wrath%s", skillcount ? ", " : "\n");
        }
        break;
      case 1: /* Adept (Skillset 1, 0000 0100) */
        if(SkillAlloc(&entrybufferskill[0], 4, &skillcount))
        {
          fprintf(log, "Adept%s", skillcount ? ", " : "\n");
        }
        break;
      case 2: /* Charm (Skillset 1, 0001 0000) */
        if(SkillAlloc(&entrybufferskill[0], 16, &skillcount))
        {
          fprintf(log, "Charm%s", skillcount ? ", " : "\n");
        }
        break;
      case 3: /* Nihil (Skillset 1, 0100 0000) */
        if(SkillAlloc(&entrybufferskill[0], 64, &skillcount))
        {
          fprintf(log, "Nihil%s", skillcount ? ", " : "\n");
        }
        break;
      case 4: /* Miracle (Skillset 1, 1000 0000) */
        if(SkillAlloc(&entrybufferskill[0], 128, &skillcount))
        {
          fprintf(log, "Miracle%s", skillcount ? ", " : "\n");
        }
        break;
      case 5: /* Critical (Skillset 2, 0000 0001) */
        if(SkillAlloc(&entrybufferskill[1], 1, &skillcount))
        {
          fprintf(log, "Critical%s", skillcount ? ", " : "\n");
        }
        break;
      case 6: /* Vantage (Skillset 2, 0000 0010) */
        if(SkillAlloc(&entrybufferskill[1], 2, &skillcount))
        {
          fprintf(log, "Vantage%s", skillcount ? ", " : "\n");
        }
        break;
      case 7: /* Accost (Skillset 2, 0000 0100) */
        if(SkillAlloc(&entrybufferskill[1], 4, &skillcount))
        {
          fprintf(log, "Accost%s", skillcount ? ", " : "\n");
        }
        break;
      case 8: /* Astra (Skillset 2, 0000 1000) */
        if(SkillAlloc(&entrybufferskill[1], 8, &skillcount))
        {
          fprintf(log, "Astra%s", skillcount ? ", " : "\n");
        }
        break;
      case 9: /* Luna (Skillset 2, 0001 0000) */
        if(SkillAlloc(&entrybufferskill[1], 16, &skillcount))
        {
          fprintf(log, "Luna%s", skillcount ? ", " : "\n");
        }
        break;
      case 10: /* Sol (Skillset 2, 0010 0000) */
        if(SkillAlloc(&entrybufferskill[1], 32, &skillcount))
        {
          fprintf(log, "Sol%s", skillcount ? ", " : "\n");
        }
        break;
      case 11: /* Renewal (Skillset 3, 0000 0001) */
        if(SkillAlloc(&entrybufferskill[2], 1, &skillcount))
        {
          fprintf(log, "Renewal%s", skillcount ? ", " : "\n");
        }
        break;
      case 12: /* Paragon (Skillset 3, 0000 0010) */
        if(SkillAlloc(&entrybufferskill[2], 2, &skillcount))
        {
          fprintf(log, "Paragon%s", skillcount ? ", " : "\n");
        }
        break;
      case 13: /* Bargain (Skillset 3, 0001 0000) */
        if(SkillAlloc(&entrybufferskill[2], 16, &skillcount))
        {
          fprintf(log, "Bargain%s", skillcount ? ", " : "\n");
        }
        break;
      default: /* Pursuit (Skillset 1, 0000 0010) */ /* Called for any number above 13 */
        if(SkillAlloc(&entrybufferskill[0], 2, &skillcount))
        {
          fprintf(log, "Pursuit%s", skillcount ? ", " : "\n");
        }
        break;
    }
  }
  
  return;
}


/* Function for applying the requested skill */
/* Returns 1 on success, 0 if the given skill is already applied */
int SkillAlloc(unsigned char *skillslot, int skillID, int *skillcount)
{
  /* If this skill is already given, skip */
  if(*skillslot & skillID)
  {
    return 0;  
  }
  
  /* else add the skill and decrement how many skills we still need */
  *skillslot += skillID;
  (*skillcount)--;
  
  return 1;
}