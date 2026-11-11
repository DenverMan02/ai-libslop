#ifndef COMPILEDMAP_H_INCLUDED
#define COMPILEDMAP_H_INCLUDED


namespace Sexy
{
	/**
	 * Preliminary. Docs coming soon. Basically this is the same-in-memory as it is 
	 * on disk search tree structure that was used for the dictionary optimization in
	 * Bookworm for iPhone that Joe made. It is being adapted for use in the Res Streams 
	 * system in Prime, and maybe generalized for broader use. The compiler for it can 
	 * be found in the prime packer tool.
	 */
	class CompiledMap 
	{
	public:
		CompiledMap();
		CompiledMap(uint8* theBuffer, uint32 theSize);


		void Init(uint8* theBuffer, uint32 theSize);
		bool Initialized();
        
        void Clear() { Init(NULL, 0); }

		/**
		 * Find returns the a pointer to the data that "hangs"
		 * off of the node. This data can be of arbitrary length,
		 * so it's up to the application to understand how to parse
		 * it/use it.
		 */
		uint8* Find(const char* theString);
		uint8* Find(const wchar_t* theString);
        void    DebugPrint(std::string& o_str);
        uint32  GetNumNodes() const { return mNumNodes; }

	private:
		typedef uint8	char_t;
		typedef uint32	index_t;
		struct Node
		{
			uint32	v;
			
			inline char_t ch() { return (char_t)(v&0xFF); }
			inline index_t alt() { return (index_t)((v>>8)&0xFFFFFF); }
		};

		Node*			mNodes;
		uint32			mNumNodes;

		Node*			Find( Node* node, const char_t* word, char_t* foundWord );
		uint8*			FindFast( const char_t* word);
        void            DebugPrint_rescurive(Node* realNode, const std::vector<char>& i_Buffer, std::vector<char>& o_Buffer);
        
	};


};


#endif