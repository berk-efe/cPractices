#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct SnakeBlockStruct {
  int x, y;
  struct SnakeBlockStruct *next;
  struct SnakeBlockStruct *prev;
} SnakeBlock;

typedef struct SnakeStruct {
  int length;
  SnakeBlock *head;
  SnakeBlock *tail;
} Snake;

void draw_snake(WINDOW *p_win, Snake *p_snake);
void spawn_apples(WINDOW *p_win);

int main(void) {
  int ch;

  int apples = 0;

  // West, East, North, South
  // North as default.
  char DIR = 'N';
  bool running = true;

  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  // enable non-blocking mode on getch()
  nodelay(stdscr, TRUE);
  // draw box for default win
  box(stdscr, 0, 0);

  Snake snake;

  // Allocate all initial blocks on the HEAP
  SnakeBlock *tail = (SnakeBlock *)malloc(sizeof(SnakeBlock));
  SnakeBlock *block = (SnakeBlock *)malloc(sizeof(SnakeBlock));
  SnakeBlock *head = (SnakeBlock *)malloc(sizeof(SnakeBlock));

  // Check for allocation failure
  if (tail == NULL || block == NULL || head == NULL) {
    endwin();
    printf("Failed to allocate initial snake memory\n");
    return 1;
  }

  // Initialize head
  head->x = COLS / 2;
  head->y = LINES / 2;
  head->next = block;
  head->prev = NULL;

  // Initialize block
  block->x = COLS / 2;
  block->y = (LINES / 2) + 1;
  block->next = tail;
  block->prev = head;

  // Initialize tail
  tail->x = COLS / 2;
  tail->y = (LINES / 2) + 2;
  tail->next = NULL;
  tail->prev = block;

  // Set the main snake pointers
  snake.length = 3;
  snake.head = head;
  snake.tail = tail;

  spawn_apples(stdscr);

  int counter = 0;
  WINDOW *log_win = newwin(6, 32, 0, 0);
  box(log_win, 0, 0);
  while (running) {
    ch = getch();

    if (ch != ERR) {
      switch (ch) {
      case 'q':
        running = false;
        break;
      case KEY_LEFT:
        if (DIR != 'E')
          DIR = 'W';
        break;
      case KEY_RIGHT:
        if (DIR != 'W')
          DIR = 'E';
        break;
      case KEY_UP:
        if (DIR != 'S')
          DIR = 'N';
        break;
      case KEY_DOWN:
        if (DIR != 'N')
          DIR = 'S';
        break;
      }
    }

    mvwprintw(log_win, 1, 1, "Direction: %c", DIR);
    mvwprintw(log_win, 2, 1, "Counter: %d", counter);
    mvwprintw(log_win, 3, 1, "Apples: %d", apples);
    wrefresh(log_win);

    napms(10);
    counter++;

    if (counter == 10) {
      // step forward the snake

      SnakeBlock *new_head_ptr = (SnakeBlock *)malloc(sizeof(SnakeBlock));

      if (new_head_ptr == NULL) {
        return 1;
      }

      new_head_ptr->x = snake.head->x;
      new_head_ptr->y = snake.head->y;
      new_head_ptr->next = snake.head;
      new_head_ptr->prev = NULL;

      snake.head->prev = new_head_ptr;
      snake.head = new_head_ptr;

      switch (DIR) {
      case 'W':
        snake.head->x--;
        break;
      case 'E':
        snake.head->x++;
        break;
      case 'N':
        snake.head->y--;
        break;
      case 'S':
        snake.head->y++;
        break;
      }

      int next_tile_y = snake.head->y;
      int next_tile_x = snake.head->x;

      chtype next_tile_ch = mvinch(next_tile_y, next_tile_x);
      char next_tile_char = next_tile_ch & A_CHARTEXT;

      if (next_tile_char == '*') {
        snake.length++;
        apples++;
        spawn_apples(stdscr);

      } else {

        SnakeBlock *old_tail = snake.tail;
        mvwaddch(stdscr, old_tail->y, old_tail->x, ' ');

        SnakeBlock *new_tail = old_tail->prev;
        if (new_tail != NULL) {
          new_tail->next = NULL;
        }
        snake.tail = new_tail;
        free(old_tail);
      }

      // draw the snake
      draw_snake(stdscr, &snake);
      counter = 0;
    }

    refresh();
  }

  delwin(log_win);
  endwin();
  return 0;
}

void draw_snake(WINDOW *p_win, Snake *p_snake) {
  SnakeBlock *cur_snake_block = p_snake->head;
  int count = 0;
  while (cur_snake_block != NULL) {
    mvwaddch(p_win, cur_snake_block->y, cur_snake_block->x, '#');
    cur_snake_block = cur_snake_block->next;
    count++;
  }

  wrefresh(p_win);
}

void spawn_apples(WINDOW *p_win) {
  // there is a bug here,
  // apples can spawn on bottom or top borders.
  srand(time(NULL));
  int x_cord = (rand() % COLS - 1) + 1; // 1-maxX (not incl the last col)
  srand(time(NULL));
  int y_cord = (rand() % LINES - 7) + 7; // 7-maxY (not including the last line)

  char apple_ch = '*';

  mvwaddch(p_win, y_cord, x_cord, apple_ch);
}
