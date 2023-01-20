#pragma once
#include <DxLib.h>
#include <unordered_map>
#include "Particle.hpp"
#include "Draw.hpp"

class Effect
{
	class Template
	{
		friend Effect;

		struct Shape
		{
			char type;
			unsigned char mode;
			short start;
			float preset[8];
			std::vector<uint32_t> func;

			// “_Aü
			Shape(char type, unsigned char mode, unsigned short start) :type(type), mode(mode), start(start)
			{
				for(int i = 0; i < 8; ++i)
					preset[i] = 0;
			}
			// ‰~
			Shape(char type, unsigned char mode, unsigned short start, int num, bool fill) :type(type), mode(mode), start(start)
			{
				for(int i = 0; i < 8; ++i)
					preset[i] = 0;
				preset[5] = static_cast<float>(fill);
				preset[6] = static_cast<float>(num);
			}
			// ‘½ŠpŒ`
			Shape(char type, unsigned char mode, unsigned short start, int num) :type(type), mode(mode), start(start)
			{
				for(int i = 0; i < 8; ++i)
					preset[i] = 0;
				preset[6] = static_cast<float>(num);
			}
		};

		short duration;
		std::vector<std::unique_ptr<Shape>> shape;

	public:
		Template() :duration(0) {}
		Template(int duration) :duration(duration) {}
	};

	static inline std::unordered_map<int, Template> data;

public:
	class Instance :public Snowflake
	{
		// ‚±‚Ì•Ó‚É}Œ`‚Æ‚»‚ÌŠÖ”‚ğ‚µ‚Ü‚¢‚±‚Ş\‘¢‘Ì
		struct Shape
		{
			char type;
			unsigned char mode;
			short start;
			float buffer[8];
			std::vector<uint32_t> func;

			Shape(char type, unsigned char mode, short start, float pre[8], const std::vector<uint32_t>& func)
				:type(type), mode(mode), start(start), func(func)
			{
				for(int i = 0; i < 8; ++i)
					buffer[i] = pre[i];
			}
		};

		Draw d;
		int t;
		std::vector<Shape> shape;

	public:
		Instance(int x, int y, const Template& temp);
		void update()override;
		void draw()const override;
	};

	static int load(const char* FileName);
	static void TestWrite();
	static const Template& get(int handle)
	{
		auto i = data.find(handle);
		if(i == data.end())
			throw;
		return i->second;
	}

	static void emit(float x, float y, int handle);

	static void erase(int handle)
	{
		data.erase(handle);
	}
};

