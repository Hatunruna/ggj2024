#include "DebriefEntity.h"

#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Text.h>

#include "GameData.h"
#include "GameHub.h"
#include "GameState.h"

namespace mm {

  DebriefEntity::DebriefEntity(GameHub& game)
  : m_game(game)
  , m_gameState(game.state)
  , m_font(game.resources.getFont("fonts/GoudyBookletter1911.otf"))
  {
  }

  // void DebriefEntity::update(gf::Time time) {
  //
  // }

  void DebriefEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coordinates(target);

    gf::Text title("Shift End", m_font, coordinates.getRelativeCharacterSize(0.12));
    title.setColor(gf::Color::White);
    title.setParagraphWidth(coordinates.getRelativeSize({ 0.7f, 0.0f }).width);
    title.setAlignment(gf::Alignment::Center);
    title.setPosition(coordinates.getRelativePoint({ 0.5f, 0.05f }));
    title.setAnchor(gf::Anchor::TopCenter);
    title.draw(target, states);

    std::string debriefText;
    debriefText += "Correct choices: " + std::to_string(m_gameState.correctChoices) + "\n";
    debriefText += "Incorrect choices: " + std::to_string(m_gameState.incorrectChoices) + "\n";
    const int totalMovies = m_game.data.levelSettings[m_game.state.currentLevel].movieCount;
    debriefText += "Unhandled movies: " + std::to_string(totalMovies - (m_gameState.correctChoices + m_gameState.incorrectChoices)) + "\n";

    gf::Text debrief(debriefText, m_font, coordinates.getRelativeCharacterSize(0.08));
    debrief.setColor(gf::Color::White);
    debrief.setParagraphWidth(coordinates.getRelativeSize({ 0.7f, 0.0f }).width);
    debrief.setAlignment(gf::Alignment::Center);
    debrief.setPosition(coordinates.getRelativePoint({ 0.5f, 0.2f }));
    debrief.setAnchor(gf::Anchor::TopCenter);
    debrief.draw(target, states);

    auto drawBarSide = [&](gf::Vector2f position, gf::Color4f color, float offset = 0.0f) {
      gf::RoundedRectangleShape rect;
      rect.setRadius(10.0f);
      rect.setPosition(coordinates.getRelativePoint(position) + gf::dirx(offset));
      rect.setColor(color);
      rect.setSize(coordinates.getRelativeSize(gf::vec(0.10f, 0.05f)) + gf::dirx(40.0f)); // offset to hide the rounded side
      rect.draw(target, states);
    };

    drawBarSide(gf::vec(0.25f, 0.65f), gf::Color::darker(gf::Color::Red, 0.2f));
    drawBarSide(gf::vec(0.65f, 0.65f), gf::Color::darker(gf::Color::Green, 0.2f), -40.0f);

    auto drawBar = [&](gf::Vector2f position, gf::Color4f color) {
      gf::RectangleShape rect;
      rect.setPosition(coordinates.getRelativePoint(position));
      rect.setOutlineColor(gf::Color::Black);
      rect.setOutlineThickness(coordinates.getRelativeSize(gf::vec(0.001f, 0.00f)).width);
      rect.setColor(color);
      rect.setSize(coordinates.getRelativeSize(gf::vec(0.10f, 0.05f)));
      rect.draw(target, states);
    };

    drawBar(gf::vec(0.35f, 0.65f), gf::Color::darker(gf::Color::fromRgba32(240, 124, 0, 255), 0.1f));
    drawBar(gf::vec(0.45f, 0.65f), gf::Color::darker(gf::Color::Yellow, 0.1f));
    drawBar(gf::vec(0.55f, 0.65f), gf::Color::darker(gf::Color::fromRgba32(143, 255, 34, 255), 0.1f));

    gf::CircleShape cursor;
    cursor.setPointCount(3); // Fake triangle
    cursor.setColor(gf::Color::White);
    int happinessOffset = static_cast<int>(m_gameState.monsterHappiness);
    cursor.setPosition(coordinates.getRelativePoint(gf::vec(0.30f + happinessOffset * 0.10f, 0.63f)));
    cursor.setRadius(coordinates.getRelativeSize(gf::vec(0.025f, 0.025f)).width);
    cursor.setAnchor(gf::Anchor::TopCenter);
    cursor.setRotation(gf::Pi);
    cursor.draw(target, states);
  }

}
