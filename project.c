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

