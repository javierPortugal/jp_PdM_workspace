# Práctica 4

Una máquina de estado finito (FSM, por sus siglas en inglés) es un modelo computacional que describe 
el comportamiento de un sistema utilizando un número limitado de estados y transiciones entre ellos. 
Solo puede estar en un estado a la vez y cambia a otro en respuesta a eventos o entradas externas. 

Las máquinas de estado finito que pueden ser de dos tipos:

1.- Máquina de Mealy: La salida depende del estado actual y de la entrada.

2.- Máquina de Moore: La salida depende únicamente del estado actual.

El ejercicio en esta práctica implementa una MEF (Maquina de Estados Finita) anti-rebote que
permita leer el estado de un pulsador de la placa NUCLEO-F446RE y generar
acciones o eventos ante un flanco descendente o ascendente esta aplicación pretende eliminar
el efecto de rebote que se produce cuando se activa un pulsador mecánico.

El tiempo anti-rebote es de 40mS con un retardo no bloqueante utilizando la
libreria `Drivers/API/API_delay.(c|h)`.

El driver de la práctica se encuentra definido en los archivos `Drivers/API/API_debounce.(c
|h)` e implementa los requerimientos descritos en la práctica como se indica a continuación:


```
/**
 * @brief representation of each state of the FSM
 */
typedef enum {
	BUTTON_UP,			///< The button is up after 40mS of rising edge detected
	BUTTON_FALLING,		///< A falling edge has been detected
	BUTTON_DOWN,		///< delay of 40mS passed and logic level of button is low, FSM passed to BUTTON_DOWN
	BUTTON_RISING		///< A rising edge has been detected, waiting for delay 40mS and button up so FSM transitions to BUTTON_UP
} debounceState_t;

/**
 * @brief load initial state
 * 
 * This function initializes the debounce FSM by setting the initial state to
 * BUTTON_UP and initializing the debounce delay timer.
 * It should be called once at the start of the program.
 */
void debounceFSM_init();

/**
 * @brief update FSM according to inputs
 * 
 * This function should be called periodically in the main loop to update the
 * state of the FSM based on the button input and timing. It checks the current
 * state and transitions to the next state based on the button's logic level and
 * the debounce delay.
 */
void debounceFSM_update();

/**
 * @brief public function to get key value
 *
 * @return true if the button was pressed, false otherwise
 * @note this function will return true only once per button press, it resets
 * the keyPressed variable after reading it
 */
bool_t readKey();
```



