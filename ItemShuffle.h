
/* Save the unique stuff in character's 1. inventory slot from being randomized away, by swapping them with junk from the shop. */
void ItemShuffle(FILE *rom, unsigned char header)
{
  /* Locations of first weapon of each character with a non-generic one */ 
  const int JamkeW1 = 0x3B406;
  const int DeirdreW1 = 0x3B4C4;
  const int EdainW1 = 0x3B5CE;
  const int LachesisW1 = 0x3B510;
  const int LevinW1 = 0x3B394;
  /*const int ErinysW1 = 0x3B55C;*/ /* Add one Slim Lance to the reimbursement pool */
  const int TailtiuW1 = 0x3B582;
  const int ClaudeW1 = 0x3B42C;
  const int LexW1 = 0x3B478;  /* For Lex we let him keep his Iron Axe, and give him Sigurds Iron Lance */
  /*const int EthlinW1 = 0x3B4EA*/ /* Add one Slim Sword to the reimbursement pool */
  /*const int SylviaW1 = 0x3B5A8*/
  /* Gen 2 */
  /* Add 2 slim lances and a slim sword to gen 2 reimbursement pool */
  const int CedW1 = 0x3B98C;
  const int HawkW1 = 0x3B6F0;
  const int PattyW1 = 0x3B9BC;
  const int DaisyW1 = 0x3B820;
  const int AressW1 = 0x3B7AE; /* Swap the 2 weapons so he gets to keep Mystletainn */
  const int AltennaW1 = 0x3B89E;
  
  /* Locations of shop weapons to swap them with */
  const int DeirdreSwap = 0x6CBAD;
  const int EdainSwap = 0x6CBAC;
  /*const int LachesisSwap = */
  const int LevinSwap = 0x6D1DA;
  /*const int ErinysSwap = */
  const int TailtiuSwap = 0x6D1DC;
  const int ClaudeSwap = 0x6D1D9;
  const int JamkeSwap = 0x6CBAE;
  /*const int EthlinSwap = */
  /*const int SylviaSwap = */
  const int EmptyWeapon = 0x3F515;
  const int SigurdsLance = 0x3B28B;
  
  /* Lex gets Sigurds Lance, moved to his first slot */
  ByteSwap(rom, LexW1 + 1 + header, SigurdsLance + header);
  ByteSwap(rom, LexW1 + header, LexW1 + 1 + header);
  
  /* Swap Altenna's 2 weapons so she gets to keep Gae Bolg */
  ByteSwap(rom, AltennaW1 + header, AltennaW1 + 1 + header);
  
  /* Swap Aress' 2 weapons so he gets to keep Mystletainn */
  ByteSwap(rom, AressW1 + header, AressW1 + 1 + header);
  
  /* Swap Lacheses' 2 weapons so she gets to keep the Miracle Sword */
  ByteSwap(rom, LachesisW1 + header, LachesisW1 + 1 + header);
  
  /* The empty weapon slot 8D is filled out with a Steel Sword that is given to Ced and Hawk, and moved to their 1st slot */
  fseek(rom, EmptyWeapon + header, SEEK_SET);
  fputc(0x01, rom);
  fseek(rom, CedW1 + 1 + header, SEEK_SET);
  fputc(0x8D, rom);
  ByteSwap(rom, CedW1 + header, CedW1 + 1 + header);
  fseek(rom, HawkW1 + 1 + header, SEEK_SET);
  fputc(0x8D, rom);
  ByteSwap(rom, HawkW1 + header, HawkW1 + 1 + header);
  
  /* The empty weapon slot 8F is filled out with a Steel Sword that is given to Patty and Daisy, and moved to his 1st slot */
  fseek(rom, EmptyWeapon + 1 + header, SEEK_SET);
  fputc(0x01, rom);
  fseek(rom, PattyW1 + 1 + header, SEEK_SET);
  fputc(0x8F, rom);
  ByteSwap(rom, PattyW1 + header, PattyW1 + 1 + header);
  fseek(rom, DaisyW1 + 1 + header, SEEK_SET);
  fputc(0x8F, rom);
  ByteSwap(rom, DaisyW1 + header, DaisyW1 + 1 + header);
  
  /* Swap the weapons of all the others */
  ByteSwap(rom, DeirdreW1 + header, DeirdreSwap + header);
  ByteSwap(rom, TailtiuW1 + header, TailtiuSwap + header);
  /*ByteSwap(rom, LachesisW1 + header, LachesisSwap + header);*/
  ByteSwap(rom, EdainW1 + header, EdainSwap + header);
  ByteSwap(rom, LevinW1 + header, LevinSwap + header);
  ByteSwap(rom, ClaudeW1 + header, ClaudeSwap + header);
  ByteSwap(rom, JamkeW1 + header, JamkeSwap + header);
  
  return;
}