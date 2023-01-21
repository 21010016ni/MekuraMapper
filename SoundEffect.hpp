#pragma once

class SoundEffect
{
	struct Data
	{
		int handle;
		short pan;
		char volume;

		void Play();
	};
};

