#include "helpers.h"

/* Converts the mode_t value to a human-readable string like 'drwxrwxrwx'
 */
void str_file_mode(mode_t mode, unsigned char type, char *str) {
    str[0] = (type == 4) ? 'd' : '-'; /* directory */
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = 0;
}

/* Converts the timespec value to a human-readable string
 */
int str_timespec(struct timespec const *ts, char *str, size_t len) {
    struct tm t;
    tzset();

    if (localtime_r(&(ts->tv_sec), &t) == NULL) {
        return 1;
    }

    if (strftime(str, len, "%F %T", &t) == 0) {
        return 1;
    }

    return 0;
}

/* Returns the number of columns of a given width that can fit in the terminal
 */
int get_columns_count(unsigned column_width) {
    struct winsize ws;
    int terminal_width;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0) {
        terminal_width = 0;
    }
    else {
        terminal_width = ws.ws_col;
    }

    int columns_count = terminal_width / column_width;
    return columns_count ? columns_count : 1;
}
