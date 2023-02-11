#include "./includes/main.h"
#include "./includes/mainui.h"
#include "./includes/GPIOact.h"
void sig_winch(int signum)
{
    endwin();
    refresh();
    paintWindow();
}

int main(int argc, char *argv[])
{
    initUI();
    signal(SIGWINCH, sig_winch);
    inputLoop();
    endwin();
    return 0;
}
