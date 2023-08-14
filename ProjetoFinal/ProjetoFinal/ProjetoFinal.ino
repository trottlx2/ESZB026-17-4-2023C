#include <Thermistor.h>
const int analogInPin = A0; // o potenciômetro esta ligado ao pino A0

#define TEMPO_APNEA 100
#define TEMPO_G_APNEA 200

//Thermistor temp(0);
float media;
boolean inicial = true;
boolean coleta = false;
int contador = 0;
int insp_flag = 0;
int exp_flag = 0;
int insp_cont = 0;
int exp_cont = 0;
int apneia = 0;
int apneia_grave = 0;
int tmp_insp = 0;
int tmp_exp = 0;
boolean apnea_flag = false;
unsigned long ultima_apnea =0;

int final;

#define TAMANHO 100
byte vetor[TAMANHO];
int posicao = 0;

unsigned long ultima_medida = millis();

void setup(){
  // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
  Serial.begin(115200, SERIAL_8N1);
  pinMode(7, OUTPUT);
  pinMode(6,OUTPUT);
}

void toca(unsigned long instante){
  int tempo = 200;
  int      notas[]={
    440,294,349,392,440,294,349,392,330};
  int     tempos[]={  
    2,  2,  2,  1,  1,  1,  1,  1,  1 };
  int tempo_acum[]={  
    2,  4,  6,  7,  8, 9, 10, 11, 12 };

  int n;
  for (n = 0; n<9; n++){
    if(instante<tempo_acum[n]*tempo){
      break;
    }

  }


  if (n < 9){
    tone(6,notas[n],tempo*tempos[n]); //LA
    //delay(tempo*tempos[n]);
  }

  if (instante > tempo*16){
    ultima_apnea = millis();
  }
}

void envia_dados(){  // envia "7+TAMANHO" bytes
    Serial.write(insp_flag); 
    Serial.write(insp_cont);
    Serial.write(exp_flag);
    Serial.write(exp_cont);
    Serial.write(apneia);
    Serial.write(apneia_grave);
    Serial.write(final);  
    
    for(int p = 0; p < TAMANHO; p++){
      int pos_envia = (p+posicao)%TAMANHO;
      Serial.write(vetor[pos_envia]);
    }
}


void loop(){
  byte charIn;                  // cria uma variavel para armazenar o caractere recebido

  char comando = '1';
  if(Serial.available()){       // verifica se recebeu algo pela serial
    charIn = Serial.read();    // le o caractere recebido
    if(charIn=='1'){
      coleta = true;
      envia_dados();
    }
    else if(charIn=='0'){
      coleta = false;
    }
  }
  
  


  if (abs(millis()-ultima_medida)>100){
    ultima_medida = millis();


    int valor = analogRead(analogInPin);// cria uma variavel para armazenar o caractere recebido
    float voltagem = valor*5.0/1023.0;

    if(inicial){
      inicial = false;
      media = voltagem;
    }

    else{
      media = media*0.65 + voltagem*0.35;

    }
    final = (50-((voltagem-media)*1000.0));
    
    vetor[posicao] = final;
    posicao = posicao + 1;
    
    if(posicao>=TAMANHO) posicao = 0;



    if (final < 30){
      insp_flag = 0;
      exp_flag = 1;
      exp_cont = 0;
      tmp_exp = 0;
      digitalWrite(7, LOW);
    }
    else if( final > 70){
      insp_flag = 1;cd
      exp_flag = 0;
      insp_cont = 0;
      tmp_insp = 0;
      digitalWrite(7, LOW);
    }

    if (insp_flag == 1){
      insp_cont +=1;
    }
    if (exp_flag == 1){
      exp_cont += 1;
    }
    if (insp_cont > TEMPO_APNEA && tmp_insp ==0){
      digitalWrite(7, HIGH);
      apneia = apneia + 1;
      tmp_insp = 1;
    }
    if (exp_cont > TEMPO_APNEA && tmp_exp ==0){
      digitalWrite(7, HIGH);
      apneia = apneia + 1;
      tmp_exp = 1;
    }
    if ((insp_cont > TEMPO_G_APNEA || exp_cont > TEMPO_G_APNEA) && apnea_flag==false){
      //delay(1000);
      apneia_grave = apneia_grave + 1;
      apnea_flag = true;
      ultima_apnea = millis();
    }
    else if (insp_cont <= TEMPO_G_APNEA && exp_cont <= TEMPO_G_APNEA){
      apnea_flag = false;
    }

    if (apnea_flag){
      toca(millis()-ultima_apnea);
    }
    
    Serial.print("IF:"); 
    Serial.print(apnea_flag); 
    
    coleta = false;
  }

  delay(10);     

}



