#include <ext_headers.h>
EXT_HEADERS_OPEN
#include <stdio.h>
#include <stdlib.h>
#include <keystone/keystone.h>
EXT_HEADERS_CLOSE

#include <testKeystone.h>

#define COUNT_OF(X) (sizeof(X)/sizeof(*(X)))

static const TestInstruction Mips32TestInstructions[] = {
  {0X00000020, "add $zero, $zero, $zero"},
  {0X00421020, "add $v0, $v0, $v0"},
  {0X00631820, "add $v1, $v1, $v1"},
  {0X00842020, "add $a0, $a0, $a0"},
  {0X00A52820, "add $a1, $a1, $a1"},
  {0X00421020, " add $v0, $v0, $v0"},
  {0X00631820, "add  $v1, $v1, $v1"},
  {0X00842020, "add $a0,  $a0,  $a0"},
  {0X00A52820, "add $a1, $a1, $a1 "},
  {0X03E00008, "jr $ra"},
  {0X8C850003, "lw $a1, 3($a0)"},
  {0X10A40007, "beq $a1, $a0, 32"},
  {0X46000000, "add.s $f0, $f0, $f0"},
  {0X20000000, "addi $zero, $zero, 0"},
  {0X25000000, "addiu $zero, $t0, 0"},
  {0X2500ffe7, "addiu $zero, $t0, -0x19"},
  {0X30000000, "andi $zero, $zero, 0"},
  {0X10000001, "b 8"},
  {0X11101112, "beq $t0, $s0, 0x444c"},
  {0X53b85001, "beql $sp, $t8, 0x14008"},
  {0X50000001, "beqzl $zero, 8"},
  {0X11000001, "beqz $t0, 8"},
  {0X04410003, "bgez $v0, 0x10"},
  {0X05c30049, "bgezl $t6, 0x128"},
  {0X06310041, "bgezal $s1, 0x108"},
  {0X05730049, "bgezall $t3, 0x128"},
  {0X1c000001, "bgtz $zero, 8"},
  {0X5c000001, "bgtzl $zero, 8"},
  {0X18000001, "blez $zero, 8"},
  {0X58000001, "blezl $zero, 8"},
  {0X04000001, "bltz $zero, 8"},
  {0X06c20045, "bltzl $s6, 0x118"},
  {0X15101102, "bne $t0, $s0, 0x440c"},
  {0X5610d001, "bnel $s0, $s0, -0xbff8"},
  {0X14000001, "bnez $zero, 8"},
  {0X55000001, "bnezl $t0, 8"},
  {0Xbc000000, "cache 0, ($zero)"},
  {0X08000000, "j 0"},
  {0X0c000000, "jal 0"},
  {0X74000000, "jalx 0"},
  {0X74000001, "jalx 4"},
  {0X80000000, "lb $zero, ($zero)"},
  {0X90000000, "lbu $zero, ($zero)"},
  {0Xd4000000, "ldc1 $f0, ($zero)"},
  {0Xd8000000, "j"}, // Keystone crash
};

int main()
{
	printf("### TEST: incomplete j instruction after multiple instructions\n");

	return testKeystone(KS_MODE_32, Mips32TestInstructions, COUNT_OF(Mips32TestInstructions));
}
