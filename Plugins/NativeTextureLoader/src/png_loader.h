#include <memory>
#include <png.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#endif

namespace NativeImageLoader
{

class PngLoader
{
public:
    void SetData(const void *pData, size_t size);
    void SetTexture(GLuint texture) { m_texture = texture; }
    void Load();
    void UpdateTexture();
    bool HasLoaded() const { return m_hasLoaded; }
    bool HasTextureUpdated() const { return m_hasUpdated; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    std::unique_ptr<unsigned char[]> m_pngData;
    size_t m_pngDataSize = 0;
    std::unique_ptr<unsigned char[]> m_rawData;
    bool m_hasLoaded = false;
    bool m_hasUpdated = false;
    GLuint m_texture = 0;
    GLenum m_format = 0;
    GLint m_alignment = 1;
    size_t m_dataSize = 0;
	png_uint_32 m_width = 0;
    png_uint_32 m_height = 0;
};

}
