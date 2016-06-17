#ifndef CDATWaterproFormat_H
#define CDATWaterproFormat_H

#define MAX_WATER_LEVEL_COUNT 48

#include "Types.h"
#include "CFormat.h"
#include "CDATWaterproEntry.h"
#include "Pool/CVectorPool.h"
#include <vector>

class CDATWaterproFormat : public CFormat, public CVectorPool<CDATWaterproEntry*>
{
public:
	CDATWaterproFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
	
	void					setVisibleWaterLevelMap(std::vector<uint8>& vecVisibleWaterLevelMap) { m_vecVisibleWaterLevelMap = vecVisibleWaterLevelMap; }
	std::vector<uint8>&		getVisibleWaterLevelMap(void) { return m_vecVisibleWaterLevelMap; }
	
	void					setPhysicalWaterLevelMap(std::vector<uint8>& vecPhysicalWaterLevelMap) { m_vecPhysicalWaterLevelMap = vecPhysicalWaterLevelMap; }
	std::vector<uint8>&		getPhysicalWaterLevelMap(void) { return m_vecPhysicalWaterLevelMap; }
	
private:
	std::vector<uint8>		m_vecVisibleWaterLevelMap;
	std::vector<uint8>		m_vecPhysicalWaterLevelMap;
};

#endif