#include "Character.h"

#include <Gameplay.h>
#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Character::Character(Gameplay *context)
{
    /*
    NOTE:
        - Just a good ol' regular constructor.
    */
    this->context = context;
}
Character::~Character()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
void Character::setAnimator(Animator<string> animator)
{
    this->animator = animator;
}

Gameplay *Character::getContext()
{
    return this->context;
}

Animator<string> &Character::getAnimator()
{
    return this->animator;
}
/*
SECTION 3: OTHER METHODS
*/

void Character::render()
{
    /*
    NOTE:
        - A scrolling level (or a camera that follows the sprite) has
        been implemented. This function will always have the camera
        follow the character.
    */

    SDL_Rect &viewport = this->getViewport();

    viewport.x = this->getRelativePosition().getX();
    viewport.y = this->getRelativePosition().getY();

    SDL_Renderer *renderer = this->getContext()->getContext()->getRenderer();

    if (this->getDirectionFacing() == Direction::LEFT)
    {
        /*
        NOTE:
            - By default, all character textures will be facing right. We flip
            it if the player is trying to go left. We use `SDL_RenderCopyEx()`
            instead of `SDL_RenderCopy()` for this purpose.
        */
        const SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        if (SDL_RenderCopyEx(renderer, this->getTexture(), NULL, &viewport, 0.00,
                             NULL, flip))
        {
            cerr << "Error: unable to render the current texture." << endl;
            assert(false);
        }
    }
    else if (this->getDirectionFacing() == Direction::RIGHT ||
             this->getDirectionFacing() == Direction::NONE)
    {
        if (SDL_RenderCopy(renderer, this->getTexture(), NULL, &viewport))
        {
            cerr << "Error: unable to render the current texture." << endl;
            assert(false);
        }
    }
}