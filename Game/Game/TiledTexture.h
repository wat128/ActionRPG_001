#pragma once
#include <Siv3D.hpp>

class TiledTexture
{
private:
    Texture m_texture;
    Size m_chipSize;
    int32 m_w, m_h;
public:
    TiledTexture(const FilePath& path, const Size& chipSize)
        : m_texture(path)
        , m_chipSize(chipSize)
        , m_w(m_texture.width() / chipSize.x)
        , m_h(m_texture.height() / chipSize.y) {}

    TextureRegion get(const int& index)
    {
        const int x = index % m_w;
        const int y = index / m_w;

        return m_texture(RectF(x * m_chipSize.x, y * m_chipSize.y, m_chipSize));
    }

    inline int32 width() const { return m_w; }
    inline int32 height() const { return m_h; }
    inline const Size& chhipSize() const { return m_chipSize; }
    inline const Texture& getTexture() const { return m_texture; }
};

