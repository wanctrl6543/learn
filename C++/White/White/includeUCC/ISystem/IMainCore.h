#ifndef PL_MAINCORE_H_20120203
#define PL_MAINCORE_H_20120203

#include <string>
#include <vector>

#define PluginCore_API __declspec(dllexport)

extern "C"
{
	// ����ں˵����
	PluginCore_API int MainCore(const std::vector<std::string>& vecArgs);
}


#endif