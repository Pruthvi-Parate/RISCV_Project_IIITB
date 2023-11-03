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
			//"addi x10, x30, 0\n\t"
			"andi %0, x30, 2\n\t"
			:"=r"(echo)
			:
			:"x30"
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


new:     file format elf32-littleriscv


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
   100c4:	002f7793          	andi	a5,t5,2
   100c8:	fcf42e23          	sw	a5,-36(s0)
   100cc:	fdc42703          	lw	a4,-36(s0)
   100d0:	00200793          	li	a5,2
   100d4:	00f70a63          	beq	a4,a5,100e8 <main+0x94>
   100d8:	fe842783          	lw	a5,-24(s0)
   100dc:	00178793          	addi	a5,a5,1
   100e0:	fef42423          	sw	a5,-24(s0)
   100e4:	f91ff06f          	j	10074 <main+0x20>
   100e8:	fc042c23          	sw	zero,-40(s0)
   100ec:	ff400793          	li	a5,-12
   100f0:	fef42623          	sw	a5,-20(s0)
   100f4:	fd842783          	lw	a5,-40(s0)
   100f8:	fec42703          	lw	a4,-20(s0)
   100fc:	00ef7f33          	and	t5,t5,a4
   10100:	00ff6f33          	or	t5,t5,a5
   10104:	fc042a23          	sw	zero,-44(s0)
   10108:	ff800793          	li	a5,-8
   1010c:	fef42623          	sw	a5,-20(s0)
   10110:	fd442783          	lw	a5,-44(s0)
   10114:	fec42703          	lw	a4,-20(s0)
   10118:	00ef7f33          	and	t5,t5,a4
   1011c:	00ff6f33          	or	t5,t5,a5
   10120:	fe842783          	lw	a5,-24(s0)
   10124:	fe442583          	lw	a1,-28(s0)
   10128:	00078513          	mv	a0,a5
   1012c:	0c8000ef          	jal	ra,101f4 <division>
   10130:	00050793          	mv	a5,a0
   10134:	fcf42823          	sw	a5,-48(s0)
   10138:	fd042703          	lw	a4,-48(s0)
   1013c:	00070793          	mv	a5,a4
   10140:	00179793          	slli	a5,a5,0x1
   10144:	00e787b3          	add	a5,a5,a4
   10148:	00279793          	slli	a5,a5,0x2
   1014c:	40e787b3          	sub	a5,a5,a4
   10150:	00279793          	slli	a5,a5,0x2
   10154:	40e787b3          	sub	a5,a5,a4
   10158:	00279793          	slli	a5,a5,0x2
   1015c:	fcf42623          	sw	a5,-52(s0)
   10160:	fcc42703          	lw	a4,-52(s0)
   10164:	0ac00793          	li	a5,172
   10168:	04e7c863          	blt	a5,a4,101b8 <main+0x164>
   1016c:	fcc42783          	lw	a5,-52(s0)
   10170:	0407c463          	bltz	a5,101b8 <main+0x164>
   10174:	00400793          	li	a5,4
   10178:	fcf42c23          	sw	a5,-40(s0)
   1017c:	ff400793          	li	a5,-12
   10180:	fef42623          	sw	a5,-20(s0)
   10184:	fd842783          	lw	a5,-40(s0)
   10188:	fec42703          	lw	a4,-20(s0)
   1018c:	00ef7f33          	and	t5,t5,a4
   10190:	00ff6f33          	or	t5,t5,a5
   10194:	00800793          	li	a5,8
   10198:	fcf42a23          	sw	a5,-44(s0)
   1019c:	ffc00793          	li	a5,-4
   101a0:	fef42623          	sw	a5,-20(s0)
   101a4:	fd442783          	lw	a5,-44(s0)
   101a8:	fec42703          	lw	a4,-20(s0)
   101ac:	00ef7f33          	and	t5,t5,a4
   101b0:	00ff6f33          	or	t5,t5,a5
   101b4:	03c0006f          	j	101f0 <main+0x19c>
   101b8:	fc042c23          	sw	zero,-40(s0)
   101bc:	ff400793          	li	a5,-12
   101c0:	fef42623          	sw	a5,-20(s0)
   101c4:	fd842783          	lw	a5,-40(s0)
   101c8:	fec42703          	lw	a4,-20(s0)
   101cc:	00ef7f33          	and	t5,t5,a4
   101d0:	00ff6f33          	or	t5,t5,a5
   101d4:	fc042a23          	sw	zero,-44(s0)
   101d8:	ff800793          	li	a5,-8
   101dc:	fef42623          	sw	a5,-20(s0)
   101e0:	fd442783          	lw	a5,-44(s0)
   101e4:	fec42703          	lw	a4,-20(s0)
   101e8:	00ef7f33          	and	t5,t5,a4
   101ec:	00ff6f33          	or	t5,t5,a5
   101f0:	e85ff06f          	j	10074 <main+0x20>

000101f4 <division>:
   101f4:	fd010113          	addi	sp,sp,-48
   101f8:	02812623          	sw	s0,44(sp)
   101fc:	03010413          	addi	s0,sp,48
   10200:	fca42e23          	sw	a0,-36(s0)
   10204:	fcb42c23          	sw	a1,-40(s0)
   10208:	fe042623          	sw	zero,-20(s0)
   1020c:	0200006f          	j	1022c <division+0x38>
   10210:	fdc42703          	lw	a4,-36(s0)
   10214:	fd842783          	lw	a5,-40(s0)
   10218:	40f707b3          	sub	a5,a4,a5
   1021c:	fcf42e23          	sw	a5,-36(s0)
   10220:	fec42783          	lw	a5,-20(s0)
   10224:	00178793          	addi	a5,a5,1
   10228:	fef42623          	sw	a5,-20(s0)
   1022c:	fdc42703          	lw	a4,-36(s0)
   10230:	fd842783          	lw	a5,-40(s0)
   10234:	fcf75ee3          	bge	a4,a5,10210 <division+0x1c>
   10238:	fec42783          	lw	a5,-20(s0)
   1023c:	00078513          	mv	a0,a5
   10240:	02c12403          	lw	s0,44(sp)
   10244:	03010113          	addi	sp,sp,48
   10248:	00008067          	ret

```
# Unique Instructions
```
Number of different instructions: 19
List of unique instructions:
add
slli
bge
li
blt
lw
addi
bltz
sw
jal
ret
sub
mv
and
beq
or
andi
j
bgeu

```

# Spike simulator output 

![image](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/ece0df0d-a023-4ec0-9201-070af80693e4)

![spike-result](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/b9979d17-5820-4d3e-9ad9-27453212180d)


# Explaination

Here what's happening is first trigger is made 1 for some time (using for loop) and then turned off the trigger pin and when echo pin receives the waves "echo pin is triggered" 
and thus buzzer and led will be turn , which is 12 = 1100 so two msb are led and buzzer which is turned on in above case.

# Functional Simualation

By performing functional simulation we can verify our design through the verilog code which is processor.v and testbench.v. Here one trigger pin is there , input_wire is the echo pin and
output_wires is led and buzzer. So as shown in the gtkwave diagram when trigger is made zero and echo pin(input_wire) is 1 , buzzer and led (output_wires) is 11. There is also shown the 
clk, write_done and ID_instruction in the gtkwave diagram below.

![12](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/c6c51864-1779-4b22-a942-5308133b38eb)

Here below input wire is 0 which is echo pin so outputs (buzzer and led) are also 00. Here clk , ID_instruction  and write_done also shown.

![13](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/9c3e977a-a9c1-4370-9e0a-a4272a8fb497)

# Instruction Verification
Here as shown below at instruction : 00FF6F33 output is shown where input pin is 1 and output pins (buzzer, led) is 11:
![14](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/594afba1-76d7-4413-a04f-9e8f29b0abd5)

And as shown below at instruction : FE442783 trig pin is 1 and input pin (echo pin) is 0 thus output pins(buzzer,led) is 00:
![15](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/46bd1c14-a97c-40d9-8f4c-453d764083bf)

# GLS
As you can see in below image sky130_sram cell is implemented in gate level simulation:  

![18](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/99570de9-d182-4283-8e15-fe644b2c6090)   

Here in below image the output is showing 11 when input is 1 at the instruction 00FF6F33 = or	t5,t5,a5  

![19](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/7a96b470-3710-4b3c-bcff-ae9e2ea4d737)


Here in below image shown that when input is 0 output is 00 and then trig pin is turned on , Here instruction is 
FEE7F6E3 = bgeu	a5,a4,10094 <main+0x40> , where 10094 is fe842783   = 	lw	a5,-24(s0).

![20](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/ba14ca89-52bd-424c-af4c-65f419fe69cd)

Now using below command we can see the wrapper module :  
```
show wrapper
```

![17](https://github.com/Pruthvi-Parate/RISCV_Project_IIITB/assets/72121158/3f53771a-fa5a-491f-a47a-cd68121042e3)

### References
 
 1. https://github.com/SakethGajawada/RISCV_GNU
 2. https://github.com/SarthakSKumar/IoT-Projects-and-Scripts/tree/master/Arduino%20Projects/Social%20Distance%20Detector
