/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2009-2011  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef NUMBER_H
#define NUMBER_H
#include "compat.h"
#include "asobject.h"

namespace lightspark
{

class Number : public ASObject
{
friend ASObject* abstract_d(number_t i);
friend class ABCContext;
friend class ABCVm;
CLASSBUILDABLE(Number);
private:
	Number():val(0) {type=T_NUMBER;}
	Number(double v):val(v){type=T_NUMBER;}
	static void purgeTrailingZeroes(char* buf);
public:
	static const number_t NaN;
	double val;
	ASFUNCTION(_constructor);
	ASFUNCTION(_toString);
	ASFUNCTION(toFixed);
	tiny_string toString();
	static tiny_string toString(number_t val);
	static bool isInteger(number_t val)
	{
		return floor(val) == val;
	}
	unsigned int toUInt()
	{
		return (unsigned int)(val);
	}
	int32_t toInt()
	{
		if(val<0)
			return int(val);
		else
		{
			uint32_t ret=val;
			return ret;
		}
	}
	TRISTATE isLess(ASObject* o);
	bool isEqual(ASObject* o);
	static void buildTraits(ASObject* o){};
	static void sinit(Class_base* c);
	ASFUNCTION(generator);
	std::string toDebugString() { return toString()+"d"; }
	//Serialization interface
	void serialize(ByteArray* out, std::map<tiny_string, uint32_t>& stringMap,
				std::map<const ASObject*, uint32_t>& objMap,
				std::map<const Class_base*, uint32_t>& traitsMap);
};


};

#endif // NUMBER_H
