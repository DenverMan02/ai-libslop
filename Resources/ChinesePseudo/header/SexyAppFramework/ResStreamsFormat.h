#ifndef RESSTREAMSFORMAT_H_INCLUDED
#define RESSTREAMSFORMAT_H_INCLUDED


namespace Sexy
{
	const uint32 RESSTREAMBUNDLE_ID = ('r' << 24 | 's' << 16 | 'b' << 8 | '1');
	const uint32 RESSTREAMVERSION_MAJOR = 4;
	const uint32 RESSTREAMVERSION_MINOR = 0;

	// Version History:
	// 1.1    Initial file version
	// 2.0	  Removed texture descs from pools. Incompatible with previous versions.
	// 3.0	  Added language to Composite Descriptors. Incompatible with previous versions.

	const uint32 RESSTREAMGROUP_ID = ('r' << 24 | 's' << 16 | 'g' << 8 | 'p');


	struct ResStreamHeaderV1
	{
		//common data size is the amount of data that needs to be read in
		// to hold all of the common data for the res streams system. this
		// includes the file index, the compiled resources.xml data, the 
		// group list, and the pool list.
		uint32				common_data_size;


		//the file index is the optimized tree structure that holds
		// an index of every file in the system to group mapping.
		// This is an optional feature that could be turned off if the
		// game has no need for it. file_index_size is 0 if it's turned 
		// off.
		uint32				file_index_size;

		//the file index location is the offset from the beginning of the 
		// file for where the file index exists. For now, the file index
		// if it exists should be located at the beginning of the block after
		// the header, so at 2048. This will be 0 if it does not exist.
		uint32				file_index_location;

		//the CompiledMap of id to location uses the same optimized tree structure
		// that the file index uses. this is basically a resourceId to
		// file / file metadata map.
		uint32				id_index_size;
		uint32				id_index_location;

		//this is a small CompiledMap that converts a group name into the group index
		uint32				group_name_to_id_size;
		uint32				group_name_to_id_location;

		//groups are the main block of data that gets loaded in with 
		// the res streams system. 
		uint32				groups_count;
		uint32				groups_location;
		//the size in bytes for each header id. this will likely change
		//per major version of the file format
		uint32				group_header_size;
		
		//composites logically associate groups so that multiple resolutions can co-exist in one RSB
		uint32				composites_count;
		uint32				composites_location;
		uint32				composites_size;
		
		uint32				composite_name_to_id_size;
		uint32				composite_name_to_id_location;

		//pools are used to preallocate memory and resources that can be
		//replaced with the data in the groups to prevent fragmentation and
		//speed up loading.
		uint32				pools_count;
		uint32				pools_location;
		uint32				pool_header_size;

		uint32				texture_desc_count;
		uint32				texture_desc_location;
		//this is the size of one texture description
		uint32				texture_desc_size;
		
		
		//Compiled Resources.xml data - no longer used
		uint32				res_xml_index;
		uint32				base_res_data_index;
		uint32				attrib_data_index;

		uint32				common_data_size_nomanifest;
	};


	//the header will exist in it's own 2k block on disk, so it's 
	// free to have that much data in it at least
	//
	//All ResStream header/descriptor data is endian flipped for the target platform on creation
	//(all non-gpu data is considered opaque and will not be explicity endian flipped)
	struct ResStreamHeader
	{
		uint32				id;
		uint32				version_major;
		uint32				version_minor;
		ResStreamHeaderV1	v1;
	};


	enum ResStreamDataType
	{
		RESSTREAM_RESIDENT = 0,
		RESSTREAM_GPU_TRANSFER = 1,
		RESSTREAM_TRANSIENT = 2,
	};
	
	struct ResStreamCompositeDescriptor
	{
		static const uint32 MAX_NAME = 128;
		static const uint32 MAX_CHILDREN = 64;
		//the composite name as a 0 terminated ascii string
		uint8				name[MAX_NAME];
		
		struct Child
		{
			uint32			group_id;
			uint32			resolution; //(uint32)-1 for all resolutions
			uint32			locale;	//(uint32)0 for no language
			uint32			_reserved;  //should be 0
		};
		
		Child				children[MAX_CHILDREN];
		uint32				children_count;
	};

	//the GroupDescriptor is embedded in the common data that gets loaded up
	// at startup. There is additonal data in the group header that gets loaded 
	// when the group is loaded.
	struct ResStreamGroupDescriptor
	{
		static const uint32 MAX_NAME = 128;
		//the group name as a 0 terminated ascii string
		uint8				name[MAX_NAME];

		//the location of the group in the larger res stream bundle
		uint32				file_location;

		//the size of the group data on disk. the size should be block
		// aligned. this will likely be different than the in memory size
		uint32				file_size;

		//the index of the pool that this group uses. pools have a set of textures
		//that groups can reuse and a memory area that can be overwritten.
		uint32				pool;
		
		//
		uint32				compression_type;

		//duplicated from the group bundle themselves. This is here so that 
		// read sizes can be optimized without having to read the rsg header before
		// loading in the group
		uint32				data_common_size; 

		uint32				data_resident_location;
		uint32				data_resident_file_size;
		uint32				data_resident_total_size; //uncompressed
		uint32				data_resident_mem_size;

		uint32				data_gpu_location;
		uint32				data_gpu_file_size;
		uint32				data_gpu_total_size; //uncompressed
		uint32				data_gpu_mem_size;

		uint32				data_transient_location;
		uint32				data_transient_file_size;
		uint32				data_transient_total_size; //uncompressed
		uint32				data_transient_mem_size;
		
		//this is the number of textures used by this group. The texture descriptors
		//follow the pool descriptor
		uint32				texture_count;
		//this is the offset from the start of the global texture descriptor list to 
		//where the textures for this pool start
		uint32				texture_offset;
	};

	enum ResStreamPoolFlags
	{
		RESSTREAM_POOL_ALLOC_AT_STARTUP = 0x0001,

		//this means that the pool should not destroy itself when 
		//there are no more groups using it. This is not recommended,
		// but could be useful for old apps just trying to get started
		// with RSB
		RESSTREAM_POOL_NOT_REF_COUNTED		= 0x0002
	};

	struct ResStreamPoolDescriptor
	{
		static const uint32 MAX_NAME = 128;
		//the pool name as a 0 terminated ascii string.
		// primarily used for the debug draw interface
		uint8				name[MAX_NAME];

		//this is the size to allocate for the permanent resident data
		uint32				resident_data_size;

		//this is the size to allocate for gpu data for platforms that are
		// responsible for allocating this (Xbox and PS3 for now)
		uint32				gpu_data_size;

		//this is the number of instances that this pool supports, these 
		//will be allocated at startup (in the first version of res streams,
		//later versions may be able to cycle pools in and out of memory if needed)
		uint32				instance_count;

		//these flags describe behavior of this group, and come from the
		//ResStreamPoolFlags enum
		uint32				flags;

		//(Deprecated, left for struct sizing)
		uint32				_deprecated_texture_count;
		
		//(Deprecated, left for struct sizing)
		uint32				_deprecated_texture_offset;
	};

	//Texture descriptors are for 2D textures only now (Prime doesn't yet really support
	// cube or volume textures)
	struct ResStreamTextureDescriptor
	{
		uint32				width;
		uint32				height;
		//pitch is size in bytes from the beginning of one horizontal line to the next
		// Some platforms call it stride.
		uint32				pitch;
		//format is system specific in this case.
		uint32				format;
		//for the alpha compress. add by jeffty
		uint32				alphaTextureSize;
		//for texture size optimize. add by jeffty
		uint32				scalePercent;
	};

	struct ResStreamGroupHeader
	{
		//these can be ignored during runtime. they're primarly for the assembly
		// tool to make sure that group formats are up to date.
		uint32				id;
		uint32				version_major;
		uint32				version_minor;

		uint32				total_size;
		
		uint32				compression_type;

		//location for the data chunks of the group are relative to the
		// file location of the group. (this is because the groups are built
		// independentally and assembled together)
		uint32				data_common_size; 

		uint32				data_resident_location;
		uint32				data_resident_file_size;
		uint32				data_resident_total_size; 
		uint32				data_resident_mem_size;

		uint32				data_gpu_location;
		uint32				data_gpu_file_size;
		uint32				data_gpu_total_size;
		uint32				data_gpu_mem_size;

		uint32				data_transient_location;
		uint32				data_transient_file_size;
		uint32				data_transient_total_size;
		uint32				data_transient_mem_size;

		//Groups have more detailed file indices than the global file index.
		//these file indices specify offsets into the data chunks and file sizes,
		//in addition to other metadata.
		//If the file is an image, the metadata will have the location of the
		//image as a texture index and atlas info.
		// GPU data is different and based on texture lists.
		uint32				file_index_size;
		uint32				file_index_location;

		//note that the pool will define the texture data info also
		uint32				texture_desc_count;
		uint32				texture_desc_location;
		uint32				texture_desc_size;

	};

	struct ResStreamFileLocationInfo
	{
		uint32				res_type; //gpu data (1) or resident (0) for now...
		uint32				location; //offset from the type (gpu or resident banks)
		uint32				size;
	};

	//GPU transfer specific data...
	struct ResStreamFileGPULocationInfo : public ResStreamFileLocationInfo
	{
		//texture index is the index of the texture
		uint32				texture_index; 
		//atlas info is for the FUTURE...
		uint32				atlas_x;
		uint32				atlas_y;
		uint32				atlas_width;
		uint32				atlas_height;
	};

	
	//The following structs are used for the compiled form of Resources.xml
	//This describes the base asset for loading in by the ResourceManager 
	
	struct ResStream_CompositeResDesc
	{
		uint32				name_index;
		uint32				group_count;
		uint32				group_size; //size of the group struct
		
		//the group structs will follow this directly
	};
	
	struct ResStream_GroupResDesc
	{
		int32				resolution;
		uint32				locale;
		uint32				name_index;
		uint32				res_count;
		
		//offsets to the Groups will follow directly
		//offsets for Groups are from the BaseResIndex in the header
	};
	
	struct ResStream_BaseResDesc 
	{
		//static const uint32 MAX_RES_ID_LENGTH = 256;
		//static const uint32 MAX_RES_PATH_LENGTH = 256;
		
		uint32				flags;
		uint16				type;
		uint16				size; //size of the struct
		
		uint32				attrib_index;
		uint32				data_index; //index of the specific parsed info (like ResStream_ImageResDesc)
		
		uint32				id_index;
		uint32				path_index;
		
		uint32				num_attribs;
		//offsets for attribs are from the AttribIndex in the header
	};
	
	struct ResStream_ImageResDesc
	{
		static const uint32 FLAG_NOTRIREP =		0x0001;
		static const uint32 FLAG_ISATLAS  =		0x0002;
		static const uint32 FLAG_ISATLASED =	0x0004;
		static const uint32 FLAG_CUBE =			0x0008;
		static const uint32 FLAG_VOLUME =		0x0010;
		
		
		uint16				image_flags;
		uint16				atlas_flags;
		
		int16				x;
		int16				y;
		
		int16				atlas_x;
		int16				atlas_y;
		
		int16				atlas_w;
		int16				atlas_h;
		
		int16				rows;
		int16				cols;
		
		uint32				atlas_index;
		//needs to support the int vectors for per-frame delay and frame-map
	};
	
	struct ResStream_SoundResDesc
	{
		float				volume;
		int32				pan;
	};
	
	struct ResStream_FontResDesc
	{
		//first version is just a delimited string of tags...
		//second version will be a list of strings
		uint32				tags_index;
	};
	
	struct ResStream_Attrib
	{
		uint32				key_index;
		uint32				value_type;
		uint32				value_index;
	};


	//these are the standard formats, platforms can define their own formats at starting at RSB_TEXTURE_FORMAT_PLATFORM
	// Because this is a fast data packing system, these formats describe both the way that the data is packed and what 
	// it should be unpacked as. 
	// 
	enum ResStream_TextureFormat
	{
		RSB_TEXTURE_FORMAT_A8R8G8B8	= 0,
		RSB_TEXTURE_FORMAT_A4R4G4B4	= 1,
		RSB_TEXTURE_FORMAT_R5G6B5	= 2,
        RSB_TEXTURE_FORMAT_R5G5B5A1	= 3,
        
        
        RSB_TEXTURE_FORMAT_A8R8G8B8_TILED = 20,
        RSB_TEXTURE_FORMAT_A4R4G4B4_TILED = 21,
        RSB_TEXTURE_FORMAT_R5G6B5_TILED = 22,
        RSB_TEXTURE_FORMAT_R5G5B5A1_TILED = 23,
        
        
        RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT = 30,
        RSB_TEXTURE_FORMAT_COMPRESSED_PVR_2BIT = 31,
        RSB_TEXTURE_FORMAT_COMPRESSED_ETC1 = 32,
        RSB_TEXTURE_FORMAT_COMPRESSED_ETC2_RGB = 33,
        RSB_TEXTURE_FORMAT_COMPRESSED_ETC2_RGBA = 34,
        RSB_TEXTURE_FORMAT_COMPRESSED_DXT1_RGB = 35,
        RSB_TEXTURE_FORMAT_COMPRESSED_DXT3_RGBA = 36,
        RSB_TEXTURE_FORMAT_COMPRESSED_DXT5_RGBA = 37,
        RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGB = 38,
        RSB_TEXTURE_FORMAT_COMPRESSED_ATITC_RGBA = 39,


        // Alpha separation formats
        // Developed for Android developers to support compression
        
        // Alpha_Copy : Bottom half of texture is copy of top where alpha is in all three RGB channels
        // Implemented in ResGen but removed from Prime due to being less efficient
/*        RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_COPY = 0x90,       //
        RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_COPY = 0x91,   // PVR compressed texture using RGB (same bitrate as RGBA but slightly better quality)
        RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_COPY = 0x92,       // For testing purposes - inefficient*/
        
        // Alpha_Split : Texture is followed by an 8-bit uncompressed alpha texture of the same height/width
        RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_ALPHA_SPLIT = 0x93,      //
        RSB_TEXTURE_FORMAT_COMPRESSED_PVR_4BIT_ALPHA_SPLIT = 0x94,  //
        RSB_TEXTURE_FORMAT_COMPRESSED_RGBA_ALPHA_SPLIT = 0x95,      // For testing purposes - inefficient
        RSB_TEXTURE_FORMAT_COMPRESSED_ETC1_COMPRESS_ALPHA_SPLIT = 0x96,      //
        
	RSB_TEXTURE_FORMAT_PLATFORM = 0xFF,
	};
};

#endif
