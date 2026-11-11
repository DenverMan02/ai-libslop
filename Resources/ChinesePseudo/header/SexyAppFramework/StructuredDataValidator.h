
#pragma once
#include "StructuredData.h"

namespace Sexy
{
	
	class StructuredDataValidator
	{
		
	public:

		static void LoadCoreMetaSchema( StructuredData* metaSchema );
		
		StructuredDataValidator();

		/**
		 * Validate against a JSON Schema.  See http://json-schema.org/
		 * Returns true if valid.  If there are errors, and errors is not NULL,
		 * an array named "validationErrors" is added to errors.
		 * Each object in the array will have the following values:
		 *   "property" (string) - JSONPath of the instance that failed validation.
		 *   "schema" (string) - JSONPath of the schema that the property was checked against.
		 *   "message" (string) - description of how the property was invalid.
		 *
		 * Core schema implementation status.  See section 5 of the specification.
		 * schema property                                             status
		 * ---------------                                             ------
		 * 5.1.  type                                             implemented
		 * 5.2.  properties                                       implemented
		 * 5.3.  patternProperties                            not implemented
		 * 5.4.  additionalProperties                             implemented
		 * 5.5.  items                                            implemented
		 * 5.6.  additionalItems                                  implemented
		 * 5.7.  required                                         implemented
		 * 5.8.  dependencies                                 not implemented
		 * 5.9.  minimum                                          implemented
		 * 5.10. maximum                                          implemented
		 * 5.11. exclusiveMinimum                                 implemented
		 * 5.12. exclusiveMaximum                                 implemented
		 * 5.13. minItems                                         implemented
		 * 5.14. maxItems                                         implemented
		 * 5.15. uniqueItems                                  not implemented
		 * 5.16. pattern                                      not implemented
		 * 5.17. minLength                                        implemented
		 * 5.18. maxLength                                        implemented
		 * 5.19. enum                                         not implemented
		 * 5.20. default                                      not implemented
		 * 5.21. title                                            informative
		 * 5.22. description                                      informative
		 * 5.23. format                                       not implemented
		 * 5.24. divisibleBy                                      implemented
		 * 5.25. disallow                                     not implemented
		 * 5.26. extends                                      not implemented
		 * 5.27. id                                           not implemented
		 * 5.28. $ref                       only supports the special URI "#"
		 * 5.29. $schema                                      not implemented
		 */
		bool Validate( StructuredData* instance, const StructuredData* schema, StructuredData* errors );
		
	protected:
		
		typedef StructuredData::Value Value;
		typedef StructuredData::String String;
		
        enum SchemaValueType
		{
			SD_ANY = StructuredData::SD_VALUE_TYPE_COUNT,
			SD_SCHEMA_VALUE_TYPE_COUNT,
		};
		
		enum TypeValidationResult
		{
			INVALID_TYPE = 0,
			VALID_SIMPLE_TYPE,
			VALID_SCHEMA_TYPE,
		};
			
		static String kSchemaTypeStrings[ SD_SCHEMA_VALUE_TYPE_COUNT ];
		static SchemaValueType SchemaValueTypeFromString( String schemaType );
		
		bool Validate           ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );
		int  ValidateType       ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );
		bool ValidateSimpleType ( const Value* instance, const Value* simple, std::string& instancePath, std::string& schemaPath );
		bool ValidateString     ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );
		bool ValidateNumber     ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );
		bool ValidateObject     ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );
		bool ValidateArray      ( const Value* instance, const Value* schema, std::string& instancePath, std::string& schemaPath );

		const Value* ResolveSchemaRef( const Value* schema, std::string& instancePath, std::string& schemaPath );
		void AppendValidationError( const std::string& valuePath, const std::string& schemaPath, const std::string& message );

		const Value* mRootSchema;
		std::string mRootSchemaPath;
		StructuredData* mErrors;
		bool mTraceValidation;
		static StructuredData sDefaultSchema;
		static uchar sCoreMetaSchemaBase64[];
		
	};
	
}
