#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

#define TUNING_SPEED_SLOW  	30000
#define TUNING_SPEED_MIDDLE	7500
#define TUNING_SPEED_FAST       2000

/* baudrate settings (<asm/termbits.h>) */
#define BAUDRATE B115200

/* change this definition for the correct  */
#define PORT "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

volatile int STOP;

int main()
{
   int fd, c, res;
   struct termios oldtio, newtio;
   char buf[2];
   STOP = false;
   struct timeval oldTime, newTime;

   signal(SIGTSTP,SIG_IGN); /* disable ctrl-Z, because this command is used to center waterfall on twente websdr */

   /* Open modem device for reading and not as controlling tty
     because we don't want to get killed if linenoise sends CTRL−C. */
   fd = open(PORT, O_RDONLY | O_NOCTTY );
   if (fd <0) {
     perror(PORT); 
     exit(-1); 
   }

   tcgetattr(fd,&oldtio); /* save current serial settings */
   bzero(&newtio, sizeof(newtio)); /* clear struct for new  settings */

   /* BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
      CRTSCTS : output hardware flow control (only used if the cable has
      all necessary lines. See sect. 7 of Serial−HOWTO)
      CS8 : 8n1 (8bit,no parity,1 stopbit)
      CLOCAL : local connection, no modem contol
      CREAD : enable receiving characters */
   newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
   newtio.c_iflag = IGNPAR ; //| ICRNL;

   /* ICANON : enable canonical input disable all echo functionality, and don't send signals to calling program */
   newtio.c_lflag = ICANON;


   /* now clean the modem line and activate the settings for the  */
   tcflush(fd, TCIFLUSH);
   tcsetattr(fd,TCSANOW,&newtio);

   /* terminal settings done, now handle input In this example, inputting a 'z' at the beginning of a line will exit the program.*/
   while (!STOP) { /* loop until we have a terminating condition */      
      res = read(fd,buf,2);
      buf[res]='\0'; /* set end of string, so we can printf */
      printf("%s", buf);
      if (buf[0]=='z') { 
	STOP=true;
      }

       // frequency up
      if (buf[0]=='+') {
        gettimeofday(&newTime, 0);
        unsigned long microseconds = newTime.tv_usec - oldTime.tv_usec;

        if (microseconds>=TUNING_SPEED_SLOW) {  
	   system("xdotool key k");
        }
  
        if ( (microseconds>=TUNING_SPEED_MIDDLE) && (microseconds<TUNING_SPEED_SLOW) ) {
          system("xdotool key shift+k");
        }      

        if ( (microseconds>=TUNING_SPEED_FAST) && (microseconds<TUNING_SPEED_MIDDLE) ) {
          system("xdotool key ctrl+k");
        }    

        if (microseconds<TUNING_SPEED_FAST) {
          system("xdotool key alt+k");
        }       

	system("xdotool key ctrl+z"); // center waterfall
        gettimeofday(&oldTime, 0);
      }

      // frequency down
      if (buf[0]=='-') {
        gettimeofday(&newTime, 0);
        unsigned long microseconds = newTime.tv_usec - oldTime.tv_usec;

        if (microseconds>=TUNING_SPEED_SLOW) {  
	   system("xdotool key j");
        }
  
        if ( (microseconds>=TUNING_SPEED_MIDDLE) && (microseconds<TUNING_SPEED_SLOW) ) {
          system("xdotool key shift+j");
        }      

        if ( (microseconds>=TUNING_SPEED_FAST) && (microseconds<TUNING_SPEED_MIDDLE) ) {
          system("xdotool key ctrl+j");
        }    

        if (microseconds<TUNING_SPEED_FAST) {
          system("xdotool key alt+j");
        }
   
        system("xdotool key ctrl+z"); // center waterfall
        gettimeofday(&oldTime, 0);
      }

      // filter bandwidth narrower
      if (buf[0]=='w') {
        system("xdotool key w");
      }

      // filter bandwidth wider
      if (buf[0]=='W') {
        system("xdotool key shift+w");
      }

   }

   /* restore the old  settings */
   tcsetattr(fd,TCSANOW,&oldtio);
   close(fd);
}
