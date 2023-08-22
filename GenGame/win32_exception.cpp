#include "win32_exception.h"
#include <sstream>

win32_exception::win32_exception(int line, const char* file) noexcept
	: line(line), file(file)
{}

const char* win32_exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* win32_exception::GetType() const noexcept
{
	return "Gen Exception";
}

int win32_exception::GetLine() const noexcept
{
	return line;
}

const std::string& win32_exception::GetFile() const noexcept
{
	return file;
}

std::string win32_exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
