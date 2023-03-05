#include "GameStateMachine.h"

GameState* GameStateMachine::currentState()
{
    return gameStack.top();
}

void GameStateMachine::pushState(GameState* state)
{
    gameStack.push(state);
    gameStack.top()->onEnter();
}

void GameStateMachine::changeState(GameState* state)
{

    if (!gameStack.empty() && gameStack.top()->onExit())
    {
        delete gameStack.top();
        gameStack.pop();
    }

    gameStack.push(state);

    gameStack.top()->onEnter();
}

void GameStateMachine::popState()
{
    if (!gameStack.empty() && gameStack.top()->onExit())
    {
        delete gameStack.top();
        gameStack.pop();
    }
}

void GameStateMachine::update()
{
    if (!gameStack.empty())
    {
        gameStack.top()->update();
    }
}

void GameStateMachine::render()
{
    if (!gameStack.empty())
    {
        gameStack.top()->render();
    }
}
