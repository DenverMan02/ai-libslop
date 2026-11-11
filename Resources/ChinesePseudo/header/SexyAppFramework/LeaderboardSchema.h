#pragma once
#include <string>
#include <vector>

#include "Common.h"

namespace Sexy
{
class LeaderboardSchema
{
public:
	
	enum DataType
	{
		INVALID = -1,
		INT32,
		INT64,
		FLOAT,
		DOUBLE,
		STRING,
		BINARY
	};
	
	enum AggregationRule
	{
		LAST,
		MIN,
		MAX,
		ADD,
		BIT_OR,
	};
	
	enum AggregationRole
	{
		KEY,
		DEPENDENT,
		INDEPENDENT,
	};
	
	struct Column
	{
		std::string name;
		DataType dataType;
		AggregationRule rule;
		AggregationRole role;

		uint32 aux1;
		uint32 aux2;
	};

	LeaderboardSchema( const std::string& schemaId );
	void AddColumn( const std::string& name, DataType dataType, AggregationRule rule, AggregationRole role, uint32 aux1 = (uint32)-1, uint32 aux2 = (uint32)-1 );

	const std::string& GetSchemaId() const;
	
	uint32 NumColumns() const { return (int)mColumns.size(); };
	const Column& GetColumn(uint32 index) const { return mColumns[index]; };

	const Column* GetKeyColumn() const;
protected:
	
	typedef std::vector< Column > Columns;
	
	std::string mSchemaId;
	
	Columns mColumns;
};

}
