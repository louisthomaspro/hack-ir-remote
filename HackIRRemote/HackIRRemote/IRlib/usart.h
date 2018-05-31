/*
 * usart.h
 *
 * Created: 31/05/2018 13:55:10
 *  Author: CDT
 */ 


#ifndef USART_H_
#define USART_H_

void
 USART_Transmit( 
unsigned char
 data )
{
/* 
Wait for empty transmit buffer
 */
while
 ( !( UCSRnA & (1<<UDREn)) )
;
/* 
Put data into buffer, sends the data
 */
UDRn = data;
}



#endif /* USART_H_ */