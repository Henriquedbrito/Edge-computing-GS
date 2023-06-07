#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);//pinos de leitura do lcd
float valor_potencia;
int backLight = 13;  
int umidade;//recebe do sensor os valores 
int motorPin =6;//pino do motor
int motorState = 1;//estado do motor
int sensorPin = A1;//pino do sensor de temperatura
const int trigger=5; //pino de saida do sensor de distancia
const int echo=4; //pino de entrada do sensor de distancia
float dist;//recebe valores do sensor de distancia
int motorPin2 =3;//pino do motor 2


//iniciondo o lcd, sensores e motores
void setup() {
  lcd.begin(19, 9);
  // inicia a tela
  pinMode(motorPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  //reconhece entrada do sensor ultrassonico
   pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  
  //limpa a tela
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); 
  lcd.begin(16,2);              
  lcd.clear(); 
          
 
  
}

  //setando a atuação dos sensores e motores
void loop() {
   digitalWrite(trigger,HIGH);   
  delayMicroseconds(100);        
  digitalWrite(trigger,LOW);      

  dist = pulseIn(echo,HIGH);     
  
  //setando mensagem para o sensor ultrasonico
  dist = dist/58;
  lcd.setCursor(0,0);// posição que ira imprimir na tela
  lcd.print ("Distancia = "); //mensagem que vai aparecer no lcd
  lcd.setCursor(0,1);// posição que ira imprimir na tela
  lcd.print (dist);
  lcd.print (" cm");
   if (dist < 50){//se for maior que 450 
  digitalWrite(motorPin2, LOW);//desliga motor
    
  if (umidade == analogRead(LOW)){
    digitalWrite(motorPin2, LOW);//desliga motor
  }    
  } else if (dist > 50){ 
    motorState = digitalRead(motorPin);  
     digitalWrite(motorPin2, HIGH);//liga motor
  } 
  
    delay (3000);

  
  //é definida uma variável para receber os valores do sensor
  float tmp = analogRead(sensorPin);
  
  //Converter a voltagem obtida pelo sensor em temperatura através do
  //da constantes utilizadas abaixo;
  float tmpCel = map(((tmp - 20) * 3.04), 0, 1023, -40, 125);

  //é defininida a primeira linha onde será iniciado o cursor 
  //e onde as primeiras linhas serão escritas
  lcd.setCursor(0, 0);// posição que ira imprimir na tela
  lcd.print(tmpCel); //LCD irá imprimir o valor obtido pelo sensor
  lcd.print(" \xDF" "C"); //Linha que irá imprimir o simbolo ASCII "º" e a unidade de medida
  
  /*
  Inicio de condicional:
  
  Se tmpCel for maior que 0:
  -imprima a palavra : "Perigo!!!"
  
  */
  if (tmpCel > 0){
    lcd.setCursor(0,1);// posição que ira imprimir na tela
    lcd.print("Perigo!");//mensagem que vai aparecer no lcd
    delay(1500);
    
  }else{
    /*
    SENÃO (caso a tmpcel seja menor que zero)
    -apague a mensagem e não imprima nada além do contador de temperatura
    
    */
    
  	lcd.setCursor(0,1);// posição que ira imprimir na tela
    lcd.print("temperatura ok");//mensagem que vai aparecer no lcd
    delay(1500);
  }
  
  umidade=analogRead(A0);
// define a entrada analogica na porta A01
  lcd.begin(16, 2);
 
  
  
  // Print a message to the LCD.
  
  lcd.setCursor(0, 0); // posição que ira imprimir na tela
  //lcd.print("PROJECT");
  delay(2000);
  lcd.setCursor(0, 1);//seta a posição do texto
  if (umidade < 450){//se for maior que 450 
  lcd.print("salinidade ok");//mensagem que vai aparecer no lcd
  lcd.setCursor(0, 0);//imprimi no inicio da tela
  digitalWrite(motorPin, LOW);//desliga motor
    
  if (umidade == analogRead(LOW)){
    digitalWrite(motorPin, LOW);//desliga motor
  }    
  } else if (umidade > 450){ 
    lcd.setCursor(0, 1);// posição que ira imprimir na tela
    lcd.print("salinidade alta");//mensagem que vai aparecer no lcd
    motorState = digitalRead(motorPin);  
     digitalWrite(motorPin, HIGH);//liga motor
   
  
  }
    
  delay(1500);
  lcd.clear();//limpa
  

  }