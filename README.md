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

# Assembly Code
```

output.o:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	fc010113          	add	sp,sp,-64
   10078:	02812e23          	sw	s0,60(sp)
   1007c:	04010413          	add	s0,sp,64
   10080:	009897b7          	lui	a5,0x989
   10084:	68078793          	add	a5,a5,1664 # 989680 <__global_pointer$+0x977c78>
   10088:	fef42023          	sw	a5,-32(s0)
   1008c:	ffe00793          	li	a5,-2
   10090:	fef42423          	sw	a5,-24(s0)
   10094:	00100793          	li	a5,1
   10098:	fcf42e23          	sw	a5,-36(s0)
   1009c:	fdc42783          	lw	a5,-36(s0)
   100a0:	fe842703          	lw	a4,-24(s0)
   100a4:	00ef7f33          	and	t5,t5,a4
   100a8:	00ff6f33          	or	t5,t5,a5
   100ac:	fe042223          	sw	zero,-28(s0)
   100b0:	0100006f          	j	100c0 <main+0x4c>
   100b4:	fe442783          	lw	a5,-28(s0)
   100b8:	00178793          	add	a5,a5,1
   100bc:	fef42223          	sw	a5,-28(s0)
   100c0:	fe442703          	lw	a4,-28(s0)
   100c4:	009897b7          	lui	a5,0x989
   100c8:	67f78793          	add	a5,a5,1663 # 98967f <__global_pointer$+0x977c77>
   100cc:	fee7f4e3          	bgeu	a5,a4,100b4 <main+0x40>
   100d0:	fc042e23          	sw	zero,-36(s0)
   100d4:	fdc42783          	lw	a5,-36(s0)
   100d8:	fe842703          	lw	a4,-24(s0)
   100dc:	00ef7f33          	and	t5,t5,a4
   100e0:	00ff6f33          	or	t5,t5,a5
   100e4:	fe042223          	sw	zero,-28(s0)
   100e8:	000f0513          	mv	a0,t5
   100ec:	00257793          	and	a5,a0,2
   100f0:	fef42623          	sw	a5,-20(s0)
   100f4:	01c0006f          	j	10110 <main+0x9c>
   100f8:	fe442783          	lw	a5,-28(s0)
   100fc:	00178793          	add	a5,a5,1
   10100:	fef42223          	sw	a5,-28(s0)
   10104:	000f0513          	mv	a0,t5
   10108:	00257793          	and	a5,a0,2
   1010c:	fef42623          	sw	a5,-20(s0)
   10110:	fec42703          	lw	a4,-20(s0)
   10114:	00100793          	li	a5,1
   10118:	fef710e3          	bne	a4,a5,100f8 <main+0x84>
   1011c:	fe042783          	lw	a5,-32(s0)
   10120:	fe442703          	lw	a4,-28(s0)
   10124:	02f757b3          	divu	a5,a4,a5
   10128:	fcf42c23          	sw	a5,-40(s0)
   1012c:	fd842703          	lw	a4,-40(s0)
   10130:	0ac00793          	li	a5,172
   10134:	02f707b3          	mul	a5,a4,a5
   10138:	fcf42a23          	sw	a5,-44(s0)
   1013c:	fc042823          	sw	zero,-48(s0)
   10140:	ff400793          	li	a5,-12
   10144:	fef42423          	sw	a5,-24(s0)
   10148:	fd042783          	lw	a5,-48(s0)
   1014c:	fe842703          	lw	a4,-24(s0)
   10150:	00ef7f33          	and	t5,t5,a4
   10154:	00ff6f33          	or	t5,t5,a5
   10158:	fc042623          	sw	zero,-52(s0)
   1015c:	ff800793          	li	a5,-8
   10160:	fef42423          	sw	a5,-24(s0)
   10164:	fcc42783          	lw	a5,-52(s0)
   10168:	fe842703          	lw	a4,-24(s0)
   1016c:	00ef7f33          	and	t5,t5,a4
   10170:	00ff6f33          	or	t5,t5,a5
   10174:	fd442703          	lw	a4,-44(s0)
   10178:	00100793          	li	a5,1
   1017c:	04e7c863          	blt	a5,a4,101cc <main+0x158>
   10180:	fd442783          	lw	a5,-44(s0)
   10184:	0407c463          	bltz	a5,101cc <main+0x158>
   10188:	00100793          	li	a5,1
   1018c:	fcf42823          	sw	a5,-48(s0)
   10190:	ff400793          	li	a5,-12
   10194:	fef42423          	sw	a5,-24(s0)
   10198:	fd042783          	lw	a5,-48(s0)
   1019c:	fe842703          	lw	a4,-24(s0)
   101a0:	00ef7f33          	and	t5,t5,a4
   101a4:	00ff6f33          	or	t5,t5,a5
   101a8:	00100793          	li	a5,1
   101ac:	fcf42623          	sw	a5,-52(s0)
   101b0:	ff800793          	li	a5,-8
   101b4:	fef42423          	sw	a5,-24(s0)
   101b8:	fcc42783          	lw	a5,-52(s0)
   101bc:	fe842703          	lw	a4,-24(s0)
   101c0:	00ef7f33          	and	t5,t5,a4
   101c4:	00ff6f33          	or	t5,t5,a5
   101c8:	03c0006f          	j	10204 <main+0x190>
   101cc:	fc042823          	sw	zero,-48(s0)
   101d0:	ff400793          	li	a5,-12
   101d4:	fef42423          	sw	a5,-24(s0)
   101d8:	fd042783          	lw	a5,-48(s0)
   101dc:	fe842703          	lw	a4,-24(s0)
   101e0:	00ef7f33          	and	t5,t5,a4
   101e4:	00ff6f33          	or	t5,t5,a5
   101e8:	fc042623          	sw	zero,-52(s0)
   101ec:	ff800793          	li	a5,-8
   101f0:	fef42423          	sw	a5,-24(s0)
   101f4:	fcc42783          	lw	a5,-52(s0)
   101f8:	fe842703          	lw	a4,-24(s0)
   101fc:	00ef7f33          	and	t5,t5,a4
   10200:	00ff6f33          	or	t5,t5,a5
   10204:	e91ff06f          	j	10094 <main+0x20>

```
# Unique Instructions
```
Number of different instructions: 15
List of unique instructions:
or
and
mv
bne
mul
add
j
blt
divu
sw
lui
bltz
li
bgeu
lw
```
### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
