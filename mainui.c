#include "./includes/mainui.h"

#define TOPWINHEIGHT 5

WINDOW *_topWin, *_bottomWin, *_smallWin;
PANEL *_topPanel, *_bottomPanel, *_smallPanel;

void initUI()
{
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    refresh();
    curs_set(0);
    initColor();
    initWin();
    initPanel();
    paintWindow();
}

void initColor()
{
    if (has_colors())
    {
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
        init_pair(2, COLOR_GREEN, COLOR_BLUE);
    }
}

void _paintBottomWindow(int maxy, int maxx)
{
    werase(_bottomWin);
    wresize(_bottomWin, maxy - TOPWINHEIGHT, maxx);
    mvwin(_bottomWin, maxy - TOPWINHEIGHT, 0);
    wattron(_bottomWin, COLOR_PAIR(2));
    box(_bottomWin, 0, 0);
    mvwhline(_bottomWin, 1, 2, '-', 21);
    mvwaddch(_bottomWin, 1, 1, '[');
    mvwaddch(_bottomWin, 1, 23, ']');
    mvwaddstr(_bottomWin, 1, 24, "(???%)");
    mvwaddstr(_bottomWin, 1, 30, "(0:00:00)");
    mvwhline(_bottomWin, 2, 1, ':', 40 - 2);
    mvwaddstr(_bottomWin, 3, 1, "[ |< ]  [暂停]  [停止]  [ >| ]  [MUTE]");
    mvwprintw(_bottomWin, (maxy - TOPWINHEIGHT) / 2, 1, "%d列", maxx);
    wattroff(_bottomWin, COLOR_PAIR(2));
    wnoutrefresh(_bottomWin);
}

void _paintTopWindow(int maxy, int maxx)
{
    werase(_topWin);
    wresize(_topWin, TOPWINHEIGHT, maxx);
    mvwin(_topWin, 0, 0);
    wattron(_topWin, COLOR_PAIR(1));
    wattron(_topWin, A_BOLD);
    mvwprintw(_topWin, TOPWINHEIGHT / 2, 1, "%d行", maxy);
    box(_topWin, 0, 0);
    wattroff(_topWin, COLOR_PAIR(1));
    wattroff(_topWin, A_BOLD);
    wnoutrefresh(_topWin);
}

void _paintSmallWindow(int maxy, int maxx)
{
    werase(_smallWin);
    mvwin(_smallWin, 0, 0);
    wresize(_smallWin, maxy, maxx);
    mvwprintw(_smallWin, maxy / 2, (maxx - strlen("窗口过小无法显示,请拉大终端")) / 2, "窗口过小无法显示,请拉大终端。");
    wnoutrefresh(_smallWin);
}

void paintWindow()
{
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    refresh();
    if (maxy < TOPWINHEIGHT + 5)
    {
        show_panel(_smallPanel);
        hide_panel(_topPanel);
        hide_panel(_bottomPanel);
        _paintSmallWindow(maxy, maxx);
    }
    else
    {
        hide_panel(_smallPanel);
        show_panel(_topPanel);
        show_panel(_bottomPanel);

        _paintTopWindow(maxy, maxx);
        _paintBottomWindow(maxy, maxx);
    }
    update_panels();
    doupdate();
}

void initWin()
{
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);

    _topWin = newwin(TOPWINHEIGHT, maxx, 0, 0);
    box(_topWin, 0, 0);
    wrefresh(_topWin);

    _bottomWin = newwin(maxy - TOPWINHEIGHT, maxx, TOPWINHEIGHT, 0);
    box(_bottomWin, 0, 0);

    wrefresh(_bottomWin);

    _smallWin = newwin(TOPWINHEIGHT, maxx, 0, 0);
    wrefresh(_smallWin);
}

void initPanel()
{
    _topPanel = new_panel(_topWin);
    _bottomPanel = new_panel(_bottomWin);
    _smallPanel = new_panel(_smallWin);
    hide_panel(_smallPanel);
    show_panel(_topPanel);
    show_panel(_bottomPanel);
    update_panels();
    doupdate();
}

void _command(int nCmd)
{
    switch (nCmd)
    {

    case eUCMute:
    {
        wattron(_bottomWin, COLOR_PAIR(1));
        mvwaddstr(_bottomWin, 3, 34, "MUTE");
        wrefresh(_bottomWin);
        wattroff(_bottomWin, COLOR_PAIR(1));

        usleep(200 * 1000);
        wattron(_bottomWin, COLOR_PAIR(2));

        mvwaddstr(_bottomWin, 3, 34, "MUTE");
        wattroff(_bottomWin, COLOR_PAIR(2));
        wrefresh(_bottomWin);
    }
    break;
    }
}

void MouseHint(MEVENT *event)
{
    if (!event)
    {
        return;
    }

    wattron(_topWin, COLOR_PAIR(1));
    mvwprintw(_topWin, 2, 1, "鼠标点击了第%d行，第%d列", event->y, event->x);
    wattroff(_topWin, COLOR_PAIR(1));
    wrefresh(_topWin);

    int x = event->x;
    int y = event->y;
    if (y == 8)
    {
        if (x >= 34 && x <= 37)
        {
            _command(eUCMute);
        }
    }
}

void inputLoop()
{
    int c;
    while ((c = getch()) != 'q')
    {

        switch (c)
        {
        case ',':
        {
            _command(eUCMute);
        }
        break;
        case '.':
        {
            _command(eUCNext);
        }
        case KEY_MOUSE:
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                if ((event.bstate & BUTTON1_CLICKED) || (event.bstate & BUTTON1_DOUBLE_CLICKED))
                {
                    MouseHint(&event);
                }
            }
        }
        break;
        }
    }
}