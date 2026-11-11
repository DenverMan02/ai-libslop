
#include "SexyAppBase.h"

#include "RenderStateManager.h"
#include "MemPools.h"

namespace Sexy {
	
	//looks the same as the D3D version from now,
	class GLContext
	{
	public:
		Image* mDestImage;
		RenderStateManager::Context mStateContext;
		bool mInitialized;
		mutable GLContext* mParent; // we track parent/child contexts based on copy-ctor, since state manager contexts have some optimizations for these situations
		mutable SimplePooledVector<GLContext*>::Type mChildren;
		
		GLContext(Image* inImage)
		: mDestImage(inImage)
		, mInitialized(false)
		, mParent(NULL)
		, mChildren(&msChildrenPool)
		{}
		
		GLContext(const GLContext& inContext)
		: mDestImage(inContext.mDestImage)
		, mStateContext(inContext.mStateContext)
		, mInitialized(true) // because we're copying state from an existing context
		, mParent((GLContext*)&inContext)
		, mChildren(&msChildrenPool)
		{
			mParent->mChildren.push_back(this);
		}
		
		~GLContext()
		{
			// separate from children and parent, if applicable
			
			auto aChildCount = mChildren.size();
			for (int iChild=0; iChild<aChildCount; ++iChild)
			{
				assert(mChildren[iChild]->mParent == this);
				mChildren[iChild]->mParent = NULL;
			}
			mChildren.clear();
			
			if (mParent)
			{
				aChildCount = mParent->mChildren.size();
				for (int iChild=0; iChild<aChildCount; ++iChild)
				{
					if (mParent->mChildren[iChild] == this)
					{
						mParent->mChildren.erase(mParent->mChildren.begin()+iChild);
						break;
					}
				}
			}
		}
		
	public:
		static SimpleMemPool msPool;
		static SimpleMemPool msChildrenPool;
		
		void *operator new( size_t size )
		{
			return msPool.GetMemory(static_cast<uint32_t>(size));
		}
		
		void operator delete( void * addr)
		{
			msPool.ReturnMemory((uint8*)addr);
		}

	};
}