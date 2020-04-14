#include "timer.h"

void timer_start() {
	s_timer.isRunning = true;
	s_timer.startTime = std::chrono::high_resolution_clock::now();
}

void timer_stop() {
	s_timer.isRunning = false;
	s_timer.endTime   = std::chrono::high_resolution_clock::now();
}

float timer_get() {
	std::chrono::duration<float> duration =
		std::chrono::high_resolution_clock::now() - s_timer.startTime;
	return duration.count();
}

