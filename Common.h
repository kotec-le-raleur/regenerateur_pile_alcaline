// Macro et define pour ce programme
// RL  20/04/2020   Confinement jour 32
//
//
#define  TIME_READ  10000
#define  TIME_LOAD  800
#define  CMD_LOAD   PB1
#define  CMD_DRAIN  PB2
#define  TX         PB3
#define  RX         0 

#define  LOAD_ON      digitalWrite(CMD_LOAD,  LOW); 
#define  LOAD_OFF     digitalWrite(CMD_LOAD,  HIGH); 
#define  DRAIN_ON     digitalWrite(CMD_DRAIN, HIGH); 
#define  DRAIN_OFF    digitalWrite(CMD_DRAIN, LOW); 
#define  PRT          TinySerial.print
#define  PRTL         TinySerial.println

#define  REF_EXT  2.492
#define  MAX_VAL  1.750  // correspond à 700 pour ValAdc
#define  MAX_ADC  720
#define  RESISTANCE 24   /// resistance de drain = 24 ohm 
//#define  INC_CHARGE  0.027778   // équivalent à 100 mA durant 1 seconde
#define  INC_CHARGE  0.555       // équivalent à 100 mA durant 20 seconde
#define  NBPASSMAX   10

  
