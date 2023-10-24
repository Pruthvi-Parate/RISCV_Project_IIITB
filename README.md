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
	int clk_freq = 100;
	int distance;
	int dummy=0xFFFFFFFE;
	unsigned int i;
	unsigned int duration;
	//for(int z=0;z<10;z++)
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
			//debug
			//give echo input here
			/*int input = 0;
			if(z==5){ 
			input = 2;
			}
			int mask = 0xFFFFFFFD;
			asm volatile(
			"and x30, x30, %1\n\t"
			"or x30, x30, %0\n\t"
			:
			:"r"(input),"r"(mask)
			:"x30"
			);*/
			//debug
			asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
			:"=r"(echo)
			:
			:"x10"
			);         
			//debug
			
			//printf("echo = %d\n",echo);
			//debug
		if(echo!= 2){
			i++;
			/*asm volatile(
			"addi x10, x30, 0\n\t"
			"and %0, x10, 2\n\t"
			:"=r"(echo)
			:
			:"x10"
			);*/
		}
		else {
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
	} }
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


b.out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fc010113          	addi	sp,sp,-64
   10058:	02112e23          	sw	ra,60(sp)
   1005c:	02812c23          	sw	s0,56(sp)
   10060:	04010413          	addi	s0,sp,64
   10064:	06400793          	li	a5,100
   10068:	fef42223          	sw	a5,-28(s0)
   1006c:	ffe00793          	li	a5,-2
   10070:	fef42623          	sw	a5,-20(s0)
   10074:	00100793          	li	a5,1
   10078:	fef42023          	sw	a5,-32(s0)
   1007c:	fe042783          	lw	a5,-32(s0)
   10080:	fec42703          	lw	a4,-20(s0)
   10084:	00ef7f33          	and	t5,t5,a4
   10088:	00ff6f33          	or	t5,t5,a5
   1008c:	fe042423          	sw	zero,-24(s0)
   10090:	0100006f          	j	100a0 <main+0x4c>
   10094:	fe842783          	lw	a5,-24(s0)
   10098:	00178793          	addi	a5,a5,1
   1009c:	fef42423          	sw	a5,-24(s0)
   100a0:	fe842703          	lw	a4,-24(s0)
   100a4:	06300793          	li	a5,99
   100a8:	fee7f6e3          	bgeu	a5,a4,10094 <main+0x40>
   100ac:	fe042023          	sw	zero,-32(s0)
   100b0:	fe042783          	lw	a5,-32(s0)
   100b4:	fec42703          	lw	a4,-20(s0)
   100b8:	00ef7f33          	and	t5,t5,a4
   100bc:	00ff6f33          	or	t5,t5,a5
   100c0:	fe042423          	sw	zero,-24(s0)
   100c4:	000f0513          	mv	a0,t5
   100c8:	00257793          	andi	a5,a0,2
   100cc:	fcf42e23          	sw	a5,-36(s0)
   100d0:	fdc42703          	lw	a4,-36(s0)
   100d4:	00200793          	li	a5,2
   100d8:	02f70063          	beq	a4,a5,100f8 <main+0xa4>
   100dc:	fe842783          	lw	a5,-24(s0)
   100e0:	00178793          	addi	a5,a5,1
   100e4:	fef42423          	sw	a5,-24(s0)
   100e8:	000f0513          	mv	a0,t5
   100ec:	00257793          	andi	a5,a0,2
   100f0:	fcf42e23          	sw	a5,-36(s0)
   100f4:	f81ff06f          	j	10074 <main+0x20>
   100f8:	fc042c23          	sw	zero,-40(s0)
   100fc:	ff400793          	li	a5,-12
   10100:	fef42623          	sw	a5,-20(s0)
   10104:	fd842783          	lw	a5,-40(s0)
   10108:	fec42703          	lw	a4,-20(s0)
   1010c:	00ef7f33          	and	t5,t5,a4
   10110:	00ff6f33          	or	t5,t5,a5
   10114:	fc042a23          	sw	zero,-44(s0)
   10118:	ff800793          	li	a5,-8
   1011c:	fef42623          	sw	a5,-20(s0)
   10120:	fd442783          	lw	a5,-44(s0)
   10124:	fec42703          	lw	a4,-20(s0)
   10128:	00ef7f33          	and	t5,t5,a4
   1012c:	00ff6f33          	or	t5,t5,a5
   10130:	fe842783          	lw	a5,-24(s0)
   10134:	fe442583          	lw	a1,-28(s0)
   10138:	00078513          	mv	a0,a5
   1013c:	0c8000ef          	jal	ra,10204 <division>
   10140:	00050793          	mv	a5,a0
   10144:	fcf42823          	sw	a5,-48(s0)
   10148:	fd042703          	lw	a4,-48(s0)
   1014c:	00070793          	mv	a5,a4
   10150:	00179793          	slli	a5,a5,0x1
   10154:	00e787b3          	add	a5,a5,a4
   10158:	00279793          	slli	a5,a5,0x2
   1015c:	40e787b3          	sub	a5,a5,a4
   10160:	00279793          	slli	a5,a5,0x2
   10164:	40e787b3          	sub	a5,a5,a4
   10168:	00279793          	slli	a5,a5,0x2
   1016c:	fcf42623          	sw	a5,-52(s0)
   10170:	fcc42703          	lw	a4,-52(s0)
   10174:	0ac00793          	li	a5,172
   10178:	04e7c863          	blt	a5,a4,101c8 <main+0x174>
   1017c:	fcc42783          	lw	a5,-52(s0)
   10180:	0407c463          	bltz	a5,101c8 <main+0x174>
   10184:	00400793          	li	a5,4
   10188:	fcf42c23          	sw	a5,-40(s0)
   1018c:	ff400793          	li	a5,-12
   10190:	fef42623          	sw	a5,-20(s0)
   10194:	fd842783          	lw	a5,-40(s0)
   10198:	fec42703          	lw	a4,-20(s0)
   1019c:	00ef7f33          	and	t5,t5,a4
   101a0:	00ff6f33          	or	t5,t5,a5
   101a4:	00800793          	li	a5,8
   101a8:	fcf42a23          	sw	a5,-44(s0)
   101ac:	ffc00793          	li	a5,-4
   101b0:	fef42623          	sw	a5,-20(s0)
   101b4:	fd442783          	lw	a5,-44(s0)
   101b8:	fec42703          	lw	a4,-20(s0)
   101bc:	00ef7f33          	and	t5,t5,a4
   101c0:	00ff6f33          	or	t5,t5,a5
   101c4:	03c0006f          	j	10200 <main+0x1ac>
   101c8:	fc042c23          	sw	zero,-40(s0)
   101cc:	ff400793          	li	a5,-12
   101d0:	fef42623          	sw	a5,-20(s0)
   101d4:	fd842783          	lw	a5,-40(s0)
   101d8:	fec42703          	lw	a4,-20(s0)
   101dc:	00ef7f33          	and	t5,t5,a4
   101e0:	00ff6f33          	or	t5,t5,a5
   101e4:	fc042a23          	sw	zero,-44(s0)
   101e8:	ff800793          	li	a5,-8
   101ec:	fef42623          	sw	a5,-20(s0)
   101f0:	fd442783          	lw	a5,-44(s0)
   101f4:	fec42703          	lw	a4,-20(s0)
   101f8:	00ef7f33          	and	t5,t5,a4
   101fc:	00ff6f33          	or	t5,t5,a5
   10200:	e75ff06f          	j	10074 <main+0x20>

00010204 <division>:
   10204:	fd010113          	addi	sp,sp,-48
   10208:	02812623          	sw	s0,44(sp)
   1020c:	03010413          	addi	s0,sp,48
   10210:	fca42e23          	sw	a0,-36(s0)
   10214:	fcb42c23          	sw	a1,-40(s0)
   10218:	fe042623          	sw	zero,-20(s0)
   1021c:	0200006f          	j	1023c <division+0x38>
   10220:	fdc42703          	lw	a4,-36(s0)
   10224:	fd842783          	lw	a5,-40(s0)
   10228:	40f707b3          	sub	a5,a4,a5
   1022c:	fcf42e23          	sw	a5,-36(s0)
   10230:	fec42783          	lw	a5,-20(s0)
   10234:	00178793          	addi	a5,a5,1
   10238:	fef42623          	sw	a5,-20(s0)
   1023c:	fdc42703          	lw	a4,-36(s0)
   10240:	fd842783          	lw	a5,-40(s0)
   10244:	fcf75ee3          	bge	a4,a5,10220 <division+0x1c>
   10248:	fec42783          	lw	a5,-20(s0)
   1024c:	00078513          	mv	a0,a5
   10250:	02c12403          	lw	s0,44(sp)
   10254:	03010113          	addi	sp,sp,48
   10258:	00008067          	ret


```
# Unique Instructions
```
Number of different instructions: 19
List of unique instructions:
mv
addi
bltz
bge
ret
andi
li
slli
beq
sw
lw
and
blt
add
sub
bgeu
j
jal
or

```

# Spike simulator output 

![spike-result](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/16758988-29c5-4efa-9b5e-264256bf7c9d)


### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
