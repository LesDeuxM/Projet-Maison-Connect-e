int buzzer =13;// Borne de sortie

void setup()
{
pinMode(buzzer,OUTPUT);// Définir la sortie du buzzer
}

void loop(){
    tone(buzzer,500,600);
    delay(150);
    tone(buzzer,700,500);
    delay(120);
    tone(buzzer,900,500);
    delay(700);
}
