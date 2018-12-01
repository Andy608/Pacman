#include "SettingsFile.h"
#include <fstream>
#include <iostream>

SettingsFile::SettingsFile(std::string fileSrc)
{
	mFileSource = fileSrc;

	std::ifstream readStream;
	readStream.open(fileSrc, std::ifstream::in);

	if (readStream.is_open())
	{
		std::string line;
		unsigned int i;

		while (std::getline(readStream, line))
		{
			if (line.empty() || line.at(0) == '*')
			{
				continue;
			}

			for (i = 0; i < line.size(); ++i)
			{
				if (line.at(i) == '=')
				{
					mSettingsMap.insert(std::make_pair(line.substr(0, i), line.substr(i + 1)));
					std::cout << "Inserting Key: " << line.substr(0, i) << ", Value: " << line.substr(i + 1) << std::endl;
					break;
				}
			}
		}

		readStream.close();
	}
	else
	{
		std::cout << "Unable to read file: \'" << fileSrc << "\'";
	}
}

SettingsFile::~SettingsFile()
{

}

std::string SettingsFile::getSettingFromKey(std::string key)
{
	std::string value = "";
	std::map<std::string, std::string>::iterator iter = mSettingsMap.find(key);

	if (iter != mSettingsMap.end())
	{
		value = iter->second;
	}
	else
	{
		std::string s = "Could not find setting with key: \'" + key + "\'";
		std::cout << s << std::endl;
		throw std::exception(s.c_str());
	}

	return value;
}

std::string SettingsFile::getKeyFromSetting(std::string setting)
{
	bool isKeyFound = false;
	std::string key = "";
	std::map<std::string, std::string>::iterator iter;

	for (iter = mSettingsMap.begin(); iter != mSettingsMap.end(); ++iter)
	{
		if (iter->second == setting)
		{
			key = iter->first;
			isKeyFound = true;
		}
	}

	if (!isKeyFound)
	{
		std::string s = "Could not find key from setting: \'" + setting + "\'";
		std::cout << s << std::endl;
		throw std::exception(s.c_str());
	}

	return key;
}

void SettingsFile::clearFile() const
{
	std::ofstream oFile;

	oFile.open(mFileSource);

	if (oFile.is_open())
	{
		oFile.close();
	}
}

bool SettingsFile::isEmpty()
{
	std::ifstream iFile;
	iFile.open(mFileSource, std::ios::app);
	return iFile.peek() == std::ifstream::traits_type::eof();
}