#ifndef CWTDFormat_Header1_H
#define CWTDFormat_Header1_H

#include "Types.h"

#pragma pack(push, 1)
struct CWTDFormat_Header1
{
	uint32					m_uiMagicNumber;
	uint32					m_uiType;
	uint32					m_uiFlags;
};
#pragma pack(pop)

#endif