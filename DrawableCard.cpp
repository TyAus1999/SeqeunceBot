#include "DrawableCard.h"

DrawableCard::DrawableCard() :Drawable(DrawableTypeCard) {

}

void DrawableCard::setCard(Card c) {
	card = c;
}

Card DrawableCard::getCard() {
	return card;
}

void DrawableCard::draw(u32 modelLocation, u64 currentTime) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}