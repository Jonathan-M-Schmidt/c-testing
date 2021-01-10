#include <stdio.h>
#include "../color/color.c"
#include "../canvas/canvas.c"

typedef struct Projectile {
    struct Tuple position;
    struct Tuple velocity;
} Projectile;

typedef struct Environment {
    struct Tuple gravity;
    struct Tuple wind;
} Environment;

Projectile tick( Environment env, Projectile pro ) {
    Tuple newPos = add( pro.position, pro.velocity );
    Tuple newVel = add( pro.velocity, add( env.gravity, env.wind ) );
    Projectile p = { newPos, newVel };
    return p;
};

int main() {
    Tuple start = createPoint(0, 1, 0);
    Tuple velocity = multiply(normalize(createVector(1, 1.8, 0)), 11.25);
    Projectile projectile = {start, velocity};
    Tuple gravity = createVector(0, -0.1, 0);
    Tuple wind = createVector(-0.01, 0, 0);
    Environment env = {gravity, wind};
    Canvas* canvas = createCanvas(900, 550);
    while( projectile.position.y > 0 ) {
        int pos_y = canvas->height - projectile.position.y;
        int pos_x = projectile.position.x;
        writePixel(canvas, pos_x, pos_y, createColor(0.8, 0.2, 0));
        projectile = tick(env, projectile);
    }
    canvasToPpm(canvas, "result_chapter2");
};
