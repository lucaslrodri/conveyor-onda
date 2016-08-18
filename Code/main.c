//Carrega a biblioteca para o microcontrolador
#include <18F4550.h>
 
//Configuracao FUSES

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES HS                    	//High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT
#FUSES NOPROTECT
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES NOMCLR  //No Master Clear
#FUSES NOLVP
#FUSES NOCPD
 


//Define a utilização do clock interno de 16 Mhz
#use delay(clock=16000000)

int posicao=0;

int const step[8] ={
	0b00001110, //1
	0b00001100, //2
	0b00001101, //3
	0b00001001, //4
	0b00001011, //5
	0b00000011, //6
	0b00000111, //7
	0b00000110, //8
};

int mover_esteira(int passo_atual){
	int proximo_passo;
	proximo_passo = passo_atual;
	if(proximo_passo<8)
		proximo_passo++;
	else
		proximo_passo = 0;
	output_d(step[proximo_passo]);
	delay_ms(1);
	return proximo_passo;
}

#INT_RTCC
void eventoMoverEsteira(){
	static int passo = 0;
	posicao++;
	passo = mover_esteira(passo);
	set_timer0(get_timer0()+0);
}

 
void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64);
   set_timer0(0);
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);
while (TRUE);
}