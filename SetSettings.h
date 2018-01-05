
/* Function for asking for settings */
/* Input and Output happen to a Settings by reference */
void SetSettings(Settings *settings)
{
  unsigned char charbuffer, confirm;
  int intbuffer, weaponyesno;
  
  do /* Input loop, escapes when the user says they are staisfied with their settings */
  {
    do  /* Prompt difficulty */
    {
      printf("\nThis randomizer has a tendency to make the game easier, especially when using the interesting options like many skills and holy bloods.\n"
      "So here is a chance to up the difficulty by nerfing your units. You will get a chance to change your choice at the end.\n"
      "Enter a number for how many times you want to take 10%% growth and 1 base stat point off your units.\n"
      "0 for   -0  growthtotal               \"The bad spreads are compensation enough. Im not taking the crazy options anyway.\"\n"
      "2 for  -20  growthtotal and  -2 base  \"A little hit is enough.\"\n"
      "4 for  -40  growthtotal and  -4 base  \"The middle option.\"\n"
      "6 for  -60  growthtotal and  -6 base  \"This brings characters with no holy blood that gained Major about back on par, before the randomizer makes them worse.\"\n"
      "8 for  -80  growthtotal and  -8 base  \"Now we are taking off some serious stuff.\"\n"
      "10 for -100 growthtotal and -10 base  \"... Proceed with caution.\n"
      "Or anything inbetween, or all the way up to 20!!!\n"
      "*These are only applied if you randomize growths and bases respecively\n"
      "*(Don't actually go up to 20, your units will have almost 0%% growth and class base bases)");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 20);

    settings->difficulty = intbuffer;
    
    do  /* Prompt class */
    {
      printf("\nDo you want randomized classes? Enter:\n"
      "0 for no changes\n"
      "1 to randomize, and put the children's available weapons in the spoilerfree log so you can plan inheritance\n"
      "2 to randomize, without showing the kids' weapons\n"
      "*This will also edit several weapons, and slightly alter shop inventory.\n"
      "*Does not affect or produce Dancers.\n"
      "*Replacement kids get the weapons of the kid they are replacing, which they probably can't use after being randomized.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->class = charbuffer;
    
    do  /* Prompt promotion */
    {
      printf("\nDo you want randomized promotion? Enter:\n"
      "0 for the expected promotion of the base class\n"
      "1 for anything that retains your weapon ranks (No changing mount, foot units may gain a mount)\n"
      "2 to let any unpromoted class promote into any promoted class\n"
      "*If you didn't randomize classes, 0 won't change anything either.\n"
      "*Classes with multiple \"standard\" promotions (Mages, Myrmidons) have an even chance for each, even on option 0\n"
      "**For option 1:\n"
      "*Be prepared to get a LOT of Paladins\n"
      "*Classes that can become either male or female Paladin still only have one lot for \"Paladin\" in their randomization.\n"
      "*Lord Knight is excluded from classes other than Junior Lord because it sucks.\n"
      "*Units won't gain or lose armored status.\n"
      "*Shamans without Naga blood lose light magic rank on promotion because there is no promoted class with A-rank light.\n"
      "*Master Knight is not included in the regular pool, except for Prince and Princess (Who can still become many other things!), but every character has a 5%% chance of becoming a Master Knight.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->promotion = charbuffer;

    do  /* Prompt bases */
    {
      printf("\nDo you want randomized bases? Enter:\n"
      "0 for no changes\n"
      "1 for randomly distributed personal bases\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1');

    settings->bases = charbuffer;

    do  /* Prompt growths */
    {
      printf("\nDo you want randomized growths? Enter:\n"
      "0 for no changes\n"
      "1 for randomly distributed growths\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1');

    settings->growths = charbuffer;

    /*do   Prompt class bases *//*              NOTE: Maybe come back to this.
    {
      printf("\nDo you want randomized class bases? Enter:\n"
      "0 for no changes\n"
      "1 for random class bases\n"
      "*Warning: This affects enemies too, completely changes class' identities, and makes promotion bonuses wonky\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1');

    settings->classbases = charbuffer; */

    do  /* Prompt skills */
    {
      printf("\nDo you want randomized skills? Enter:\n"
      "0 for no changes\n"
      "1 everyone gets 1 skill\n"
      "2 everyone gets 2 skills\n"
      "3 everyone gets 3 skills\n"
      "*Pursuit will appear more often than other skills, you get to pick the rate.\n"
      "*Remember Pursuit takes up a slot, so with only 1 skill, most units will only get Pursuit.\n"
      "*Sword skills are usable by all weapons and classes\n"
      "*If you pass too many skills to a kid, the menu display will get weird, but the skills still function correctly\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2' && charbuffer != '3');

    settings->skills = charbuffer;
    
    if(settings->skills > '0')
    {
      do  /* Prompt pursuit */
      {
        printf("\nHow much Pursuit do you want? Enter:\n"
        "0 everyone gets Pursuit\n"
        "1 for 1x as often as others\n"
        "2 for 2x, etc up to 9\n");
        charbuffer = getchar();
        Flushline(stdin);
      }
      while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2' && charbuffer != '3' && charbuffer != '4' && charbuffer != '5' && charbuffer != '6' && charbuffer != '7' && charbuffer != '8' && charbuffer != '9');
    }
    
    settings->pursuit = charbuffer;
    
    do  /* Prompt holyblood allocation */
    {
      printf("\nDo you want randomized holy blood allocation? Enter:\n"
      "0 for no changes\n"
      "1 everyone gets 1 Major blood\n"
      "2 everyone gets 1 Major and 1 Minor blood\n"
      "*Seliph is incapable of inheriting certain holy blood types.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->bloodalloc = charbuffer;

    do  /* Prompt holy blood bonuses */
    {
      printf("\nDo you want randomized holy blood growth bonuses? Enter:\n"
      "0 for no changes\n"
      "1 for 20%% to one stat 10%% to another\n"
      "2 for 30%% spread in chunks of 10%%\n"
      "3 for 30%% in one stat\n"
      "*All holy bloods also give 20%% HP\n"
      "*Loptyr gets 10%% extra because it sucks for the coolest one to also be the worst one.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2' && charbuffer != '3');

    settings->bloodbonus = charbuffer;
    
    do  /* Prompt holy weapon bonuses */
    {
      printf("\nDo you want randomized holy weapon bonuses? Enter:\n"
      "0 for no changes\n"
      "1 for 20 to one stat 10 to another\n"
      "2 for 30 randomly spread in chunks of 10\n"
      "*Like in vanilla, Tyrfing gets +10 and Naga gets +50.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->weaponbonus = charbuffer;
    
    /*This option feels off, so im not making it:*/
    
    /*do   Prompt Bad Stats *//*      
    {
      printf("\nLuck is a bad stat. Strength on a Mage or Magic on a Melee unit is not good either.\n"
      "If you wish, i can give you a little bonus to HP for any stats that end up there. Enter:\n"
      "0 for no changes\n"
      "1 only give for Luck\n"
      "2 only give for Magic/Strength\n"
      "3 give HP for both\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->badstats = charbuffer;
    */

    do  /* Prompt weapons rebalance: Melee */
    {
      printf("\nDo you want rebalanced melee weapons? Enter:\n"
      "0 for no\n"
      "1 for giving Swords -2 might and Axes +2 might\n"
      "2 for giving Swords +3 weight and Axes -3 weight\n"
      "3 for doing both of 1 and 2\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 3);

    settings->weapons->balancemelee = intbuffer;
    
    do  /* Prompt weapons rebalance: Magic */
    {
      printf("\nDo you want rebalanced magic weapons? Enter:\n"
      "0 for no\n"
      "1 for giving Wind -3 might and Fire +3 might\n"
      "2 for giving Wind +2 weight and Fire -2 weight\n"
      "3 for doing both of 1 and 2\n"
      "*Long range magic is excluded, as is Valflame.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 3);

    settings->weapons->balancemagic = intbuffer;
    
    do  /* Prompt weapon randomization */
    {
      printf("\nDo you want randomized weapons? Enter:\n"
      "0 for no\n"
      "1 for yes\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 1);

    weaponyesno = intbuffer;
    
    if(weaponyesno)
    {
      do  /* Prompt Might */
      {
        printf("\nHow large variance do you want on weapon might? (Capped at 10) Enter:\n");
        fscanf(stdin, "%d", &intbuffer);
        Flushline(stdin);
      }
      while(intbuffer < 0 || intbuffer > 10);

      settings->weapons->might = intbuffer;
      
      do  /* Prompt Weight */
      {
        printf("\nHow large variance do you want on weapon weight? (Capped at 10) Enter:\n");
        fscanf(stdin, "%d", &intbuffer);
        Flushline(stdin);
      }
      while(intbuffer < 0 || intbuffer > 10);

      settings->weapons->weight = intbuffer;
      
      do  /* Prompt Hit */
      {
        printf("\nHow large variance do you want on weapon hit? (Capped at 50) Enter:\n");
        fscanf(stdin, "%d", &intbuffer);
        Flushline(stdin);
      }
      while(intbuffer < 0 || intbuffer > 50);

      settings->weapons->hit = intbuffer;
    }
    
    do  /* Prompt difficulty */
    {
      printf("\nIf your decisions made you change your mind about your chosen difficulty, you can change it now:\n"
      "Enter:\n"
      "0 for 0%%, \"the bad spreads are compensation enough. Im not taking the crazy options anyway.\"\n"
      "1 for 40%% and 1 base, \"A minor holy blood's worth is enough\"\n"
      "2 for 80%% and 2 base, \"This brings characters with no holy blood that gained Major back on par, before randomizer badness and skills.\"\n"
      "3 for 120%% and 3 base, \"Now we are taking off some serious stuff.\"\n"
      "4 for 160%% and 4 base, \"Relying a lot on bases and skills at this point!\"\n"
      "5 for 200%% and 5 base, \"I don't know where to stop, this is pretty intense... Proceed with caution.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2' && charbuffer != '3' && charbuffer != '4' && charbuffer != '5');

    settings->difficulty = charbuffer;
    
    do
    {
      printf("\nAre you statisfied with your decisions? Enter:\n"
      "0 \"Yes, lets begin the randomizing.\"\n"
      "1 \"No, i want to redo them.\"\n");
      confirm = getchar();
      Flushline(stdin);
    }
    while(confirm != '0' && confirm != '1');
  }
  while(confirm != '0');
  return;
}