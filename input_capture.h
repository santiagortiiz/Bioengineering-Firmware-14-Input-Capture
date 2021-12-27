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

#ifndef INPUT_CAPTURE_H
    #define INPUT_CAPTURE_H
    
    #include "project.h"

    /*** MACROS ***/
    #define rango_del_contador 16777216 // 2^n - 1, n = 24
    
    /*** PROTOTIPO DE VARIABLES GLOBALES ***/
    typedef struct Estructura_1{
        uint32 contador_de_flancos: 1;
        uint32 overflows: 8;
        uint32 valor_1: 24;
        uint32 valor_2: 24;
        uint32 capturas_listas: 1;
        uint32 conteos_entre_eventos: 24;
        uint32 tiempo_entre_eventos: 32;
    } estructura_1;
    
    extern estructura_1 timer;
    
    /*** PROTOTIPO DE FUNCIONES ***/
    void calcular_tiempo_transcurrido(void);
    
    /*** PROTOTIPO DE INTERRUPCIONES ***/
    CY_ISR_PROTO(flanco_detectado);
    
#endif

/* [] END OF FILE */
