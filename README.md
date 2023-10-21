# RISCV_Social_Distance_Detection
![image](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/bfc1cd72-51fa-48c9-bab9-b71fea6f1ddb)

# Aim
The aim of this project is to design and create a versatile social distance detection system controlled by a RISC-V. This system will be helpful to measure social distance. User will be alarmed when distance will be less than 2m and greater than 0. 
# Working
In this project using RISC-V which is connected to one ultrasonic sensor, one buzzer and one led. First ultrasonic sensor will start to detect the users/objects.  Ultrasonic sensors measure distance by sending and receiving the ultrasonic wave. Using the trigger pin it sends the the transmitted ultrasonic wave travels through the air and is reflected by hitting the Object/users.We know that the speed of sound in air is nearly 344 m/s, so using the speed, time and distance formula we can find the distance using duration. If user is nearer than 2 meters then buzzer will be turned on and led will also turn on.

# Block Diagram
![diagram](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/bea6173f-0e38-4385-bc36-c115a870731f)

# Testing 

1. Open a terminal or command prompt.
2. Change your current working directory to the location where you have the sample.c file.
3. Create a custom function that implements the desired functionality.
4. Use the GCC (GNU Compiler Collection) to compile the code, and then proceed to validate the program's output.

    Below shown the representation of social distance detection logic.

![Untitled (1)](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/31ec34f9-c06f-4393-847f-ff6b24f52ed7)




# C Program
```
int division(int , int );
int main(){
	int trig;// bit 0
	int echo;//bit 1
	int buzzer;//bit 2
	int led;//bit 3
	int clk_freq = 10000000;
	int distance;
	int dummy=0xFFFFFFFE;
	unsigned int i;
	unsigned int duration;
	while(1)
	{
		trig = 1;
		asm volatile(
		"and x30, x30, %1\n\t"
    		"or x30, x30, %0\n\t"
    		:
		:"r"(trig),"r"(dummy)
		:"x30"
		);
		for(i=0;i<10000000;i++);
			
			trig = 0;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(trig),"r"(dummy)
			:"x30"
			);
			i=0;
			
			asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
			:"=r"(echo)
			:
			:"x10"
			);         
			
		while(echo!= 1){
			i++;
			asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
			:"=r"(echo)
			:
			:"x10"
			);
		}
		//duration = i/clk_freq;
		duration=division(i,clk_freq);
		distance = duration*172;
		
		buzzer = 0;
		dummy=0xFFFFFFF4;
		asm volatile(
		"and x30, x30, %1\n\t"
    		"or x30, x30, %0\n\t"
    		:
		:"r"(buzzer),"r"(dummy)
		:"x30"
		);
		
		led = 0;
		dummy=0xFFFFFFF8;
		asm volatile(
		"and x30, x30, %1\n\t"
    		"or x30, x30, %0\n\t"
    		:
		:"r"(led),"r"(dummy)
		:"x30"
		);
		
		
		if(distance <= 1 && distance >= 0){
			buzzer = 1;
			dummy=0xFFFFFFF4;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(buzzer),"r"(dummy)
			:"x30"
			);
			
			led = 1;
			dummy=0xFFFFFFF8;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(led),"r"(dummy)
			:"x30"
			);
		}
		else{
			buzzer = 0;
			dummy=0xFFFFFFF4;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(buzzer),"r"(dummy)
			:"x30"
			);
			
			led = 0;
			dummy=0xFFFFFFF8;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(led),"r"(dummy)
			:"x30"
			);
		}
	}
	return 0;
}
int division(int dividend, int divisor) {
    int quotient = 0;
    
   
    while (dividend >= divisor) {
        dividend -= divisor;
        quotient++;
    }

    return quotient;
}

```

Now using below commands we can compile to assembly 
```
riscv32-unkown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o project.c
riscv32-unknown-elf-objdump -d -r out > project.txt
```

# Assembly Code
```

a.out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02112e23          	sw	ra,60(sp)
   1005c:	02812c23          	sw	s0,56(sp)
   10060:	04010413          	addi	s0,sp,64
   10064:	009897b7          	lui	a5,0x989
   10068:	68078793          	addi	a5,a5,1664 # 989680 <__global_pointer$+0x977c1c>
   1006c:	fef42023          	sw	a5,-32(s0)
   10070:	ffe00793          	li	a5,-2
   10074:	fef42423          	sw	a5,-24(s0)
   10078:	00100793          	li	a5,1
   1007c:	fcf42e23          	sw	a5,-36(s0)
   10080:	fdc42783          	lw	a5,-36(s0)
   10084:	fe842703          	lw	a4,-24(s0)
   10088:	00ef7f33          	and	t5,t5,a4
   1008c:	00ff6f33          	or	t5,t5,a5
   10090:	fe042223          	sw	zero,-28(s0)
   10094:	0100006f          	j	100a4 <main+0x50>
   10098:	fe442783          	lw	a5,-28(s0)
   1009c:	00178793          	addi	a5,a5,1
   100a0:	fef42223          	sw	a5,-28(s0)
   100a4:	fe442703          	lw	a4,-28(s0)
   100a8:	009897b7          	lui	a5,0x989
   100ac:	67f78793          	addi	a5,a5,1663 # 98967f <__global_pointer$+0x977c1b>
   100b0:	fee7f4e3          	bgeu	a5,a4,10098 <main+0x44>
   100b4:	fc042e23          	sw	zero,-36(s0)
   100b8:	fdc42783          	lw	a5,-36(s0)
   100bc:	fe842703          	lw	a4,-24(s0)
   100c0:	00ef7f33          	and	t5,t5,a4
   100c4:	00ff6f33          	or	t5,t5,a5
   100c8:	fe042223          	sw	zero,-28(s0)
   100cc:	000f0513          	mv	a0,t5
   100d0:	00257793          	andi	a5,a0,2
   100d4:	fef42623          	sw	a5,-20(s0)
   100d8:	01c0006f          	j	100f4 <main+0xa0>
   100dc:	fe442783          	lw	a5,-28(s0)
   100e0:	00178793          	addi	a5,a5,1
   100e4:	fef42223          	sw	a5,-28(s0)
   100e8:	000f0513          	mv	a0,t5
   100ec:	00257793          	andi	a5,a0,2
   100f0:	fef42623          	sw	a5,-20(s0)
   100f4:	fec42703          	lw	a4,-20(s0)
   100f8:	00100793          	li	a5,1
   100fc:	fef710e3          	bne	a4,a5,100dc <main+0x88>
   10100:	fe442783          	lw	a5,-28(s0)
   10104:	fe042583          	lw	a1,-32(s0)
   10108:	00078513          	mv	a0,a5
   1010c:	100000ef          	jal	ra,1020c <division>
   10110:	00050793          	mv	a5,a0
   10114:	fcf42c23          	sw	a5,-40(s0)
   10118:	fd842703          	lw	a4,-40(s0)
   1011c:	00070793          	mv	a5,a4
   10120:	00179793          	slli	a5,a5,0x1
   10124:	00e787b3          	add	a5,a5,a4
   10128:	00279793          	slli	a5,a5,0x2
   1012c:	40e787b3          	sub	a5,a5,a4
   10130:	00279793          	slli	a5,a5,0x2
   10134:	40e787b3          	sub	a5,a5,a4
   10138:	00279793          	slli	a5,a5,0x2
   1013c:	fcf42a23          	sw	a5,-44(s0)
   10140:	fc042823          	sw	zero,-48(s0)
   10144:	ff400793          	li	a5,-12
   10148:	fef42423          	sw	a5,-24(s0)
   1014c:	fd042783          	lw	a5,-48(s0)
   10150:	fe842703          	lw	a4,-24(s0)
   10154:	00ef7f33          	and	t5,t5,a4
   10158:	00ff6f33          	or	t5,t5,a5
   1015c:	fc042623          	sw	zero,-52(s0)
   10160:	ff800793          	li	a5,-8
   10164:	fef42423          	sw	a5,-24(s0)
   10168:	fcc42783          	lw	a5,-52(s0)
   1016c:	fe842703          	lw	a4,-24(s0)
   10170:	00ef7f33          	and	t5,t5,a4
   10174:	00ff6f33          	or	t5,t5,a5
   10178:	fd442703          	lw	a4,-44(s0)
   1017c:	00100793          	li	a5,1
   10180:	04e7c863          	blt	a5,a4,101d0 <main+0x17c>
   10184:	fd442783          	lw	a5,-44(s0)
   10188:	0407c463          	bltz	a5,101d0 <main+0x17c>
   1018c:	00100793          	li	a5,1
   10190:	fcf42823          	sw	a5,-48(s0)
   10194:	ff400793          	li	a5,-12
   10198:	fef42423          	sw	a5,-24(s0)
   1019c:	fd042783          	lw	a5,-48(s0)
   101a0:	fe842703          	lw	a4,-24(s0)
   101a4:	00ef7f33          	and	t5,t5,a4
   101a8:	00ff6f33          	or	t5,t5,a5
   101ac:	00100793          	li	a5,1
   101b0:	fcf42623          	sw	a5,-52(s0)
   101b4:	ff800793          	li	a5,-8
   101b8:	fef42423          	sw	a5,-24(s0)
   101bc:	fcc42783          	lw	a5,-52(s0)
   101c0:	fe842703          	lw	a4,-24(s0)
   101c4:	00ef7f33          	and	t5,t5,a4
   101c8:	00ff6f33          	or	t5,t5,a5
   101cc:	03c0006f          	j	10208 <main+0x1b4>
   101d0:	fc042823          	sw	zero,-48(s0)
   101d4:	ff400793          	li	a5,-12
   101d8:	fef42423          	sw	a5,-24(s0)
   101dc:	fd042783          	lw	a5,-48(s0)
   101e0:	fe842703          	lw	a4,-24(s0)
   101e4:	00ef7f33          	and	t5,t5,a4
   101e8:	00ff6f33          	or	t5,t5,a5
   101ec:	fc042623          	sw	zero,-52(s0)
   101f0:	ff800793          	li	a5,-8
   101f4:	fef42423          	sw	a5,-24(s0)
   101f8:	fcc42783          	lw	a5,-52(s0)
   101fc:	fe842703          	lw	a4,-24(s0)
   10200:	00ef7f33          	and	t5,t5,a4
   10204:	00ff6f33          	or	t5,t5,a5
   10208:	e71ff06f          	j	10078 <main+0x24>

0001020c <division>:
   1020c:	fd010113          	addi	sp,sp,-48
   10210:	02812623          	sw	s0,44(sp)
   10214:	03010413          	addi	s0,sp,48
   10218:	fca42e23          	sw	a0,-36(s0)
   1021c:	fcb42c23          	sw	a1,-40(s0)
   10220:	fe042623          	sw	zero,-20(s0)
   10224:	0200006f          	j	10244 <division+0x38>
   10228:	fdc42703          	lw	a4,-36(s0)
   1022c:	fd842783          	lw	a5,-40(s0)
   10230:	40f707b3          	sub	a5,a4,a5
   10234:	fcf42e23          	sw	a5,-36(s0)
   10238:	fec42783          	lw	a5,-20(s0)
   1023c:	00178793          	addi	a5,a5,1
   10240:	fef42623          	sw	a5,-20(s0)
   10244:	fdc42703          	lw	a4,-36(s0)
   10248:	fd842783          	lw	a5,-40(s0)
   1024c:	fcf75ee3          	bge	a4,a5,10228 <division+0x1c>
   10250:	fec42783          	lw	a5,-20(s0)
   10254:	00078513          	mv	a0,a5
   10258:	02c12403          	lw	s0,44(sp)
   1025c:	03010113          	addi	sp,sp,48
   10260:	00008067          	ret

```
# Unique Instructions
```
Number of different instructions: 20
List of unique instructions:
jal
mv
bne
sub
bgeu
and
ret
slli
li
j
bltz
lw
lui
andi
bge
add
blt
addi
or
sw
```
### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
