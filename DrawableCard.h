#pragma once
#include "Drawable.h"

class DrawableCard :public Drawable {
	Card card;
public:
	DrawableCard();
	void setCard(Card c);
	Card getCard();
	void draw(u32 modelLocation, u64 currentTime);
};