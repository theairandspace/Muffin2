/*

The Air and Space Box Program 2018
 

MUFFIN DOS Satellite Prototype Piggy backed on SERVET III

code V1.1 12/jul/2018

Unlicensed Software: 

Este software esta basado en codigo abierto de otras personas, así­ que puedes usarlo sin indicar ni siquiera la fuente, pero sería un detalle :).


Controlador ATtiny85 y las patas que usamos con X

           _________________
         _|      |___|      |_
   RESET|_|                 |X| VCC
         _|                 |_
  I/O 3 |_|     ATtiny85    |X| I/O 2
         _|                 |_
  I/O 4 |_|                 |_| I/O 1
         _|                 |_
    GND |X|                 |_| I/O 0
          |_________________|      

Generamos una linea de texto a enviar y la transformamos en CW

Velocidad de CW = 80 msegundos
sonido 800 Hz periodo 1250 microsegundos

 
 */
 
 
// Declaramos la linea que emite el TX//

char StringToCW[] = "CQ CQ MUFFIN2 FROM SERVET3. RX? PSE SND QRA QTH QTR INFO@AIRBOX.SPACE TNX 73 AR";

// Definimos el pin de salida para el TX

int AudioOUT = 2;      // output audio on fisical PIN 2

// Definimos el tiempo de delay antes de enviar el siguiente mensaje

int espera = 30000;   // tiempo muerto entre mensaje y mensaje

/*

El codigo Morse consta de puntos, rayas y espacios, que al combinarse entre si forman letras, números y otros símbolos.

El punto en el código Morse se usa como unidad de referencia. 
La línea, en tiempo, equivale a tres puntos.
La separación entre puntos y rallas tambien será un punto. 
Cada letra se separa por un silencio de tres puntos de duración. 
Cada palabra se separa por cinco puntos.

ESTOS SON LOS CARACTERES USADOS:

A ._      B _..     C _._.     D _..      E _..       F .._.      G _ _.      H .... 

I ..      J ._ _ _  K _._      L ._..     M _ _       N _.        O _ _ _     P ._ _. 

Q _ _ ._  R ._.     S ...      T _        U .._       V ..._      W ._ _      X _.._ 

Y _._ _   Z _ _..

0 _ _ _ _ _       1 ._ _ _ _      2 .._ _ _       3 ..._ _      4 ...._       

5 .....           6 _....         7 _ _...        8 _ _ _..     9 _ _ _ _.

"."               ,             $                @  ? .._ _ ..
*/
int dotLen = 80;    // definimos el tiempo en ms que dura 'dot'
int dashLen = dotLen * 3;    // un 'dash' son tres dots
int elemPause = dotLen;  // la separacion entre los puntos y rallas al escribir letras es de un dot
int Spaces = dotLen * 3;     // la separacion entre caracteres
int wordPause = dotLen * 4;  // probamos con 7 dots (Spaces + wordPause = 7)
// la separación entre palabras es de 5 dots pero como ya se hace un Spaces entre letras solo hacen falta dos dots más

// no requerimos nada especial antes del loop

void setup() 
{                
}

void loop()
{ 

  transmitir();
  
  // Al final del string hacemos un paron antes de repetir el mensaje
  LightsOff(espera);      
}

void transmitir()
{
// avanzamos sobre el string leyendo caracter a caracter
  for (unsigned int i = 0; i < sizeof(StringToCW) - 1; i++)
  {
    // seleccionamos el caracter que toca
  char tmpChar = StringToCW[i];
  // convertimos la letra a minusculas
  tmpChar = toLowerCase(tmpChar);
  // converimos a puntos y rallas
  GetChar(tmpChar);
  }
}  


// DOT definimos punto
void MorseDot()
{
  
  for (int i = 0; i < dotLen/2; i++)
  {
  //tone(AudioOUT, note, dotLen); // iniciamos el tono
  //delay(dotLen);              // lo alargamos un punto
  digitalWrite(AudioOUT, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(625);                       // wait for 625 microseconds
  digitalWrite(AudioOUT, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(625);                       // wait for 625 microseconds
  }  
}

// DASH definimos ralla
void MorseDash()
{
  for (int i = 0; i < dashLen/2; i++)
  {
  //tone(AudioOUT, note, dotLen); // iniciamos el tono
  //delay(dotLen);              // lo alargamos un punto
  digitalWrite(AudioOUT, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(625);                       // wait for 625 microseconds
  digitalWrite(AudioOUT, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(625);                       // wait for 625 microseconds

  //tone(AudioOUT, note, dashLen);  // iniciamos el tono
  //delay(dashLen);               // lo alargamos tres puntos
  }
}
// silencio
void LightsOff(int delayTime)
{
  digitalWrite(AudioOUT,LOW);             // stop playing a tone
  delay(delayTime);             // hold in this position
}

// *** Characters to Morse Code Conversion *** //
void GetChar(char tmpChar)
{
  // usamos un case
  switch (tmpChar) {

    case 'a': 
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'b':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'c':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'd':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'e':
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'f':
      MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'g':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'h':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'i':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'j':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'k':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'l':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'm':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'n':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'o':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'p':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 'q':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'r':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 's':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case 't':
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'u':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'v':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'w':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'x':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'y':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;
    
    case 'z':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    case '0':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;

    case '1':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;


    case '2':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;


    case '3':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;


    case '4':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;


    case '5':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

    case '6':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

    case '7':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

    case '8':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

    case '9':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

    
    case ',':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;

    case '.':
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;

    case '$':
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;

case ':':
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;

case '-':
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(Spaces);
    break;


case '@': //. _ _ . _ .
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
case '?': //. . _ _ . .
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDash();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(elemPause);
    MorseDot();
    LightsOff(Spaces);
    break;
    
    
    default: 
    // El espacio y cualquier caracter que no aparezca en la lista lo pintara como espacio entre palabras.
    LightsOff(wordPause);      
  }
}
