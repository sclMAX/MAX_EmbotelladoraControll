#ifndef CONFIG_H
#define CONFIG_H

//<PINES>
#define PIN_DESPLAZAMIENTO 14
#define PIN_LLENADO 15
#define PIN_TAPADO 16
#define PIN_ELECTRO_CERVEZA 17
#define PIN_ELECTRO_CO2_IN 18
#define PIN_ELECTRO_CO2_OUT1 19

//<RETARDOS>
#define RPOS_BOTELLA 3
#define RCOMUN 1
//</RETARDOS>
//<TECLADO>
#define PINS_TECLADO_ROW 7, 6, 5, 4
#define PINS_TECLADO_COL 3, 2, 1, 0
//</TECLADO>

//<LCD>
// LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //    ( RS, EN, d4, d5, d6, d7)
#define RS 8
#define EN 9
#define D4 10
#define D5 11
#define D6 12
#define D7 13
//</LCD>
#endif // CONFIG_H