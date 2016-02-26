#include "endless-knot.hh"
#include "../point.hh"

EndlessKnot::EndlessKnot(const Kaleielak &k)
    : Scene(k)
{

}

void
EndlessKnot::draw(cairo_t *cr)
{
    cairo_set_source_rgb(cr, 0.75, 0.58, 0.13);

    const double scale = 1.0 / 10.0;

    cairo_scale(cr, scale, scale);

    static const Point points[] = {
        //{ 0, 0 },
        { 2, 2 },
        { 1, 3},
        { -3, -1},
        { -4, 0},
        { -3, 1},
        { 1, -3},
        { 2, -2},
        { -2, 2},
        { -1, 3},
        { 3, -1},
        { 4, 0},
        { 3, 1},
        { -1, -3},
        { -2, -2},
        { 0, 0 },
    };

    cairo_move_to(cr, 0, 0);
    for (auto & point : points)
    {
        cairo_line_to(cr, point.x, point.y);
    }

    cairo_scale(cr, 1.0 / scale, 1.0 /scale);
    cairo_stroke(cr);
}
