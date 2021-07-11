//******************************************************************************
/* 
 * File:   Juego de Carreras.c
 * Author: Daniel
 *
 * Created on July 08, 2021, 7:14 PM
 */
//******************************************************************************
// Importación de Librerías
//******************************************************************************

#include <xc.h>

//******************************************************************************
// Palabra de configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
//******************************************************************************
// Variables
//******************************************************************************
__bit ESTADO_SEMAFORO;
__bit ESTADO_JUGADOR1;
__bit ESTADO_JUGADOR2;
__bit BLOQUEO1;
__bit BLOQUEO2;
    char CONTADOR1;
char CONTADOR2;


//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void Setup(void);
void delay(char n);
void Win(void);
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void) { 
    Setup();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1){
        delay(1);
        if (BLOQUEO1 == 0 && PORTEbits.RE0 == 1){
            ESTADO_SEMAFORO = 1;    //ANTIREBOTE
        }
        if (ESTADO_SEMAFORO == 1 && PORTEbits.RE0 == 0){
            //EJECUTA SEMAFORO
            BLOQUEO1 = 1;           //BLOQUEA EL MISMO BOTON
            
            PORTAbits.RA3 = 0;      //APAGA LUCES DE VICTORIA
            PORTAbits.RA4 = 0;
            PORTC = 0;              //LIMPIA LAS LUCES DE JUGADORES
            PORTB = 0;
            CONTADOR1 = 0x00;       //REINICIA CONTADORES
            CONTADOR2 = 0x00;
            
            PORTD = 0xB0;
            delay(100);
            PORTAbits.RA0 = 1;      //EMPIEZA SEMAFORO
            PORTD = 0xA4;
            delay(100);
            PORTAbits.RA0 = 0;
            PORTAbits.RA1 = 1;
            PORTD = 0xF9;
            delay(100);
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 1;
            PORTD = 0xC0;
            delay(1);
            BLOQUEO2 = 0;           //HABILITA LOS BOTONES DE JUGADORES            
            //FIN SEMAFORO
            ESTADO_SEMAFORO = 0;
        }
        delay(1);
//******************************************************************************        
        if (BLOQUEO2 == 0 && PORTEbits.RE1 == 1){
            ESTADO_JUGADOR1 = 1;    //ANTIREBOTE
        }
        if (ESTADO_JUGADOR1 == 1 && PORTEbits.RE1 == 0){
            ESTADO_JUGADOR1 = 0;
            //EJECUTA CONTADOR DE DECADAS JUGADOR 1
            CONTADOR1 += 1;         //CONTADOR 1 A 1 PARA INDICAR QUE LED DEBE ENCENDERSE
        }
        if (CONTADOR1 == 0x01){     //DEPENDIENDO DE EL NUMERO DEL CONTADOR VA ENCENDIENDO UN LED SEGUN NUMERO HEXADECIMAL
            PORTC = 0x01;
        }
        if (CONTADOR1 == 0x02){
            PORTC = 0x02;
        }
        if (CONTADOR1 == 0x03){
            PORTC = 0x04;
        }
        if (CONTADOR1 == 0x04){
            PORTC = 0x08;
        }
        if (CONTADOR1 == 0x05){
            PORTC = 0x10;
        }
        if (CONTADOR1 == 0x06){
            PORTC = 0x20;
        }
        if (CONTADOR1 == 0x07){
            PORTC = 0x40;
        }
        if (CONTADOR1 == 0x08){
            PORTC = 0x80;
            Win();
        }
//******************************************************************************
        if (BLOQUEO2 == 0 && PORTEbits.RE2 == 1){
            ESTADO_JUGADOR2 = 1;        //ANTIREBOTE
        }
        if (ESTADO_JUGADOR2 == 1 && PORTEbits.RE2 == 0){
            ESTADO_JUGADOR2 = 0;            
            //EJECUTA CONTADOR DE DECADAS JUGADOR 2
            CONTADOR2 += 1;         //CONTADOR 1 A 1 PARA JUGADOR 2
            //FIN CONTADOR JUGADOR 2
        }
        if (CONTADOR2 == 0x01){     //SE ELIGE EL PIN O LED A ENCENDER SEGUN CONTADOR 1 A 1
            PORTB = 0x01;
        }
        if (CONTADOR2 == 0x02){
            PORTB = 0x02;
        }
        if (CONTADOR2 == 0x03){
            PORTB = 0x04;
        }
        if (CONTADOR2 == 0x04){
            PORTB = 0x08;
        }
        if (CONTADOR2 == 0x05){
            PORTB = 0x10;
        }
        if (CONTADOR2 == 0x06){
            PORTB = 0x20;
        }
        if (CONTADOR2 == 0x07){
            PORTB = 0x40;
        }
        if (CONTADOR2 == 0x08){
            PORTB = 0x80;
            Win();
        }
//******************************************************************************
    }
}
//******************************************************************************
// Configuración
//******************************************************************************
void Setup(void){
    PORTB = 0;
    PORTC = 0;
    PORTD = 0xFF;
    PORTA = 0;
    
    ANSEL = 0;
    ANSELH = 0;
    
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISA = 0;
    /*TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;*/
    TRISE = 1;  
    PORTE = 0;
    BLOQUEO1 = 0;       //CONDICION INICIAL PARA LOS BOTONES
    BLOQUEO2 = 1;
    CONTADOR1 = 0x00;   //CONTADORES EMPIEZAN EN 0
    CONTADOR2 = 0x00;
}
//******************************************************************************
// Delay
//******************************************************************************
void delay(char n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 255; j++ ){
            
        }
    }

}
//******************************************************************************
// Funciones Adicionales
//******************************************************************************
void Win(void){
    if (CONTADOR1 == 0x08){     //SI GANA JUGADOR 1 APAGA LUZ SEMAFORO Y ENCIENDE LUZ DE VICTORIA 1
        PORTAbits.RA3 = 1;
        PORTAbits.RA2 = 0;
        PORTD = 0xF9;
        BLOQUEO2 = 1;           //SE BLOQUEAN LOS BOTONES PARA AMBOS JUGADORES
        BLOQUEO1 = 0;           //SE DESBLOQUEA EL SEMAFORO PARA VOLVER A JUGAR
        delay(1);
    }
    if (CONTADOR2 == 0x08){     //SI GANA JUGADOR 2 APAGA LUZ SEMAFORO Y ENCIENDE LUZ DE VICTORIA 2
        PORTAbits.RA4 = 1;
        PORTAbits.RA2 = 0;
        PORTD = 0xA4;
        BLOQUEO2 = 1;           //SE BLOQUEAN LOS BOTONES PARA AMBOS JUGADORES
        BLOQUEO1 = 0;           //SE DESBLOQUEA EL SEMAFORO PARA VOLVER A JUGAR
        delay(1);
    }    
}