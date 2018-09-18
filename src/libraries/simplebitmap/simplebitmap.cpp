#include "simplebitmap.h"
#include "yspng.h"
#include "yspngenc.h"



SimpleBitmap::SimpleBitmap(const SimpleBitmap &incoming)
{
	CopyFrom(incoming);
}
SimpleBitmap &SimpleBitmap::operator=(const SimpleBitmap &from)
{
	CopyFrom(from);
	return *this;
}
SimpleBitmap::SimpleBitmap(SimpleBitmap &&incoming)
{
	MoveFrom(incoming);
}
SimpleBitmap &SimpleBitmap::operator=(SimpleBitmap &&incoming)
{
	MoveFrom(incoming);
	return *this;
}
bool SimpleBitmap::LoadPng(const char fn[])
{
	YsRawPngDecoder decoder;
	if(YSOK==decoder.Decode(fn))
	{
		MoveFrom(decoder);
		return true;
	}
	return false;
}
bool SimpleBitmap::LoadPng(FILE *fp)
{
	YsRawPngDecoder decoder;
	if(YSOK==decoder.Decode(fp))
	{
		MoveFrom(decoder);
		return true;
	}
	return false;
}
SimpleBitmap &SimpleBitmap::operator=(class YsRawPngDecoder &&pngDecoder)
{
	return MoveFrom(pngDecoder);
}
SimpleBitmap &SimpleBitmap::MoveFrom(class YsRawPngDecoder &decoder)
{
	// Ownership of decoder.rgba needs to be transferred to this bitmap.
	SetDirect(decoder.wid,decoder.hei,decoder.rgba);
	decoder.wid=0;
	decoder.hei=0;
	decoder.rgba=nullptr;  // <=This way, decoder's destructor will not delete it.
	return *this;
}
SimpleBitmap SimpleBitmap::CutOut(int x0,int y0,int wid,int hei) const
{
	SimpleBitmap cut;
	SimpleBitmapTemplate <unsigned char,4>::CutOut(cut,x0,y0,wid,hei,0);
	return cut;
}
void SimpleBitmap::Clear(unsigned char r,unsigned char g,unsigned char b,unsigned char a)
{
	auto rgba=GetEditableBitmapPointer();
	auto numPix=GetWidth()*GetHeight();
	for(int i=0; i<numPix; ++i)
	{
		rgba[i*4  ]=r;
		rgba[i*4+1]=g;
		rgba[i*4+2]=b;
		rgba[i*4+3]=a;
	}
}
bool SimpleBitmap::SavePng(FILE *fp) const
{
	YsRawPngEncoder encoder;
	if(YSOK==encoder.EncodeToFile(fp,GetWidth(),GetHeight(),8,6,GetBitmapPointer()))
	{
		return true;
	}
	return false;
}

bool SimpleBitmap::operator==(const SimpleBitmap &bitmapB) const
{
	if(this->GetWidth()!=bitmapB.GetWidth() || this->GetHeight()!=bitmapB.GetHeight())
	{
		return false;
	}
	auto numPix=GetWidth()*GetHeight();
	auto thisRgba=GetBitmapPointer();
	auto testRgba=bitmapB.GetBitmapPointer();
	for(int i=0; i<numPix*4; ++i)
	{
		if(thisRgba[i]!=testRgba[i])
		{
			return false;
		}
	}
	return true;
}

bool SimpleBitmap::operator!=(const SimpleBitmap &bitmapB) const
{
	if(this->GetWidth()!=bitmapB.GetWidth() || this->GetHeight()!=bitmapB.GetHeight())
	{
		return true;
	}
	auto numPix=GetWidth()*GetHeight();
	auto thisRgba=GetBitmapPointer();
	auto testRgba=bitmapB.GetBitmapPointer();
	for(int i=0; i<numPix*4; ++i)
	{
		if(thisRgba[i]!=testRgba[i])
		{
			return true;
		}
	}
	return false;
}

