#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
  int serial_port = open("/dev/ttyACM0", O_RDWR);  // Serielle Schnittstelle öffnen (passen Sie den Pfad entsprechend an)

  struct termios tty;
  memset(&tty, 0, sizeof(tty));

  // Serielle Schnittstellenkonfiguration
  tty.c_cflag = B9600;  // Baudrate
  tty.c_cflag |= CS8;   // 8 Datenbits
  tty.c_cflag |= CLOCAL | CREAD;  // Lokale Verbindung, Empfang aktivieren

  tcsetattr(serial_port, TCSANOW, &tty);  // Konfiguration anwenden

  char buf[255];
  while (1) {
    ssize_t len = read(serial_port, &buf, sizeof(buf));  // Daten von der seriellen Schnittstelle lesen
    if (len > 0) {
      buf[len] = '\0';
      printf("%s\n", buf);
    }
  }

  close(serial_port);
  return 0;
}
