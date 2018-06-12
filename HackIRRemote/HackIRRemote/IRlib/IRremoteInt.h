/*
 * IRremote
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
 *
 * Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
 * Ported to PIC18F2550 by Marco Koehler, 2013
 *
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 */

#ifndef IRremoteint_h
#define IRremoteint_h

#include "IRremote.h"





// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 0

// Pulse parms are *50-100 for the Mark and *50+100 for the space
// First MARK is the one after the long gap
// pulse parameters in usec
#define NEC_HDR_MARK  9000
#define NEC_HDR_SPACE 4500
#define NEC_BIT_MARK  560
#define NEC_ONE_SPACE 1600
#define NEC_ZERO_SPACE  560
#define NEC_RPT_SPACE 2250

#define SIGMA_HDR_MARK  8440
#define SIGMA_HDR_SPACE 4240
#define SIGMA_NEXT_SPACE 4240
#define SIGMA_BIT_MARK  520
#define SIGMA_ONE_SPACE 1600
#define SIGMA_ZERO_SPACE 520

#define SONY_HDR_MARK 2400
#define SONY_HDR_SPACE  600
#define SONY_ONE_MARK 1200
#define SONY_ZERO_MARK  600
#define SONY_RPT_LENGTH 45000
#define SONY_DOUBLE_SPACE_USECS  500  // usually ssee 713 - not using ticks as get number wrapround

// SA 8650B
#define SANYO_HDR_MARK  3500  // seen range 3500
#define SANYO_HDR_SPACE 950 //  seen 950
#define SANYO_ONE_MARK  2400 // seen 2400  
#define SANYO_ZERO_MARK 700 //  seen 700
#define SANYO_DOUBLE_SPACE_USECS  800  // usually ssee 713 - not using ticks as get number wrapround
#define SANYO_RPT_LENGTH 45000

// Mitsubishi RM 75501
// 14200 7 41 7 42 7 42 7 17 7 17 7 18 7 41 7 18 7 17 7 17 7 18 7 41 8 17 7 17 7 18 7 17 7 

// #define MITSUBISHI_HDR_MARK  250  // seen range 3500
#define MITSUBISHI_HDR_SPACE  350 //  7*50+100
#define MITSUBISHI_ONE_MARK 1950 // 41*50-100
#define MITSUBISHI_ZERO_MARK  750 // 17*50-100
// #define MITSUBISHI_DOUBLE_SPACE_USECS  800  // usually ssee 713 - not using ticks as get number wrapround
// #define MITSUBISHI_RPT_LENGTH 45000


#define RC5_T1    889
#define RC5_RPT_LENGTH  46000

#define RC6_HDR_MARK  2666
#define RC6_HDR_SPACE 889
#define RC6_T1    444
#define RC6_RPT_LENGTH  46000

#define SHARP_BIT_MARK 245
#define SHARP_ONE_SPACE 1805
#define SHARP_ZERO_SPACE 795
#define SHARP_GAP 600000
#define SHARP_TOGGLE_MASK 0x3FF
#define SHARP_RPT_SPACE 3000

#define DISH_HDR_MARK 400
#define DISH_HDR_SPACE 6100
#define DISH_BIT_MARK 400
#define DISH_ONE_SPACE 1700
#define DISH_ZERO_SPACE 2800
#define DISH_RPT_SPACE 6200
#define DISH_TOP_BIT 0x8000

#define PANASONIC_HDR_MARK 3502
#define PANASONIC_HDR_SPACE 1750
#define PANASONIC_BIT_MARK 502
#define PANASONIC_ONE_SPACE 1244
#define PANASONIC_ZERO_SPACE 400

#define JVC_HDR_MARK 8000
#define JVC_HDR_SPACE 4000
#define JVC_BIT_MARK 600
#define JVC_ONE_SPACE 1600
#define JVC_ZERO_SPACE 550
#define JVC_RPT_LENGTH 60000

#define SHARP_BITS 15
#define DISH_BITS 16

#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

#define _GAP 5000 // Minimum map between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))

// receiver states
#define STATE_IDLE     2
#define STATE_MARK     3
#define STATE_SPACE    4
#define STATE_STOP     5

// IR detector output is active low
#define MARK  1
#define SPACE 0
#define LOW 0
#define OUTPUT 0
#define INPUT 1

#define TOPBIT 0x80000000


// information for the interrupt handler
typedef struct {
  uint8_t rcvstate;          // state machine
  uint8_t blinkflag;         // TRUE to enable blinking of pin 13 on IR processing
  uint16_t timer;     // state timer, counts 50uS ticks.
  uint16_t rawbuf[RAWBUF]; // raw data
  uint16_t rawlen;         // counter of entries in rawbuf
} 
irparams_t;

// Defined in IRremote.c
extern volatile irparams_t irparams;


////////////////////////////////////////////////////////////
// internal Prototypes                                    //
////////////////////////////////////////////////////////////

static void ir_delayMicroseconds(int time);
static void ir_timerCfgNorm(void);
static void ir_timerCfgKhz(uint8_t val);
static void ir_timerRst(void);
static void ir_enableIROut(unsigned char khz);
static void ir_mark(int time);
static void ir_space(int time);
static int ir_getRClevel(decode_results *results, int *offset, int *used, int t1);
static long ir_decodeNEC(decode_results *results);
static long ir_decodeSigma(decode_results *results);
static long ir_decodeSony(decode_results *results);
static long ir_decodeSanyo(decode_results *results);
static long ir_decodeMitsubishi(decode_results *results);
static long ir_decodeRC5(decode_results *results);
static long ir_decodeRC6(decode_results *results);
static long ir_decodePanasonic(decode_results *results);
static long ir_decodeJVC(decode_results *results);
static long ir_decodeHash(decode_results *results);
static int ir_compare(unsigned int oldval, unsigned int newval);
static int MATCH(int measured, int desired);
static int MATCH_MARK(int measured_ticks, int desired_us);
static int MATCH_SPACE(int measured_ticks, int desired_us);

////////////////////////////////////////////////////////////
// PIC2550 hardware depending defines                     //
////////////////////////////////////////////////////////////

#define SYSCLOCK  F_CPU     // main Arduino clock


// defines for timers
#define MAX_TMR_VAL          255
//#define US_PER_SEC           1000000
#define TIMER_ENABLE_PWM     (TCCR0A |= 0x40)
#define TIMER_DISABLE_PWM    (TCCR0A &= ~(0x40))
#define TIMER_ENABLE_INTR    (TIMSK0=0b00000010)   
#define TIMER_DISABLE_INTR   (TIMSK0=0)
/*#define TIMER_INT_FLAG       PIR2bits.TMR3IF
#define TIMER_PWM_PIN        13
#define DELAY_INT_FLAG       PIR1bits.TMR1IF
#define DELAY_PRESCALE       4
#define DELAY_TICKS_PER_US   (SYSCLOCK/US_PER_SEC/DELAY_PRESCALE)

// defines for blinking the LED
#define BLINKLED_PIN         2
#define BLINKLED_ON()        (LATAbits.LATA0 = 1)
#define BLINKLED_OFF()       (LATAbits.LATA0 = 0)



#define DISABLE_INTERRUPTS   (INTCONbits.GIEH = 0)
#define ENABLE_INTERRUPTS    (INTCONbits.GIEH = 1)*/

#define USECPERTICK 50       // microseconds per clock interrupt tick

#define IR_RECEIVE_PIN	(7)
#define IR_RECEIVE_PINx	(PIND)
#define IR_RECEIVE_DDR	(DDRD)

#define IR_SEND_PIN (6)
#define IR_SEND_DDR (DDRD)
#define IR_SEND_PORT (PORTD)

////////////////////////////////////////////////////////////
// PIC2550 hardware depending functions                   //
////////////////////////////////////////////////////////////

volatile unsigned char half_pwm = 0;

static void ir_timerRst(void) {
    /*timer 3 for ir-receiving*/
    //TMR3H = (MAX_TMR_VAL - (USECPERTICK*(SYSCLOCK/US_PER_SEC)))/256;
    //TMR3L = (MAX_TMR_VAL - (USECPERTICK*(SYSCLOCK/US_PER_SEC)))%256;
	TCNT0=0;
}

static void ir_timerCfgNorm(void) {
  /*timer 0 for ir-receiving*/
  OCR0A=6; // division par 200
  TCCR0A=0b00000010;
  TCCR0B=0b00000011; // /256
  TIMSK0=0b00000010;
  
}


static void ir_timerCfgKhz(uint8_t khz) {
  TIMSK0=0;
  OCR0A = (uint8_t)((float)SYSCLOCK / 2000.f / ((float)khz)); 
  TCCR0A = 0x42;
  TCCR0B = 0x01; 
}

static void ir_delayMicroseconds(int time)
{
    //unsigned long tm_val = MAX_TMR_VAL - (time*DELAY_TICKS_PER_US);
	
	
	
	//const uint8_t pwmval = (uint8_t)((SYSCLOCK / 2UL / 8UL )*(time));
	TCCR1B = 0x0;
	TCNT1=0;
	TIFR1 |= (1<<OCF1A);
	OCR1A = time;
	TCCR1A = 0x0;
	TCCR1B = 0x0A;
	//TIMSK1=0x02;
	
	while(!((TIFR1 & (1<<OCF1A))>>OCF1A));
	
    //using timer 1 for a delay during ir-sending
   /* T1CON = 0b10100100; //16bit timer using a prescale of 4
    TMR1H = tm_val/256;
    TMR1L = tm_val%256;
    DELAY_INT_FLAG = 0;//clear interrupt flag
    IPR1bits.TMR1IP = 1;//set to high prio
    INTCONbits.GIEH = 1;//enable high prio
    INTCONbits.GIEL = 1;//enable low prio
    T1CONbits.TMR1ON = 1;// start timer
    while(DELAY_INT_FLAG == 0){};//wait for timer interrupt flag
    T1CONbits.TMR1ON = 0;// disable timer*/
}

/*static void ir_delay(unsigned long time)
{
    unsigned long i;
    for(i=0; i<time; i++) ir_delayMicroseconds(1000);
}*/

#endif
