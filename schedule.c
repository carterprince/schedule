#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100

int get_current_day() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return tm->tm_wday == 0 ? 6 : tm->tm_wday - 1;
}

void calculate_time_diff(int current_hour, int current_min, int current_sec, int activity_hour, int activity_min, int activity_sec, char *activity_name) {
    int seconds_till_activity = (activity_hour - current_hour) * 3600 + (activity_min - current_min) * 60 + (activity_sec - current_sec);

    if (seconds_till_activity < 0) {
        seconds_till_activity += 24 * 3600;
    }

    int hours = seconds_till_activity / 3600;
    int minutes = (seconds_till_activity % 3600) / 60;
    int seconds = seconds_till_activity % 60;

    printf("%02d:%02d:%02d %s\n", hours, minutes, seconds, activity_name);
}

int in_future(int current_hour, int current_min, int current_sec,
              int activity_hour, int activity_min, int activity_sec) {
    if (current_hour < activity_hour) {
        return 1;
    }
    if (current_hour == activity_hour) {
        if (current_min < activity_min) {
            return 1;
        }
        if (current_min == activity_min && current_sec <= activity_sec) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *file;
    char path[1000];
    snprintf(path, sizeof(path), "%s/.config/schedule.cfg", getenv("HOME"));
    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int current_day = get_current_day();
    int day_counter = 0;
    int current_hour, current_min, current_sec;
    int activity_hour, activity_min, activity_sec;
    char activity_name[MAX_LINE_LENGTH];
    
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    current_hour = tm_now->tm_hour;
    current_min = tm_now->tm_min;
    current_sec = tm_now->tm_sec;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strcmp(line, "\n") == 0) {
            day_counter++;
            continue;
        }

        if (day_counter == current_day) {
            sscanf(line, "%d:%d:%d:%99[^\n]", &activity_hour, &activity_min, &activity_sec, activity_name);
            
            if (in_future(current_hour, current_min, current_sec, 
                          activity_hour, activity_min, activity_sec)) {
                calculate_time_diff(current_hour, current_min, current_sec, 
                                    activity_hour, activity_min, activity_sec, activity_name);
                break;
            }
        }
    }

    if (feof(file)) {
        rewind(file);
        fgets(line, MAX_LINE_LENGTH, file);
	sscanf(line, "%d:%d:%d:%99[^\n]", &activity_hour, &activity_min, &activity_sec, activity_name);
        calculate_time_diff(current_hour, current_min, current_sec, activity_hour, activity_min, activity_sec, activity_name);
    }

    fclose(file);
    return 0;
}
