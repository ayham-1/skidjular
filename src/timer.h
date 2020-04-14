#ifndef TIMER_H
#define TIMER_H

#include <atomic>
#include <chrono>

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::chrono::time_point<std::chrono::steady_clock> endTime;

	bool isRunning = false;
};

static Timer s_timer;

void  timer_start();
void  timer_stop();
float timer_get();

#endif
