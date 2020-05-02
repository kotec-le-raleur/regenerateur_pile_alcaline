// chargeur de pile alcaline
// Rlef 16 avril 2020 
// charge 100 mA 
// montage juste pour le fun

#define  VERSION  "V2.11 30/04/2020\n"

#undef 	 USE_CONSOLE
#undef	 USE_TRACEUR
#define	 USE_LOGVIEW

#define  REF_1V       6
#define  REF_256V     4
#define  REF_VCC      0

#include "Common.h"
#include <SoftwareSerial.h>

// PINS    ATT85
//        ________U_______
//        | 1:RST  8: Vcc |
// TX+Led | 2:PB3  7: PB2 |Cmd drain 50mA
// A2 Pile| 3:PB4  6: PB1 |Cmd charge 100mA
//        | 4:Gnd  5: PB0 |External Ref ==> TL431
//        -----------------

SoftwareSerial TinySerial(RX, TX);  // ( 0 , 3 )
char  Buf[24];
float Charge_Totale = 0.0;
int   NbPass 		= 0;
int   ValAdc 		= 0;   	// tension pile en charge à  100 mA
float PileValue 	= 0.0;  // tension pile en charge 100mA
int   Val_C0 		= 0;   	// tension pile à vide
int   Val_C1 		= 0;   	// tension pile en débit de 50 mA
float deltaV 		= 0.0;
unsigned long time  = 0;
unsigned long Temps = 0;

void setup() {
  TinySerial.begin(9600);
  pinMode(CMD_DRAIN,OUTPUT);
  pinMode(CMD_LOAD,OUTPUT);
  LOAD_OFF  // load coupée
  DRAIN_OFF // drain coupé

  analogReference(EXTERNAL);  // utilise la tension du TL431 sur la pin 5 ===> 2.493 V 
  Charge_Totale = 0.0;
  Temps         = 0;
  NbPass 		= 0;
  #ifdef USE_LOGVIEW
    PRTL("$1;Start");
  #endif
  
  #ifdef USE_CONSOLE
	PRTL(VERSION);
  #endif

}
///********************************************************/
void loop() {
// on met en marche la charge de 100mA
    ValAdc = CourantPulse(32);
	Charge_Totale = Charge_Totale + INC_CHARGE;  // charge 
	
 	if (NbPass > NBPASSMAX)
	{
		PileValue = ValAdc * (REF_EXT/1024.0);
		
		Val_C0 = analogRead(A2);  // Vpile à vide
		DRAIN_ON
		delay(5);   // delai stabilisation de Vpile
		Val_C1 = analogRead(A2);
		DRAIN_OFF
		deltaV = (Val_C0 - Val_C1) * 1.0;
		deltaV = (deltaV / Val_C1) * RESISTANCE;
		Temps = Temps + INC_TEMPS; // temps écoulé depuis le départ
		NbPass = 0;
		
#ifdef USE_CONSOLE
		PRT("Pile = ");
		PRT(C); PRT(" V");
		PRT("\tR_int = ");
		PRT(deltaV);PRT(" Ohm");
		PRT("\tQt = ");
		PRT((int)Charge_Totale);PRT(" mAh");
		PRT("\tTemps = "); CvTemp(Temps);PRTL(Buf);
#endif

#ifdef USE_TRACEUR
		PRT(PileValue); PRT(" , ");	PRTL(deltaV);
#endif

#ifdef USE_LOGVIEW
		PRT("$1;1;; ");
		PRT(PileValue);PRT(";");
		PRT(deltaV);PRT(";");
		PRT((int)Charge_Totale);PRT(";");
		PRTL("0");
#endif
		
		if (ValAdc > MAX_ADC){
			while (1){
				LOAD_OFF
				DRAIN_OFF
				delay(1000);
				PileValue = analogRead(A2) * (REF_EXT/1024.0);
				PRT("Charge terminee Tension Pile = ");
				PRTL(PileValue);
				
				for (int x=60; x>1; x--)  // 2 mn entre chaque print 
				{	
					delay(2000);
					PRT(".");
				}
				PRTL(".");
			}
		}
	}
	NbPass++;         			// compteur de passage

}

///********************************************************/
///********************************************************/
int CourantPulse(int count)
{
    int adc ;
    int x;	
		for (adc=0, x=0; x<count; x++)
		{
			LOAD_ON
			delay(40);                // charge = 50ms
			adc += analogRead(A2);    // Vpile en charge
			delay(10);               
			LOAD_OFF
			DRAIN_ON
			delay(2);  		          // décharge = 5ms
			DRAIN_OFF
		}
	return (adc/count);	  // moyenne sur count mesures
}

///********************************************************/
void CvTemp(unsigned long tx)
{
	int h,m,s = 0;
	unsigned long ti = tx;
	
	h = ti/3600;
	ti = ti - (h*3600);
	m = ti/60;
	s = ti - (m*60);
	sprintf(Buf,"%2d:%02d:%02d",h,m,s);
}
///********************************************************/
