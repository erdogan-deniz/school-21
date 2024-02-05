// Necessary libraries:
#include <stdio.h>
#include <time.h>

// For that .py file can find function:
int monotonic(void);

// The main function:
int monotonic(void) {

    time_t MyTime = time(NULL);
    struct tm *now = localtime(&MyTime);

    printf("%llu\n",
        (long long int)((now->tm_year - 1970) * 365 * 24 * 60 * 60) +
        (long long int)(now->tm_yday * 24 * 60 * 60) +
        (long long int)(now->tm_hour * 3600) +
        (long long int)(now->tm_min * 60) +
        (long long int)(now->tm_sec)
    );

    return 0;
}
