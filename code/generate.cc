#include <array>
#include <iostream>
#include <random>
#include <string_view>

#include <gf/Random.h>

namespace {
  constexpr std::string_view Countries[] = {
    "Canterlot",
    "Gallifrey",
    "Hyrule",
    "Innistrad",
    "Morrowind",
    "Temeria",
    "Valinor",
    "Wonderland",
  };

  constexpr std::string_view Genres[] = {
    "Action",
    "Comedy",
    "Drama",
    "Fantasy",
    "Horror",
    "Musical",
    "Romance",
    "ScienceFiction",
    "Western",
  };

  constexpr std::string_view Techniques[] = {
    "Animated",
    "LiveAction",
    "StopMotion",
  };

  constexpr std::string_view Ratings[] = {
    "0+",
    "12+",
    "16+",
    "18+",
  };

  void displayOne(gf::Random& random) {
    std::discrete_distribution<std::size_t> techniqueDistribution({ 0.3, 0.65, 0.05 });

    std::cout << "  {\n";
    std::cout << "    \"title\": \"\",\n";
    std::cout << "    \"year\": " << random.computeUniformInteger(1970, 2024) << ",\n";
    std::cout << "    \"duration\": " << random.computeUniformInteger(60, 200) << ",\n";
    std::cout << "    \"note\": " << random.computeUniformInteger(1, 5) << ",\n";
    std::cout << "    \"country\": \"" << Countries[random.computeUniformInteger(std::size_t(0), std::size(Countries) - 1)]  << "\",\n";
    std::cout << "    \"genre\": \"" << Genres[random.computeUniformInteger(std::size_t(0), std::size(Genres) - 1)] << "\",\n";
    std::cout << "    \"technique\": \"" << Techniques[techniqueDistribution(random.getEngine())]  << "\",\n";
    std::cout << "    \"rating\": \"" << Ratings[random.computeUniformInteger(std::size_t(0), std::size(Ratings) - 1)] << "\",\n";
    std::cout << "    \"themes\": [ \"\", \"\" ]\n";
    std::cout << "  }\n";
  }


}

int main() {
  gf::Random random;

  displayOne(random);
}
