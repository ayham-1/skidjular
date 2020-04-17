#include "timer.h"

void timer_start() {
	s_timer.isRunning = true;
	s_timer.startTime = std::chrono::steady_clock::now();
}

void timer_stop() {
	s_timer.isRunning = false;
	s_timer.endTime	  = std::chrono::steady_clock::now();
}

float timer_get() {
	if (!s_timer.isRunning)
		return 0;
	std::chrono::duration<float> duration =
		std::chrono::steady_clock::now() - s_timer.startTime;
	return duration.count();
}
