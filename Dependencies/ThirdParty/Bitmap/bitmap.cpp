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

#pragma comment (lib, "gdiplus.lib")

#include <windows.h>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <memory>
#include "bitmap.h"

namespace
{
    #pragma pack(push, 1)
    
    // TGA file header structure. This *must* be byte aligned.
    struct TgaHeader
    {
        BYTE idLength;
        BYTE colormapType;
        BYTE imageType;
        WORD firstEntryIndex;
        WORD colormapLength;
        BYTE colormapEntrySize;
        WORD xOrigin;
        WORD yOrigin;
        WORD width;
        WORD height;
        BYTE pixelDepth;
        BYTE imageDescriptor;
    };

    // TGA file footer structure. This *must* be byte aligned.
    struct TgaFooter
    {
        LONG extensionAreaOffet;
        LONG developerDirectoryOffset;
        BYTE signature[18];
    };

    #pragma pack(pop)
}

ULONG_PTR DHPOBitmap::m_gdiplusToken;
Gdiplus::GdiplusStartupInput DHPOBitmap::m_gdiplusStartupInput;
CLSID DHPOBitmap::m_clsidEncoderBmp;
CLSID DHPOBitmap::m_clsidEncoderGif;
CLSID DHPOBitmap::m_clsidEncoderJpeg;
CLSID DHPOBitmap::m_clsidEncoderPng;
CLSID DHPOBitmap::m_clsidEncoderTiff;

DHPOBitmap::DHPOBitmap()
{
    dc = 0;
    hBitmap = 0;
    width = 0;
    height = 0;
    pitch = 0;
    m_hPrevObj = 0;
    m_pBits = 0;
}

DHPOBitmap::DHPOBitmap(const DHPOBitmap &bitmap)
{
    dc = 0;
    hBitmap = 0;
    width = 0;
    height = 0;
    pitch = 0;
    m_hPrevObj = 0;
    m_pBits = 0;
    
    clone(bitmap);
}

DHPOBitmap::~DHPOBitmap()
{
    destroy();
}

DHPOBitmap &DHPOBitmap::operator=(const DHPOBitmap &bitmap)
{
    if (this != &bitmap)
        clone(bitmap);

    return *this;
}

void DHPOBitmap::blt(HDC hdcDest)
{
    StretchBlt(hdcDest, 0, 0, width, height, dc, 0, 0, width, height, SRCCOPY);
}

void DHPOBitmap::blt(HDC hdcDest, int x, int y)
{
    StretchBlt(hdcDest, x, y, width, height, dc, 0, 0, width, height, SRCCOPY);
}

void DHPOBitmap::blt(HDC hdcDest, int x, int y, int w, int h)
{
    StretchBlt(hdcDest, x, y, w, h, dc, 0, 0, width, height, SRCCOPY);
}

void DHPOBitmap::blt(HDC hdcDest, const RECT &rcDest, const RECT &rcSrc)
{
    StretchBlt(hdcDest, rcDest.left, rcDest.top, rcDest.right - rcDest.left,
        rcDest.bottom - rcDest.top, dc, rcSrc.left, rcSrc.top,
        rcSrc.right - rcSrc.left, rcSrc.bottom - rcSrc.top, SRCCOPY);
}

bool DHPOBitmap::clone(const DHPOBitmap &bitmap)
{
    if (create(bitmap.width, bitmap.height))
    {
        memcpy(m_pBits, bitmap.m_pBits, bitmap.pitch * bitmap.height);
        return true;
    }

    return false;
}

bool DHPOBitmap::create(int widthPixels, int heightPixels)
{
    destroy();

    width = widthPixels;
    height = heightPixels;
    pitch = ((width * 32 + 31) & ~31) >> 3;
    dc = CreateCompatibleDC(0);

    if (!dc)
        return false;

    memset(&info, 0, sizeof(info));

    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biPlanes = 1;

    hBitmap = CreateDIBSection(dc, &info, DIB_RGB_COLORS, 
        reinterpret_cast<void**>(&m_pBits), 0, 0);

    if (!hBitmap)
    {
        destroy();
        return false;
    }

    GdiFlush();
    return true;
}

void DHPOBitmap::destroy()
{
    deselectObject();

    if (hBitmap)
    {
        DeleteObject(hBitmap);
        hBitmap = 0;
    }

    if (dc)
    {
        DeleteDC(dc);
        dc = 0;
    }

    width = height = pitch = 0;
    m_hPrevObj = 0;
    m_pBits = 0;
}

void DHPOBitmap::fill(int r, int g, int b, int a)
{
    int pixelPitch = pitch / sizeof(DWORD);
    DWORD pixel = createPixel(r, g, b, a);
    DWORD *pPixels = reinterpret_cast<DWORD*>(m_pBits);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
            pPixels[y * pixelPitch + x] = pixel;
    }
}

void DHPOBitmap::fill(float r, float g, float b, float a)
{
    int pixelPitch = pitch / sizeof(DWORD);
    DWORD pixel = createPixel(r, g, b, a);
    DWORD *pPixels = reinterpret_cast<DWORD*>(m_pBits);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
            pPixels[y * pixelPitch + x] = pixel;
    }
}

bool DHPOBitmap::loadDesktop()
{
    // Takes a screen capture of the current Windows desktop and stores
    // the image in the Bitmap object.

    HWND hDesktop = GetDesktopWindow();

    if (!hDesktop)
        return false;

    int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
    int desktopHeight = GetSystemMetrics(SM_CYSCREEN);
    HDC hDesktopDC = GetDCEx(hDesktop, 0, DCX_CACHE | DCX_WINDOW);

    if (!hDesktopDC)
        return false;

    if (!create(desktopWidth, desktopHeight))
    {
        ReleaseDC(hDesktop, hDesktopDC);
        return false;
    }

    selectObject();

    if (!BitBlt(dc, 0, 0, width, height, hDesktopDC, 0, 0, SRCCOPY))
    {
        destroy();
        ReleaseDC(hDesktop, hDesktopDC);
        return false;
    }

    deselectObject();
    ReleaseDC(hDesktop, hDesktopDC);
    return true;
}

bool DHPOBitmap::loadImage(LPCTSTR pszFilename)
{
    // Loads a supported bitmap image file using GDI+.
    // Supported formats include: BMP, GIF, JPEG, PNG, TIFF, and TGA.
    // GDI+ doesn't support TGA files so a separate code path loads them.

    if (_tcsstr(pszFilename, _T(".TGA")) || _tcsstr(pszFilename, _T(".tga")))
        return loadTarga(pszFilename);
   
    initGdiplus();

    std::auto_ptr<Gdiplus::Bitmap> pBitmap(Gdiplus::Bitmap::FromFile(pszFilename, FALSE));

    if (pBitmap.get() == 0)
        return false;

    if (!create(pBitmap->GetWidth(), pBitmap->GetHeight()))
        return false;
    
    Gdiplus::BitmapData data;
    Gdiplus::Rect rect(0, 0, width, height);

    if (pBitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &data) != Gdiplus::Ok)
        return false;

    if (data.Stride == pitch)
    {
        memcpy(m_pBits, data.Scan0, pitch * height);
    }
    else
    {
        unsigned char *pSrcPixels = static_cast<unsigned char *>(data.Scan0);

        for (int i = 0; i < height; ++i)
            memcpy(&m_pBits[i * pitch], &pSrcPixels[i * data.Stride], pitch);
    }
    
    pBitmap->UnlockBits(&data);
    return true;
}

bool DHPOBitmap::loadTarga(LPCTSTR pszFilename)
{
    // Loads a TGA image and stores it in the Bitmap object.

    HANDLE hFile = CreateFile(pszFilename, FILE_READ_DATA, FILE_SHARE_READ, 0,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    DWORD dwBytesRead = 0;
    TgaHeader header = {0};
    
    // Read in the TGA file header.
    ReadFile(hFile, &header, sizeof(header), &dwBytesRead, 0);

    // Skip over the TGA file's ID field.
    if (header.idLength > 0)
        SetFilePointer(hFile, header.idLength, 0, FILE_CURRENT);

    // Check for compatible color depth.
    if (!(header.pixelDepth == 32 || header.pixelDepth == 24 || header.pixelDepth == 8))
    {
        CloseHandle(hFile);
        return false;
    }

    // Only support uncompressed true color and grayscale images.
    if (!(header.imageType == 0x02 || header.imageType == 0x01))
    {
        CloseHandle(hFile);
        return false;
    }

    // Read the TGA file into a temporary buffer.

    DWORD dwPitch = header.width * (header.pixelDepth / 8);
    DWORD dwBufferSize = dwPitch * header.height;
    std::vector<BYTE> buffer(dwBufferSize);

    // Load the pixel data from the TGA file. Flip image if it's not top down.
    if ((header.imageDescriptor & 0x30) == 0x20)
    {
        // TGA image is stored top down in file.
        ReadFile(hFile, &buffer[0], dwBufferSize, &dwBytesRead, 0);
    }
    else
    {
        // TGA image is stored bottom up in file. Need to flip it.
        
        BYTE *pRow = 0;

        for (int i = 0; i < header.height; ++i)
        {
            pRow = &buffer[(header.height - 1 - i) * dwPitch];
            ReadFile(hFile, pRow, dwPitch, &dwBytesRead, 0);
        }
    }

    CloseHandle(hFile);

    if (!create(header.width, header.height))
        return false;

    setPixels(&buffer[0], header.width, header.height, header.pixelDepth / 8);
    return true;
}

void DHPOBitmap::setPixels(const BYTE *pPixels, int w, int h, int bytesPerPixel)
{
    // Copies the specified input pixels to the Bitmap object.
    // This method performs color conversion on the source pixels so that
    // the pixels stored in the Bitmap object have a 32 bit color depth.

    if (!pPixels)
        return;

    int srcPitch = w * bytesPerPixel;

    if (bytesPerPixel == 4)
    {
        const BYTE *pSrcRow = 0;
        BYTE *pDestRow = 0;
                
        for (int i = 0; i < h; ++i)
        {
            pSrcRow = &pPixels[i * srcPitch];
            pDestRow = &m_pBits[i * pitch];
            memcpy(pDestRow, pSrcRow, srcPitch);
        }
    }
    else if (bytesPerPixel == 3)
    {
        const BYTE *pSrcPixel = 0;
        BYTE *pDestPixel = 0;

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                pSrcPixel = &pPixels[(i * srcPitch) + (j * 3)];
                pDestPixel = &m_pBits[(i * pitch) + (j * 4)];

                pDestPixel[0] = pSrcPixel[0];
                pDestPixel[1] = pSrcPixel[1];
                pDestPixel[2] = pSrcPixel[2];
                pDestPixel[3] = 255;
            }
        }
    }
    else if (bytesPerPixel == 1)
    {
        BYTE srcPixel = 0;
        BYTE *pDestPixel = 0;

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                srcPixel = pPixels[i * srcPitch + j];
                pDestPixel = &m_pBits[(i * pitch) + (j * 4)];

                pDestPixel[0] = srcPixel;
                pDestPixel[1] = srcPixel;
                pDestPixel[2] = srcPixel;
                pDestPixel[3] = 255;
            }
        }
    }
}

bool DHPOBitmap::saveImage(LPCTSTR pszFilename) const
{
    initGdiplus();

    LPCTSTR szFormat = 0;
    const CLSID *pClsidEncoder = 0;
    
    if (_tcsstr(pszFilename, _T(".bmp")) || _tcsstr(pszFilename, _T(".BMP")))
        pClsidEncoder = &m_clsidEncoderBmp;
    else if (_tcsstr(pszFilename, _T(".gif")) || _tcsstr(pszFilename, _T(".GIF")))
        pClsidEncoder = &m_clsidEncoderGif;
    else if (_tcsstr(pszFilename, _T(".jpg")) || _tcsstr(pszFilename, _T(".JPG")))
        pClsidEncoder = &m_clsidEncoderJpeg;
    else if (_tcsstr(pszFilename, _T(".png")) || _tcsstr(pszFilename, _T(".PNG")))
        pClsidEncoder = &m_clsidEncoderPng;
    else if (_tcsstr(pszFilename, _T(".tga")) || _tcsstr(pszFilename, _T(".TGA")))
        return saveTarga(pszFilename);
    else if (_tcsstr(pszFilename, _T(".tif")) || _tcsstr(pszFilename, _T(".TIF")))
        pClsidEncoder = &m_clsidEncoderTiff;
    else
        pClsidEncoder = 0;
    
    std::auto_ptr<Gdiplus::Bitmap> pBitmap(Gdiplus::Bitmap::FromBITMAPINFO(&info, m_pBits));

    if (pBitmap.get() == 0)
        return false;

    if (pBitmap->Save(pszFilename, pClsidEncoder, 0) != Gdiplus::Ok)
        return false;

    return true;
}

bool DHPOBitmap::saveTarga(LPCTSTR pszFilename) const
{
    HANDLE hFile = CreateFile(pszFilename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL, 0);

    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    TgaHeader header = {0};
    TgaFooter footer = {0, 0, "TRUEVISION-XFILE."};

    // Fill in file header.
    header.width = width;
    header.height = height;
    header.pixelDepth = 32;
    header.imageType = 2;               // uncompressed true-color
    header.imageDescriptor = 0x20;      // top-down orientation
        
    DWORD dwNumberOfBytesWritten = 0;

    // Write file header.
    WriteFile(hFile, &header, sizeof(header), &dwNumberOfBytesWritten, 0);

    // Write the pixel data. Pixel data needs to be byte aligned.
    for (int i = 0; i < height; ++i)
    {
        WriteFile(hFile, &m_pBits[i * pitch], width * 4,
            &dwNumberOfBytesWritten, 0);
    }

    // Write the file footer.
    WriteFile(hFile, &footer, sizeof(footer), &dwNumberOfBytesWritten, 0);

    CloseHandle(hFile);
    return true;
}

void DHPOBitmap::selectObject()
{
    if (dc)
        m_hPrevObj = SelectObject(dc, hBitmap);
}

void DHPOBitmap::deselectObject()
{
    if (dc && m_hPrevObj)
    {
        SelectObject(dc, m_hPrevObj);
        m_hPrevObj = 0;
    }
}

void DHPOBitmap::copyBytes24Bit(BYTE *pDest) const
{
    // 'pDest' must already point to a chunk of allocated memory of the correct
    // size (i.e., width pixels X height pixels X 24 bits).
    //
    // The returned image is byte aligned and the pixel format is BGR.

    if (!pDest)
        return;

    BYTE *pSrc = 0;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            pSrc = &m_pBits[(pitch * y) + (x * 4)];

            *pDest++ = *pSrc;
            *pDest++ = *(pSrc + 1);
            *pDest++ = *(pSrc + 2);
        }
    }
}

void DHPOBitmap::copyBytes32Bit(BYTE *pDest) const
{
    // 'pDest' must already point to a chunk of allocated memory of the correct
    // size (i.e., width pixels x height pixels x 32 bits).
    //
    // The returned image is byte aligned and the pixel format is BGRA.

    if (!pDest)
        return;

    const int widthBytes = width * 4;

    for (int y = 0; y < height; ++y)
        memcpy(&pDest[widthBytes * y], &m_pBits[pitch * y], widthBytes);
}

void DHPOBitmap::copyBytesAlpha8Bit(BYTE *pDest) const
{
    // 'pDest' must already point to a chunk of allocated memory of the correct
    // size (i.e., width pixels X height pixels X 8 bits).
    //
    // The returned image is byte aligned and the pixel format is grayscale.
    //
    // The luminance conversion used is the one that Real-Time Rendering
    // 2nd Edition (Moller and Haines,  ) recommends. It is based on modern
    // CRT and HDTV phosphors.
    //      Y = 0.2125R + 0.7154G + 0.0721B

    if (!pDest)
        return;

    BYTE *pSrc = 0;
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            pSrc = &m_pBits[(pitch * y) + (x * 4)];
            b = (*pSrc / 255.0f) * 0.0721f;
            g = (*(pSrc + 1) / 255.0f) * 0.7154f;
            r = (*(pSrc + 2) / 255.0f) * 0.2125f;
            *pDest++ = static_cast<BYTE>(255.0f * (b + g + r));
        }
    }
}

void DHPOBitmap::copyBytesAlpha32Bit(BYTE *pDest) const
{
    // 'pDest' must already point to a chunk of allocated memory of the correct
    // size (i.e., width pixels X height pixels X 32 bits).
    //
    // This is similar to copyBytesAlpha8Bit() only the alpha channel will
    // contain the grayscale luminance map generated by copyBytesAlpha8Bit().
    // The RGB channels are filled with pure white (255, 255, 255).
    //
    // The returned image is byte aligned and the pixel format is BGRA.
    //
    // The luminance conversion used is the one that Real-Time Rendering
    // 2nd Edition (Moller and Haines, 2002) recommends. It is based on modern
    // CRT and HDTV phosphors.
    //      Y = 0.2125R + 0.7154G + 0.0721B

    if (!pDest)
        return;

    BYTE *pSrc = 0;
    float fRed = 0.0f;
    float fGreen = 0.0f;
    float fBlue = 0.0f;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            pSrc = &m_pBits[(pitch * y) + (x * 4)];

            fBlue = (*pSrc / 255.0f) * 0.0721f;
            fGreen = (*(pSrc + 1) / 255.0f) * 0.7154f;
            fRed = (*(pSrc + 2) / 255.0f) * 0.2125f;

            *pDest++ = 255;
            *pDest++ = 255;
            *pDest++ = 255;
            *pDest++ = static_cast<BYTE>(255.0f * (fBlue + fGreen + fRed));
        }
    }
}

void DHPOBitmap::flipHorizontal()
{
    BYTE *pFront = 0;
    BYTE *pBack = 0;
    BYTE pixel[4] = {0};

    for (int i = 0; i < height; ++i)
    {
        pFront = &m_pBits[i * pitch];
        pBack = &pFront[pitch - 4];

        while (pFront < pBack)
        {
            // Save current pixel at position pFront.
            pixel[0] = pFront[0];
            pixel[1] = pFront[1];
            pixel[2] = pFront[2];
            pixel[3] = pFront[3];

            // Copy new pixel from position pBack into pFront.
            pFront[0] = pBack[0];
            pFront[1] = pBack[1];
            pFront[2] = pBack[2];
            pFront[3] = pBack[3];

            // Copy old pixel at position pFront into pBack.
            pBack[0] = pixel[0];
            pBack[1] = pixel[1];
            pBack[2] = pixel[2];
            pBack[3] = pixel[3];

            pFront += 4;
            pBack -= 4;
        }
    }
}

void DHPOBitmap::flipVertical()
{
    std::vector<BYTE> srcPixels(pitch * height);

    memcpy(&srcPixels[0], m_pBits, pitch * height);

    BYTE *pSrcRow = 0;
    BYTE *pDestRow = 0;

    for (int i = 0; i < height; ++i)
    {
        pSrcRow = &srcPixels[(height - 1 - i) * pitch];
        pDestRow = &m_pBits[i * pitch];
        memcpy(pDestRow, pSrcRow, pitch);
    }
}

void DHPOBitmap::resize(int newWidth, int newHeight)
{
    // Resizes the bitmap image using bilinear sampling.

    float ax = 0.0f, ay = 0.0f;
    float bx = 0.0f, by = 0.0f;
    float cx = 0.0f, cy = 0.0f;
    float dx = 0.0f, dy = 0.0f;
    float u = 0.0f, v = 0.0f, uv = 0.0f;
    float oneMinusU = 0.0f, oneMinusV = 0.0f, oneMinusUOneMinusV = 0.0f;
    float uOneMinusV = 0.0f, vOneMinusU = 0.0f;

    float srcX = 0.0f;
    float srcY = 0.0f;
    float srcXStep = static_cast<float>(width) / static_cast<float>(newWidth);
    float srcYStep = static_cast<float>(height) / static_cast<float>(newHeight);

    int destPitch = newWidth * 4;
    std::vector<BYTE> destPixels(destPitch * newHeight);

    BYTE pixel[4] ={0};

    const BYTE *pSrcPixelA = 0;
    const BYTE *pSrcPixelB = 0;
    const BYTE *pSrcPixelC = 0;
    const BYTE *pSrcPixelD = 0;
    BYTE *pDestPixel = 0;

    for (int y = 0; y < newHeight; ++y)
    {
        for (int x = 0; x < newWidth; ++x)
        {
            ax = floor(srcX);
            u = srcX - ax;

            ay = floor(srcY);
            v = srcY - ay;

            dx = ax + 1.0f;
            dy = ay + 1.0f;

            if (dx >= width)
                dx = width - 1.0f;

            if (dy >= height)
                dy = height - 1.0f;

            bx = dx;
            by = ay;

            cx = ax;
            cy = dy;

            uv = u * v;
            oneMinusU = 1.0f - u;
            oneMinusV = 1.0f - v;
            uOneMinusV = u * oneMinusV;
            vOneMinusU = v * oneMinusU;
            oneMinusUOneMinusV = oneMinusU * oneMinusV;

            pSrcPixelA = &m_pBits[(static_cast<int>(ay) * pitch) + (static_cast<int>(ax) * 4)];
            pSrcPixelB = &m_pBits[(static_cast<int>(by) * pitch) + (static_cast<int>(bx) * 4)];
            pSrcPixelC = &m_pBits[(static_cast<int>(cy) * pitch) + (static_cast<int>(cx) * 4)];
            pSrcPixelD = &m_pBits[(static_cast<int>(dy) * pitch) + (static_cast<int>(dx) * 4)];

            pixel[0] = static_cast<BYTE>(pSrcPixelA[0] * oneMinusUOneMinusV + pSrcPixelB[0] * uOneMinusV + pSrcPixelC[0] * vOneMinusU + pSrcPixelD[0] * uv);
            pixel[1] = static_cast<BYTE>(pSrcPixelA[1] * oneMinusUOneMinusV + pSrcPixelB[1] * uOneMinusV + pSrcPixelC[1] * vOneMinusU + pSrcPixelD[1] * uv);
            pixel[2] = static_cast<BYTE>(pSrcPixelA[2] * oneMinusUOneMinusV + pSrcPixelB[2] * uOneMinusV + pSrcPixelC[2] * vOneMinusU + pSrcPixelD[2] * uv);
            pixel[3] = static_cast<BYTE>(pSrcPixelA[3] * oneMinusUOneMinusV + pSrcPixelB[3] * uOneMinusV + pSrcPixelC[3] * vOneMinusU + pSrcPixelD[3] * uv);

            pDestPixel = &destPixels[(y * destPitch) + (x * 4)];

            pDestPixel[0] = pixel[0];
            pDestPixel[1] = pixel[1];
            pDestPixel[2] = pixel[2];
            pDestPixel[3] = pixel[3];

            srcX += srcXStep;
        }

        srcX = 0.0f;
        srcY += srcYStep;
    }

    destroy();

    if (create(newWidth, newHeight))
        setPixels(&destPixels[0], newWidth, newHeight, 4);
}

DWORD DHPOBitmap::createPixel(int r, int g, int b, int a) const
{
    return static_cast<DWORD>(
          (static_cast<DWORD>(a) << 24)
        | (static_cast<DWORD>(r) << 16)
        | (static_cast<DWORD>(g) << 8)
        |  static_cast<DWORD>(b));
}

DWORD DHPOBitmap::createPixel(float r, float g, float b, float a) const
{
    return static_cast<DWORD>(
          (static_cast<DWORD>(a * 255.0f) << 24)
        | (static_cast<DWORD>(r * 255.0f) << 16)
        | (static_cast<DWORD>(g * 255.0f) << 8)
        |  static_cast<DWORD>(b * 255.0f));
}

void DHPOBitmap::initGdiplus()
{
    if (!m_gdiplusToken)
    {
        Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, 0);
        atexit(shutdownGdiplus);

        getEncoderClsid(_T("image/bmp"), &m_clsidEncoderBmp);
        getEncoderClsid(_T("image/gif"), &m_clsidEncoderGif);
        getEncoderClsid(_T("image/jpeg"), &m_clsidEncoderJpeg);
        getEncoderClsid(_T("image/png"), &m_clsidEncoderPng);
        getEncoderClsid(_T("image/tiff"), &m_clsidEncoderTiff);
    }
}

void DHPOBitmap::shutdownGdiplus()
{
    if (m_gdiplusToken)
    {
        Gdiplus::GdiplusShutdown(m_gdiplusToken);
        memset(&m_gdiplusStartupInput, 0, sizeof(m_gdiplusStartupInput));
        m_gdiplusToken = 0;
    }
}

bool DHPOBitmap::getEncoderClsid(LPCTSTR pszFormat, CLSID *pClsid)
{
    UINT num = 0;
    UINT size = 0;

    Gdiplus::GetImageEncodersSize(&num, &size);

    if (!size)
        return false;

    Gdiplus::ImageCodecInfo *pImageCodecInfo = static_cast<Gdiplus::ImageCodecInfo *>(malloc(size));

    if (!pImageCodecInfo)
        return false;

    Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT i = 0; i < num; ++i)
    {
        if (_tcscmp(pImageCodecInfo[i].MimeType, pszFormat) == 0)
        {
            memcpy(pClsid, &pImageCodecInfo[i].Clsid, sizeof(CLSID));
            free(pImageCodecInfo);
            return true;
        }
    }

    free(pImageCodecInfo);
    return false;
}