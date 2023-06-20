#include "RenderSystem.h"
#include "../game/game.h"
#include "../sdlutils/Texture.h"


void RenderSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_START_GAME:
		onGameStart();
		break;
	case _m_PAUSE_GAME:
		onRoundOver();
		break;
	case _m_END_GAME:
		onGameOver(m.end_game_data.win);
		break;
	default: 
		break;
	}
}

void RenderSystem::initSystem()
{
	fighterTex = game->getArrayTexture(FIGHTER);
	bulletTex = game->getArrayTexture(FIRE);
	infoText = game->getArrayText(PAUSE);
	loseText = game->getArrayText(WIN);
	winText = game->getArrayText(LOSE);
}

void RenderSystem::update()
{
	Vector2D pos = { 10, 10 };
	Vector2D posChange = { 30, 0 };
	for (auto e : man->getEntities(ecs::_grp_FIGHTER)) {
		auto tr = man->getComponent<Transform>(e);
		auto h = man->getComponent<Health>(e);
		for (int i = 0; i < h->getLives(); i++) {
			h->getTexture()->render(getTrRect(pos, tr), 0);
			pos = pos + posChange;
		}
	}

	switch (state_) {
	case 0:
		for (auto e : man->getEntities(ecs::_grp_FIGHTER)) {
			auto tr = man->getComponent<Transform>(e);
			fighterTex->render(getTrRect(tr), tr->getRot());
		}
		for (auto e : man->getEntities(ecs::_grp_ASTEROIDS)) {
			auto tr = man->getComponent<Transform>(e);
			auto fI = man->getComponent<FramedImage>(e);
			fI->getTexture()->render(fI->getTextFrame(), getTrRect(tr), tr->getRot());
		}
		for (auto e : man->getEntities(ecs::_grp_BULLETS)) {
			auto tr = man->getComponent<Transform>(e);
			bulletTex->render(getTrRect(tr), tr->getRot());
		}
		break;
	case 1:
		for (auto e : man->getEntities(ecs::_grp_INFO)) {
			auto tr = man->getComponent<Transform>(e);
			infoText->render(getTrRect(tr), tr->getRot());
		}
		break;
	case 2:
		//ASTEROID
		if (winner_ == 1) {
			for (auto e : man->getEntities(ecs::_grp_LOSE)) {
				auto tr = man->getComponent<Transform>(e);
				loseText->render(getTrRect(tr), tr->getRot());
			}
		}
		//FIGHTER
		else if(winner_ == 2){
			for (auto e : man->getEntities(ecs::_grp_WIN)) {
				auto tr = man->getComponent<Transform>(e);
				winText->render(getTrRect(tr), tr->getRot());
			}
		}
		for (auto e : man->getEntities(ecs::_grp_INFO)) {
			auto tr = man->getComponent<Transform>(e);
			infoText->render(getTrRect(tr), tr->getRot());
		}
		
		break;
	default:
		break;
	}

}

SDL_Rect RenderSystem::getTrRect(Transform* tr)
{
	SDL_Rect dest = build_sdlrect(tr->getPos(), tr->getW(), tr->getH());
	return dest;
}

SDL_Rect RenderSystem::getTrRect(Vector2D pos, Transform* tr)
{
	SDL_Rect dest = build_sdlrect(pos, tr->getW(), tr->getH());
	return dest;
}

//Pausa el juego. PAUSE
void RenderSystem::onRoundOver()
{
	winner_ = 0;
	state_ = 1;
}
//Empieza el juego de cero o se vuelve después de pausar. START
void RenderSystem::onGameStart() 
{
	winner_ = 0;
	state_ = 0;
}
//Se acaba el juego, pierdes o ganas. END
void RenderSystem::onGameOver(bool win)
{
	if (win) winner_ = 2;
	else winner_ = 1;

	state_ = 2;
}
