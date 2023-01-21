#include "SoundEffect.hpp"
#include <DxLib.h>

void SoundEffect::Data::Play()
{
	ChangeNextPlayPanSoundMem(pan, handle);
	ChangeNextPlayVolumeSoundMem(volume, handle);
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);
}

