#include <Keypad.h>

#define ROWS 4
#define COLS 4
#define KEY_LENGTH 5

// Posição do caracter da secret_key que está sendo testado
int Position = 0;

// Chave secreta para destravar
char * SECRET_KEY = "123D";

// Caracteres do teclado
char Keys[ROWS][COLS] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}  
};

// Pinos de saída das linhas do teclado
byte RowPins[ROWS] = {2,3,4,5};

// Pinos de saída das colunas do teclado
byte ColPins[COLS] = {6,7,8,9};

// Instância do objeto que representa o teclado
Keypad keypad = Keypad(makeKeymap(Keys), RowPins, ColPins, ROWS, COLS);

// Leds de saída do circuito
int RedLED = 12;
int GreenLED = 13;


void setup() 
{
    pinMode(RedLED,OUTPUT);
    pinMode(GreenLED, OUTPUT);

    // Inicializa o LED vermelho, indicando que o sistema está "trancado"
    setLocked(true);
}

// Main loop do circuito
void loop() 
{
    // Captura a tecla pressionada
    char key = keypad.getKey();

    // Caso seja * ou #, bloqueia o sistema
    if (key == '*' || key == '#')
    {
        Position = 0;
        setLocked(true);
    }

    // Caso seja o caracter esperado na posição "Position", incrementa o counter Position
    if (key == SECRET_KEY[Position])
        Position++;

    // Se Position chegou até a 
    if (Position == KEY_LENGTH) 
        setLocked(false);

    delay(100);
}

// Inverte os pinos; 0 = Locked (LED Vermelho ativado); 1 = Unlocked (LED Verde ativado)
void setLocked(int locked)
{
    digitalWrite(RedLED, locked);
    digitalWrite(GreenLED, !locked);
}
