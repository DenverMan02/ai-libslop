#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "SharedImage.h"
#include "Image.h"

namespace Sexy
{
	class Mesh;


	class MeshListener 
	{
	public:	
		virtual void			MeshPreLoad(Mesh* theMesh) {}
		virtual void			MeshHandleProperty(Mesh* theMesh, const std::string& theMeshName, const std::string& theSetName, const std::string& thePropertyName, const std::string& thePropertyValue) {}
		virtual RtId			MeshLoadTex(Mesh* theMesh, const std::string& theMeshName, const std::string& theSetName, const std::string& theTexType, const std::string& theFileName) { return RtId(); }

		virtual void			MeshPreDraw(Mesh* theMesh) {}
		virtual void			MeshPostDraw(Mesh* theMesh) {}
		virtual void			MeshPreDrawSet(Mesh* theMesh, const std::string& theMeshName, const std::string& theSetName, bool hasBump) {}
		virtual void			MeshPostDrawSet(Mesh* theMesh, const std::string& theMeshName, const std::string& theSetName) {}	

		virtual void			MeshPreDeleted(Mesh* theMesh) {}
	};


	class MeshPiece
	{
	public:
		std::string				mObjectName;
		std::string				mSetName;
		
		MixedImagePtr			mTexture;	
		MixedImagePtr			mBumpTexture;
		
	public:
		MeshPiece();
		virtual ~MeshPiece();
	};

	class Mesh
	{	
	public:
		std::string				mFileName;
		MeshListener*			mListener;
		void*					mUserData;

		typedef std::list<MeshPiece*> MeshPieceList;

		MeshPieceList			mPieces;
	public:
		Mesh();	
		~Mesh();

		virtual void			Cleanup();
		virtual void			SetListener(MeshListener* theListener);
	};
}


#endif