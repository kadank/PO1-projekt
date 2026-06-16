#ifndef PROJEKT_TRANSFORM_H
#define PROJEKT_TRANSFORM_H

struct Transform {
    double scale;
    double offsetX;
    double offsetY;
};

#define X(x) floor(t.offsetX + (x) * t.scale)
#define Y(y) floor(t.offsetY + (y) * t.scale)
#define DONT_SCALE (Transform){1.0, 0.0, 0.0}

#endif //PROJEKT_TRANSFORM_H
