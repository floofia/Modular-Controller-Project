//Serial Setup

void serial_setup(int baud)
{
Serial.begin(baud);
while (!Serial);             // Leonardo: wait for serial monitor
Serial.setTimeout(3000);
Serial.println("\nI2C Scanner and more!");
}
