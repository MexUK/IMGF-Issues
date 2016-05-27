#ifndef eDataType_H
#define eDataType_H

#include "Types.h"

enum eDataType : uint8
{
	DATATYPE_UINT8,
	DATATYPE_UINT16,
	DATATYPE_UINT32,
	DATATYPE_INT8,
	DATATYPE_INT16,
	DATATYPE_INT32,
	DATATYPE_FLOAT32,
	DATATYPE_FLOAT64,
	DATATYPE_FLOAT80,
	DATATYPE_STRING
};

#endif