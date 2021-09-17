/*
 *
 * For detailed info regarding fgets, refer manpage at linprog
 *    % man 3 fgets
 *
 */
#include <stdio.h>

#define MAXLINE 80
#define MAXREG  5
FILE *inf;

typedef enum {
   RFORMAT,
   IFORMAT,
   JFORMAT,
   NONE
} mips_format;

typedef struct template {
   union {
      struct {
         unsigned funct: 6;
         unsigned shamt: 5;
         unsigned rd: 5;
         unsigned rt: 5;
         unsigned rs: 5;
         unsigned opcode: 6;
      } rformat;
      struct {
         unsigned immed: 16;
         unsigned rt: 5;
         unsigned rs: 5;
         unsigned opcode: 6;
      } iformat;
      struct {
         unsigned address: 26;
         unsigned opcode: 6;
      } jformat;
      unsigned int encodedValue;
   } u;
   mips_format format;
} mips_template;


mips_template example_encoding;

int main()
{
   char line[MAXLINE]={0};
   char oper[MAXLINE];
   char rd[MAXREG],rs[MAXREG],rt[MAXREG];
   inf = fopen("sum.asm", "r");

   //while (fgets(line, MAXLINE, stdin)) {  // replace line below with this
   while (fgets(line, MAXLINE, inf)) {
      /* check if a 3-address R format instruction */
      if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) {
         printf("input line: %s\n", line);
         example_encoding.u.rformat.opcode = 0;
         example_encoding.u.rformat.rd = 16;
         example_encoding.u.rformat.rt = 0;
         example_encoding.u.rformat.rs = 0;
         example_encoding.u.rformat.funct = 33;
         printf("parsed line: op:%10s rd:%5s rs:%5s rt:%5s\n",
                oper, rd, rs, rt);
         printf("encoded line: 0x%08x\n", example_encoding.u.encodedValue);

      }
         /* you need to add other patterns for R,I,and J encoding */
      else {
         printf("input line: %s\n", line);
         printf("you need to add sscanf format\n");
      }
   }
   return 0;
}
