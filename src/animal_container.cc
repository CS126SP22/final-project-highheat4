#include "animal_container.h"
#include "herbivore.h"

namespace animal_simulator {

  using glm::vec2;

  AnimalContainer::AnimalContainer() {
    width_ = kDefaultWidth;
    height_ = kDefaultHeight;
    x_coor_ = kDefaultXCoord;
    y_coor_ = kDefaultYCoord;

    Vegetation vegetation = Vegetation(vec2(kDefaultXCoord, kDefaultYCoord), vec2(kDefaultXCoord + kDefaultWidth, kDefaultYCoord + kDefaultHeight));
    vegetation_.push_back(vegetation);
    herbivores_.push_back(Herbivore(vec2(kDefaultXCoord+50, kDefaultYCoord+50), vec2(4.5,1.5),2, ci::Color("blue")));
  }

  AnimalContainer::AnimalContainer(std::vector<Herbivore> & animals, vec2 top_left_corner, vec2 bottom_right_corner) {
    x_coor_ = top_left_corner.x;
    y_coor_ = top_left_corner.y;
    width_ = bottom_right_corner.x - x_coor_;
    height_ = bottom_right_corner.y - y_coor_;

    herbivores_ = animals;
    Vegetation vegetation = Vegetation(top_left_corner, bottom_right_corner);
    vegetation_.push_back(vegetation);
  }

  std::vector<Herbivore> AnimalContainer::GetAnimals() {
    return herbivores_;
  }

  void AnimalContainer::Display() const {
    for (size_t i = 0; i < herbivores_.size(); i++) {
      ci::gl::color(herbivores_.at(i).GetColor());
      ci::gl::drawSolidCircle(herbivores_.at(i).GetPosition(), herbivores_.at(i).GetRadius());
    }

    ci::gl::drawStrokedRect(ci::Rectf(vec2(x_coor_, y_coor_),
                      vec2(x_coor_ + width_, y_coor_ + height_)));

    for (int i = 0; i < vegetation_.size(); i++) {
      vegetation_[i].Draw();
    }
  }

  void AnimalContainer::AdvanceOneFrame() {
    for (size_t i = 0; i < herbivores_.size(); i++) {
      //Checks and updates upon wall collision

      herbivores_.at(i).CheckContainerCollision(x_coor_, x_coor_ + width_, y_coor_, y_coor_ + height_);

      //Checks and updates upon animal collision
      for (size_t j = i + 1; j < herbivores_.size(); j++) {
        if (herbivores_.at(i).ApproachesOtherAnimal(herbivores_.at(j))) {
          if (herbivores_.at(i).IsTouchingAnimal(herbivores_.at(j))) {
            //Update velocities
            std::vector<vec2> new_velocities =
                herbivores_.at(i).CalculateCollisionResults(herbivores_.at(j));

            herbivores_.at(i).SetVelocity(new_velocities.at(0));
            herbivores_.at(j).SetVelocity(new_velocities.at(1));
          }
        }
      }
        for (int k = 0; k < vegetation_.size(); k++) {
            if (herbivores_.at(i).IsTouchingVegetation(vegetation_[k]) &&
                    herbivores_.at(i).Consume(vegetation_[k])) {
                vegetation_.erase(vegetation_.begin() + k);
            }
        }
      herbivores_.at(i).Move();
      if (herbivores_.at(i).IsDead())
          herbivores_.erase(herbivores_.begin() + i);
    }

    if (frame_count_ > 60) {
        if (vegetation_.size() < kMaxVegetationCount)
            vegetation_.push_back(Vegetation(vec2(kDefaultXCoord, kDefaultYCoord),
                     vec2(kDefaultXCoord + kDefaultWidth, kDefaultYCoord + kDefaultHeight)));
        if (herbivores_.size() < kMaxHerbivoreCount)
        {herbivores_.push_back(Herbivore());}
        frame_count_ = 0;
        for (int i = 0; i < vegetation_.size(); i++) {
            vegetation_[i].Grow();
        }
    }
    frame_count_++;
  }


}  // namespace animal_simulator
