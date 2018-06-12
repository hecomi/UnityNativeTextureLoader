#include <cstdio>
#include <png.h>
#include "png_loader.h"
#include "util.h"

using namespace NativeImageLoader;


void PngLoader::SetData(const void *pData, size_t dataSize)
{
    m_pngData = std::make_unique<unsigned char[]>(dataSize);
    m_pngDataSize = dataSize;
    memcpy(m_pngData.get(), pData, dataSize);
}


void PngLoader::Load()
{
    if (m_pngDataSize < 8) return;

    const auto *pHeader = reinterpret_cast<png_byte*>(m_pngData.get());
    if (png_sig_cmp(pHeader, 0, 8)) return;

    auto png = png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr);
    if (!png) return;

    auto info = png_create_info_struct(png);
    if (!info) return;

    ScopeReleaser releaser([&]
    {
        png_destroy_read_struct(&png, &info, nullptr);
    });

    struct Data
    {
        unsigned char *m_pData;
        unsigned long m_offset;
    };
    Data data
    {
        static_cast<unsigned char*>(m_pngData.get()),
        8,
    };

    png_set_read_fn(
        png,
        &data,
        [](png_structp png, png_bytep buf, png_size_t size)
        {
            auto &data = *static_cast<Data*>(png_get_io_ptr(png));
            memcpy(buf, data.m_pData + data.m_offset, size);
            data.m_offset += size;
        });

    png_set_sig_bytes(png, 8);
    png_read_png(
        png,
        info,
        PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
        nullptr);

    const auto type = png_get_color_type(png, info);
    switch (type)
    {
        case PNG_COLOR_TYPE_PALETTE:
            png_set_palette_to_rgb(png);
            m_format = GL_RGB;
            m_alignment = 1;
            break;
        case PNG_COLOR_TYPE_RGB:
            m_format = GL_RGB;
            m_alignment = 1;
            break;
        case PNG_COLOR_TYPE_RGBA:
            m_format = GL_RGBA;
            m_alignment = 4;
            break;
        default:
            return;
    }

    const size_t rowBytes = png_get_rowbytes(png, info);
    m_width = png_get_image_width(png, info);
    m_height = png_get_image_height(png, info);
    m_rawData = std::make_unique<unsigned char[]>(rowBytes * m_height);

    const auto rows = png_get_rows(png, info);
    for (int i = 0; i < m_height; ++i)
    {
        const size_t offset = rowBytes * i;
        memcpy(m_rawData.get() + offset, rows[i], rowBytes);
    }

    m_hasLoaded = true;
}


void PngLoader::UpdateTexture()
{
    if (!HasLoaded() || m_texture == 0) return;

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, m_alignment);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        m_width,
        m_height,
        0,
        m_format,
        GL_UNSIGNED_BYTE,
        m_rawData.get());

    glBindTexture(GL_TEXTURE_2D, 0);
}
