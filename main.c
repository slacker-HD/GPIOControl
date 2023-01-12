#include "./includes/main.h"
#include "./includes/mainui.h"

void sig_winch(int signum)
{
    endwin();
    refresh();
    paintWindow();
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    signal(SIGWINCH, sig_winch);
    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    refresh();
    curs_set(0);
    initColor();
    initWin();
    initPanel();
    paintWindow();
    while (1)
    {
        int c = fgetc(stdin);
        if (c == 'q')
        {
            break;
        }
    }
    endwin();
    return 0;
}
