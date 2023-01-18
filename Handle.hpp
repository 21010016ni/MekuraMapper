#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class Handle
{
public:
	enum class type :char
	{
		graph,
		sound,
		font,
	};

private:
	struct Data
	{
		type t;
		int handle;

	public:
		int duration;

		Data(type t, int handle, int duration) :t(t), handle(handle), duration(duration) {}
		~Data();
		constexpr int get()const noexcept { return handle; }
	};

	static inline std::unordered_map<std::u8string, std::unique_ptr<Data>> handle;

public:
	static void update();
	static int get(const std::u8string& key, type t, int value = 3600);
};

