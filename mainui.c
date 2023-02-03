#include "./includes/mainui.h"

#define TOPWINHEIGHT 5

WINDOW *_topWin, *_bottomWin, *_smallWin;
PANEL *_topPanel, *_bottomPanel, *_smallPanel;

void initColor()
{
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);
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

        werase(_smallWin);
        mvwin(_smallWin, 0, 0);
        wresize(_smallWin, maxy, maxx);
        mvwprintw(_smallWin, maxy / 2, (maxx - strlen("窗口过小无法显示,请拉大终端")) / 2, "窗口过小无法显示,请拉大终端。");
        wnoutrefresh(_smallWin);
    }
    else
    {
        hide_panel(_smallPanel);
        show_panel(_topPanel);
        show_panel(_bottomPanel);

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

        werase(_bottomWin);
        wresize(_bottomWin, maxy - TOPWINHEIGHT, maxx);
        mvwin(_bottomWin, maxy - TOPWINHEIGHT, 0);
        wattron(_bottomWin, COLOR_PAIR(2));
        box(_bottomWin, 0, 0);

        mvwprintw(_bottomWin, (maxy - TOPWINHEIGHT) / 2, 1, "%d列", maxx);
        wattroff(_bottomWin, COLOR_PAIR(2));
        wnoutrefresh(_bottomWin);
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
