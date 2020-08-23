#include "include/filter_test.h"

#define TAG "[native] {{ TEST_NAME }}"

static std::string __GET_FILTER_ATTRS__() {
{{TEST_JSONGEN}}
}

TEST_F(GLFilterTest, {{ TEST_NAME }}) {
    int w = WIDTH;
    int h = HEIGHT;
    FOO::BARCore* pGLCore = FOO::BARCore::SharedGLCore();
    ASSERT_EQ(FOO::BARCore::kNoError, pGLCore->Init(w, h, false));

    const char* path = {{ TEST_PICTURE }};
    std::vector<uint8_t> buffer;
    int img_w = 0, img_h = 0, img_ct = 0;
    ASSERT_TRUE(FOO::load_png(path, buffer, img_w, img_h, img_ct));
    ASSERT_EQ(LIBPNG_COLOR_RGB, img_ct);

    int img_id = pGLCore->GenTexture();
    ASSERT_TRUE(img_id > 0);
    ASSERT_EQ(FOO::BARCore::kNoError, pGLCore->SetPosition(img_id, (w - img_w) / 2, (h - img_h)/ 2, img_w, img_h));
    ASSERT_EQ(FOO::BARCore::kNoError, pGLCore->TexImage2D(img_id, buffer, img_w, img_h, FOO::BARCore::GLC_RGB));

    std::string attrs = __GET_FILTER_ATTRS__();
    LOGD(TAG, "attrs:%s\n", attrs.c_str());
    ASSERT_EQ(FOO::BARCore::kNoError, pGLCore->SetRender(img_id, attrs.c_str(), NULL));

    ALOGV("draw begin\n");
    ASSERT_EQ(FOO::BARCore::kNoError, pGLCore->BindDefaultCanvas());

    pGLCore->Draw(img_id);
    pGLCore->Flush();
    ALOGV("draw end\n");
    canvas_shot({{TEST_IMAGE_OUTPUT}}, w, h);
    pGLCore->Release();
}