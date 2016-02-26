#pragma once

#include "../scene.hh"

class EndlessKnot : public Scene
{
public:
    EndlessKnot(const Kaleielak &k);

    virtual void draw(cairo_t *cr) override;
};
