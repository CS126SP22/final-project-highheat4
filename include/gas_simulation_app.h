#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * Basic constructor for the IdealGasApp.
   */
  IdealGasApp();

  /**
   * Sets the background of the visualization before calling GasContainer's Display.
   */
  void draw() override;

  /**
   * Updates the visualization to move on to the next frame (thus telling backend to update particle position).
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
  GasContainer container_;
};

}  // namespace idealgas
