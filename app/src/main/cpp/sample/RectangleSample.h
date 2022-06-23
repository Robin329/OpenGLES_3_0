//
// Created by Robin on 2021/12/19.
//

#ifndef NDK_OPENGLES_3_0_RECTANGLESAMPLE_H
#define NDK_OPENGLES_3_0_RECTANGLESAMPLE_H

#include "GLSampleBase.h"

class RectangleSample : public GLSampleBase {
public:
    RectangleSample();
    virtual ~RectangleSample();

    virtual void LoadImage(NativeImage *pImage);

    virtual void Init();

    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();
};

#endif // NDK_OPENGLES_3_0_RECTANGLESAMPLE_H
