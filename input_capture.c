/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/*** COMPONENTES INCLUIDOS ***/
#include "input_capture.h"

/*** VARIABLES ***/
static volatile uint8 registros_del_timer;
estructura_1 timer;


/*** FUNCIONES ***/
void calcular_tiempo_transcurrido(void){
    timer.conteos_entre_eventos = timer.overflows*rango_del_contador + timer.valor_1 - timer.valor_2;
    timer.tiempo_entre_eventos = timer.conteos_entre_eventos/24; // Realmente son 24MHz. Al poner solo 24 obtengo el tiempo en us
    
    timer.contador_de_flancos = 0;
    timer.overflows = 0;
}

/*** INTERRUPCIONES ***/
CY_ISR(flanco_detectado){
    registros_del_timer = Timer_ReadStatusRegister();
    
    /* Detección de interrupcion por TC */
    if (registros_del_timer & Timer_STATUS_TC){                 // Este condicional se evalua dentro de la interrupcion 
        if (timer.contador_de_flancos == 1){                    // de captura de flancos debido a que los finales de
            timer.overflows++;                                  // conteo mientras no se presenten eventos no me interesan 
        }
    } 
    
    /* Detección de interrupcion por captura de flancos */
    if (registros_del_timer & Timer_STATUS_CAPTURE){
        if (timer.contador_de_flancos == 0){
            timer.valor_1 = Timer_ReadCapture();
            timer.contador_de_flancos++;
        }
        else if (timer.contador_de_flancos == 1){
            timer.valor_2 = Timer_ReadCapture();
            timer.capturas_listas = 1;
        }
    } 
}

/* [] END OF FILE */
