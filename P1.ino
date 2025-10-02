#define F_CPU 16000000UL  // Define CPU frequency for delay functions

#include <avr/io.h>       // AVR I/O definitions
#include <util/delay.h>   // For _delay_ms
#include <stdio.h>
#include <avr/interrupt.h> // For ISR and interrupts

// Global variables used in interrupts
volatile int disable_outer_leds = 0; // Flag to disable outer LEDs
volatile int warten = 500;           // Delay time in ms, modifiable via interrupt

// Define LED bit masks
uint8_t LED1 = (1 << PD5);
uint8_t LED2 = (1 << PD6);
uint8_t LED3 = (1 << PD7);
uint8_t LED4 = (1 << PB0);
uint8_t LED5 = (1 << PB1);
uint8_t LED6 = (1 << PB2);
uint8_t LED7 = (1 << PB3);
uint8_t LED8 = (1 << PB4);

// Custom delay function
void delay(int a){
  while(a--)
    _delay_ms(1);
}

// Initialize interrupt for button S3 (connected to INT0, PD2)
void ini_s3_interrupt() {
    EICRA |= (1 << ISC01);   // Trigger on falling edge
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0);    // Enable INT0
}

// Initialize interrupt for button S2 (connected to INT1, PD3)
void ini_s2_interrupt(){
    EICRA |= (1 << ISC11);   // Trigger on falling edge
    EICRA &= ~(1 << ISC10);
    EIMSK |= (1 << INT1);    // Enable INT1
}

// ISR for INT1 (S2 pressed): speed up LED sequence
ISR(INT1_vect) {
    warten = 200;  // Reduce delay time to make animation faster
}

// ISR for INT0 (S3 pressed): disable outer LEDs in the pattern
ISR(INT0_vect) {
    disable_outer_leds = 1;
}

int main(void) {
    // Initialize interrupts
    ini_s2_interrupt();
    ini_s3_interrupt();
    sei(); // Enable global interrupts

    // Configure LED pins as output
    DDRD = (LED1 | LED2 | LED3);                  // PD5–PD7 as output
    DDRB = (LED4 | LED5 | LED6 | LED7 | LED8);    // PB0–PB4 as output
 PORTD =0;
    // Set PD2 (INT0), PD3 (INT1), PD4 as input
    DDRD &= ~((1 << PD4) | (1 << PD3) | (1 << PD2));
    // Enable pull-ups on those inputs
    PORTD = (1 << PD4) | (1 << PD3) | (1 << PD2);

    int i = 0;

    while (1) {
        i = 0;
        
        // Check if button connected to PD4 is pressed (active low)
        if (!(PIND & (1 << PD4))) {
    // Debounce delay
    _delay_ms(50); }
        if (!(PIND & (1 << PD4))) {
            // Execute LED pattern 3 times
            while (i < 3) {

                // Stage 1: All PD LEDs on, PB LEDs off
                PORTD |= (LED1 | LED2 | LED3);
                PORTB &= ~(LED4 | LED5 | LED6 | LED7 | LED8);
                delay(warten);

                // Stage 2: Shift right
                PORTD |= (LED2 | LED3);
                PORTB |= (LED4);
                PORTD &= ~(LED1);
                PORTB &= ~(LED5 | LED6 | LED7 | LED8);
                delay(warten);

                // Stage 3
                PORTD |= (LED3);
                PORTB |= (LED4 | LED5);
                PORTD &= ~(LED1 | LED2);
                PORTB &= ~(LED6 | LED7 | LED8);
                delay(warten);

                // Stage 4
                PORTB |= (LED4 | LED5 | LED6);
                PORTD &= ~(LED1 | LED2 | LED3);
                PORTB &= ~(LED7 | LED8);
                delay(warten);

                // Stage 5: Conditional outer LED disable
                if(disable_outer_leds)
                    PORTB &= ~(LED7);
                else
                    PORTB |= (LED7);

                PORTB |= (LED5 | LED6);
                PORTD &= ~(LED1 | LED2 | LED3);
                PORTB &= ~(LED4 | LED8);
                delay(warten);

                // Stage 6
                if(disable_outer_leds)
                    PORTB &= ~(LED8 | LED7);
                else
                    PORTB |= (LED8 | LED7);

                PORTB |= (LED6);
                PORTD &= ~(LED1 | LED2 | LED3);
                PORTB &= ~(LED4 | LED5);
                delay(warten);

                 // Reverse pattern
                if(disable_outer_leds)
                    PORTB &= ~(LED7);
                else
                    PORTB |= (LED7);

                PORTB |= (LED5 | LED6);
                PORTD &= ~(LED1 | LED2 | LED3);
                PORTB &= ~(LED4 | LED8);
                delay(warten);

                
                PORTB |= (LED4 | LED5 | LED6);
                PORTD &= ~(LED1 | LED2 | LED3);
                PORTB &= ~(LED7 | LED8);
                delay(warten);

               
                PORTD |= (LED3);
                PORTB |= (LED4 | LED5);
                PORTD &= ~(LED1 | LED2);
                PORTB &= ~(LED6 | LED7 | LED8);
                delay(warten);

                PORTD |= (LED2 | LED3);
                PORTB |= (LED4);
                PORTD &= ~(LED1);
                PORTB &= ~(LED5 | LED6 | LED7 | LED8);
                delay(warten);

                PORTD |= (LED1 | LED2 | LED3);
                PORTB &= ~(LED4 | LED5 | LED6 | LED7 | LED8);
                delay(warten);

                i++; // Move to next iteration
               
            }
          
        }
    }

    return 0;
}
