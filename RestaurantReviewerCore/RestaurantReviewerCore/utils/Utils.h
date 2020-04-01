#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace toptal
{
namespace utils
{
class Utils
{
public:
	static Utils&	instance();

					Utils(const Utils&) = delete;

	QString			dataDirectory();
	bool			initPublicFolder();

private:
					Utils() = default;
}; // class Utils

} } // toptal::platform

#endif // UTILS_H