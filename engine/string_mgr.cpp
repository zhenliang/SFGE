#include "string_mgr.h"

#include <fstream>
#include <iostream>
#include <util\container.h>
#include <util\string.h>

bool StringManager::AddString( std::string key, std::wstring value,
							   const Font& font /*= Font::GetDefaultFont()*/, float size /*= 30.0f*/ )
{
	return AddString(key, String(value, font, size));
}

bool StringManager::AddString( std::string key, String value )
{
	return util::Insert(strings_, Strings::value_type(key, value));
}

bool StringManager::AddStrings( std::string file )
{
	if (!file.empty())
	{
		const size_t ID_LENGHT = 32;
		const size_t TEXT_LENGHT = 1024;

		char id[ID_LENGHT + 1] = {};
		char text[TEXT_LENGHT + 1] = {};

		std::ifstream ifstream(file.c_str());
		if (ifstream.is_open())
		{
			std::cout<<file<<" :"<<std::endl;

			while (ifstream.get(id, ID_LENGHT, ' '))
			{
				ifstream.ignore();
				ifstream.getline(text, TEXT_LENGHT, '\n');

				std::wstring wtext = util::S2WS(text);
				AddString(id, wtext);

				std::cout<<id<<std::ends;
				std::cout<<text<<std::endl;
			}
		}
		else
			std::cout<<"Cant not opened file: "<<file<<std::endl;

	}

	return true;
}

String& StringManager::GetString( std::string key )
{
	return util::Get(strings_, key);
}
