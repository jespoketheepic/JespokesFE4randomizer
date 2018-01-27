#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>


/* Dev NOTE: you may find commented out bits of code pertaining to a more elaborate promotion randomization. 
I scrapped it because the way i was going about it was ABSOLUTELY ATTROCIOUS. I agonized and worked over it for too long to let
myself delete it outright, in case some slim chance i though of a way to fix it, but it is trash. */

/* Define constants */
#define TEXTBUFFERSIZE 30       /* Big enough to fit a name or classname, expand if other stuff needs to be stored there */ 
#define CHARACTER 0x3B268       /* The position in the rom where the first character entry starts */
#define CHARACTERSIZE 0x26      /* The distance to offset to get to the same place in the next character entry */
#define GENDER 0x11             /* The distance from the start of the character entry to their gender */
#define GROWTH 0x13             /* The distance from the start of the character entry to their first growth rate */
#define SKILL 0x1B              /* The distance from the start of the character entry to their first Skill */
#define BLOOD 0x1E              /* The distance from the start of the character entry to their first holy blood */
#define WEAPON1 0x22            /* The distance from the start of the character entry to their first weapon */
#define CLASS 0x08              /* The distance from the start of the character entry to their class */

#define UNPROMOTEDCLASSCOUNT 22     /* The number of elements in the "unpromoted[]" array excluding the \0 at the end since it is only there so i can read it as a string (SORRY!!!)*/
#define PROMOTEDCLASSCOUNT 20       /* The number of elements in the "promoted[]" array excluding the \0 at the end since it is only there so i can read it as string (SORRY!!!)*/
#define MAXPROMOOPTIONS 15          /* The max number of promotions the randomizer can chose from without errors when not picking from the full pool. */

#define HOLYBLOOD 0x389E5       /* The position in the rom where the first holy blood entry starts (its first growth bonus) */
#define HOLYBLOODSIZE 0x10      /* The distance to offset to get to the same place in the next holy blood entry */
#define HOLYWEAPONBONUS 0x08    /* The distance from the start of the holy blood entry to their holy weapon bonus */

#define SELIPHBLOOD 0x4836D     /* NOTE: VERIFY. The location of Seliph's holy blood */
#define PROMOTION 0x3833C       /* Location of the first character's promotion */

#define CHARACTERTOTAL 0x3F     /* Total number of characers (gen 1, gen 2 adults, kids, substitutes) */
#define FIRSTGEN 24             /* Nr of units in gen 1*/
#define SECONDGENFIX 22         /* Nr of FIXED AND REPLACEMENT UNITS in gen 2*/
#define KIDSCOUNT 17            /* Nr of child units */

#define CLASSBASE 0x38FC7       /* Location of the Str base of the first class */
#define CLASSSIZE 0x1F          /* The distance from a class entry to get to the same place in the next */

#define SELLHOLYWEAPON 0x4B2E7  /* The location of the byte to set to 00 so we can sell holyweapons */
#define INHERITHOLYWEAPON 0x7AB6C   /* The location of the byte to set to 05 so all holyweapons can be inherited */
#define SEIZEFIX1 0x5E43C       /* Change to 22 33 A3 84 to fix seizing */
#define SEIZEFIX2 0x5E441       /* Change from 06 to 01 */
#define SEIZEFIX3 0x5E446       /* Change from 2C to 19 */
#define SWORDSKILLINHERIT 0x7A976   /* The position in the rom of the first sword skill inheritance byte. Set to FF.*/
#define INHERITSIZE 0x03        /* The distance to offset to get to the next character's inheritance */
#define INHERITCOUNT 0x27         /* I don't know why there are 25 inheritance adresses when there are way fewer kids than that */
#define JULIUSSKILLS 0x3D15C    /* Location of Julius' skill slot 1 */
#define JULIUSDEF 0x3D146       
#define WEAPONENTRY 0x3F488     /* Location of the 0th weapon entry. (No ID 0.) Add a weapon ID from a character entry to get to the specific one */

#define WEAPONSTATS 0x3EAEF     /* Location of the Might of the Iron Sword */
#define WEAPONSTATSSIZE 0x13    /* Distance to offset to get to the next weapon */
#define WEAPONSTATSCOUNT 0x55   /* Number of entries to go through (aka not all relevant entries, but im not jumping through hoops to get all the broken weapons along)*/

typedef struct Weapons
{
  int balancemagic;   /* 0 for no, 1 for -3 mt Wind +3 mt Fire, 2 +2 weight Wind -2 weight Fire, 3 both of 1 and 2 */
  int balancemelee;   /* 0 for no, 1 for -2 mt Sword +2 mt Axe, 2 +3 weight Sword -3 weight Axe, 3 both of 1 and 2 */
  int might;          /* How much it can vary, suggested 2-4 */
  int hit;            /* How much it can vary, suggested 10-20 */
  int weight;         /* How much it can vary, suggested 2-4 */
} Weapons;

typedef struct Settings
{
  int difficulty;               /* This randomizer has a tendency to make the game easier, especially when using the interesting options like many skills and holy bloods.
                                So pick how much to take off growth total to compensate*/
  unsigned char class;       /* 0 for no, 1 to put children's weapons in spoilerfree log so you can plan inheritance, 2 for surprise me! */
  unsigned char promotion;   /* 0 for the expected, 1 for anything that retains your weapon ranks (No mount downgrades), 2 for complete madness.
                                *If you didn't randomize classes, 0 won't change anything either.
                                *Classes with multiple "standard" promotions (Mages, Myrmidons) have an even chance for each even on 0
                                *If you pick option 1, be prepared to get a LOT of Falcon Knights and Paladins 
                                *For option 1, Master Knight is not included in the regular pool, except for Prince and Princess (Who can still become many other things!), but every character has a 5% chance of becoming a Master Knight. */
  unsigned char bases;       /* 0 for no, 1 for yes */
  unsigned char growths;     /* 0 for no, 1 for yes */
/*  unsigned char classbases;*/  /* 0 for no, 1 for yes */
  unsigned char skills;      /* 0 for leaving skills alone, 11 everyone gets 1 skill, 12 everyone gets 2 skills, 13 everyone gets 3 skills 
                                *Pursuit will appear more often than other skills
                                *Sword skills are usable by all weapons and classes */
  int pursuit;               /* 0 for everyone gets Pursuit, 1 for 1x as often as others, etc up to 9 */
  int bloodalloc;  /* 0 for no, 1 for everyone gets a Major, 2 for everyone gets a Major and a Minor */
  int bloodbonus;            /* 0 for no, 1 20% to one stat 10% to another, 2 30% spread in chunks of 10%, 3 30% in one stat, 
                                *all bloods also give 20% HP */
  unsigned char weaponbonus; /* 0 for keep, 1 for 20 to one stat 10 to another, 2 for 30 points spread in chunks of 10
                                *Naga gets +50 bonus*/
  /*unsigned char badstats;*/   /* 0 for no, 1 for adding luck to HP, 2 for adding Str/Mag to HP, 3 for both */ /*NOTE: scrapped for not feeling in the randomizer spirit */
  
  Weapons *weapons;
} Settings;


/* Prototypes */
void SetSettings(Settings *settings);
void ItemShuffle(FILE *rom, int header);
void ByteSwap(FILE *file, int loc1, int loc2);
void Flushline(FILE *file);
void FixedStuff(FILE *rom, int header);
void RandomizeCharactersG1(FILE *rom, Settings *settings, unsigned char *entrybuffer, int header, FILE *names, FILE *log, FILE *superlog);
void RandomizeClass(unsigned char *class, unsigned char gender, FILE *log);
int CharInArray(unsigned char id, const unsigned char *list);
void PrintClassName(unsigned char id, FILE *file);
unsigned char RandomizePromotion(FILE *rom, int header, unsigned char promosetting, FILE *log, unsigned char class, unsigned char gender, int offset);
void RandomizeBases(unsigned char *entrybuffer, int diffsetting);
void RandomizeGrowths(unsigned char *entrybuffer, int diffsetting);
void PrintStats(FILE *log, unsigned char *entrybuffer, unsigned char basesetting, unsigned char growthsetting, FILE *rom, int header, unsigned char class, unsigned char *blood);
void RandomizeSkills(unsigned char *entrybufferskill, unsigned char skillsetting, int pursuitsetting, FILE *log);
void RandomizeCharacterHolyBlood(unsigned char *entrybufferblood, int bloodsetting, FILE *log);
void RandomizeBloodBonus(FILE *rom, int header, int BBsetting, FILE *log, FILE *superlog);
void RandomizeWeaponBonus(FILE *rom, int header, unsigned char WBsetting, FILE *log);
void RandomizeCharactersG2Fix(FILE *rom, Settings *settings, unsigned char *entrybuffer, int header, FILE *names, FILE *log);
int ClassWeaponRanks(int *weaponrankbuffer, unsigned char class);
void RandomizeChildClassAndPromo(FILE *rom, int header, char classsetting, unsigned char promosetting, FILE *names, FILE *log, FILE *superlog);
void MatchWeapon(FILE *rom, int header, unsigned char class, unsigned char weaponID, unsigned char *spareweapons);
int GenderMatch(unsigned char gender, unsigned char class);
void RandomizeWeapons(FILE *rom, int header, Weapons *weapons);
void ApplyDifficulty(unsigned char *entrybuffer, int difficulty, int scale);
void SwordSkillsPatch(FILE *rom, int header);
void SeliphBlood(FILE *rom, int header, unsigned char *parentblood, unsigned char *seliphblood, int parent, FILE *superlog);


/* Include functions */
#include "SetSettings.h"
#include "ItemShuffle.h"
#include "ByteSwap.h"
#include "Flushline.h"
#include "FixedStuff.h"
#include "RandomizeCharactersG1.h"
#include "RandomizeClass.h"
#include "CharInArray.h"
#include "PrintClassName.h"
#include "RandomizePromotion.h"
#include "RandomizeBases.h"
#include "RandomizeGrowths.h"
#include "PrintStats.h"
#include "RandomizeSkills.h"
#include "RandomizeCharacterHolyBlood.h"
#include "RandomizeBloodBonus.h"
#include "RandomizeWeaponBonus.h"
#include "RandomizeCharactersG2Fix.h"
#include "ClassWeaponRanks.h"
#include "RandomizeChildClassAndPromo.h"
#include "MatchWeapon.h"
#include "GenderMatch.h"
#include "RandomizeWeapons.h"
#include "ApplyDifficulty.h"
#include "SwordSkillsPatch.h"
#include "SeliphBlood.h"


int main()
{
  /* Declare variables */
  /* Plain char for text */
  char textbuffer[TEXTBUFFERSIZE];
  unsigned char entrybuffer[CHARACTERSIZE];
  FILE *rom, *names, *log, *superlog;
  int header;
  
  /* Initialize random seed */
  srand (time(NULL));
  
  /* Prompt for file */
  printf("Welcome to Jespoke's FE4 randomizer!\n"
  "This randomizer is tested on a raw ROM and with the Project Naga translation patch.\n"
  "It supports both headered and unheadered ROMs.\n"
  "You should probably make this window bigger, there is gonna be a lot of text.\n"
  "Enter the name of your ROM (remember the file extention)(no names longer than 40 characters)\n");
  
  /* Open ROM */
  fgets(textbuffer, sizeof(textbuffer), stdin);
  textbuffer[strcspn(textbuffer, "\n")] = '\0'; /* Remove the newline that fgets gives */
  if((rom = fopen(textbuffer, "r+b")) == NULL)
  {
    printf("Error: Couldn't find ROM. (%s)\n"
    "Is it in the folder together with this program?\n"
    "Is its name 40 characters or less long?\n"
    "Press Enter to exit.\n", textbuffer);
    Flushline(stdin);
    return EXIT_FAILURE;
  }
  
  /* Open data files */
  if((names = fopen("Names.txt", "r")) == NULL)
  {
    printf("Error: Missing Names.txt\n"
    "Press Enter to exit.\n");
    Flushline(stdin);
    return EXIT_FAILURE;
  }
  
  /* RIP Promotionchances.txt
  if((randompromotxt = fopen("Promotionchances.txt", "r")) == NULL)
  {
    printf("Error: Missing Promotionchances.txt\n"
    "Press Enter to exit.\n");
    Flushline(stdin);
    return EXIT_FAILURE;
  }*/
  
  /* Open changelogs */
  if((log = fopen("FULL changelog.txt", "w")) == NULL
   || (superlog = fopen("Spoilerfree changelog.txt", "w")) == NULL)
  {
    printf("Error: Failed to make a changelog.\n"
    "Is there no space?\n"
    "Do i not have permission from the system?\n"
    "Press Enter to exit.\n");
    Flushline(stdin);
    return EXIT_FAILURE;
  }
  
  Settings *settings = malloc(sizeof(*settings));
  settings->weapons = malloc(sizeof(*(settings->weapons)));
  if(settings == NULL || settings->weapons == NULL)
  {
    printf("Error: Could not allocate enough space to run program.\n"
    "Press Enter to exit.\n");
    Flushline(stdin);
    free(settings);
    free(settings->weapons);
    return EXIT_FAILURE;
  }
  
  
  /* Basic info */
  printf("\nSome changes that will happen either way, that are nice to know beforehand:\n"
  "*Sword skills can be used and inherited by anyone\n"
  "*Holy weapons can be sold and bought\n"
  "*Normally non-playable classes are left out of class randomizing just in case they break something. Plain Mage is left out because it is just a strictly worse Bard\n"
  "*Seliph can not inherit Thrud, Forseti, Blagi, Hezul or Loptyr blood. If his parents have these, the randomizer will give him random other holybloods instead.\n"
  "* A few enemies were moved in chapter 7 to give Shannan and Patty/Daisy some hope of survival. If you are particularly unlucky you may still need to make more edits to make it possible.\n"
  "*Various minor changes to accomodate non-flying Altenna.\n"
  "*The final boss' defenses are lowered, and he no longer has Wrath.\n\n"
  "Warnings:\n"
  "*Inheriting multiple Holy Weapons on the same characer messes up your save file.\n"
  "*Some sprites for reqruitable enemies load wrong. Reseting the game once they are reqruited fixes it.\n" 
  "*Seizing the second to last castle in chapter 9 before defeating Travant will prevent Altenna from joining you.\n"
  "Press Enter to continue.\n"); /* NOTE: Add stuff as it is added */
  Flushline(stdin);
  
  /* Prompt for settings */
  SetSettings(settings);
  
  /* If there is no header, getc returns 0xE0(true), so header is set 0. If there is a header, getc returns 0(false), so header is set 0x200 */
  header = getc(rom) ? 0 : 0x200;
  printf("%c", header);

  /* Make the changes that are the same no matter what */
  FixedStuff(rom, header);
  fprintf(log, "Changes that are made regardless of settings:\n"
  "* All skills are usable and inheritable by all classes\n"
  "* Holy weapons can be sold and bought. (They won't always display a price)\n"
  "* Seliph can not inherit Thrud, Forseti, Blagi, Hezul or Loptyr blood. If his parents have these, the randomizer will give him random other holybloods instead.\n"
  "* A few enemies were moved in chapter 7 to give Shannan and Patty/Daisy some hope of survival. If you are particularly unlucky you may still need to make more edits to make it possible.\n"
  "* Various minor changes to accomodate non-flying Altenna.\n"
  "* The final boss' defenses are lowered, and he no longer has Wrath.\n\n"
  "Warnings:\n"
  "*Inheriting multiple Holy Weapons on the same characer messes up your save file.\n"
  "*Some sprites for reqruitable enemies load wrong. Reseting the game once they are reqruited fixes it.\n"
  "*Seizing the second to last castle in chapter 9 before defeating Travant will prevent Altenna from joining you.\n\n");
  fprintf(superlog, "Changes that are made regardless of settings:\n"
  "* All skills are usable and inheritable by all classes\n"
  "* Holy weapons can be sold and bought. (They still won't display a price)\n"
  "* Seliph can not inherit Thrud, Forseti, Blagi, Hezul or Loptyr blood. If his parents have these, the randomizer will give him random other holybloods instead.\n"
  "* A few enemies were moved in chapter 7 to give Shannan and Patty/Daisy some hope of survival. If you are particularly unlucky you may still need to make more edits to make it possible.\n"
  "* Various minor changes to accomodate non-flying Altenna.\n"
  "* The final boss' defenses are lowered, and he no longer has Wrath.\n\n"
  "Warning:\n"
  "*Inheriting multiple Holy Weapons on the same characer messes up your save file.\n"
  "*Some sprites for reqruitable enemies load wrong. Reseting the game once they are reqruited fixes it.\n"
  "*Seizing the second to last castle in chapter 9 before defeating Travant will prevent Altenna from joining you.\n\n");
  
  /* Save the unique stuff in character's 1st inventory slot from being randomized away, by swapping them with junk from the shop. */
  if(settings->class)
  {
    ItemShuffle(rom, header);
  }
  
  /* Randomize non-character stuff*/
  printf("\nBonus:\n");
  if(settings->bloodbonus > 0)
  {
    RandomizeBloodBonus(rom, header, settings->bloodbonus, log, superlog);
  }
  if(settings->weaponbonus > '0')
  {
    RandomizeWeaponBonus(rom, header, settings->weaponbonus, log);
  }
/*  if(settings->classbases > '0')    NOTE: Might return for this option, even if i think it is terrible.
  {
    
  }*/
  
  /* Randomize the characters! */
  printf("\nGen 1:\n");
  RandomizeCharactersG1(rom, settings, entrybuffer, header, names, log, superlog);
  printf("\nGen 2:\n");
  RandomizeCharactersG2Fix(rom, settings, entrybuffer, header, names, log);
  printf("\nKids:\n");
  RandomizeChildClassAndPromo(rom, header, settings->class, settings->promotion, names, log, superlog);
  
  /* Randomize Weapons */
  printf("\nWeapons:\n");
  RandomizeWeapons(rom, header, settings->weapons);
  
  printf("\nThanks to the various Serenesforest users who found most of the obscure ROM adresses this program edits. Particular thanks to Lamia and the other posters in \"Lamia's FE4 stuff\"\n"
  "Thanks to the people behind the FE4 Binary tools for making the Sword Skills patch.\n"
  "Press Enter to finish.");
  getchar();
  
  free(settings);
  free(settings->weapons);
  return EXIT_SUCCESS;
}


/* =======================================================================================================================================================*/


