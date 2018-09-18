#ifndef SIMPLEBITMAP_24783_IS_INCLUDED
#define SIMPLEBITMAP_24783_IS_INCLUDED
/* { */

#include <stdio.h>
#include "simplebitmaptemplate.h"

class SimpleBitmap : public SimpleBitmapTemplate <unsigned char,4>
{
public:
	/* 'using' statement makes a label from the base code just like this class's own label. */
	using SimpleBitmapTemplate <unsigned char,4>::CopyFrom;
	using SimpleBitmapTemplate <unsigned char,4>::MoveFrom;

	/*! Default constructor is needed to allow making an empty bitmap.
	    Becasue this class has a copy constructor, the compiler will complain
	    when you want to make an empty bitmap unless you define a default constructor.
	    After C++11, you can also write as:
	        SimpleBitmap()=default;
	    This feature had relatively slow support.
	    It should be available in Xcode 7.x and VS2015.
	*/
	SimpleBitmap(){}
	~SimpleBitmap(){}

	/*! Default copy constructor. */
	SimpleBitmap(const SimpleBitmap &incoming);

	/*! Default copy operator. */
	SimpleBitmap &operator=(const SimpleBitmap &from);

	/*! Move-assignment constructor. */
	SimpleBitmap(SimpleBitmap &&incoming);

	/*! Move-assignment operator. */
	SimpleBitmap &operator=(SimpleBitmap &&incoming);

	/*! Load a PNG image into this bitmap. */
	bool LoadPng(const char fn[]);

	/*! fp must be opened with "rb". */
	bool LoadPng(FILE *fp);

	/*! Move-assignment operator from a YsRawPngDecoder object. */
	SimpleBitmap &operator=(class YsRawPngDecoder &&pngDecoder);

	/*! Move bitmap from YsRawPngDecoder. */
	SimpleBitmap &MoveFrom(class YsRawPngDecoder &pngDecoder);

	/*! Cut out a rectangular part of the bitmap, (x0,y0)-(x0+wid-1,y0+hei-1) and returns it. */
	SimpleBitmap CutOut(int x0,int y0,int wid,int hei) const;

public:
	/*! Clears the bitmap with the given RGBA values. */
	void Clear(unsigned char r,unsigned char g,unsigned char b,unsigned char a);

	/*! Saves the bitmap in .PNG format.
	    The origin of the .PNG format is bottom-left, while this bitmap top-left.
	    To save it corrctly, use Invert() function before saving.
	    The file must be opened in "wb" mode.
	    Common mistake is ending up with opening "w" mode.  This is good in Unix systems, but breaks in Windows. */
	bool SavePng(FILE *fp) const;

	/*! Returns true if bitmapB is exactly same as this bitmap. */
	bool operator==(const SimpleBitmap &bitmapB) const;

	/*! Returns true if bitmapB is not same as this bitmap. */
	bool operator!=(const SimpleBitmap &bitmapB) const;
};


/* } */
#endif
