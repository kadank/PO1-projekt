#include "Sprite.h"

Sprite::Sprite(std::string texture_path) {
    this->bitmap = wxBitmap(texture_path, wxBITMAP_TYPE_PNG);
}

Sprite::Sprite(std::string texture_path, wxColor accent) {
    auto tmpBitmap = wxBitmap(texture_path, wxBITMAP_TYPE_PNG);
    auto image = tmpBitmap.ConvertToImage();
    image.Replace(255, 0, 255, accent.Red(), accent.Green(), accent.Blue());
    bitmap = wxBitmap(image);
}

void Sprite::Draw(wxGraphicsContext* ctx, double x, double y, double w, double h, Transform t, int frames) {
    wxImage img = bitmap.ConvertToImage();

    img = img.Scale(ceil(w * t.scale), ceil(h * t.scale), wxIMAGE_QUALITY_NEAREST);

    wxBitmap scaled(img);
    ctx->DrawBitmap(scaled, X(x), Y(y), scaled.GetWidth(), scaled.GetHeight());
}
