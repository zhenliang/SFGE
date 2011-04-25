#include "string_mgr.h"

#include <fstream>
#include <iostream>
#include <util\container.h>
#include <util\string.h>

bool StringManager::AddString(const std::string& key, const std::wstring& value,
							   const Font& font /*= Font::GetDefaultFont()*/, float size /*= 30.0f*/)
{
	return AddString(key, String(value, font, size));
}

bool StringManager::AddString(const std::string& key, const String& value)
{
	return util::Insert(strings_, Strings::value_type(key, value));
}

bool StringManager::AddStrings(const std::string& path)
{
	if (!path.empty())
	{
		const size_t MAX_KEY_LENGHT = 32;
		const size_t MAX_VAL_LENGHT = 1024;

		char key[MAX_KEY_LENGHT + 1] = {};
		char val[MAX_VAL_LENGHT + 1] = {};

		std::ifstream ifstream(path.c_str());
		if (ifstream.is_open())
		{
			std::cout<<path<<" :"<<std::endl;

			while (ifstream.get(key, MAX_KEY_LENGHT, ' '))
			{
				ifstream.ignore();
				ifstream.getline(val, MAX_VAL_LENGHT, '\n');

				std::wstring wval = util::S2WS(val);
				AddString(key, wval);

				std::cout<<key<<std::ends;
				std::cout<<val<<std::endl;
			}
		}
		else
			std::cout<<"Cant not opened file: "<<path<<std::endl;
	}

	return true;
}

String& StringManager::GetString(const std::string& key)
{
	return util::Get(strings_, key);
}
