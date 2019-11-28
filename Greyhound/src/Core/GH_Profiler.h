#pragma once

#include <string>
#include <unordered_map>
#include <chrono>

/*
TODO:
 - Write to file
 - At the end of every frame, delete any non completed section for repeating sections
 - Add Optional Discriptions for sections

*/

class GH_Profiler
{
public:
	GH_Profiler() { um_profileSections = std::unordered_map < std::size_t, GH_ProfileSection>(); }
	~GH_Profiler() {}

	void begin_section(const char* sectionName)
	{
		auto nameHashed = std::hash<std::string>{}(sectionName);

		auto existingItem = um_profileSections.find(nameHashed);
		if (existingItem != um_profileSections.end()) return;

		auto begin = std::chrono::high_resolution_clock::now();

		GH_ProfileSection new_section = {};
		new_section.sectionName = sectionName;
		new_section.m_startTime = begin;
		new_section.m_endTime = std::chrono::steady_clock::time_point();

		um_profileSections.insert({ nameHashed, new_section });
	}

	void end_section(const char* sectionName)
	{
		auto nameHashed = std::hash<std::string>{}(sectionName);

		auto existingItem = um_profileSections.find(nameHashed);
		if (existingItem == um_profileSections.end()) return;

		auto end = std::chrono::high_resolution_clock::now();

		existingItem->second.m_endTime = end;
	}

	long get_duration_of_section(const char* sectionName)
	{
		auto nameHashed = std::hash<std::string>{}(sectionName);

		auto existingItem = um_profileSections.find(nameHashed);
		if (existingItem == um_profileSections.end()) return;

		auto duration = existingItem->second.m_endTime - existingItem->second.m_startTime;

		return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	}

private:
	struct GH_ProfileSection
	{
		const char* sectionName;

		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
	};

	std::unordered_map<std::size_t, GH_ProfileSection> um_profileSections;
};
