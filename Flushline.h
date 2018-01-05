
/* Moves through file until newline (flush 1 line in stdin) */
void Flushline(FILE *file)
{
  int flush;
  
  while((flush = fgetc(file) != '\n') && !(feof(file)))
  {}

  return;
}