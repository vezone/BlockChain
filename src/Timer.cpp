#include "Timer.h"

namespace TimerNamespace {

	void Timer::Start() {
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&begin);
	}

	void Timer::Stop() {
		QueryPerformanceCounter(&end);
	}

	double Timer::Time() {
		return ((double)(end.QuadPart - begin.QuadPart) / (double)frequency.QuadPart);
	}

	void Timer::Print(const char* str) {
		printf("Time(%s): %f\n", str, Time());
	}

}
