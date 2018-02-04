
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
      printf("\nRandomizing the game has various factors that can make the game harder or easier.\n"
      "So here is a chance to up the difficulty by nerfing your units. You will get a chance to change your choice at the end.\n"
      "Enter a number for how many times you want to take 20%% growth and 1 base stat point off your units. (Capped at 5)\n"
      "For example:\n"
      "0 for no changes                      \"The bad spreads are compensation enough. Im not taking the crazy options anyway.\"\n"
      "1 for  -20  growthtotal and  -1 base  \"A little hit is enough.\"\n"
      "3 for  -60  growthtotal and  -3 base  \"This brings characters with no holy blood that gained Major back about where they started, even before other options set in.\"\n"
      "5 for  -100  growthtotal and  -5 base  \"... Proceed with caution.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 5);

    settings->difficulty = intbuffer;
    
    do  /* Prompt class */
    {
      printf("\nDo you want randomized classes? Enter:\n"
      "0 for no changes\n"
      "1 to randomize, and put the children's available weapons in the spoilerfree log so you can plan inheritance\n"
      "2 to randomize, without showing the kids' weapons\n"
      "*This will also edit several weapons, and slightly alter shop inventory.\n"
      "*Does not affect or produce Dancers.\n"
      "*Characters can become any class that won't break the game due to gender incompatibility.\n"
      "*Class/gender combinations that cause minor visual glitches are still included. Female sword cavalry for example fights with invisible swords, but otherwise work fine.\n"
      "*Replacement kids get the weapons of the kid they are replacing, which they probably can't use after being randomized.\n");
      charbuffer = getchar();
      Flushline(stdin);
    }
    while(charbuffer != '0' && charbuffer != '1' && charbuffer != '2');

    settings->class = charbuffer;
    
    do  /* Prompt Troubadour */
    {
      printf("\nDo you want a guaranteed Troubadour, so you can be sure to have a healer?\n"
      "0 for no\n"
      "1 for Ethlin, who joins earlier, but leaves at a point.\n"
      "2 for Edain, who joins a bit later, but stays around.\n"
      "*If you pick either one, Lana/Muirne will remain a cleric in gen 2 as well."
      "*Whichever one you pick will get Ethlin's Heal staff in their inventory.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 2);
    
    if(intbuffer == 1)
      intbuffer = 0x10;
    else if(intbuffer == 2)
      intbuffer = 0x16;
    
    settings->healer = intbuffer;
    
    do  /* Prompt promotion */
    {
      printf("\nDo you want randomized promotion? Enter:\n"
      "0 for the expected promotion of the base class\n"
      "1 for anything that retains your weapon ranks (No changing mount, foot units may gain a mount)\n"
      "2 to let any unpromoted class promote into any promoted class\n"
      "*If you didn't randomize classes, 0 won't change anything either.\n"
      "*Classes with multiple \"standard\" promotions (Mages, Myrmidons) have an even chance for each, even on option 0\n"
      "**For option 1:\n"
      "*Lord Knight is excluded from classes other than Junior Lord because it sucks.\n"
      "*Units won't gain or lose armored status.\n"
      "*Priestess' without Naga blood lose light magic rank on promotion because there is no promoted class with A-rank light.\n"
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
      "1 for randomly distributed growths\n"
      "*Keep in mind that some of the growths will end up in undesirable stats.\n");
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
        "2 for 2x, etc up to 20\n"
        "*There are 14 other skills than Pursuit, so 14 makes it a 50/50 on each skill roll.\n");
        fscanf(stdin, "%d", &intbuffer);
        Flushline(stdin);
      }
      while(intbuffer < 0 || intbuffer > 20);
    }
    
    settings->pursuit = intbuffer;
    
    do  /* Prompt holyblood allocation */
    {
      printf("\nDo you want randomized holy blood allocation? Enter:\n"
      "0 for no changes\n"
      "1 everyone gets 1 Major blood\n"
      "2 everyone gets 1 Major and 1 Minor blood\n"
      "3 everyone has 33%% chance of getting a Major blood, and 66%% chance of a Minor blood.\n"
      "4 everyone gets 4 minor bloods.\n"
      "*Option 4 means you can't use Holy Weapons in gen 1, but gives a lot of options when matching for children.\n"
      "*Consider that most units will get holy blood that doesn't match their weapon.\n"
      "*Seliph is incapable of inheriting certain holy blood types.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 4);

    settings->bloodalloc = intbuffer;

    do  /* Prompt holy blood bonuses */
    {
      printf("\nDo you want randomized holy blood growth bonuses? Enter:\n"
      "0 for no changes\n"
      "1 for 20%% HP and 30%% spread among the rest\n"
      "2 for 20%% HP and 20%% spread among the rest\n"
      "3 for 10%% HP and 20%% spread among the rest\n"
      "4 for 10%% HP and 10%% on another stat\n"
      "5 for no bonus\n"
      "*It is highly advised you pick a small holy blood bonus when playning with many skills and holy bloods, if you wish for any challenge out of the second half of the game."
      "*Loptyr gets 10%% extra because it sucks for the coolest one to also be the worst one.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 5);

    settings->bloodbonus = intbuffer;
    
    do  /* Prompt holy weapon bonuses */
    {
      printf("\nDo you want randomized holy weapon bonuses? Enter:\n"
      "0 for no changes\n"
      "1 for 30 randomly spread in chunks of 10\n"
      "2 for 20 to one stat 10 to another\n"
      "*Like in vanilla, Naga gets +50.\n");
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
      "1 for giving Swords +3 weight and Axes -2 weight +2 might\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 1);

    settings->weapons->balancemelee = intbuffer;
    
    do  /* Prompt weapons rebalance: Magic */
    {
      printf("\nDo you want rebalanced magic weapons? Enter:\n"
      "0 for no\n"
      "1 for giving Wind -2 might and Fire +2 might\n"
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
    else
    {
      settings->weapons->might = 0;
      settings->weapons->hit = 0;
      settings->weapons->weight = 0;
    }
    
    do  /* Prompt difficulty */
    {
      printf("\nRandomizing the game has various factors that can make the game harder or easier.\n"
      "So here is a chance to up the difficulty by nerfing your units. You will get a chance to change your choice at the end.\n"
      "Enter a number for how many times you want to take 20%% growth and 1 base stat point off your units. (Capped at 5)\n"
      "For example:\n"
      "0 for no changes                      \"The bad spreads are compensation enough. Im not taking the crazy options anyway.\"\n"
      "1 for  -20  growthtotal and  -1 base  \"A little hit is enough.\"\n"
      "3 for  -60  growthtotal and  -3 base  \"This brings characters with no holy blood that gained Major back about where they started, even before other options set in.\"\n"
      "5 for  -100  growthtotal and  -5 base  \"... Proceed with caution.\n");
      fscanf(stdin, "%d", &intbuffer);
      Flushline(stdin);
    }
    while(intbuffer < 0 || intbuffer > 5);

    settings->difficulty = intbuffer;
    
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
  
  printf("If the program gets stuck beyond this point, get a fresh rom and consider sending a bug report.\n"
  "Press Enter to continue:");
  getchar();
  
  return;
}