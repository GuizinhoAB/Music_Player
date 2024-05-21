#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 4, 5, 6, 7);

// Botões
int buttonUp = 2, buttonDown = 3, buttonPP = 9, buttonStop = 8;

// Buzzer e LED
int buzzer = 10, LedGreen = 1, LedRed = 0;

// Variáveis
int valUp = 0, valDown = 0, valPP = 0, valStop = 0;
int led_num = 1, led_pp = 0;
int pauseVal = 1;


// Notas das músicas                           
char *Str[] = {"G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4", "-"};
int freq[] = {196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

// Música 1
char *Song[] = {"E4", "F4", "G4", "A4", "B4", "A4", "G4", "F4", "E4", "D4", "E4", "F4", "G4", "A4", "B4", "A4"};

// Música 2
char *Song2[] = {"E4", "-", "E4", "-", "E4", "C4", "E4", "G4", "G4", "-", "C4", "E4", "G4", "A4", "A4"};

// Música 3
char *Song3[] = {"G4", "G4", "G4", "E4", "A4", "A4", "G4", "-", "F4", "F4", "F4", "D4", "A4", "A4", "G4"};

// Música 4
char *Song4[] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "-", "G4", "A4", "G4", "F4", "E4", "D4", "C4"};

// Música 5
char *Song5[] = {"E4", "G4", "A4", "B4", "A4", "-", "E4", "D4", "E4", "G4", "A4", "B4", "A4", "-", "E4", "D4"};


void setup()
{
  // Configurando as entradas, saídas e o display LCD
  lcd.begin(16, 2);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonPP, INPUT);
  pinMode(buttonStop, INPUT);

}


void loop() {
  // Arrays
  int arrayLen = sizeof(Song) / sizeof(Song[0]);
  int arrayLen2 = sizeof(Song2) / sizeof(Song2[0]);
  int arrayLen3 = sizeof(Song3) / sizeof(Song3[0]);
  int arrayLen4 = sizeof(Song4) / sizeof(Song4[0]);
  int arrayLen5 = sizeof(Song5) / sizeof(Song5[0]);
  // Variavel
  int position;
 
  // Se o botao para "subir" a musica for acionado
  // a variavel led_num e somada em 1
  if (digitalRead(buttonUp) == HIGH) {
    led_num = led_num + 1;
  }
  // faz um loop entre o menu, se chegar no final, volta para o inicio
  if (led_num > 5){
   led_num = 1;
  }
  
  // se o botao para "descer" for acionado
  // a variavel led_num e diminuida em 1
  if (digitalRead(buttonDown) == HIGH) {
    led_num = led_num - 1;
  }
  // faz um loop entre o menu, se passar do inicio, retorna para o final
  if (led_num < 1){
   led_num = 5;
  }
  
  // se o botao de stop for acionado, retorna para o menu principal
  if (digitalRead(buttonStop) == HIGH){
   led_num = 1;
  }
  
  
  // caso led_num for 1, o menu de musica 1 e 2 e exibido
  if (led_num == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("--> Musica 1");
      lcd.setCursor(0, 1);
      lcd.print("    Musica 2");
      delay(100);
  }

  // caso led_num for 2, o menu de musica 2 e 3 e exibido
  else if (led_num == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("--> Musica 2");
      lcd.setCursor(0, 1);
      lcd.print("    Musica 3");
      delay(100);
  }
  
  // caso led_num for 3, o menu de musica 3 e 4 e exibido
  else if (led_num == 3) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("--> Musica 3");
      lcd.setCursor(0, 1);
      lcd.print("    Musica 4");
    delay(100);
  }
  
  // caso led_num for 4, o menu de musica 4 e 5 e exibido
  else if (led_num == 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("--> Musica 4");
      lcd.setCursor(0, 1);
      lcd.print("    Musica 5");
    delay(100);
  }
  
  // caso led_num for 5, o menu de musica 5 e 1 e exibido
  else if (led_num == 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("--> Musica 5");
      lcd.setCursor(0, 1);
      lcd.print("    Musica 1");
    delay(100);
  }

  // Musica 1
  // caso o botão seja acionado e a variável de controle seja 1
  // entra na condição da música 1
  if (digitalRead(buttonPP) == HIGH && led_num == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TOCANDO MUSICA 1");
    delay(100);

    // Para percorrer o array da música e toca ou pausa a música
    for (int x = 0; x < arrayLen; x++) {
      for (int a = 0; a < 11; a++) {
        if (Str[a] == Song[x] && digitalRead(buttonPP) == HIGH) {
          position = a;
          break;
          // Pausa a música se o botão não estiver acionado
        } else if (digitalRead(buttonPP) == LOW) { 
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PAUSADO");
          digitalWrite(LedGreen, LOW);
          digitalWrite(LedRed, HIGH);
          a--;
          delay(100);
        }
        // Interrompe a música se o botão Stop for acionado e se o botão Pause/Play
        // não estiver acionado, significando que está pausado
        if (digitalRead(buttonStop) == HIGH && digitalRead(buttonPP) == LOW) { 
          led_num = 1;
          digitalWrite(LedRed, LOW);
          digitalWrite(LedGreen, LOW);
          noTone(buzzer); // Parar o tom
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("INTERROMPIDA");
          delay(1500);
          return; // Sair da função e interromper a música
        } 
        // Se o botão Pause/Play estiver acionado, faz o controle do LED e exibe no display
        else if (digitalRead(buttonPP) == HIGH) {
          lcd.setCursor(0, 0);
          lcd.print("TOCANDO MUSICA 1");
          digitalWrite(LedRed, LOW);
          digitalWrite(LedGreen, HIGH);
        }
      }
      // Controle da música e ativação do buzzer
      if (digitalRead(buttonPP) == HIGH) {
        tone(10, freq[position], 200);
      }
      // Delay
      delay(250);
    }

    // Adiciona uma volta ao menu ao chegar ao fim da música
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Musica Concluida");
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, LOW);
    delay(2000);
    led_num = 1;  // Reinicia o índice da música, para retornar ao menu principal
  }
  // Fim da musica 1
  
  //
  //
  
  // Musica 2
  // caso o botão seja acionado e a variável de controle seja 2
  // entra na condição da música 2
  if (digitalRead(buttonPP) == HIGH && led_num == 2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOCANDO MUSICA 2");
  delay(100);

  // Para percorrer o array da música e toca ou pausa a música
  for (int x = 0; x < arrayLen2; x++) {
    for (int a = 0; a < 11; a++) {
      if (Str[a] == Song2[x] && digitalRead(buttonPP) == HIGH) {
        position = a;
        break;
      } 
      // Se o botão Pause/Play não estiver acionado, decaí a variável "a",
      // faz o controle dos LEDs e exibe no display
      else if (digitalRead(buttonPP) == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PAUSADO");
        digitalWrite(LedGreen, LOW);
        digitalWrite(LedRed, HIGH);
        a--;
        delay(100);  
      }
       // Interrompe a música se o botão Stop for acionado e se o botão Pause/Play
       // não estiver acionado, significando que está pausado
       if (digitalRead(buttonStop) == HIGH && digitalRead(buttonPP) == LOW) {
        led_num = 1;
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, LOW);
        noTone(buzzer); // Parar o tom
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INTERROMPIDA");
        delay(1500);
        return; // Sair da função e interromper a música
       } 
      // Se o botão Pause/Play estiver acionado, faz o controle do LED e exibe no display
      else if (digitalRead(buttonPP) == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("TOCANDO MUSICA 2");
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, HIGH);
      }
    }
    // Controle da música e ativação do buzzer
    if (digitalRead(buttonPP) == HIGH) {
      tone(10, freq[position], 200);
    }
    // Delay
    delay(250);
  }

  // Adiciona uma volta ao menu ao chegar ao fim da música
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Musica Concluida");
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
  delay(2000);
  led_num = 2;  // Reinicia o índice da música
  }
  // Fim da musica 2
  
  //
  //
  
  // Musica 3
  // caso o botão seja acionado e a variável de controle seja 3
  // entra na condição da música 3
  if (digitalRead(buttonPP) == HIGH && led_num == 3) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOCANDO MUSICA 3");
  delay(100);
	
  // Para percorrer o array da música e toca ou pausa a música  
  for (int x = 0; x < arrayLen3; x++) {
    for (int a = 0; a < 11; a++) {
      if (Str[a] == Song3[x] && digitalRead(buttonPP) == HIGH) {
        position = a;
        break;
      } 
      // Se o botão Pause/Play não estiver acionado, decaí a variável "a",
      // faz o controle dos LEDs e exibe no display
      else if (digitalRead(buttonPP) == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PAUSADO");
        digitalWrite(LedGreen, LOW);
        digitalWrite(LedRed, HIGH);
        a--;
        delay(100);
      }
      // Interrompe a música se o botão Stop for acionado e se o botão Pause/Play
      // não estiver acionado, significando que está pausado
      if (digitalRead(buttonStop) == HIGH && digitalRead(buttonPP) == LOW) {
        led_num = 1;
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, LOW);
        noTone(buzzer); // Parar o tom
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INTERROMPIDA");
        delay(1500);
        return; // Sair da função e interromper a música
    } 

	// Se o botão Pause/Play estiver acionado, faz o controle do LED e exibe no display
    else if (digitalRead(buttonPP) == HIGH) {
      lcd.setCursor(0, 0);
      lcd.print("TOCANDO MUSICA 3");
      digitalWrite(LedRed, LOW);
      digitalWrite(LedGreen, HIGH);
    }
    }
    // Controle da música e ativação do buzzer
    if (digitalRead(buttonPP) == HIGH) {
      tone(10, freq[position], 200);
    }
    // Delay
    delay(250);
  }

  // Adiciona uma volta ao menu ao chegar ao fim da música
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Musica Concluida");
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
  delay(1000);
  led_num = 3;  // Reinicia o índice da música
  }
  // Fim da musica 3
  
  //
  //
  
  // Musica 4
  // caso o botão seja acionado e a variável de controle seja 4
  // entra na condição da música 4
  if (digitalRead(buttonPP) == HIGH && led_num == 4) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOCANDO MUSICA 4");
  delay(100);

  // Para percorrer o array da música e toca ou pausa a música  
  for (int x = 0; x < arrayLen4; x++) {
    for (int a = 0; a < 11; a++) {
      if (Str[a] == Song4[x] && digitalRead(buttonPP) == HIGH) {
        position = a;
        break;
      }
      // Se o botão Pause/Play não estiver acionado, decaí a variável "a",
      // faz o controle dos LEDs e exibe no display
      else if (digitalRead(buttonPP) == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PAUSADO");
        digitalWrite(LedGreen, LOW);
        digitalWrite(LedRed, HIGH);
        a--;
        delay(100);

      }
      // Interrompe a música se o botão Stop for acionado e se o botão Pause/Play
      // não estiver acionado, significando que está pausado
      if (digitalRead(buttonStop) == HIGH && digitalRead(buttonPP) == LOW) {
        led_num = 1;
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, LOW);
        noTone(buzzer); // Parar o tom
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INTERROMPIDA");
        delay(1500);
        return; // Sair da função e interromper a música
    } 
      // Se o botão Pause/Play estiver acionado, faz o controle do LED e exibe no display
      else if (digitalRead(buttonPP) == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("TOCANDO MUSICA 4");
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, HIGH);
      }
    }
    // Controle da música e ativação do buzzer
    if (digitalRead(buttonPP) == HIGH) {
      tone(10, freq[position], 200);
    }// Delay
    delay(250);
  }

  // Adiciona uma volta ao menu ao chegar ao fim da música
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Musica Concluida");
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
  delay(1000);
  led_num = 4;  // Reinicia o índice da música
  }
  // Fim da musica 4
  
  //
  //
  
  // Musica 5
  // caso o botão seja acionado e a variável de controle seja 5
  // entra na condição da música 5
  if (digitalRead(buttonPP) == HIGH && led_num == 5) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TOCANDO MUSICA 5");
  delay(100);

  // Para percorrer o array da música e toca ou pausa a música  
  for (int x = 0; x < arrayLen5; x++) {
    for (int a = 0; a < 11; a++) {
      if (Str[a] == Song5[x] && digitalRead(buttonPP) == HIGH) {
        position = a;
        break;
      } 
      // Se o botão Pause/Play não estiver acionado, decaí a variável "a",
      // faz o controle dos LEDs e exibe no display
      else if (digitalRead(buttonPP) == LOW) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PAUSADO");
        digitalWrite(LedGreen, LOW);
        digitalWrite(LedRed, HIGH);
        a--;
        delay(100);

      }
      // Interrompe a música se o botão Stop for acionado e se o botão Pause/Play
      // não estiver acionado, significando que está pausado
      if (digitalRead(buttonStop) == HIGH && digitalRead(buttonPP) == LOW) {
        led_num = 1;
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, LOW);
        noTone(buzzer); // Parar o tom
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INTERROMPIDA");
        delay(1500);
        return; // Sair da função e interromper a música
    } 
	
      // Se o botão Pause/Play estiver acionado, faz o controle do LED e exibe no display
      else if (digitalRead(buttonPP) == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print("TOCANDO MUSICA 5");
        digitalWrite(LedRed, LOW);
        digitalWrite(LedGreen, HIGH);
      }
    }
    // Controle da música e ativação do buzzer
    if (digitalRead(buttonPP) == HIGH) {
      tone(10, freq[position], 200);
    }
    // Delay
    delay(250);
  }

  // Adiciona uma volta ao menu ao chegar ao fim da música
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Musica Concluida");
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
  delay(1000);
  led_num = 5;  // Reinicia o índice da música
  }
  // Fim da musica 5
 
  
}// fim do loop
