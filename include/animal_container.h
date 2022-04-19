#pragma once

#include "cinder/gl/gl.h"
#include "herbivore.h"
#include "vegetation.h"

using glm::vec2;

namespace animal_simulator {

/**
 * The container in which all of the animals are contained. This class
 * stores all of the animals and updates them on each frame of the simulation.
 */
  class AnimalContainer {
  public:

    /**
     * Constructs the animal container.
     */
    AnimalContainer();

    /**
     * Complex container for more in depth initialization.
     * @param herbivores The herbivores input to the container.
     * @param top_left_corner of the container.
     * @param bottom_right_corner of the container.
     */
    AnimalContainer(std::vector<Herbivore> & herbivores, vec2 top_left_corner, vec2 bottom_right_corner);

    /**
     * Displays the container walls and the current positions of the animals.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all animals (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();

    /**
     * @returns animals_ vector
     */
    std::vector<Herbivore> GetAnimals();

  private:
    /**
     * Default top-left corner coordinates of the rectangular animal container.
     */
    const int kDefaultXCoord = 100;
    const int kDefaultYCoord = 40;

    /**
     * The default width and height of the animal container.
     */
    const size_t kDefaultWidth = 1200;
    const size_t kDefaultHeight = 500;

    /**
     * The actual width, height, and top left corner coordinates of the animal container.
     */
    size_t width_; // Width of container.
    size_t height_; // Height of container.
    int x_coor_;
    int y_coor_;

    /**
     * A vector storing all the animals within the animal container.
     */
    std::vector<Herbivore> herbivores_;

    /**
     * The max number of herbivores.
     */
    int kMaxHerbivoreCount = 10;

    /**
     * A vector storing all the vegetation within the animal container.
     */
    std::vector<Vegetation> vegetation_;

    /**
     * The max vegetation count.
     */
    int kMaxVegetationCount = 25;

    /**
     * Keeps track of how many frames have passed so as to update spawner.
     */
    int frame_count_ = 0;
  };

}