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
		duration = i/clk_freq;
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

```

Now using below commands we can compile to assembly 
```
riscv32-unkown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o project.c
riscv32-unknown-elf-objdump -d -r out > project.txt
```

# Assembly Code
```

output.o:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	fc010113          	add	sp,sp,-64
   10078:	02112e23          	sw	ra,60(sp)
   1007c:	02812c23          	sw	s0,56(sp)
   10080:	04010413          	add	s0,sp,64
   10084:	009897b7          	lui	a5,0x989
   10088:	68078793          	add	a5,a5,1664 # 989680 <__global_pointer$+0x977ba0>
   1008c:	fef42023          	sw	a5,-32(s0)
   10090:	ffe00793          	li	a5,-2
   10094:	fef42423          	sw	a5,-24(s0)
   10098:	00100793          	li	a5,1
   1009c:	fcf42e23          	sw	a5,-36(s0)
   100a0:	fdc42783          	lw	a5,-36(s0)
   100a4:	fe842703          	lw	a4,-24(s0)
   100a8:	00ef7f33          	and	t5,t5,a4
   100ac:	00ff6f33          	or	t5,t5,a5
   100b0:	fe042223          	sw	zero,-28(s0)
   100b4:	0100006f          	j	100c4 <main+0x50>
   100b8:	fe442783          	lw	a5,-28(s0)
   100bc:	00178793          	add	a5,a5,1
   100c0:	fef42223          	sw	a5,-28(s0)
   100c4:	fe442703          	lw	a4,-28(s0)
   100c8:	009897b7          	lui	a5,0x989
   100cc:	67f78793          	add	a5,a5,1663 # 98967f <__global_pointer$+0x977b9f>
   100d0:	fee7f4e3          	bgeu	a5,a4,100b8 <main+0x44>
   100d4:	fc042e23          	sw	zero,-36(s0)
   100d8:	fdc42783          	lw	a5,-36(s0)
   100dc:	fe842703          	lw	a4,-24(s0)
   100e0:	00ef7f33          	and	t5,t5,a4
   100e4:	00ff6f33          	or	t5,t5,a5
   100e8:	fe042223          	sw	zero,-28(s0)
   100ec:	000f0513          	mv	a0,t5
   100f0:	00257793          	and	a5,a0,2
   100f4:	fef42623          	sw	a5,-20(s0)
   100f8:	01c0006f          	j	10114 <main+0xa0>
   100fc:	fe442783          	lw	a5,-28(s0)
   10100:	00178793          	add	a5,a5,1
   10104:	fef42223          	sw	a5,-28(s0)
   10108:	000f0513          	mv	a0,t5
   1010c:	00257793          	and	a5,a0,2
   10110:	fef42623          	sw	a5,-20(s0)
   10114:	fec42703          	lw	a4,-20(s0)
   10118:	00100793          	li	a5,1
   1011c:	fef710e3          	bne	a4,a5,100fc <main+0x88>
   10120:	fe042783          	lw	a5,-32(s0)
   10124:	00078593          	mv	a1,a5
   10128:	fe442503          	lw	a0,-28(s0)
   1012c:	108000ef          	jal	10234 <__hidden___udivsi3>
   10130:	00050793          	mv	a5,a0
   10134:	fcf42c23          	sw	a5,-40(s0)
   10138:	fd842703          	lw	a4,-40(s0)
   1013c:	00070793          	mv	a5,a4
   10140:	00179793          	sll	a5,a5,0x1
   10144:	00e787b3          	add	a5,a5,a4
   10148:	00279793          	sll	a5,a5,0x2
   1014c:	40e787b3          	sub	a5,a5,a4
   10150:	00279793          	sll	a5,a5,0x2
   10154:	40e787b3          	sub	a5,a5,a4
   10158:	00279793          	sll	a5,a5,0x2
   1015c:	fcf42a23          	sw	a5,-44(s0)
   10160:	fc042823          	sw	zero,-48(s0)
   10164:	ff400793          	li	a5,-12
   10168:	fef42423          	sw	a5,-24(s0)
   1016c:	fd042783          	lw	a5,-48(s0)
   10170:	fe842703          	lw	a4,-24(s0)
   10174:	00ef7f33          	and	t5,t5,a4
   10178:	00ff6f33          	or	t5,t5,a5
   1017c:	fc042623          	sw	zero,-52(s0)
   10180:	ff800793          	li	a5,-8
   10184:	fef42423          	sw	a5,-24(s0)
   10188:	fcc42783          	lw	a5,-52(s0)
   1018c:	fe842703          	lw	a4,-24(s0)
   10190:	00ef7f33          	and	t5,t5,a4
   10194:	00ff6f33          	or	t5,t5,a5
   10198:	fd442703          	lw	a4,-44(s0)
   1019c:	00100793          	li	a5,1
   101a0:	04e7c863          	blt	a5,a4,101f0 <main+0x17c>
   101a4:	fd442783          	lw	a5,-44(s0)
   101a8:	0407c463          	bltz	a5,101f0 <main+0x17c>
   101ac:	00100793          	li	a5,1
   101b0:	fcf42823          	sw	a5,-48(s0)
   101b4:	ff400793          	li	a5,-12
   101b8:	fef42423          	sw	a5,-24(s0)
   101bc:	fd042783          	lw	a5,-48(s0)
   101c0:	fe842703          	lw	a4,-24(s0)
   101c4:	00ef7f33          	and	t5,t5,a4
   101c8:	00ff6f33          	or	t5,t5,a5
   101cc:	00100793          	li	a5,1
   101d0:	fcf42623          	sw	a5,-52(s0)
   101d4:	ff800793          	li	a5,-8
   101d8:	fef42423          	sw	a5,-24(s0)
   101dc:	fcc42783          	lw	a5,-52(s0)
   101e0:	fe842703          	lw	a4,-24(s0)
   101e4:	00ef7f33          	and	t5,t5,a4
   101e8:	00ff6f33          	or	t5,t5,a5
   101ec:	03c0006f          	j	10228 <main+0x1b4>
   101f0:	fc042823          	sw	zero,-48(s0)
   101f4:	ff400793          	li	a5,-12
   101f8:	fef42423          	sw	a5,-24(s0)
   101fc:	fd042783          	lw	a5,-48(s0)
   10200:	fe842703          	lw	a4,-24(s0)
   10204:	00ef7f33          	and	t5,t5,a4
   10208:	00ff6f33          	or	t5,t5,a5
   1020c:	fc042623          	sw	zero,-52(s0)
   10210:	ff800793          	li	a5,-8
   10214:	fef42423          	sw	a5,-24(s0)
   10218:	fcc42783          	lw	a5,-52(s0)
   1021c:	fe842703          	lw	a4,-24(s0)
   10220:	00ef7f33          	and	t5,t5,a4
   10224:	00ff6f33          	or	t5,t5,a5
   10228:	e71ff06f          	j	10098 <main+0x24>

0001022c <__divsi3>:
   1022c:	06054063          	bltz	a0,1028c <__umodsi3+0x10>
   10230:	0605c663          	bltz	a1,1029c <__umodsi3+0x20>

00010234 <__hidden___udivsi3>:
   10234:	00058613          	mv	a2,a1
   10238:	00050593          	mv	a1,a0
   1023c:	fff00513          	li	a0,-1
   10240:	02060c63          	beqz	a2,10278 <__hidden___udivsi3+0x44>
   10244:	00100693          	li	a3,1
   10248:	00b67a63          	bgeu	a2,a1,1025c <__hidden___udivsi3+0x28>
   1024c:	00c05863          	blez	a2,1025c <__hidden___udivsi3+0x28>
   10250:	00161613          	sll	a2,a2,0x1
   10254:	00169693          	sll	a3,a3,0x1
   10258:	feb66ae3          	bltu	a2,a1,1024c <__hidden___udivsi3+0x18>
   1025c:	00000513          	li	a0,0
   10260:	00c5e663          	bltu	a1,a2,1026c <__hidden___udivsi3+0x38>
   10264:	40c585b3          	sub	a1,a1,a2
   10268:	00d56533          	or	a0,a0,a3
   1026c:	0016d693          	srl	a3,a3,0x1
   10270:	00165613          	srl	a2,a2,0x1
   10274:	fe0696e3          	bnez	a3,10260 <__hidden___udivsi3+0x2c>
   10278:	00008067          	ret

0001027c <__umodsi3>:
   1027c:	00008293          	mv	t0,ra
   10280:	fb5ff0ef          	jal	10234 <__hidden___udivsi3>
   10284:	00058513          	mv	a0,a1
   10288:	00028067          	jr	t0
   1028c:	40a00533          	neg	a0,a0
   10290:	00b04863          	bgtz	a1,102a0 <__umodsi3+0x24>
   10294:	40b005b3          	neg	a1,a1
   10298:	f9dff06f          	j	10234 <__hidden___udivsi3>
   1029c:	40b005b3          	neg	a1,a1
   102a0:	00008293          	mv	t0,ra
   102a4:	f91ff0ef          	jal	10234 <__hidden___udivsi3>
   102a8:	40a00533          	neg	a0,a0
   102ac:	00028067          	jr	t0

000102b0 <__modsi3>:
   102b0:	00008293          	mv	t0,ra
   102b4:	0005ca63          	bltz	a1,102c8 <__modsi3+0x18>
   102b8:	00054c63          	bltz	a0,102d0 <__modsi3+0x20>
   102bc:	f79ff0ef          	jal	10234 <__hidden___udivsi3>
   102c0:	00058513          	mv	a0,a1
   102c4:	00028067          	jr	t0
   102c8:	40b005b3          	neg	a1,a1
   102cc:	fe0558e3          	bgez	a0,102bc <__modsi3+0xc>
   102d0:	40a00533          	neg	a0,a0
   102d4:	f61ff0ef          	jal	10234 <__hidden___udivsi3>
   102d8:	40b00533          	neg	a0,a1
   102dc:	00028067          	jr	t0


```
# Unique Instructions
```
Number of different instructions: 26
List of unique instructions:
srl
sw
beqz
sub
and
bgtz
blt
blez
bne
j
bnez
bgeu
neg
sll
bltz
add
li
or
lui
jr
mv
bgez
ret
lw
bltu
jal
```
### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
