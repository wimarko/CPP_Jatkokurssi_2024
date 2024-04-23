
#include <box2d.h>
#include <SDL.h>

#include <SDL_image.h>
#include <SDL_timer.h>

#include<stdio.h>


#define DEG_TO_RAD(X)	((X) * ((float)M_PI / 180.0f))

int main(int argc, char* argv[])
{
    //create gravity
    b2Vec2 gravity(0.0f, 9.2f);

    //greate world, with gravity
    b2World world(gravity);
        
    //define a body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.f, 400.f);

    //create a body (static, doesn't collide with other static bodies)
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox; //half-width, half-height params
    groundBox.SetAsBox(400.f, 10.f);

    groundBody->CreateFixture(&groundBox, 0.f);

    //Dynamic Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400.f, 200.f);
    b2Body* body = world.CreateBody(&bodyDef);

    //create polygon-shape for box
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.f, 1.f);

    //set characteristics
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;

    //create fixture
    body->CreateFixture(&fixtureDef);


    //SIMULATING WORLD
    float timestep = 1.0f / 60.f;

    //iteration times for physics / step
    int32 veloIterations = 7;
    int32 posIterations = 2;


    //sdl
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow("Wiindow", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* surface;
    surface = IMG_Load("boxi.jpg");

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture* gtex = SDL_CreateTextureFromSurface(renderer, surface);
    // clears main-memory
    SDL_FreeSurface(surface);

    SDL_Rect dest;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    SDL_Rect ground;
    SDL_QueryTexture(gtex, NULL, NULL, &ground.w, &ground.h);
    // adjust height and width of our image box.
    ground.w /= 600;
    ground.h /= 6;

   SDL_SetRenderDrawColor(renderer, 0, 55, 0, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    /*SDL_Delay(3000);*/

    int close = 0;



    while(!close)
    {
        SDL_Event event;

        // Handle SDL events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close = 1;
            }
        }

        world.Step(timestep, veloIterations, posIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

        SDL_RenderClear(renderer);



        dest.x = position.x;
        dest.y = position.y;
        /*SDL_RenderCopy(renderer, tex, NULL, &dest);*/
         // Render the texture at the new position and angle
        SDL_RenderCopyEx(renderer, tex, NULL, &dest, angle * (180.f / M_PI),
            NULL, SDL_FLIP_NONE);
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    return 0;
}