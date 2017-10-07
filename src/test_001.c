#include <ext_headers.h>
EXT_HEADERS_OPEN
#include <stdio.h>
#include <stdlib.h>
EXT_HEADERS_CLOSE

#include <testKeystone.h>
#include <keystone/keystone.h>

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
  {0Xd8000000, "ldc2 $0, ($zero)"},
  {0X84000000, "lh $zero, ($zero)"},
  {0X94000000, "lhu $zero, ($zero)"},
  {0Xc0000000, "ll $zero, ($zero)"},
  {0X3c000000, "lui $zero, 0"},
  {0X8c000000, "lw $zero, ($zero)"},
  {0Xc4000000, "lwc1 $f0, ($zero)"},
  {0Xc8000000, "lwc2 $0, ($zero)"},
  {0X88000000, "lwl $zero, ($zero)"},
  {0X98000000, "lwr $zero, ($zero)"},
  {0X44000000, "mfc1 $zero, $f0"},
  {0X00000000, "nop"},
  {0X35000000, "ori $zero, $t0, 0"},
  {0Xa0000000, "sb $zero, ($zero)"},
  {0Xe0000000, "sc $zero, ($zero)"},
  {0Xf4000000, "sdc1 $f0, ($zero)"},
  {0Xf8000000, "sdc2 $0, ($zero)"},
  {0Xa4000000, "sh $zero, ($zero)"},
  {0X28000000, "slti $zero, $zero, 0"},
  {0X2c000000, "sltiu $zero, $zero, 0"},
  {0Xac000000, "sw $zero, ($zero)"},
  {0Xe4000000, "swc1 $f0, ($zero)"},
  {0Xe8000000, "swc2 $0, ($zero)"},
  {0Xa8000000, "swl $zero, ($zero)"},
  {0Xb8000000, "swr $zero, ($zero)"},
  {0X38000000, "xori $zero, $zero, 0"},
};

int main()
{
	printf("### TEST: 32 bits instructions\n");

	return testKeystone(KS_MODE_32 ,Mips32TestInstructions, COUNT_OF(Mips32TestInstructions));
}
