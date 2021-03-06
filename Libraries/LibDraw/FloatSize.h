#pragma once

#include <AK/String.h>
#include <AK/LogStream.h>
#include <LibDraw/Orientation.h>

class FloatSize {
public:
    FloatSize() {}
    FloatSize(float w, float h)
        : m_width(w)
        , m_height(h)
    {
    }

    bool is_null() const { return !m_width && !m_height; }
    bool is_empty() const { return m_width <= 0 || m_height <= 0; }

    float width() const { return m_width; }
    float height() const { return m_height; }

    float area() const { return width() * height(); }

    void set_width(float w) { m_width = w; }
    void set_height(float h) { m_height = h; }

    bool operator==(const FloatSize& other) const
    {
        return m_width == other.m_width && m_height == other.m_height;
    }

    bool operator!=(const FloatSize& other) const
    {
        return !(*this == other);
    }

    FloatSize& operator-=(const FloatSize& other)
    {
        m_width -= other.m_width;
        m_height -= other.m_height;
        return *this;
    }

    FloatSize& operator+=(const FloatSize& other)
    {
        m_width += other.m_width;
        m_height += other.m_height;
        return *this;
    }

    float primary_size_for_orientation(Orientation orientation) const
    {
        return orientation == Orientation::Vertical ? height() : width();
    }

    void set_primary_size_for_orientation(Orientation orientation, float value)
    {
        if (orientation == Orientation::Vertical)
            set_height(value);
        else
            set_width(value);
    }

    float secondary_size_for_orientation(Orientation orientation) const
    {
        return orientation == Orientation::Vertical ? width() : height();
    }

    void set_secondary_size_for_orientation(Orientation orientation, float value)
    {
        if (orientation == Orientation::Vertical)
            set_width(value);
        else
            set_height(value);
    }

    String to_string() const { return String::format("[%gx%g]", m_width, m_height); }

private:
    float m_width { 0 };
    float m_height { 0 };
};

inline const LogStream& operator<<(const LogStream& stream, const FloatSize& value)
{
    return stream << value.to_string();
}
