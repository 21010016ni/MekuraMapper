#pragma once
#include <list>
#include <memory>
#include "common.hpp"

#define RI(mn, mx) std::uniform_int_distribution{ mn,mx }(common::engine)
#define RF(mn, mx) std::uniform_real_distribution<float>{ mn,mx }(common::engine)

class Snowflake
{
protected:
	short duration;
	
	Snowflake(short duration) :duration(duration) {};

public:
	virtual Snowflake& operator--() { --duration; return *this; }
	virtual bool operator()()const { return duration > 0; }
	virtual void update() = 0;
	virtual void draw()const = 0;
};

class Emitter
{
protected:
	int spawnrate;

	Emitter(int spawnrate) :spawnrate(spawnrate) {}

public:
	virtual bool spawn() { return RI(0, spawnrate) == 0; }
	virtual std::unique_ptr<Snowflake> generate() = 0;
};

class Particle
{
	static inline std::list<std::unique_ptr<Snowflake>> snowflake;
	static inline std::list<std::unique_ptr<Emitter>> emitter;

public:
	template<class T, class... Args> static void emit(Args... args) { snowflake.emplace_back(new T(args...)); }
	template<class T, class... Args> static void set(Args... args) { emitter.emplace_back(new T(args...)); }
	static void update();
	static void draw();
};

