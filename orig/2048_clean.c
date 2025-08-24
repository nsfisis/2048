#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define waddstr_(text) waddstr(main_window, text)
#define waddch_(ch) waddch(main_window, ch)
#define wprintw_(format, data) wprintw(main_window, format, data)
#define newline waddch_('\n')

#define repeat(i, n) for (int i = 0; i < n; ++i)

#define get_tile_at(k) (grid + y * ((x + size) % (size + 1) + k * x) + (size + 1 - y) * i)

WINDOW *main_window;
char *message = "\0";
int size, num_rows, num_columns, new_tile_pos, num_empty_slots, changed, last_empty_tile_index, *last_non_empty_tile,
    *this_tile, grid_buf[128], *grid = grid_buf;

void draw_frame_1() {
    waddch_('+');
    repeat(i, 8 * size - 1) {
        waddch_('-');
    }
    waddch_('+');
    newline;
}

void draw_frame_2() {
    waddch_('|');
    repeat(i, size) {
        repeat(j, 8) {
            waddch_(32);
        }
        waddch_('\b');
        waddch_('|');
    }
    newline;
}

void show_grid() {
    draw_frame_1();
    repeat(i, size) {
        draw_frame_2();

        waddstr_("| ");
        repeat(j, size) {
            if (!*grid) {
                waddstr_("      | ");
            } else if (*grid >= 1024) {
                wprintw_(" %2dk  | ", *grid / 1024);
            } else {
                wprintw_("%4d  | ", *grid);
            }
            ++grid;
        }
        newline;

        draw_frame_2();

        if (i < size - 1) {
            waddch_('|');
            repeat(j, size) {
                repeat(j, 8) {
                    waddch_('-');
                }
                waddch_('\b');
                if (j < size - 1) {
                    waddch_('+');
                }
            }
            waddch_('|');
            newline;
        }
    }
    draw_frame_1();
    grid -= size * size;
}

int move_grid(int x, int y, int do_change) {
    changed = 0;
    repeat(i, size) {
        last_empty_tile_index = 0;
        last_non_empty_tile = 0;
        repeat(j, size) {
            this_tile = get_tile_at(j);
            if (*this_tile) {
                if (last_non_empty_tile && *this_tile == *last_non_empty_tile) {
                    if (do_change) {
                        *last_non_empty_tile *= 2;
                        *this_tile = 0;
                    }
                    last_non_empty_tile = 0;
                    changed = 1;
                } else {
                    last_non_empty_tile = get_tile_at(last_empty_tile_index);
                    if (do_change) {
                        *last_non_empty_tile = *this_tile;
                    }
                    ++last_empty_tile_index;
                }
            }
        }
        for (; last_empty_tile_index < size; ++last_empty_tile_index) {
            this_tile = get_tile_at(last_empty_tile_index);
            changed |= *this_tile;
            if (do_change) {
                *this_tile = 0;
            }
        }
    }
    return !changed;
}

void put_new_tile() {
    num_empty_slots = 0;
    repeat(i, size * size) {
        if (!grid[i]) {
            ++num_empty_slots;
        }
    }
    if (num_empty_slots == 0) {
        return;
    }
    new_tile_pos = rand() % num_empty_slots;
    repeat(i, size * size) {
        if (!grid[i] && --num_empty_slots == new_tile_pos) {
            grid[i] = rand() % 8 ? 2 : 4;
        }
    }
}

int main(int argc, char **argv) {
    srand(time(0));

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, num_rows, num_columns);

    size = argc > 1 ? (*argv[1] - '0') : 4;
    if (size <= 1 || size > 8) {
        message = "\1Invalid size given.\n";
        goto quit;
    }

    main_window = newwin(0, 0, (num_rows - 4 * size) / 2, (num_columns - 8 * size) / 2);
    if (!main_window) {
        message = "\1Terminal too small.\n";
        goto quit;
    }

    put_new_tile();
    put_new_tile();

    while (1) {
        wclear(main_window);
        show_grid();
        waddstr_("  h,j,k,l: move         q: quit");
        wrefresh(main_window);

        switch (wgetch(main_window)) {
        case 'q':
            goto quit;

        case 'h':
            move_grid(1, 1, 1);
            goto move_end;
        case 'j':
            move_grid(-1, size, 1);
            goto move_end;
        case 'k':
            move_grid(1, size, 1);
            goto move_end;
        case 'l':
            move_grid(-1, 1, 1);
            goto move_end;

        move_end:
            if (changed) {
                put_new_tile();
            }
            if (move_grid(1, 1, 0) & move_grid(-1, 1, 0) & move_grid(1, size, 0) & move_grid(-1, size, 0)) {
                message = "\0Game over.\n";
                goto quit;
            }
            usleep(2048 * 8);
            break;
        }
    }

quit:
    if (main_window) {
        delwin(main_window);
    }
    endwin();

    fputs(message + 1, stderr);
    return *message;
}
