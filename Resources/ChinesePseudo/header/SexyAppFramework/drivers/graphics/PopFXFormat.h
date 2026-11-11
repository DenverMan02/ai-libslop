#ifndef POPFXFORMAT_H_INCLUDED
#define POPFXFORMAT_H_INCLUDED


#ifndef HOST_PLATFORM
//not compiling under prime...
//quick types update
typedef unsigned int uint32;
typedef int int32;
#endif

namespace PopFXFormat
{

typedef uint32 TableIndex;
typedef TableIndex StringIndex;
typedef TableIndex TechniqueIndex;
typedef TableIndex PassIndex;
typedef TableIndex SettingIndex;
typedef TableIndex AnnotationIndex;
typedef TableIndex ValueIndex;
typedef TableIndex ShaderParamIndex;
typedef TableIndex ShaderIndex;

const TableIndex EmptyIndex = (TableIndex)-1;

const uint32 PopFXID = (((int)'p' << 24) + ((int)'c' << 16) + ((int)'f' << 8) + (int)'x');
const uint32 PopFXVersion = 1;

struct PopFXHeader
{
	uint32 id;
	uint32 version;

	uint32 num_techniques;
	uint32 technique_table;
	uint32 technique_size;

	uint32 num_annotations;
	uint32 annotation_table;
	uint32 annotation_size;

	uint32 num_strings;
	uint32 string_table;
	uint32 string_size;

	uint32 num_values;
	uint32 value_table;
	uint32 value_size;

	uint32 num_passes;
	uint32 pass_table;
	uint32 pass_size;

	uint32 num_settings;
	uint32 setting_table;
	uint32 setting_size;

	uint32 num_shader_params;
	uint32 shader_param_table;
	uint32 shader_param_size;

	uint32 num_shaders;
	uint32 shader_table;
	uint32 shader_size;

	uint32 string_data_offset;
};

struct PopFXTechnique
{
	StringIndex		name;
	uint32			technique_number;
	
	uint32			num_passes;
	PassIndex		pass_begin;

	uint32			num_annotations;
	AnnotationIndex annotation_begin;
};

struct PopFXPass
{
	StringIndex		name;
	
	uint32			num_annotations;
	AnnotationIndex	annotation_begin;

	uint32			num_settings;
	SettingIndex	setting_begin;

	ShaderIndex		vertex_shader;
	ShaderIndex		pixel_shader;
};

struct PopFXSetting
{
	uint32			category;	//(texture stage / render state / etc...)
	uint32			type;		//(int / float / etc...)
	
	uint32			num_annotations;
	AnnotationIndex annotation_begin;

	ValueIndex		value_begin;
};

struct PopFXAnnotation
{
	StringIndex		name;
	ValueIndex		value;
};

struct PopFXShaderParam
{
	StringIndex 	name;
	ValueIndex 		shader_register;
};

struct PopFXShader
{
	StringIndex		format;		//(something like "glsl")
	StringIndex		data;		//for glsl, this is a very large string of glsl code
								//the string table should support binary data if this eventually gets
								//used for compiled formats

	uint32			num_params;
	ShaderParamIndex  param_begin;

	StringIndex		entry_point; 
};

struct PopFXValue
{
	enum 
	{
		TYPE_FLOAT			= 0,
		TYPE_INT			= 1,
		TYPE_FLOAT_VECTOR2	= 2, 
		TYPE_FLOAT_VECTOR3	= 3,
		TYPE_FLOAT_VECTOR4	= 4,
		TYPE_INT_VECTOR2	= 5, 
		TYPE_INT_VECTOR3	= 6,
		TYPE_INT_VECTOR4	= 7,
		TYPE_STRING			= 8,
	};

	uint32			type;		//(float/int/float vector/int vector/string)
	union
	{
		StringIndex s_value;
		int32		i_value;
		float		f_value;
		float		fvec_value[4];
		int32		ivec_value[4];
	};
};

struct PopFXString
{
	uint32			num_characters;
	uint32			format;		//(ascii/utf8/16bit unicode LE/binary)
	uint32			offset;		//where the data is actually located in the file. This is an offset 
								//from the string data ptr
};


}

#endif