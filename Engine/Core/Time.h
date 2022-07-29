#pragma once
#include <chrono>

namespace neu 
{
	class Time
	{
	public:
		Time() : startTimePoint_{ clock::now() }, frameTimePoint_{ clock::now() } {}
	
		void Tick();
		void Reset() { startTimePoint_ = clock::now(); }

		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

		float deltaTime = 0;
		float time = 0;


	private:

		clock::time_point startTimePoint_;
		clock::time_point frameTimePoint_;
	
	};
}