
#pragma once
#include "StructuredData.h"
using namespace Sexy;

/**
 * @param object can be one of NSDictionary, NSArray, NSError.
 */
void InitStructuredDataWithObject( StructuredData* sd, id object );

/**
 *
 */
id PropertyListObjectWithStructuredData( const StructuredData* sd );

id PropertyListObjectWithStructuredData( const StructuredData::Value* value );
