
#pragma once
#include "Rect.h"
#include "Point.h"
#include "Insets.h"
#include "RtDb.h"
#include <set>

namespace ImageLib
{
	class Image;
}

namespace Sexy
{
	class Image;
	class DeviceImage;

	class AtlasedImageStore
	{
	public:
		
		AtlasedImageStore();
		~AtlasedImageStore();

		/* Set the dimensions and number of atlases to use. */
		void Reserve( uint32 width, uint32 height, uint32 count );
		
		/* Delete all images and atlases. Does not reset the reserve setup. */
		void Clear();
		
		/* Returns true if store is empty. */
		bool Empty();
		
		/* Add an image to the store.  Returns an invalid pointer if the image
		 * cannot be fit onto any atlas.
		 */
		RtWeakPtr<Image> AddImage( const ImageLib::Image* rawImage );
		
		/* Create an image in the store of the given dimensions. */
		RtWeakPtr<Image> AddImage( uint32 width, uint32 height );
		
		/* Replace the image data of an image in the store.  If the new image
		 * data is not the same size as the existing image, this function
		 * does nothing.
		 */
		void ReplaceImage( RtWeakPtr<Image> existingImage, const ImageLib::Image* rawImage );

	protected:

		typedef RtMixedPtr<DeviceImage> ImageGrip;
		typedef RtWeakPtr<DeviceImage> ImagePtr;
		
		struct Span
		{
			int start, end;
		};
		
		struct SpanRow
		{
			std::vector<Span> spans;
			int available;
			bool IsSpanOpen( int inStart, int inEnd, int& outSkipToX );
			void AddSpan( int inStart, int inEnd );
		};
		
		struct SubImage
		{
			ImageGrip image;
			ImagePtr atlas;
			Rect frame;
			Insets pad;
			
			SubImage();
			void Init( ImagePtr atlas, const Rect& frame, const Insets& pad );
			void ReplacePixels( const uint32* pixels );
			void ReplaceImage( const ImageLib::Image* rawImage );
		};
		
		class Atlas
		{
			ImageGrip mImage;

			typedef std::vector< SpanRow > Rows;
			Rows mRows;
		public:
			Atlas();
			~Atlas();
			void Init( int width, int height );
			void AllocateSubImage( SubImage& subImage, const ImageLib::Image* rawImage );
		protected:
			bool IsRectOpen( int inX, int inY, int inWidth, int inHeight, int& outSkipToX );
			void AddRect( int inX, int inY, int inWidth, int inHeight );
		};

		typedef std::vector<SubImage> Images;
		typedef std::vector<Atlas> Atlases;
		
		Point mAtlasSize;
		Atlases mAtlases;
		Images mImages;
	};
}
