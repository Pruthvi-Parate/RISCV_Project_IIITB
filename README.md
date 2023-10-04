# RISCV_Social_Distance_Detection

# Aim
The aim of this project is to design and create a versatile social distance detection system controlled by a RISC-V. This system will be helpful to measure social distance. User will be alarmed when distance will be less than 100cm and greater than 0. 
# Working
In this project using RISC-V which is connected to one ultrasonic sensor, one buzzer and one led. First ultrasonic sensor will start to detect the users/objects.  Ultrasonic sensors measure distance by sending and receiving the ultrasonic wave. Using the trigger pin it sends the the transmitted ultrasonic wave travels through the air and is reflected by hitting the Object/users.We know that the speed of sound in air is nearly 344 m/s, so using the speed, time and distance formula we can find the distance using duration. If user is nearer than 100 cm then buzzer will be turned on and led will also turn on.

# Block Diagram
![diagram](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/bea6173f-0e38-4385-bc36-c115a870731f)

# C Program
```
int main(){
	int trig;// bit 0
	int echo;//bit 1
	int buzzer;//bit 2
	int led;//bit 3
	int clk_freq = 10000000;
	float distance;
	int dummy=0xFFFFFFFE;
	unsigned int i;
	unsigned int duration;
	while(1)
	{
		trig = 1;
		asm(
		"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"
    	:"=r"(trig)
		:"r"(dummy));
		for(i=0;i<10000000;i++);
			
		trig = 0;
		asm(
		"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"
    	:"=r"(trig)
		:"r"(dummy));
		i=0;
		
		asm(
		"addi x10, x30, 0\n\t"
		"and %0, x10, 2\n\t"
			:"=r"(echo));         
			
		while(echo!= 1){
			i++;
			asm(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
				:"=r"(echo));
		}
		duration = i/clk_freq;
		distance = duration	*0.0172;
		
		buzzer = 0;
		dummy=0xFFFFFFF4;
		asm(
		"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"
    	:"=r"(buzzer)
		:"r"(dummy));
		
		led = 0;
		dummy=0xFFFFFFF8;
		asm(
		"and x30, x30, %1\n\t"
    	"or x30, x30, %0\n\t"
    	:"=r"(led)
		:"r"(dummy));
		
		
		if(distance <= 100 && distance >= 0){
			buzzer = 1;
			dummy=0xFFFFFFF4;
			asm(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:"=r"(buzzer)
			:"r"(dummy));
			
			led = 1;
			dummy=0xFFFFFFF8;
			asm(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:"=r"(led)
			:"r"(dummy));
		}
		else{
			buzzer = 0;
			dummy=0xFFFFFFF4;
			asm(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:"=r"(buzzer)
			:"r"(dummy));
			
			led = 0;
			dummy=0xFFFFFFF8;
			asm(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:"=r"(led)
			:"r"(dummy));
		}
	}
	return 0;
}

```

# Assembly Code
```

project.o:     file format elf64-littleriscv


Disassembly of section .text:

0000000000000000 <main>:
   0:	fc010113          	addi	sp,sp,-64
   4:	02113c23          	sd	ra,56(sp)
   8:	02813823          	sd	s0,48(sp)
   c:	04010413          	addi	s0,sp,64
  10:	009897b7          	lui	a5,0x989
  14:	68078793          	addi	a5,a5,1664 # 989680 <.L9+0x989494>
  18:	fef42023          	sw	a5,-32(s0)
  1c:	ffe00793          	li	a5,-2
  20:	fef42423          	sw	a5,-24(s0)

0000000000000024 <.L10>:
  24:	00100793          	li	a5,1
  28:	fcf42e23          	sw	a5,-36(s0)
  2c:	fe842783          	lw	a5,-24(s0)
  30:	00ff7f33          	and	t5,t5,a5
  34:	00ff6f33          	or	t5,t5,a5
  38:	fcf42e23          	sw	a5,-36(s0)
  3c:	fe042223          	sw	zero,-28(s0)
  40:	0100006f          	j	50 <.L2>

0000000000000044 <.L3>:
  44:	fe442783          	lw	a5,-28(s0)
  48:	0017879b          	addiw	a5,a5,1
  4c:	fef42223          	sw	a5,-28(s0)

0000000000000050 <.L2>:
  50:	fe442783          	lw	a5,-28(s0)
  54:	0007871b          	sext.w	a4,a5
  58:	009897b7          	lui	a5,0x989
  5c:	67f78793          	addi	a5,a5,1663 # 98967f <.L9+0x989493>
  60:	fee7f2e3          	bgeu	a5,a4,44 <.L3>
  64:	fc042e23          	sw	zero,-36(s0)
  68:	fe842783          	lw	a5,-24(s0)
  6c:	00ff7f33          	and	t5,t5,a5
  70:	00ff6f33          	or	t5,t5,a5
  74:	fcf42e23          	sw	a5,-36(s0)
  78:	fe042223          	sw	zero,-28(s0)
  7c:	000f0513          	mv	a0,t5
  80:	00257793          	andi	a5,a0,2
  84:	fef42623          	sw	a5,-20(s0)
  88:	01c0006f          	j	a4 <.L4>

000000000000008c <.L5>:
  8c:	fe442783          	lw	a5,-28(s0)
  90:	0017879b          	addiw	a5,a5,1
  94:	fef42223          	sw	a5,-28(s0)
  98:	000f0513          	mv	a0,t5
  9c:	00257793          	andi	a5,a0,2
  a0:	fef42623          	sw	a5,-20(s0)

00000000000000a4 <.L4>:
  a4:	fec42783          	lw	a5,-20(s0)
  a8:	0007871b          	sext.w	a4,a5
  ac:	00100793          	li	a5,1
  b0:	fcf71ee3          	bne	a4,a5,8c <.L5>
  b4:	fe042783          	lw	a5,-32(s0)
  b8:	fe442703          	lw	a4,-28(s0)
  bc:	02f757bb          	divuw	a5,a4,a5
  c0:	fcf42c23          	sw	a5,-40(s0)
  c4:	fd842783          	lw	a5,-40(s0)
  c8:	00078513          	mv	a0,a5
  cc:	00000097          	auipc	ra,0x0
  d0:	000080e7          	jalr	ra # cc <.L4+0x28>
  d4:	00050713          	mv	a4,a0
  d8:	000007b7          	lui	a5,0x0
  dc:	0007b583          	ld	a1,0(a5) # 0 <main>
  e0:	00070513          	mv	a0,a4
  e4:	00000097          	auipc	ra,0x0
  e8:	000080e7          	jalr	ra # e4 <.L4+0x40>
  ec:	00050793          	mv	a5,a0
  f0:	00078513          	mv	a0,a5
  f4:	00000097          	auipc	ra,0x0
  f8:	000080e7          	jalr	ra # f4 <.L4+0x50>
  fc:	00050793          	mv	a5,a0
 100:	fcf42a23          	sw	a5,-44(s0)
 104:	fc042823          	sw	zero,-48(s0)
 108:	ff400793          	li	a5,-12
 10c:	fef42423          	sw	a5,-24(s0)
 110:	fe842783          	lw	a5,-24(s0)
 114:	00ff7f33          	and	t5,t5,a5
 118:	00ff6f33          	or	t5,t5,a5
 11c:	fcf42823          	sw	a5,-48(s0)
 120:	fc042623          	sw	zero,-52(s0)
 124:	ff800793          	li	a5,-8
 128:	fef42423          	sw	a5,-24(s0)
 12c:	fe842783          	lw	a5,-24(s0)
 130:	00ff7f33          	and	t5,t5,a5
 134:	00ff6f33          	or	t5,t5,a5
 138:	fcf42623          	sw	a5,-52(s0)
 13c:	000007b7          	lui	a5,0x0
 140:	0007a583          	lw	a1,0(a5) # 0 <main>
 144:	fd442503          	lw	a0,-44(s0)
 148:	00000097          	auipc	ra,0x0
 14c:	000080e7          	jalr	ra # 148 <.L4+0xa4>
 150:	00050793          	mv	a5,a0
 154:	06f04063          	bgtz	a5,1b4 <.L6>
 158:	00000593          	li	a1,0
 15c:	fd442503          	lw	a0,-44(s0)
 160:	00000097          	auipc	ra,0x0
 164:	000080e7          	jalr	ra # 160 <.L4+0xbc>
 168:	00050793          	mv	a5,a0
 16c:	0407c463          	bltz	a5,1b4 <.L6>
 170:	00100793          	li	a5,1
 174:	fcf42823          	sw	a5,-48(s0)
 178:	ff400793          	li	a5,-12
 17c:	fef42423          	sw	a5,-24(s0)
 180:	fe842783          	lw	a5,-24(s0)
 184:	00ff7f33          	and	t5,t5,a5
 188:	00ff6f33          	or	t5,t5,a5
 18c:	fcf42823          	sw	a5,-48(s0)
 190:	00100793          	li	a5,1
 194:	fcf42623          	sw	a5,-52(s0)
 198:	ff800793          	li	a5,-8
 19c:	fef42423          	sw	a5,-24(s0)
 1a0:	fe842783          	lw	a5,-24(s0)
 1a4:	00ff7f33          	and	t5,t5,a5
 1a8:	00ff6f33          	or	t5,t5,a5
 1ac:	fcf42623          	sw	a5,-52(s0)
 1b0:	03c0006f          	j	1ec <.L9>

00000000000001b4 <.L6>:
 1b4:	fc042823          	sw	zero,-48(s0)
 1b8:	ff400793          	li	a5,-12
 1bc:	fef42423          	sw	a5,-24(s0)
 1c0:	fe842783          	lw	a5,-24(s0)
 1c4:	00ff7f33          	and	t5,t5,a5
 1c8:	00ff6f33          	or	t5,t5,a5
 1cc:	fcf42823          	sw	a5,-48(s0)
 1d0:	fc042623          	sw	zero,-52(s0)
 1d4:	ff800793          	li	a5,-8
 1d8:	fef42423          	sw	a5,-24(s0)
 1dc:	fe842783          	lw	a5,-24(s0)
 1e0:	00ff7f33          	and	t5,t5,a5
 1e4:	00ff6f33          	or	t5,t5,a5
 1e8:	fcf42623          	sw	a5,-52(s0)

00000000000001ec <.L9>:
 1ec:	e39ff06f          	j	24 <.L10>

```
# Unique Instructions
```
Number of different instructions: 21
List of unique instructions:
j
sd
sw
lui
lw
sext.w
bne
ld
divuw
auipc
li
mv
or
and
addiw
bltz
addi
bgeu
bgtz
andi
jalr

```
