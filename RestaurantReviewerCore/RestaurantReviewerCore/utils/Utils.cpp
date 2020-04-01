#include "Utils.h"
#include "Constants.h"

#include <ShlObj.h>

#include <QDir>

using namespace toptal::utils;

Utils& Utils::instance()
{
	static Utils instance;
	return instance;
}

QString Utils::dataDirectory()
{
	wchar_t* publicDir = 0;
	SHGetKnownFolderPath(FOLDERID_Public, 0, nullptr, &publicDir);
	
	return QString::fromWCharArray(publicDir);
}

bool Utils::initPublicFolder()
{
	const QString publicFolderName = dataDirectory() + kDirSeparator + kDataFolderName;

	QDir dir(publicFolderName);

	if (!dir.exists())	
	{
		// Create folder if it doesn't exist
		if (!QDir().mkdir(publicFolderName))
			return false;
	}

	return true;
}
