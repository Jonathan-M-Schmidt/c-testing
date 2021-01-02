#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include "../tuple/tuple.c"

struct Projectile {
    struct Tuple position;
    struct Tuple velocity;
};

struct Environment {
    struct Tuple gravity;
    struct Tuple wind;
};

struct World {
    float x;
    float y;
    float zoom;
};

void printProjectile(struct Projectile p) {
    printf("Position:\n");
    printTuple(p.position);
    printf("Velocity:\n");
    printTuple(p.velocity);
};

void printWorld(struct World world, struct Projectile p) {
    float EPSILON = world.zoom;
    int getsPrinted = 0;
    int arraySize = ceil((world.x/world.zoom) * (world.y/world.zoom)) + world.y;
    char string[arraySize];
    for( float i = world.y; i > 0; i-=world.zoom) {
        int isEqualY = fabs(p.position.y - i) < EPSILON;
        for( float j = 0; j < world.x; j+=world.zoom ){
            int isEqualX = fabs(p.position.x - j) < EPSILON;
            if( isEqualX == 1 && isEqualY == 1 && getsPrinted == 0)  {
                strcat(string, "#");
                getsPrinted = 1;
            } else {
                strcat(string, ".");
            }
        }
        strcat(string, "\n");
    }
    printf(string);
};

struct Projectile tick( struct Environment env, struct Projectile pro ) {
    struct Tuple newPos = add( pro.position, pro.velocity );
    struct Tuple newVel = add( pro.velocity, add( env.gravity, env.wind ) );
    struct Projectile p = { newPos, newVel };
    return p;
};

int main() {
    printf("Running chapter 1\n");
    struct Projectile p = {createPoint(0, 1, 0), normalize(createVector(1, 1, 0))};
    struct Environment env = {createVector(0, -0.1, 0), createVector(-0.01, 0, 0)};
    struct World world = {12.0, 5.0, 0.25};
    int tickCounter = 0;
    while( p.position.y > 0 ) {
        system("cls");
        printWorld(world, p);
        printProjectile(p);
        p = tick(env, p);
        tickCounter++;
        Sleep(200);
    }
    printf("ticks needed: %i\n", tickCounter);
};
