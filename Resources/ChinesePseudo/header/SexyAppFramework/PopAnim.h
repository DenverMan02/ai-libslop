#ifndef __POPANIM_H__
#define __POPANIM_H__

#include "Common.h"
#include "SexyAppBase.h"
#include "DescParser.h"
#include "SexyMatrix.h"
#include "ResourceManager.h"
#include "MTRand.h"

namespace Sexy
{
    class Buffer;
    class PopAnimListener;
    
	class PopTransformMatrix
	{
	public:
		union
		{
			float m[6];
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
			};
		};
		
	public:
		PopTransformMatrix() {}
		
		PopTransformMatrix(const SexyMatrix3 &theMat)
		{
			m00 = theMat.m00;
			m01 = theMat.m01;
			m02 = theMat.m02;
			m10 = theMat.m10;
			m11 = theMat.m11;
			m12 = theMat.m12;
		}
		
		void LoadIdentity()
		{
			m01	= m02 = m10 = m12  = 0;
			m00 = m11 = 1;
		}
		SexyVector2 operator*(const SexyVector2 &theVec) const
		{
			float xDot1 = m00*theVec.x;
			float xDot2 = m10*theVec.x;
			
			float yDot1 = m01*theVec.y;
			float yDot2 = m11*theVec.y;
			
			xDot1 += yDot1;
			xDot2 += yDot2;
			xDot1 += m02;
			xDot2 += m12;
			
			return SexyVector2(xDot1, xDot2);
		}
		
		const PopTransformMatrix& operator=(const SexyMatrix3 &theMat)
		{
			m00 = theMat.m00;
			m01 = theMat.m01;
			m02 = theMat.m02;
			m10 = theMat.m10;
			m11 = theMat.m11;
			m12 = theMat.m12;
			return *this;
		}
		
		//jvw -- inlining this could cause some code bloat... use the Static Multiply version for speed
		PopTransformMatrix operator*(const PopTransformMatrix &theMat) const
		{
			PopTransformMatrix aResult;
			Multiply(&aResult, this, &theMat);
			return aResult;
		}
		
		inline static void Multiply(PopTransformMatrix *pOut, const PopTransformMatrix *pM1, const PopTransformMatrix *pM2)
		{
			//------
			float m1_00_X_m2_00 = pM1->m00;
			float m1_01_X_m2_10 = pM1->m01;
			
			float m1_00_X_m2_01 = pM1->m00;
			float m1_01_X_m2_11 = pM1->m01;
			
			float m1_00_X_m2_02 = pM1->m00;
			float m1_01_X_m2_12 = pM1->m01;
			
			float m1_10_X_m2_00 = pM1->m10;
			float m1_11_X_m2_10 = pM1->m11;
			
			float m1_10_X_m2_01 = pM1->m10;
			float m1_11_X_m2_11 = pM1->m11;
			
			float m1_10_X_m2_02 = pM1->m10;
			float m1_11_X_m2_12 = pM1->m11;
			
			//------
			m1_00_X_m2_00 *= pM2->m00;
			m1_01_X_m2_10 *= pM2->m10;
			
			m1_00_X_m2_01 *= pM2->m01;
			m1_01_X_m2_11 *= pM2->m11;
			
			m1_00_X_m2_02 *= pM2->m02;
			m1_01_X_m2_12 *= pM2->m12;
			
			m1_10_X_m2_00 *= pM2->m00;
			m1_11_X_m2_10 *= pM2->m10;
			
			m1_10_X_m2_01 *= pM2->m01;
			m1_11_X_m2_11 *= pM2->m11;
			
			m1_10_X_m2_02 *= pM2->m02;
			m1_11_X_m2_12 *= pM2->m12;
			
			//------
			m1_00_X_m2_00 += m1_01_X_m2_10;
			m1_00_X_m2_01 += m1_01_X_m2_11;
			
			m1_00_X_m2_02 += m1_01_X_m2_12;
			m1_10_X_m2_00 += m1_11_X_m2_10;
			
			m1_10_X_m2_01 += m1_11_X_m2_11;
			m1_10_X_m2_02 += m1_11_X_m2_12;
			
			m1_00_X_m2_02 += pM1->m02;
			m1_10_X_m2_02 += pM1->m12;
			
			//------
			pOut->m00 = m1_00_X_m2_00;
			pOut->m01 = m1_00_X_m2_01;
			
			pOut->m02 = m1_00_X_m2_02;
			pOut->m10 = m1_10_X_m2_00;
			
			pOut->m11 = m1_10_X_m2_01;
			pOut->m12 = m1_10_X_m2_02;
		}
				
		SexyMatrix3 GetMatrix3()
		{
			SexyMatrix3 rval;
			rval.m00 = m00;
			rval.m01 = m01;
			rval.m02 = m02;
			rval.m10 = m10;
			rval.m11 = m11;
			rval.m12 = m12;
			rval.m20 = 0;
			rval.m21 = 0;
			rval.m22 = 1;
			return rval;
		}
	};

    class PATransform
    {
    public:
        PopTransformMatrix				mMatrix;
		
    public:
        PATransform();
        
        PATransform				TransformSrc(const PATransform& theSrcTransform) const;
        PATransform				InterpolateTo(const PATransform& theNextTransform, float thePct) const;
    };
    
    class PAImage
    {
    public:
        DeviceImage*            mImage;
        int						mOrigWidth;
        int						mOrigHeight;
        int						mCols;
        int						mRows;
        std::string				mImageName;
        int						mDrawMode;
        PATransform				mTransform;
    };
    
    typedef std::vector<PAImage> PAImageVector;
    
    class PAObjectPos
    {
    public:
        int						mObjectNum;
        int16					mResNum;
        bool                    mIsSprite;
        bool                    mIsAdditive;
		
		uint8					mRed;
		uint8					mGreen;
		uint8					mBlue;
		uint8					mAlpha;

		//(6 X 4)
        PATransform				mTransform;
    };
    
    typedef std::vector<PAObjectPos> PAObjectPosVector;
    typedef std::map<int, PAObjectPos> IntToPAObjectPosMap;
    
    class PACommand
    {
    public:
        std::string				mCommand;
        std::string				mParam;
    };
    
    typedef std::vector<PACommand> PACommandVector;
    
    class PAFrame
    {
    public:
        std::vector<int>        mFrameObjectPosIndexVector;
        bool					mHasStop;
        PACommandVector			mCommandVector;
        
    public:
        PAFrame()
        {
            mHasStop = false;
        }
    };
    
    typedef std::vector<PAFrame> PAFrameVector;
    typedef std::map<std::string, int> StringToIntMap;
    
    class PASpriteDef;
    
    typedef std::vector<PASpriteDef*> PASpriteDefPtrVector;
    
    class PAObjectDef
    {
    public:
        const char*				mName;
        PASpriteDef*			mSpriteDef; // Null if not a sprite
        
    public:
        PAObjectDef()
        {
            mName = NULL;
            mSpriteDef = NULL;
        }
    };
    
    typedef std::vector<PAObjectDef> PAObjectDefVector;
    
    class PASpriteDef
    {
    public:
        const char*				mName;
        std::string				mExportName;
        PAFrameVector			mFrames;
        int						mWorkAreaStart;
        int						mWorkAreaDuration;
        StringToIntMap			mLabels;
        PAObjectDefVector		mObjectDefVector;
        PAObjectPosVector       mObjectPosVector;
        float					mAnimRate;
        
    public:
        int						GetLabelFrame(const std::string& theLabel);
        void					GetLabelFrameRange(const std::string& theLabel, int& theStart, int& theEnd );
        
    };
    
    class PASpriteInst;
    
    
    class PAObjectInst
    {
    public:
        const char*				mName;
        PASpriteInst*			mSpriteInst; // Null if not a sprite
        Color					mBlendSrcColor;
        
        // User settings
//        Color					mColorMult;
        
        PATransform				mBlendSrcTransform;
        bool                    mIsBlending;
        
    public:
        PAObjectInst()
        {
            mName = NULL;
            mSpriteInst = NULL;
            mIsBlending = false;
        }
    };
    
    typedef std::vector<PAObjectInst> PAObjectInstVector;
    
    class PASpriteInst
    {
    public:
        PASpriteInst*			mParent = nullptr;
        int16					mDelayFrames = 0;
        bool                    mSpriteVisibility;
        bool                    mOnNewFrame = true;
        float					mFrameNum = 0;
        int						mFrameRepeats = 0; //16
		
        int						mLastUpdated = -1;
        PASpriteDef*			mDef = nullptr; //+8 = 24
		
        Color					mCurColor;
		
        PATransform				mCurTransform;
		
        PAObjectInstVector		mChildren;
        
    public:
        PASpriteInst() { mSpriteVisibility = true; }
        ~PASpriteInst();
        PAObjectInst*			GetObjectInst(const std::string& theName); // Uses backslashes for children
        bool					SetSpriteVisibility(const std::string& spriteDefName, const bool visibility);
        bool					GetSpriteVisibility(const std::string& spriteDefName);            
    };
    
    typedef std::vector<PASpriteDef> PASpriteDefVector;
    typedef std::vector<std::string> StringVector;
    
    class PopAnim;
    class PopAnimDef
    {
    public:
        PASpriteDef*			mMainSpriteDef;
        PASpriteDefVector		mSpriteDefVector;
        StringVector			mObjectNamePool;
        PAImageVector           mImageVector;
        std::string             mError;
        std::string             mLoadedPamFile;
        int						mRefCount;
        int                     mVersion;
        bool                    mLoaded;
        
    public:
        PopAnimDef()
        : mMainSpriteDef(NULL)
        , mRefCount(0)
        , mVersion(0)
        , mLoaded(false)
        {
        }
        
        ~PopAnimDef() { delete mMainSpriteDef; }
    };
    
    namespace ResourceInfoTypes { class PopAnimRes; }
    
    class PopAnim
    : public BaseResource
    {
    public:
        RT_CLASS_DEFINE(PopAnim, BaseResource, ResourceClass);
        typedef ResourceInfoTypes::PopAnimRes InfoClass;
        
    public:
        int						mId;
        PopAnimListener*		mListener;
        
        float					mDrawScale;
        float					mImgScale;
        
        int						mAnimRate;
        Rect					mAnimRect;
        
        std::string				mLastPlayedFrameLabel;
        
        PASpriteInst*			mMainSpriteInst;
        PopAnimDef*				mMainAnimDef;
        float					mBlendTicksTotal;
        float					mBlendTicksCur;
        float					mBlendDelay;
        
        SexyTransform2D			mTransform;
        Color					mColor;
        bool					mAdditive;
        
        bool					mTransDirty;
        bool					mAnimRunning;
        bool					mPaused;
        
    public:
        bool			Fail(const std::string& theError);
        
        bool			LoadSpriteDef(Buffer* theBuffer, PASpriteDef* theSpriteDef);
        void			InitSpriteInst(PASpriteInst* theSpriteInst, PASpriteDef* theSpriteDef);
        
        void			FrameHit(PASpriteInst* theSpriteInst, PAFrame* theFrame, PAObjectPos* theObjectPos);
        void			DoFramesHit(PASpriteInst* theSpriteInst, PAObjectPos* theObjectPos);
        void			CalcObjectPos(const PASpriteInst* theSpriteInst, const PAObjectPos* objPos, PATransform* theTransform, Color* theColor);
        
		void			UpdateTransforms();
        void			UpdateTransforms(PASpriteInst* theSpriteInst, PATransform* theTransform, const Color& theColor);
        
		void			IncSpriteInstFrame(PASpriteInst* i_spriteInst, PAObjectPos* i_objectPos, float i_increment);
        void			PrepSpriteInstFrame(PASpriteInst* theSpriteInst, PAObjectPos* theObjectPos);
		void			AnimUpdate(float i_increment);
		
        void			ResetAnimHelper(PASpriteInst* theSpriteInst);
        void			SaveStateSpriteInst(Buffer& theBuffer, PASpriteInst* theSpriteInst);
        
        void    	    DrawSprite(Graphics* g, const PASpriteInst* theSpriteInst, const PATransform* theTransform, const Color& theColor, bool additive);
		void    	    DrawSpriteReplaceLayerWithImage(Graphics* g, const PASpriteInst* theSpriteInst, const PATransform* theTransform, const Color& theColor, bool additive, const std::string& theLayer, Image* theImage);

		//static void		DebugPrintProfilingInfo();
        
    public:
        void			Load_Init();
        bool			Load_LoadPam(const std::string& theFileName);
        
        MixedImagePtr	Load_GetImageHook(const std::string& theFileDir, const std::string& theOrigName);
        bool			Load_GetImage(PAImage* theImage, const std::string& theFileDir, const std::string& theOrigName);
        
    public:	
        PopAnim(int theId = 0, PopAnimListener* theListener = NULL);
        PopAnim(const PopAnim& rhs);
        virtual ~PopAnim();
        
        void			Clear();
        
        PopAnim*		Duplicate() const;
        
        bool			LoadFile(const std::string& theFileName);	
		
        void			ResetAnim();	
        bool			SetupSpriteInst(const std::string& theName = "");
        bool			Play(int theFrameNum = 0, bool resetAnim = true);
        bool			Play(const std::string& theFrameLabel, bool resetAnim = true);
        

        bool			BlendTo(const std::string& theFrameLabel, float theBlendTicks, float theAnimStartDelay = 0.0f);
        bool			IsActive() const;	
        
        void			SetPAMColor(const Color& theColor);
        PAObjectInst*	GetObjectInst(const std::string& theName); // Uses backslashes for children
        
        void			Draw(Graphics* g);
        void			DrawDebugOverlay(Graphics* g);
        void            DrawDebugOverlayForSprite(Graphics* i_g, PASpriteInst* i_sprite, PATransform* i_parentTransform, int i_depth);
        void            DrawReplaceLayerWithImage(Graphics* g, const std::string& theLayer, Image* theImage);

        int				GetLabelFrame(const std::string& theFrameLabel);
        PASpriteDef*    FindSpriteDef(const char* theAnimName);
    };
    
}

#endif //__POPANIM_H__
