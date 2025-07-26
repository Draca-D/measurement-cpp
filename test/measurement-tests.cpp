#include "measurement-cpp/distance.h"
#include <gtest/gtest.h>

using namespace measurement;

constexpr double EPS = 1e-9;

//
// === SI ↔ SI tests ===
//

TEST(SIConversions, MetersToKilometers) {
  si::meters m(1000);
  si::kilometers km = m;
  EXPECT_NEAR(km.count(), 1.0, EPS);
}

TEST(SIConversions, KilometersToMeters) {
  si::kilometers km(1);
  si::meters m = km;
  EXPECT_NEAR(m.count(), 1000.0, EPS);
}

TEST(SIConversions, MillimetersToMeters) {
  si::millimeters mm(1000);
  si::meters m = mm;
  EXPECT_NEAR(m.count(), 1.0, EPS);
}

TEST(SIConversions, MetersToMillimeters) {
  si::meters m(1.0);
  si::millimeters mm = m;
  EXPECT_NEAR(mm.count(), 1000.0, EPS);
}

TEST(SIConversions, NanometersToMeters) {
  si::nanometers nm(1e9);
  si::meters m = nm;
  EXPECT_NEAR(m.count(), 1.0, EPS);
}

//
// === Imperial ↔ Imperial ===
//

TEST(ImperialConversions, FeetToInches) {
  imperial::feet ft(1);
  imperial::inches in = ft;
  EXPECT_NEAR(in.count(), 12.0, EPS);
}

TEST(ImperialConversions, InchesToFeet) {
  imperial::inches in(12);
  imperial::feet ft = in;
  EXPECT_NEAR(ft.count(), 1.0, EPS);
}

TEST(ImperialConversions, MilesToYards) {
  imperial::miles mi(1);
  imperial::yards yd = mi;
  EXPECT_NEAR(yd.count(), 1760.0, 0.01);
}

TEST(ImperialConversions, YardsToMiles) {
  imperial::yards yd(1760);
  imperial::miles mi = yd;
  EXPECT_NEAR(mi.count(), 1.0, 0.01);
}

//
// === SI ↔ Imperial ===
//

TEST(SIToImperial, MetersToFeet) {
  si::meters m(1.0);
  imperial::feet ft = m;
  EXPECT_NEAR(ft.count(), 3.28084, 1e-5);
}

TEST(ImperialToSI, FeetToMeters) {
  imperial::feet ft(3.28084);
  si::meters m = ft;
  EXPECT_NEAR(m.count(), 1.0, 1e-5);
}

TEST(SIToImperial, KilometersToMiles) {
  si::kilometers km(1.60934);
  imperial::miles mi = km;
  EXPECT_NEAR(mi.count(), 1.0, 1e-5);
}

TEST(ImperialToSI, MilesToKilometers) {
  imperial::miles mi(1);
  si::kilometers km = mi;
  EXPECT_NEAR(km.count(), 1.60934, 1e-5);
}

TEST(SIToImperial, MetersToNauticalMiles) {
  si::meters m(1852.0);
  imperial::nauticalmiles nm = m;
  EXPECT_NEAR(nm.count(), 1.0, EPS);
}

TEST(ImperialToSI, NauticalMilesToMeters) {
  imperial::nauticalmiles nm(1.0);
  si::meters m = nm;
  EXPECT_NEAR(m.count(), 1852.0, EPS);
}

//
// === Mixed-Type Arithmetic ===
//

TEST(SIArithmetic, AddMetersAndMillimeters) {
  si::meters m(1.0);
  si::millimeters mm(500);
  auto result = m + mm;
  EXPECT_NEAR(result.count(), 1.5, EPS);
}

TEST(SIArithmetic, SubtractCentimetersFromMeters) {
  si::meters m(1.0);
  si::centimeters cm(25);
  auto result = m - cm;
  EXPECT_NEAR(result.count(), 0.75, EPS);
}

TEST(SIArithmetic, AddMetersAndKilometers) {
  si::meters m(500);
  si::kilometers km(0.5);
  auto result = m + km;
  EXPECT_NEAR(result.count(), 1000.0, EPS);
}

TEST(SIArithmetic, SubtractNanometersFromMicrometers) {
  si::micrometers um(1.5);
  si::nanometers nm(500);
  auto result = um - nm;
  EXPECT_NEAR(result.count(), 1.0, EPS);
}

TEST(SIImperialArithmetic, AddMetersAndFeet) {
  si::meters m(1.0);
  imperial::feet ft(3.28084); // ~1 meter
  auto result = m + ft;
  EXPECT_NEAR(result.count(), 2.0, 1e-5);
}

TEST(SIImperialArithmetic, SubtractMilesFromKilometers) {
  si::kilometers km(3.0);
  imperial::miles mi(1.0); // ~1.60934 km
  auto result = km - mi;
  EXPECT_NEAR(result.count(), 1.39066, 1e-4);
}

TEST(SIImperialArithmetic, AddNauticalMilesToMeters) {
  si::meters m(1852.0);
  imperial::nauticalmiles nm(1.0);
  auto result = m + nm;
  EXPECT_NEAR(result.count(), 3704.0, EPS);
}

TEST(SIImperialArithmetic, MixedAddSubChain) {
  si::meters m(1000);
  si::centimeters cm(100);
  imperial::feet ft(3.28084); // ~1 meter
  auto result = m + cm - ft;
  EXPECT_NEAR(result.count(), 1000.0, 1e-5); // 1 meter + 1 meter - 1 meter
}
