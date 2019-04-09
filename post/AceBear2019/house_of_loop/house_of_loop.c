/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2007-2017 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#include <defs.h>

struct note{
  char private[96];
  char title[32];
  char* data;
  note* next_note;
};

//-------------------------------------------------------------------------
// Data declarations

note *first_note;



//----- (0000000000000A8A) ----------------------------------------------------
__int64 __fastcall read_wrapper(void *a1, unsigned int a2)
{
  unsigned int v3; // [rsp+1Ch] [rbp-4h]

  v3 = read(0, a1, a2);
  if ( (v3 & 0x80000000) != 0 )
  {
    puts("Go away, Hacker!!!");
    exit(0);
  }
  if ( *((_BYTE *)a1 + (signed int)v3 - 1) == 10 )
    *((_BYTE *)a1 + (signed int)v3 - 1) = 0;
  return v3;
}

//----- (0000000000000B00) ----------------------------------------------------
int read_int()
{
  char nptr; // [rsp+0h] [rbp-20h]
  unsigned __int64 v2; // [rsp+18h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  read_wrapper(&nptr, 0x10u);
  return atoi(&nptr);
}

//----- (0000000000000B4F) ----------------------------------------------------
void __noreturn handler()
{
  puts("Time out!");
  exit(0);
}

//----- (0000000000000B69) ----------------------------------------------------
unsigned int setup()
{
  setbuf(stdin, 0LL);
  setbuf(stdout, 0LL);
  setbuf(stderr, 0LL);
  signal(14, (__sighandler_t)handler);
  return alarm(60u);
}

//----- (0000000000000BD1) ----------------------------------------------------
int intro()
{
  return puts(
           "*******************************************************************************\n"
           "*                                                                             *\n"
           "*           *      * * *   * * *     * * * *   * * *      *     * * *         *\n"
           "*          * *    *       *          *     *  *          * *    *    *        *\n"
           "*         * * *   *       * * *      * * *    * * *     * * *   * * *         *\n"
           "*        *     *  *       *          *     *  *        *     *  *   *         *\n"
           "*       *       *  * * *   * * *     * * * *   * * *  *       * *     *       *\n"
           "*                                                                             *\n"
           "*************************Challenge Created By chung96vn************************\n"
           "*   Team: AceBear                                                             *\n"
           "*   My github: https://github.com/chung96vn/                                  *\n"
           "*******************************************************************************");
}

//----- (0000000000000BE4) ----------------------------------------------------
int menu()
{
  puts("\n************************************************");
  puts("*                                              *");
  puts("* 1 - Add Note                                 *");
  puts("* 2 - View Note                                *");
  puts("* 3 - Del Note                                 *");
  puts("* 4 - Exit                                     *");
  puts("*                                              *");
  puts("************************************************");
  return printf("Your choice: ");
}

//----- (0000000000000C5C) ----------------------------------------------------
int create_note()
{
  unsigned int size; // ST04_4
  char *s; // ST18_8
  note *current_note; // [rsp+8h] [rbp-18h]
  note *new_note; // [rsp+10h] [rbp-10h]

  new_note = (note *)malloc(144uLL);
  printf("Title: ");
  read_wrapper(new_note->title, 32u);
  new_note->title[25] = 0;
  printf("Private: ", 32LL);
  read_wrapper(new_note, 96u);
  printf("Size of des: ", 96LL);
  size = read_int();
  printf("Des: ");
  s = (char *)malloc(size);
  memset(s, 0, size);
  read_wrapper(s, size);
  new_note->data = s;
  if ( first_note )
  {
    for ( current_note = first_note; current_note->next_note; current_note = current_note->next_note )
      ;                                         // loop until the last note
    current_note->next_note = new_note;
  }
  else
  {
    first_note = new_note;
  }
  return puts("Done~");
}

//----- (0000000000000D97) ----------------------------------------------------
note *view_note()
{
  note *result; // rax
  unsigned int counter; // [rsp+4h] [rbp-Ch]
  note *i; // [rsp+8h] [rbp-8h]

  counter = 1;
  result = first_note;
  for ( i = first_note; i; i = i->next_note )
  {
    printf("Note %d:\n", counter);
    printf("\tTitle: %s\n\tDes: %s\n", i->title, i->data);
    ++counter;
    result = i->next_note;
  }
  return result;
}

//----- (0000000000000E18) ----------------------------------------------------
unsigned __int64 del_note()
{
  note *tbf_note; // [rsp+0h] [rbp-40h]
  note *prev_note; // [rsp+8h] [rbp-38h]
  char s1; // [rsp+10h] [rbp-30h]
  unsigned __int64 v4; // [rsp+38h] [rbp-8h]

  v4 = __readfsqword(0x28u);
  printf("Title: ");
  read_wrapper(&s1, 0x20u);
  prev_note = 0LL;
  for ( tbf_note = first_note; tbf_note && strncmp(&s1, tbf_note->title, 0x20uLL); tbf_note = tbf_note->next_note )
    prev_note = tbf_note;
  if ( tbf_note )
  {
    if ( prev_note )
      prev_note->next_note = tbf_note->next_note;
    else
      first_note = tbf_note->next_note;
    free(tbf_note->data);
    free(tbf_note);
    puts("Done");
  }
  else
  {
    puts("Not found~~");
  }
  return __readfsqword(0x28u) ^ v4;
}

//----- (0000000000000F36) ----------------------------------------------------
void __fastcall __noreturn main(__int64 a1, char **a2, char **a3)
{
  int choice; // eax

  setup();
  intro();
  while ( 1 )
  {
    while ( 1 )
    {
      menu();
      choice = read_int();
      if ( choice != 2 )
        break;
      view_note();
    }
    if ( choice > 2 )
    {
      if ( choice == 3 )
      {
        del_note();
      }
      else
      {
        if ( choice == 4 )
        {
          puts("Bye~");
          exit(0);
        }
fail:
        puts("Invalid choice!");
      }
    }
    else
    {
      if ( choice != 1 )
        goto fail;
      create_note();
    }
  }
}
