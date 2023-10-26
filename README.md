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
//#include<stdio.h>
int division(int , int );
int main(){
	int trig;// bit 0
	int echo;//bit 1
	int buzzer;//bit 2
	int led;//bit 3
	int clk_freq = 100;
	int distance;
	int dummy=0xFFFFFFFE;
	unsigned int i;
	unsigned int duration;
	//for(int z=0;z<20;z++)
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
		//debug
		/*int output;
		asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 1\n\t"
			:"=r"(output)
			:
			:"x10"
			);  
		printf("trigger = %d\n",output);*/
		//debug
		for(i=0;i<100;i++);
			
			trig = 0;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(trig),"r"(dummy)
			:"x30"
			);
			//debug
			/*asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 1\n\t"
			:"=r"(output)
			:
			:"x10"
			);  
		        printf("trigger = %d\n",output);*/
		//debug
			i=0;
			
		while(echo!= 2 || i==200){
			
			i++;
			if(i==100 && z==3){ 
			echo = 2;
			
			}
			
			int mask = 0xFFFFFFFD;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(i),"r"(mask)
			:"x30"
			);
			
			asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
			:"=r"(echo)
			:
			:"x10"
			);
			
			//debug
			//printf("echo = %d\n",echo);
			//debug*/ 
			
		}
		if(echo==2 && z==6){
		echo = 0;
		//debug
		//printf("\necho pin is triggered\n");
		//debug
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
		
		duration=division(i,clk_freq);
		distance = duration*172;
		
		
		
		
		if(distance <= 172 && distance >= 0){
			buzzer = 4;
			dummy=0xFFFFFFF4;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(buzzer),"r"(dummy)
			:"x30"
			);
			
			led = 8;
			dummy=0xFFFFFFFC;
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
		//debug
		/*int led_buzzer;
		asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 12\n\t"
			:"=r"(led_buzzer)
			:
			:"x10"
			); 
		printf("buzzer and led = %d\n",led_buzzer);*/
		//debug
	
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
riscv64-unkown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o project.c
riscv64-unknown-elf-objdump -d -r out > project.txt
```

# Assembly Code
```


pruthvi:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02112e23          	sw	ra,60(sp)
   1005c:	02812c23          	sw	s0,56(sp)
   10060:	04010413          	addi	s0,sp,64
   10064:	06400793          	li	a5,100
   10068:	fef42023          	sw	a5,-32(s0)
   1006c:	ffe00793          	li	a5,-2
   10070:	fef42423          	sw	a5,-24(s0)
   10074:	00100793          	li	a5,1
   10078:	fcf42e23          	sw	a5,-36(s0)
   1007c:	fdc42783          	lw	a5,-36(s0)
   10080:	fe842703          	lw	a4,-24(s0)
   10084:	00ef7f33          	and	t5,t5,a4
   10088:	00ff6f33          	or	t5,t5,a5
   1008c:	fe042223          	sw	zero,-28(s0)
   10090:	0100006f          	j	100a0 <main+0x4c>
   10094:	fe442783          	lw	a5,-28(s0)
   10098:	00178793          	addi	a5,a5,1
   1009c:	fef42223          	sw	a5,-28(s0)
   100a0:	fe442703          	lw	a4,-28(s0)
   100a4:	06300793          	li	a5,99
   100a8:	fee7f6e3          	bgeu	a5,a4,10094 <main+0x40>
   100ac:	fc042e23          	sw	zero,-36(s0)
   100b0:	fdc42783          	lw	a5,-36(s0)
   100b4:	fe842703          	lw	a4,-24(s0)
   100b8:	00ef7f33          	and	t5,t5,a4
   100bc:	00ff6f33          	or	t5,t5,a5
   100c0:	fe042223          	sw	zero,-28(s0)
   100c4:	0480006f          	j	1010c <main+0xb8>
   100c8:	fe442783          	lw	a5,-28(s0)
   100cc:	00178793          	addi	a5,a5,1
   100d0:	fef42223          	sw	a5,-28(s0)
   100d4:	fe442703          	lw	a4,-28(s0)
   100d8:	06400793          	li	a5,100
   100dc:	00f71663          	bne	a4,a5,100e8 <main+0x94>
   100e0:	00200793          	li	a5,2
   100e4:	fef42623          	sw	a5,-20(s0)
   100e8:	ffd00793          	li	a5,-3
   100ec:	fcf42c23          	sw	a5,-40(s0)
   100f0:	fe442783          	lw	a5,-28(s0)
   100f4:	fd842703          	lw	a4,-40(s0)
   100f8:	00ef7f33          	and	t5,t5,a4
   100fc:	00ff6f33          	or	t5,t5,a5
   10100:	000f0513          	mv	a0,t5
   10104:	00257793          	andi	a5,a0,2
   10108:	fef42623          	sw	a5,-20(s0)
   1010c:	fec42703          	lw	a4,-20(s0)
   10110:	00200793          	li	a5,2
   10114:	faf71ae3          	bne	a4,a5,100c8 <main+0x74>
   10118:	fe442703          	lw	a4,-28(s0)
   1011c:	0c800793          	li	a5,200
   10120:	faf704e3          	beq	a4,a5,100c8 <main+0x74>
   10124:	fec42703          	lw	a4,-20(s0)
   10128:	00200793          	li	a5,2
   1012c:	f4f714e3          	bne	a4,a5,10074 <main+0x20>
   10130:	fe042623          	sw	zero,-20(s0)
   10134:	fc042a23          	sw	zero,-44(s0)
   10138:	ff400793          	li	a5,-12
   1013c:	fef42423          	sw	a5,-24(s0)
   10140:	fd442783          	lw	a5,-44(s0)
   10144:	fe842703          	lw	a4,-24(s0)
   10148:	00ef7f33          	and	t5,t5,a4
   1014c:	00ff6f33          	or	t5,t5,a5
   10150:	fc042823          	sw	zero,-48(s0)
   10154:	ff800793          	li	a5,-8
   10158:	fef42423          	sw	a5,-24(s0)
   1015c:	fd042783          	lw	a5,-48(s0)
   10160:	fe842703          	lw	a4,-24(s0)
   10164:	00ef7f33          	and	t5,t5,a4
   10168:	00ff6f33          	or	t5,t5,a5
   1016c:	fe442783          	lw	a5,-28(s0)
   10170:	fe042583          	lw	a1,-32(s0)
   10174:	00078513          	mv	a0,a5
   10178:	0c8000ef          	jal	ra,10240 <division>
   1017c:	00050793          	mv	a5,a0
   10180:	fcf42623          	sw	a5,-52(s0)
   10184:	fcc42703          	lw	a4,-52(s0)
   10188:	00070793          	mv	a5,a4
   1018c:	00179793          	slli	a5,a5,0x1
   10190:	00e787b3          	add	a5,a5,a4
   10194:	00279793          	slli	a5,a5,0x2
   10198:	40e787b3          	sub	a5,a5,a4
   1019c:	00279793          	slli	a5,a5,0x2
   101a0:	40e787b3          	sub	a5,a5,a4
   101a4:	00279793          	slli	a5,a5,0x2
   101a8:	fcf42423          	sw	a5,-56(s0)
   101ac:	fc842703          	lw	a4,-56(s0)
   101b0:	0ac00793          	li	a5,172
   101b4:	04e7c863          	blt	a5,a4,10204 <main+0x1b0>
   101b8:	fc842783          	lw	a5,-56(s0)
   101bc:	0407c463          	bltz	a5,10204 <main+0x1b0>
   101c0:	00400793          	li	a5,4
   101c4:	fcf42a23          	sw	a5,-44(s0)
   101c8:	ff400793          	li	a5,-12
   101cc:	fef42423          	sw	a5,-24(s0)
   101d0:	fd442783          	lw	a5,-44(s0)
   101d4:	fe842703          	lw	a4,-24(s0)
   101d8:	00ef7f33          	and	t5,t5,a4
   101dc:	00ff6f33          	or	t5,t5,a5
   101e0:	00800793          	li	a5,8
   101e4:	fcf42823          	sw	a5,-48(s0)
   101e8:	ffc00793          	li	a5,-4
   101ec:	fef42423          	sw	a5,-24(s0)
   101f0:	fd042783          	lw	a5,-48(s0)
   101f4:	fe842703          	lw	a4,-24(s0)
   101f8:	00ef7f33          	and	t5,t5,a4
   101fc:	00ff6f33          	or	t5,t5,a5
   10200:	03c0006f          	j	1023c <main+0x1e8>
   10204:	fc042a23          	sw	zero,-44(s0)
   10208:	ff400793          	li	a5,-12
   1020c:	fef42423          	sw	a5,-24(s0)
   10210:	fd442783          	lw	a5,-44(s0)
   10214:	fe842703          	lw	a4,-24(s0)
   10218:	00ef7f33          	and	t5,t5,a4
   1021c:	00ff6f33          	or	t5,t5,a5
   10220:	fc042823          	sw	zero,-48(s0)
   10224:	ff800793          	li	a5,-8
   10228:	fef42423          	sw	a5,-24(s0)
   1022c:	fd042783          	lw	a5,-48(s0)
   10230:	fe842703          	lw	a4,-24(s0)
   10234:	00ef7f33          	and	t5,t5,a4
   10238:	00ff6f33          	or	t5,t5,a5
   1023c:	e39ff06f          	j	10074 <main+0x20>

00010240 <division>:
   10240:	fd010113          	addi	sp,sp,-48
   10244:	02812623          	sw	s0,44(sp)
   10248:	03010413          	addi	s0,sp,48
   1024c:	fca42e23          	sw	a0,-36(s0)
   10250:	fcb42c23          	sw	a1,-40(s0)
   10254:	fe042623          	sw	zero,-20(s0)
   10258:	0200006f          	j	10278 <division+0x38>
   1025c:	fdc42703          	lw	a4,-36(s0)
   10260:	fd842783          	lw	a5,-40(s0)
   10264:	40f707b3          	sub	a5,a4,a5
   10268:	fcf42e23          	sw	a5,-36(s0)
   1026c:	fec42783          	lw	a5,-20(s0)
   10270:	00178793          	addi	a5,a5,1
   10274:	fef42623          	sw	a5,-20(s0)
   10278:	fdc42703          	lw	a4,-36(s0)
   1027c:	fd842783          	lw	a5,-40(s0)
   10280:	fcf75ee3          	bge	a4,a5,1025c <division+0x1c>
   10284:	fec42783          	lw	a5,-20(s0)
   10288:	00078513          	mv	a0,a5
   1028c:	02c12403          	lw	s0,44(sp)
   10290:	03010113          	addi	sp,sp,48
   10294:	00008067          	ret


```
# Unique Instructions
```
Number of different instructions: 20
List of unique instructions:
mv
li
or
bge
lw
slli
beq
bne
bgeu
sw
bltz
andi
add
j
blt
addi
ret
and
jal
sub
```

# Spike simulator output 

![image](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/ece0df0d-a023-4ec0-9201-070af80693e4)

![spike-result](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/b9979d17-5820-4d3e-9ad9-27453212180d)

# Functional Simualation

By performing functional simulation we can verify our design through the verilog code which is processor.v and testbench.v. Here one trigger pin is there , input_wire is the echo pin and
output_wires is led and buzzer. So as shown in the gtkwave diagram when trigger is made zero and echo pin(input_wire) is 1 , buzzer and led (output_wires) is 11. There is also shown the 
clk, write_done and ID_instruction in the gtkwave diagram below.

![11](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/efc3d21a-7553-403b-824c-fba6b38e28ef)


# Explaination

Here what's happening is first trigger is made 1 for some time (using for loop) and then turned off the trigger pin and when echo pin receives the waves "echo pin is triggered" 
and thus buzzer and led will be turn , which is 12 = 1100 so two msb are led and buzzer which is turned on in above case.

### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
