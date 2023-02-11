#include "./includes/main.h"
#include "./includes/mainui.h"
#include "./includes/GPIOact.h"

void sig_winch(int signum)
{
    endwin();
    refresh();
    PaintWindow();
}

int main(int argc, char *argv[])
{
    InitUI();
    PaintWindow();
    signal(SIGWINCH, sig_winch);
    InputLoop();
    endwin();
    return 0;
}
