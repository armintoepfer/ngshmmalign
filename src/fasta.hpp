#ifndef FASTA_HPP
#define FASTA_HPP

/*
 * Copyright (c) 2016 David Seifert
 * 	
 * This file is part of ngshmmalign
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cctype>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::vector<T> fasta_read(const std::string& input_file)
{
	std::vector<T> result;

	std::string id, seq;

	std::string temp;
	std::ifstream input(input_file);

	if (input.is_open())
	{
		while (input.good())
		{
			std::getline(input, temp);
			temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());

			if (temp.empty())
				continue;

			if (temp[0] == '>')
			{
				// identifier
				if (!(seq.empty()))
				{
					result.emplace_back(std::move(id), std::move(seq));
				}
				id = temp.substr(1);
				seq.clear();
			}
			else
			{
				// sequence
				std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
				seq.append(temp);
			}
		}
	}
	else
	{
		std::cerr << "Input file '" << input_file << "' could not be opened!\n";
		std::terminate();
	}
	input.close();

	// add the last line
	if (!(seq.empty()))
	{
		result.emplace_back(std::move(id), std::move(seq));
	}

	return result;
}

#endif /* FASTA_HPP */