#pragma once

#include <cstdio>
#include <Windows.h>

namespace TimerNamespace {

	struct Timer {
		void Start();
		void Stop();
		double Time();
		void Print(const char* str);
	private:
		LARGE_INTEGER begin, end, frequency;
	};
}
