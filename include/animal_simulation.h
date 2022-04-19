#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "animal_container.h"

namespace animal_simulator {

/**
 * An app for visualizing the behavior of different animals.
 */
class AnimalSimulationApp : public ci::app::App {
 public:
  /**
   * Basic constructor for the AnimalSimulationApp.
   */
  AnimalSimulationApp();

  /**
   * Sets the background of the visualization before calling AnimalContainer's Display.
   */
  void draw() override;

  /**
   * Updates the visualization to move on to the next frame (thus telling backend to update animal position).
   */
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSizeX = 875 * 1.6;
  const int kWindowSizeY = 875 * .95;
  const int kMargin = 100;

 private:
  /**
   * The Gas container that will be visualized on screen.
   */
  AnimalContainer container_;
};

}  // namespace animal_simulator
