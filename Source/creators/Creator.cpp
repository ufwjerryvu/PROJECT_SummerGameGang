#include "Creator.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Creator::Creator()
{
    /*
    NOTE:
        - Empty, permanently.
    */
}

Creator::~Creator()
{
    /*
    NOTE:
        - Empty, permanently.
    */
}

/*
SECTION 2: CREATOR FUNCTIONS
*/
Button Creator::createButton(SDL_Renderer *renderer, string name, Coordinates position)
{
    FileHandler file = FileHandler();
    string types[] = {"idle", "hover", "pressed"};
    map<string, SDL_Texture *> animation;

    for (string type : types)
    {
        string path = "Assets/Sprite/Button/" + name + "_" + type + ".png";
        animation[type] = file.loadTexture(renderer, path);
    }

    return Button(position, animation);
}

Player *Creator::createPlayer(Gameplay *context)
{
    Player *player = new Player(context);

    vector<SDL_Texture *> seq;
    SDL_Renderer *renderer = context->getContext()->getRenderer();
    for (char i = '1'; i < '9'; i++)
    {
        string dir = "Assets/Sprite/Character/Player/Ragdoll/run" + string(1, i);
        dir += ".png";
        seq.push_back(FileHandler().loadTexture(renderer, dir));
    }

    map<string, Animation> animations;
    animations["run"] = Animation();
    animations["run"].setFrames(seq);
    animations["run"].setInterval(5);

    Animator<string> animator = Animator<string>();

    animator.setAnimations(animations);
    animator.setKey("run");

    player->setAnimator(animator);
    player->setAbsolutePosition(Coordinates(100, 100));
    player->setDirectionFacing(Direction::LEFT);
    player->Runnable::setSpeed(5);
    player->setTexture(animator.getCurrentFrame());

    return player;
}