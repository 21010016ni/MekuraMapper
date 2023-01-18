#include "Handle.hpp"
#include <DxLib.h>
#include <stdexcept>
#include "convert_string.hpp"

void Handle::update()
{
	for (auto i = handle.cbegin(); i != handle.cend();)
	{
		if (i->second->duration != -1)
		{
			if (i->second->duration <= 0)
			{
				i = handle.erase(i);
				continue;
			}
			else
				--i->second->duration;
		}
		++i;
	}
}

int Handle::get(const std::u8string& key, type t, int value)
{
	if(key.empty())
		return -1;
	auto i = handle.find(key);
	if (i == handle.cend())
	{
		int buf = -1;
		switch(t)
		{
		case type::graph:
			buf = LoadGraph(ext::to<TCHAR>(key));
			break;
		case type::sound:
			buf = LoadSoundMem(ext::to<TCHAR>(key));
			break;
		case type::font:
			buf = LoadFontDataToHandle(ext::to<TCHAR>(key));
			break;
		}
		if(buf != -1)
			handle.emplace(key, new Data(t, buf, value));
		else
		{
			std::u8string tn = u8"undefined";
			switch(t)
			{
			case type::graph:
				tn = u8"graph";
				break;
			case type::sound:
				tn = u8"sound";
				break;
			case type::font:
				tn = u8"font";
				break;
			}
			LogFileAdd(ext::to<TCHAR>(u8"“ÇžŽ¸”s " + key + u8" : " + tn));
		}
		return buf;
	}
	else
	{
		i->second->duration = value;
		return i->second->get();
	}
}

Handle::Data::~Data()
{
	switch (t)
	{
	case type::graph:
		DeleteGraph(handle);
		break;
	case type::sound:
		DeleteSoundMem(handle);
		break;
	case type::font:
		DeleteFontToHandle(handle);
		break;
	}
}

