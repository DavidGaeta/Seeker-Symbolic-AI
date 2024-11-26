#include <Servo.h>

// Pines del sensor HC-SR501
const int pirPin = 8; 

// Pines del sensor HC-SR04
const int trigPin = 7;
const int echoPin = 6;

// Pines de los servos
const int servoXPin = 9;  // Movimiento horizontal
const int servoYPin = 10; // Movimiento vertical

// Pin del zumbador
const int buzzerPin = 12;

// Crear objetos servo
Servo servoX;
Servo servoY;

// Variables
bool movimientoDetectado = false;
long distancia = 0;

// Función para medir distancia
long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duracion = pulseIn(echoPin, HIGH);
  long distancia = duracion * 0.034 / 2; // Convertir a cm
  return distancia;
}

// Configuración inicial
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  servoX.write(90); // Posición inicial horizontal
  servoY.write(90); // Posición inicial vertical

  Serial.begin(9600);
}

// Loop principal
void loop() {
  movimientoDetectado = digitalRead(pirPin);

  if (movimientoDetectado) {
    Serial.println("Movimiento detectado");
    
    // Simular detección direccional (ajustar según posición real del PIR)
    int direccionX = random(45, 135); // Ángulo horizontal simulado
    int direccionY = random(60, 120); // Ángulo vertical simulado

    // Mover servos hacia la dirección detectada
    servoX.write(direccionX);
    servoY.write(direccionY);

    // Encender luz (puedes conectar un LED al servo o usar una salida separada)
    delay(1000); // Mantener la posición 1 segundo

    // Medir distancia con el HC-SR04
    distancia = medirDistancia();
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Activar alarma si está demasiado cerca
    if (distancia > 0 && distancia < 50) {
      digitalWrite(buzzerPin, HIGH); // Encender zumbador
      delay(1000);
      digitalWrite(buzzerPin, LOW); // Apagar zumbador
    }
  } else {
    // Regresar a posición inicial
    servoX.write(90);
    servoY.write(90);
    delay(500);
  }

  delay(100); // Pequeña espera entre lecturas
}
