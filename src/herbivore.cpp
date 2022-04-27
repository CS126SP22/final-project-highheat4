#include "herbivore.h"
#include "vegetation.h"

namespace animal_simulator {

  using glm::vec2;

  Herbivore::Herbivore(vec2 new_position, vec2 new_velocity,
                       float new_size, ci::Color new_color) {
    velocity_ = new_velocity;
    position_ = new_position;
    size_ = new_size;
    color_ = new_color;
    max_health_ = Random::fRand(0, kMaxSpawnHealth);
    health_ = max_health_;
    max_energy_ = kDefaultEnergy;
    energy_ = max_energy_;
    growth_rate_ = Random::fRand(0, kMaxSpawnGrowthRate);
    base_eat_rate_ = Random::fRand(0, kMaxEatRate);
    need_for_speed_ = Random::fRand(0,kMaxNeedForSpeed);
  }

  Herbivore::Herbivore() {
    double kMinVelocity = 0.0;
    double kMaxVelocity = 10.0;
    ci::Color new_color = cinder::Color(Random::fRand(0,1),Random::fRand(0,1),Random::fRand(0,1));
    *this = Herbivore(vec2(rand() % kDefaultWidth + kDefaultXCoord,
                           rand() % kDefaultHeight + kDefaultYCoord), //position
vec2(Random::fRand(kMinVelocity, kMaxVelocity),
     Random::fRand(kMinVelocity, kMaxVelocity)),    //velocity
      Random::fRand(0, kMaxSpawnSize), new_color);
  }

  Herbivore::Herbivore(vec2 position, vec2 velocity, float radius,
  float new_size, ci::Color new_color) {
      position_ = position;
      velocity_ = velocity;
      size_ = new_size;
      color_ = new_color;
      max_energy_ = kDefaultEnergy;
      energy_ = max_energy_;
  }

    Herbivore::Herbivore(vec2 position, vec2 new_velocity, ci::Color new_color, float new_size, float new_growth_rate,
                         float new_eat_rate, float new_max_energy,
                         float new_max_health, float new_need_for_speed) {
      position_ = position;
      velocity_ = new_velocity;
      color_ = new_color;
      size_ = new_size;
      growth_rate_ = new_growth_rate;
      base_eat_rate_ = new_eat_rate;
      max_energy_ = new_max_energy;
      energy_ = max_energy_;
      max_health_ = new_max_health;
      health_ = new_max_health;
      need_for_speed_ = new_need_for_speed;
      has_eaten_ = false;
  }

  glm::vec2 Herbivore::GetPosition() const {
    return position_;
  }

  glm::vec2 Herbivore::GetVelocity() const {
    return velocity_;
  }

    float Herbivore::GetMass() const {
        return size_;
    }

    float Herbivore::GetRadius() const {
        return size_;
    }

    ci::Color Herbivore::GetColor() const {
        return color_;
    }

  void Herbivore::SetVelocity(glm::vec2 new_velocity) {
    velocity_ = new_velocity;
  }

  void Herbivore::Move() {
    size_ += growth_rate_;
    age_ += 1;
    velocity_ = glm::normalize(velocity_) * need_for_speed_ * energy_ / max_energy_;
    if (energy_ > 0) {
        energy_ -= this -> CalculateEnergyConsumption();
        position_ += velocity_;
    }
  }

  float Herbivore::CalculateEnergyConsumption() { //.length
      float kEnergyDivisor = 100000;
      return ((1+pow(size_,2)) *
              (1 + sqrt(velocity_.x*velocity_.x + velocity_.y*velocity_.y)) * (1+max_health_)) / kEnergyDivisor;
  }

  bool Herbivore::IsDead() {
      float kMinThreshold = 0.01;
      if (energy_ < kMinThreshold || health_ < kMinThreshold) {
          return true;
      }
      return false;
  }

  float Herbivore::CalculateDistance(Herbivore animal_2) const {
    return (float) sqrt(pow(this -> position_.x - animal_2 . position_.x, 2) +
              pow(this -> position_.y - animal_2.position_.y, 2));
  }

    float Herbivore::CalculateDistance(Vegetation food) const {
        return (float) sqrt(pow(this -> position_.x - food.GetPosition().x, 2) +
                            pow(this -> position_.y - food.GetPosition().y, 2));
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

    bool Herbivore::IsTouchingVegetation(Vegetation food) const {
        float radius_1 = this -> GetRadius();
        float radius_2 = food.GetSize();

        // Hits animal
        if (this -> CalculateDistance(food) <= radius_1 + radius_2) {
            return true;
        } else {
            return false;
        }
    }

  bool Herbivore::Consume(Vegetation & food) {
    has_eaten_ = true;
    if (energy_ < max_energy_) {
        if (sqrt(base_eat_rate_ * size_) < max_energy_)
            energy_ += sqrt(base_eat_rate_ * size_);
        else
            energy_ = max_energy_;
        return food.Eaten(sqrt(base_eat_rate_ * size_));
    }
    return false;
  }

  void Herbivore::CheckContainerCollision(float left_wall, float right_wall, float top_wall, float bottom_wall) {
    if (this -> GetPosition().x - this -> size_ <= left_wall) { // Hits left wall
      if (this -> GetVelocity().x < 0) {
        this -> SetVelocity(this->GetNegatedVelocity(true));
      }
    }

    if (this -> GetPosition().x + this -> size_ >= right_wall) { // Hits right wall
      if (this -> GetVelocity().x > 0) {
        this -> SetVelocity(this->GetNegatedVelocity(true));
      }
    }

    if (this -> GetPosition().y - this -> size_ <= top_wall) { // Hits top wall
      if (this -> GetVelocity().y < 0) {
        this -> SetVelocity(this -> GetNegatedVelocity(false));
      }
    }

    if (this -> GetPosition().y + this -> size_ >= (bottom_wall)) { // Hits bottom wall
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

  Herbivore Herbivore::Reproduce() {
      float new_need_for_speed = Random::fReproductionDistribution(need_for_speed_);
      ci::Color new_color = color_;
      float new_growth_rate = Random::fReproductionDistribution(growth_rate_);
      float new_size = 1;
      float new_eat_rate = Random::fReproductionDistribution(base_eat_rate_);
      float new_max_energy = Random::fReproductionDistribution(max_energy_);
      float new_max_health = Random::fReproductionDistribution(max_health_);
      vec2 new_velocity = vec2(-velocity_.x, -velocity_.y);
      vec2 new_position = vec2(position_.x + new_size, position_.y - new_size);
      Herbivore herb = Herbivore(new_position, new_velocity, new_color, new_size, new_growth_rate, new_eat_rate, new_max_energy,
                new_max_health, new_need_for_speed);
      return herb;
  }

  bool Herbivore::CanReproduce() {
      if (age_ >= kReproductionAge && age_ % kMinReproductionTimer == 0 && has_eaten_) {
          return true;
      }
      return false;
  }
}