#include "ThisProj_Glb.h"

///S>==peripherals======================================================================================
//edwoy260502---
//gpioinit:input,polldown
STT_GPIO_INIT_T g_gpioinit_in_dn ={
    .Mode  = GPIO_MODE_INPUT , 
    .Pull  = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_HIGH,    
    
};

//gpioinit:input,polldown
STT_GPIO_INIT_T g_gpioinit_in_up ={
    .Mode  = GPIO_MODE_INPUT , 
    .Pull  = GPIO_PULLUP,
    .Speed = GPIO_SPEED_HIGH,    
    
};

//gpioinit:output,opendrain,nopull
STT_GPIO_INIT_T g_gpioinit_out_od_np ={
    .Mode  = GPIO_MODE_OUTPUT_OD,
    .Pull  = GPIO_NOPULL,
    .Speed = GPIO_SPEED_HIGH,   

};
//gpioinit:output,pp,pullup
STT_GPIO_INIT_T g_gpioinit_out_pp_up ={
    .Mode  = GPIO_MODE_OUTPUT_PP,
    .Pull  = GPIO_PULLUP,
    .Speed = GPIO_SPEED_HIGH,   

};
//gpioinit:output,pp,pulldown
STT_GPIO_INIT_T g_gpioinit_out_pp_dn ={
    .Mode  = GPIO_MODE_OUTPUT_PP,
    .Pull  = GPIO_PULLDOWN,
    .Speed = GPIO_SPEED_HIGH,   

};

///E<==peripherals======================================================================================