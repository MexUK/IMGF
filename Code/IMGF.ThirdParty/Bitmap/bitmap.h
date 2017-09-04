//-----------------------------------------------------------------------------
// Copyright (c) 2006-2009 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#if !defined(BITMAP_H)
#define BITMAP_H

#include <windows.h>
#include <tchar.h>
#include <gdiplus.h>

//-----------------------------------------------------------------------------
// 32-bit BGRA WIN32 device independent bitmap (DIB) class.
//
// Supports the loading of BMP, GIF, JPEG, PNG, and TIFF files using GDI+.
//
// Also supports the loading of true color 24-bit and 32-bit TGA files, and
// grayscale 8-bit TGA files.
//
// Support is also provided for capturing a screen shot of the current Windows
// desktop and loading that as an image into the Bitmap class.
//
// This class stores the DIB in a top-down orientation. The pixel bytes are
// stored in the standard Windows DIB order of BGRA.
//
// All Windows DIBs are aligned to 4-byte (DWORD) memory boundaries. This means
// that each scan line is padded with extra bytes to ensure that the next scan
// line starts on a 4-byte memory boundary.
//
// To get a copy of the DIB that is BYTE (1-byte) aligned with all the extra
// padding bytes removed use the copyBytes() methods.
//-----------------------------------------------------------------------------
class DHPOBitmap // renamed because of ambiguity
{
public:
    HDC dc;
    HBITMAP hBitmap;
    int width;
    int height;
    int pitch;
    BITMAPINFO info;

	DHPOBitmap();
	DHPOBitmap(const DHPOBitmap &bitmap);
	~DHPOBitmap();

	DHPOBitmap &operator=(const DHPOBitmap &bitmap);

    BYTE *operator[](int row) const
    { return &m_pBits[pitch * row]; }

    void blt(HDC hdcDest);
    void blt(HDC hdcDest, int x, int y);
    void blt(HDC hdcDest, int x, int y, int w, int h);
    void blt(HDC hdcDest, const RECT &rcDest, const RECT &rcSrc);

	bool clone(const DHPOBitmap &bitmap);
    bool create(int widthPixels, int heightPixels);
    void destroy();

    void fill(int r, int g, int b, int a);
    void fill(float r, float g, float b, float a);
    
    BYTE *getPixels() const
    { return m_pBits; }

    bool loadDesktop();

    bool loadImage(LPCTSTR pszFilename);
    bool saveImage(LPCTSTR pszFilename) const;

    void selectObject();
    void deselectObject();

    void copyBytes24Bit(BYTE *pDest) const;
    void copyBytes32Bit(BYTE *pDest) const;

    void copyBytesAlpha8Bit(BYTE *pDest) const;
    void copyBytesAlpha32Bit(BYTE *pDest) const;
    
    void setPixels(const BYTE *pPixels, int w, int h, int bytesPerPixel);

    void flipHorizontal();
    void flipVertical();
    
    void resize(int newWidth, int newHeight);

private:
    DWORD createPixel(int r, int g, int b, int a) const;
    DWORD createPixel(float r, float g, float b, float a) const;
    
    bool loadTarga(LPCTSTR pszFilename);
    bool saveTarga(LPCTSTR pszFilename) const;

    static void initGdiplus();
    static void shutdownGdiplus();
    static bool getEncoderClsid(LPCTSTR pszFormat, CLSID *pClsid);

    static ULONG_PTR m_gdiplusToken;
    static Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
    static CLSID m_clsidEncoderBmp;
    static CLSID m_clsidEncoderGif;
    static CLSID m_clsidEncoderJpeg;
    static CLSID m_clsidEncoderPng;
    static CLSID m_clsidEncoderTiff;

    HGDIOBJ m_hPrevObj;
    BYTE *m_pBits;
};

#endif