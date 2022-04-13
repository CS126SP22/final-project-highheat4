#include "herbivore.h"

namespace animal_simulator {

  using glm::vec2;

  Herbivore::Herbivore(vec2 new_position, vec2 new_velocity, float new_radius,
                       float new_mass, ci::Color new_color) {
    velocity_ = new_velocity;
    position_ = new_position;
    mass_ = new_mass;
    radius_ = new_radius;
    color_ = new_color;
    health_ = kDefaultHealth;
  }

  Herbivore Herbivore::GenerateRandomAnimal(float new_radius, float new_mass, ci::Color new_color) {
    double kMinVelocity = 0.0;
    double kMaxVelocity = 10.0;

    Herbivore new_animal =
    Herbivore(vec2(rand() % kDefaultWidth + kDefaultXCoord, rand() % kDefaultHeight + kDefaultYCoord), //position
vec2(Herbivore::fRand(kMinVelocity, kMaxVelocity),
     Herbivore::fRand(kMinVelocity, kMaxVelocity)),    //velocity
      new_radius, new_mass, new_color);
    return new_animal;
  }

  std::vector<Herbivore> Herbivore::SpawnAnimals(size_t count) {
    //constant labeling
    glm::vec3 radii;
    radii[0] = 20;
    radii[1] = 5;
    radii[2] = 30;

    glm::vec3 masses;
    masses[0] = 10;
    masses[1] = 50;
    masses[2] = 20;

    const ci::Color kColors [3] = {ci::Color("yellow"), ci::Color("red"),ci::Color("blue")};

    std::vector<Herbivore> animals;
    for (size_t i = 0; i < count; i++) {
      for (int j = 0; j < masses.length(); j++) {
        animals.push_back(GenerateRandomAnimal(radii[j], masses[j], kColors[j]));
      }
    }

    return animals;
  }

  glm::vec2 Herbivore::GetPosition() const {
    return position_;
  }

  glm::vec2 Herbivore::GetVelocity() {
    return velocity_;
  }

  void Herbivore::SetVelocity(glm::vec2 new_velocity) {
    velocity_ = new_velocity;
  }

  float Herbivore::GetMass() {
    return mass_;
  }

  float Herbivore::GetRadius() const {
    return radius_;
  }

  ci::Color Herbivore::GetColor() const {
    return color_;
  }

  void Herbivore::Move() {
    position_ += velocity_;
  }

  float Herbivore::CalculateDistance(Herbivore animal_2) const {
    return (float) sqrt(pow(this -> position_.x - animal_2 . position_.x, 2) +
              pow(this -> position_.y - animal_2.position_.y, 2) * 1.0);
  }

//// Source: Stackoverflow
  double Herbivore::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
  }

  bool Herbivore::IsTouchingAnimal(Herbivore animal_2) const {
    float radius_1 = this -> GetRadius();
    float radius_2 = animal_2.GetRadius();

    // Hits animal
    if (this -> CalculateDistance(animal_2) <= radius_1 + radius_2) {
      return true;
    } else {
      return false;
    }
  }

  void Herbivore::CheckContainerCollision(float left_wall, float right_wall, float top_wall, float bottom_wall) {
    if (this -> GetPosition().x - this -> radius_ <= left_wall) { // Hits left wall
      if (this -> GetVelocity().x < 0) {
        this -> SetVelocity(this->GetNegatedVelocity(true));
      }
    }

    if (this -> GetPosition().x + this -> radius_ >= right_wall) { // Hits right wall
      if (this -> GetVelocity().x > 0) {
        this -> SetVelocity(this->GetNegatedVelocity(true));
      }
    }

    if (this -> GetPosition().y - this -> radius_ <= top_wall) { // Hits top wall
      if (this -> GetVelocity().y < 0) {
        this -> SetVelocity(this -> GetNegatedVelocity(false));
      }
    }

    if (this -> GetPosition().y + this -> radius_ >= (bottom_wall)) { // Hits bottom wall
      if (this -> GetVelocity().y > 0) {
        this -> SetVelocity(this -> GetNegatedVelocity(false));
      }
    }
  }

  vec2 Herbivore::GetNegatedVelocity(bool x) { //true for x, false for y
    float new_x_vel = this->GetVelocity().x;
    float new_y_vel = this->GetVelocity().y;
    if (x)
      new_x_vel *= -1;
    else
      new_y_vel *= -1;

    return vec2(new_x_vel, new_y_vel);
  }

  std::vector<vec2> Herbivore::CalculateCollisionResults(Herbivore animal_2) {
    //Initialization of basic variables
    std::vector<vec2> new_velocities;

    //Updates "this" animal velocity
    vec2 new_velocity_1 = this ->ApplyCollisionFormula(animal_2);
    //Updates animal_2 velocity
    vec2 new_velocity_2 = animal_2.ApplyCollisionFormula(*this);

    //Returning updated values
    new_velocities.push_back(new_velocity_1);
    new_velocities.push_back(new_velocity_2);
    return new_velocities;
  }

  vec2 Herbivore::ApplyCollisionFormula (Herbivore animal_2) {
    std::vector<vec2> new_velocities;
    vec2 position_1 = this -> GetPosition();
    vec2 velocity_1 = this -> GetVelocity();
    float mass_1 = this -> GetMass();

    vec2 position_2 = animal_2.GetPosition();
    vec2 velocity_2 = animal_2.GetVelocity();
    float mass_2 = animal_2.GetMass();

    //Updates "this" animal velocity
    return velocity_1 - ((2 * mass_2) / (mass_1 + mass_2)) * (glm::dot((velocity_1 - velocity_2),
         (position_1 - animal_2.GetPosition()))
       / (float) pow(glm::length(position_1 - animal_2.GetPosition()), 2))
                 * (position_1 - position_2);
  }

  bool Herbivore::ApproachesOtherAnimal(Herbivore animal_2) {
    float relative_displacement = glm::dot(this -> GetVelocity() - animal_2.GetVelocity(),
                         this -> GetPosition() - animal_2.GetPosition());
    if (relative_displacement < 0) {
      return true;
    }

    return false;
  }
}