#include <Wire.h>               //librerias de pantalla LCD, Sensor de temperatura y RTC
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <RTClib.h>

#define lcdAddress 0x27  //configuracion de la lcd
#define filas 2
#define columnas 16
LiquidCrystal_I2C lcd(lcdAddress, columnas, filas);

OneWire ourWire(2);                   //configuracion de el sensor de temperatura
DallasTemperature sensors(&ourWire);

RTC_DS3231 rtc; //configuracion de el RTC

#define buzzer 3                          //configuracion del buzzer
#define salidab() pinMode(buzzer,OUTPUT)
#define ence() tone(buzzer,1000)
#define apag() noTone(buzzer)

#define bomba 4                           //configuracion de la bomba de agua
#define salidac() pinMode(bomba,OUTPUT)
#define enceb() digitalWrite(bomba,HIGH)
#define apagb() digitalWrite(bomba,LOW)

void setup() {

  Serial.begin(9600);                       //inicializacion del monitor serial

  lcd.init();       //inicializacion del LCD
  lcd.backlight();  //luz del fondo de la LCD

  sensors.begin();  //inicializacion del Sensor de calor
  
  rtc.begin();	//Inicializa el modulo RTC

 rtc.adjust(DateTime(__DATE__, __TIME__));	// funcion que permite establecer fecha y horario

 salidab(); //salida del buzzer

 salidac(); //salida de la bomba de agua

}

void loop() {

  sensors.requestTemperatures();              //configuracion de funcionamiento del sensor de calor
  float temp1 = sensors.getTempCByIndex(0);
  lcd.setCursor(0,1);
  lcd.print(temp1);
  lcd.print("C  ");
  

  DateTime tiempo = rtc.now();			// funcion que obtiene la hora de la fecha completa
  Serial.print(tiempo.hour());     /*muestra las horas, minutos y segundos en el monitor serial*/
  Serial.print(":");
  Serial.print(tiempo.minute());
  Serial.print(":");
  Serial.println(tiempo.second()); /**/
  lcd.print(tiempo.hour());        /*muestra las horas y minutos en el LCD*/
  lcd.print(":");				
  lcd.print(tiempo.minute());      /**/
  
  delay(100);

  if (tiempo.hour() ==12 && tiempo.minute() == 10 && tiempo.second() == 0){
    ence();
    delay(100);
    delay(5000);
  } else {
    apag();
  }

  if (tiempo.hour() ==12 && tiempo.minute() == 10 && tiempo.second() == 6){
    ence();
    delay(100);
    delay(5000);
  } else {
    apag();
  }

  if (tiempo.hour() ==12 && tiempo.minute() == 10 && tiempo.second() == 12){
    ence();
    delay(100);
    delay(5000);
  } else {
    apag();
  }
  
  if (tiempo.hour() == 12 && tiempo.minute() == 10 && tiempo.second() == 40) { /*if para que detecte a que hora, minuto y segundo empieza el funcionamiento de la bomba de agua*/
  apagb();
  lcd.setCursor(0,0);
  lcd.print("hora de regar");                     /**/
  delay(20000);
  lcd.clear();                                    /*limpia la primera fila del LCD*/ 
  } else{
    enceb();                                        /*apaga el funcionamiento de la bomba de agua*/
  }

}
