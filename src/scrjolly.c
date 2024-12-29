#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  initscr();
  curs_set(0);
  noecho();
  timeout(0);
  start_color();

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);

  int done = 0;
  
  int particles[100][2] = {0};
  char message[128] = "we are so jolly";
  int delay = 100000;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      printf("scrjolly\n");
      printf("-h: Show this message and exit\n");
      printf("-d <int>: Set delay between frames (Default = 100000)\n");
      printf("-m <string>: Set message (Default = \'we are so jolly\')\n");
      done = 1;
    }

    if (strcmp(argv[i], "-d") == 0) {
      delay = atoi(argv[i + 1]);
    }

    if (strcmp(argv[i], "-m") == 0) {
      strncpy(message, argv[i + 1], 128);
    }
  }

  for (int i = 0; i < 100; i++) {
    particles[i][0] = -(rand() % LINES);
    particles[i][1] = rand() % COLS;
  }

  while (!done) {
    clear();

    for (int i = 0; i < 100; i++) {
      particles[i][0] += 1;
      particles[i][1] += rand() % 3 - 1;

      particles[i][0] = (particles[i][0] > LINES) ? 0 : particles[i][0];

      particles[i][1] = (particles[i][1] < 0) ? COLS : particles[i][1];
      particles[i][1] = (particles[i][1] > COLS) ? 0 : particles[i][1];
      
      if (rand() % 3 == 0) {
        attron(COLOR_PAIR(1));
      } else if (rand() % 3 == 1) {
        attron(COLOR_PAIR(2));
      }

      mvaddch(particles[i][0], particles[i][1], '*');
      
      attroff(COLOR_PAIR(1) | COLOR_PAIR(2));
    }

    for (int x = 0; x < strlen(message) + 4; x++) {
      for (int y = 0; y < 3; y++) {
        mvaddch(y + LINES / 2 - 1, x + COLS / 2 - strlen(message) / 2 - 2, ' ');
      }
    }

    for (int i = 0; i < strlen(message); i++) {
      if (rand() % 3 == 0) {
        attron(COLOR_PAIR(1));
      } else if (rand() % 3 == 1) {
        attron(COLOR_PAIR(2));
      }

      mvaddch(LINES / 2, COLS / 2 - strlen(message) / 2 + i, message[i]);

      attroff(COLOR_PAIR(1) | COLOR_PAIR(2));
    }

    usleep(delay);

    int input = getch();

    if (input == 'q') {
      done = 1;
    }
  }

  endwin();

  return 0;
}
