/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Rect.h"

void CRect::InjectHooks()
{
    RH_ScopedClass(CRect);
    RH_ScopedCategory("Core");

    RH_ScopedInstall(IsFlipped, 0x404190);
    RH_ScopedInstall(Restrict, 0x404200);
    RH_ScopedInstall(Resize, 0x404260);
    RH_ScopedOverloadedInstall(IsPointInside, "", 0x404290, bool(CRect::*)(const CVector2D&) const);
    RH_ScopedOverloadedInstall(IsPointInside, "Tolerance", 0x4042D0, bool(CRect::*)(const CVector2D&, float) const);
    RH_ScopedInstall(SetFromCenter, 0x43E020);
    RH_ScopedOverloadedInstall(GetCenter, "", 0x43E050, void(CRect::*)(float*, float*) const);
    RH_ScopedInstall(StretchToPoint, 0x5327F0);
}

// 0x404200
inline void CRect::Restrict(const CRect& restriction)
{
    if (restriction.left < left)
        left = restriction.left;

    if (restriction.right > right)
        right = restriction.right;

    if (restriction.top < top)
        top = restriction.top;

    if (restriction.bottom > bottom)
        bottom = restriction.bottom;
}

// 0x404260
inline void CRect::Resize(float resizeX, float resizeY)
{
    left   -= resizeX;
    right  += resizeX;
    top    -= resizeY;
    bottom += resizeY;
}

// 0x404290
inline bool CRect::IsPointInside(const CVector2D& point) const
{
    return point.x >= left
        && point.x <= right
        && point.y >= top
        && point.y <= bottom;
}

// 0x4042D0
inline bool CRect::IsPointInside(const CVector2D& point, float tolerance) const
{
    return left   - tolerance <= point.x
        && right  + tolerance >= point.x
        && top    - tolerance <= point.y
        && bottom + tolerance >= point.y;
}

// 0x43E020
inline void CRect::SetFromCenter(float x, float y, float size)
{
    left   = x - size;
    top    = y - size;
    right  = x + size;
    bottom = y + size;
}

// 0x43E050
inline void CRect::GetCenter(float* x, float* y) const
{
    *x = (right + left) / 2.0f;
    *y = (top + bottom) / 2.0f;
}

// 0x5327F0
inline void CRect::StretchToPoint(float x, float y)
{
    if (x < left)
        left = x;

    if (x > right)
        right = x;

    if (y < top)
        top = y;

    if (y > bottom)
        bottom = y;
}
