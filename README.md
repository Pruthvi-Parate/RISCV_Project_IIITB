# RISCV_Social_Distance_Detection
![image](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/bfc1cd72-51fa-48c9-bab9-b71fea6f1ddb)

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
		distance = duration*172;
		
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
		
		
		if(distance <= 1 && distance >= 0){
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



project.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	fc010113          	add	sp,sp,-64
   4:	02112e23          	sw	ra,60(sp)
   8:	02812c23          	sw	s0,56(sp)
   c:	04010413          	add	s0,sp,64
  10:	009897b7          	lui	a5,0x989
  14:	68078793          	add	a5,a5,1664 # 989680 <.L9+0x9894bc>
  18:	fef42023          	sw	a5,-32(s0)
  1c:	ffe00793          	li	a5,-2
  20:	fef42423          	sw	a5,-24(s0)

00000024 <.L10>:
  24:	00100793          	li	a5,1
  28:	fcf42e23          	sw	a5,-36(s0)
  2c:	fe842783          	lw	a5,-24(s0)
  30:	00ff7f33          	and	t5,t5,a5
  34:	00ff6f33          	or	t5,t5,a5
  38:	fcf42e23          	sw	a5,-36(s0)
  3c:	fe042223          	sw	zero,-28(s0)
  40:	0100006f          	j	50 <.L2>

00000044 <.L3>:
  44:	fe442783          	lw	a5,-28(s0)
  48:	00178793          	add	a5,a5,1
  4c:	fef42223          	sw	a5,-28(s0)

00000050 <.L2>:
  50:	fe442703          	lw	a4,-28(s0)
  54:	009897b7          	lui	a5,0x989
  58:	67f78793          	add	a5,a5,1663 # 98967f <.L9+0x9894bb>
  5c:	fee7f4e3          	bgeu	a5,a4,44 <.L3>
  60:	fc042e23          	sw	zero,-36(s0)
  64:	fe842783          	lw	a5,-24(s0)
  68:	00ff7f33          	and	t5,t5,a5
  6c:	00ff6f33          	or	t5,t5,a5
  70:	fcf42e23          	sw	a5,-36(s0)
  74:	fe042223          	sw	zero,-28(s0)
  78:	000f0513          	mv	a0,t5
  7c:	00257793          	and	a5,a0,2
  80:	fef42623          	sw	a5,-20(s0)
  84:	01c0006f          	j	a0 <.L4>

00000088 <.L5>:
  88:	fe442783          	lw	a5,-28(s0)
  8c:	00178793          	add	a5,a5,1
  90:	fef42223          	sw	a5,-28(s0)
  94:	000f0513          	mv	a0,t5
  98:	00257793          	and	a5,a0,2
  9c:	fef42623          	sw	a5,-20(s0)

000000a0 <.L4>:
  a0:	fec42703          	lw	a4,-20(s0)
  a4:	00100793          	li	a5,1
  a8:	fef710e3          	bne	a4,a5,88 <.L5>
  ac:	fe042783          	lw	a5,-32(s0)
  b0:	fe442703          	lw	a4,-28(s0)
  b4:	02f757b3          	divu	a5,a4,a5
  b8:	fcf42c23          	sw	a5,-40(s0)
  bc:	fd842703          	lw	a4,-40(s0)
  c0:	0ac00793          	li	a5,172
  c4:	02f707b3          	mul	a5,a4,a5
  c8:	00078513          	mv	a0,a5
  cc:	00000097          	auipc	ra,0x0
  d0:	000080e7          	jalr	ra # cc <.L4+0x2c>
  d4:	00050793          	mv	a5,a0
  d8:	fcf42a23          	sw	a5,-44(s0)
  dc:	fc042823          	sw	zero,-48(s0)
  e0:	ff400793          	li	a5,-12
  e4:	fef42423          	sw	a5,-24(s0)
  e8:	fe842783          	lw	a5,-24(s0)
  ec:	00ff7f33          	and	t5,t5,a5
  f0:	00ff6f33          	or	t5,t5,a5
  f4:	fcf42823          	sw	a5,-48(s0)
  f8:	fc042623          	sw	zero,-52(s0)
  fc:	ff800793          	li	a5,-8
 100:	fef42423          	sw	a5,-24(s0)
 104:	fe842783          	lw	a5,-24(s0)
 108:	00ff7f33          	and	t5,t5,a5
 10c:	00ff6f33          	or	t5,t5,a5
 110:	fcf42623          	sw	a5,-52(s0)
 114:	000007b7          	lui	a5,0x0
 118:	0007a583          	lw	a1,0(a5) # 0 <main>
 11c:	fd442503          	lw	a0,-44(s0)
 120:	00000097          	auipc	ra,0x0
 124:	000080e7          	jalr	ra # 120 <.L4+0x80>
 128:	00050793          	mv	a5,a0
 12c:	06f04063          	bgtz	a5,18c <.L6>
 130:	00000593          	li	a1,0
 134:	fd442503          	lw	a0,-44(s0)
 138:	00000097          	auipc	ra,0x0
 13c:	000080e7          	jalr	ra # 138 <.L4+0x98>
 140:	00050793          	mv	a5,a0
 144:	0407c463          	bltz	a5,18c <.L6>
 148:	00100793          	li	a5,1
 14c:	fcf42823          	sw	a5,-48(s0)
 150:	ff400793          	li	a5,-12
 154:	fef42423          	sw	a5,-24(s0)
 158:	fe842783          	lw	a5,-24(s0)
 15c:	00ff7f33          	and	t5,t5,a5
 160:	00ff6f33          	or	t5,t5,a5
 164:	fcf42823          	sw	a5,-48(s0)
 168:	00100793          	li	a5,1
 16c:	fcf42623          	sw	a5,-52(s0)
 170:	ff800793          	li	a5,-8
 174:	fef42423          	sw	a5,-24(s0)
 178:	fe842783          	lw	a5,-24(s0)
 17c:	00ff7f33          	and	t5,t5,a5
 180:	00ff6f33          	or	t5,t5,a5
 184:	fcf42623          	sw	a5,-52(s0)
 188:	03c0006f          	j	1c4 <.L9>

0000018c <.L6>:
 18c:	fc042823          	sw	zero,-48(s0)
 190:	ff400793          	li	a5,-12
 194:	fef42423          	sw	a5,-24(s0)
 198:	fe842783          	lw	a5,-24(s0)
 19c:	00ff7f33          	and	t5,t5,a5
 1a0:	00ff6f33          	or	t5,t5,a5
 1a4:	fcf42823          	sw	a5,-48(s0)
 1a8:	fc042623          	sw	zero,-52(s0)
 1ac:	ff800793          	li	a5,-8
 1b0:	fef42423          	sw	a5,-24(s0)
 1b4:	fe842783          	lw	a5,-24(s0)
 1b8:	00ff7f33          	and	t5,t5,a5
 1bc:	00ff6f33          	or	t5,t5,a5
 1c0:	fcf42623          	sw	a5,-52(s0)

000001c4 <.L9>:
 1c4:	e61ff06f          	j	24 <.L10>


```
# Unique Instructions
```
Number of different instructions: 17
List of unique instructions:
and
sw
bgeu
add
bltz
mv
auipc
bgtz
li
j
bne
mul
or
divu
jalr
lw
lui

```
### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
