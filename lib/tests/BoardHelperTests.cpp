#include "doctest.h"
#include "lib/board/BoardA.h"

TEST_SUITE("Board Helper Tests") {
    TEST_CASE("Negative Mod") {
        SUBCASE("Positive A Argument") {
            CHECK_EQ(negative_mod(0, 10), 0);
            CHECK_EQ(negative_mod(10, 10), 0);
            CHECK_EQ(negative_mod(5, 10), 5);
        }
        SUBCASE("Negative A Argument") {
            CHECK_EQ(negative_mod(-0, 10), 0);
            CHECK_EQ(negative_mod(-10, 10), 0);
            CHECK_EQ(negative_mod(-5, 10), 5);

            CHECK_EQ(negative_mod(-1, 10), 9);
            CHECK_EQ(negative_mod(-9, 10), 1);
        }
    }

    TEST_CASE("Horizontal Others") {
        int a{0}, b{0};
        SUBCASE("First Row") {
            horizontal_others(0, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 2);
                CHECK_EQ(b, 1);
            } else if (b > a) {
                CHECK_EQ(b, 2);
                CHECK_EQ(a, 1);
            }

            horizontal_others(1, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 2);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 2);
                CHECK_EQ(a, 0);
            }

            horizontal_others(2, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 1);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 1);
                CHECK_EQ(a, 0);
            }
        }
        SUBCASE("Second Row") {
            horizontal_others(3, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 5);
                CHECK_EQ(b, 4);
            } else if (b > a) {
                CHECK_EQ(b, 5);
                CHECK_EQ(a, 4);
            }

            horizontal_others(4, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 5);
                CHECK_EQ(b, 3);
            } else if (b > a) {
                CHECK_EQ(b, 5);
                CHECK_EQ(a, 3);
            }

            horizontal_others(5, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 4);
                CHECK_EQ(b, 3);
            } else if (b > a) {
                CHECK_EQ(b, 4);
                CHECK_EQ(a, 3);
            }
        }
    }

    TEST_CASE("Vertical Others") {
        int a{0}, b{0};
        SUBCASE("First Column") {
            vertical_others(0, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 6);
                CHECK_EQ(b, 3);
            } else if (b > a) {
                CHECK_EQ(b, 6);
                CHECK_EQ(a, 3);
            }

            vertical_others(3, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 6);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 6);
                CHECK_EQ(a, 0);
            }

            vertical_others(6, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 3);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 3);
                CHECK_EQ(a, 0);
            }
        }

        // Verify Second Column
        SUBCASE("Second Column") {
            vertical_others(1, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 7);
                CHECK_EQ(b, 4);
            } else if (b > a) {
                CHECK_EQ(b, 7);
                CHECK_EQ(a, 4);
            }

            vertical_others(4, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 7);
                CHECK_EQ(b, 1);
            } else if (b > a) {
                CHECK_EQ(b, 7);
                CHECK_EQ(a, 1);
            }

            vertical_others(7, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 4);
                CHECK_EQ(b, 1);
            } else if (b > a) {
                CHECK_EQ(b, 4);
                CHECK_EQ(a, 1);
            }
        }
    }

    TEST_CASE("Diagonal Fours") {
        int a{0}, b{0};
        SUBCASE("Index 0") {
            diagonal_fours_others(0, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 8);
                CHECK_EQ(b, 4);
            } else if (b > a) {
                CHECK_EQ(b, 8);
                CHECK_EQ(a, 4);
            }
        }
        SUBCASE("Index 4") {
            diagonal_fours_others(4, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 8);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 8);
                CHECK_EQ(a, 0);
            }
        }
        SUBCASE("Index 8") {
            diagonal_fours_others(8, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 4);
                CHECK_EQ(b, 0);
            } else if (b > a) {
                CHECK_EQ(b, 4);
                CHECK_EQ(a, 0);
            }
        }
    }

    TEST_CASE("Diagonal Twos") {
        int a{0}, b{0};
        SUBCASE("Index 2") {
            diagonal_twos_others(2, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 6);
                CHECK_EQ(b, 4);
            } else if (b > a) {
                CHECK_EQ(b, 6);
                CHECK_EQ(a, 4);
            }
        }
        SUBCASE("Index 4") {
            diagonal_twos_others(4, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 6);
                CHECK_EQ(b, 2);
            } else if (b > a) {
                CHECK_EQ(b, 6);
                CHECK_EQ(a, 2);
            }
        }
        SUBCASE("Index 6") {
            diagonal_twos_others(6, a, b);
            REQUIRE_NE(a, b);
            if (a > b) {
                CHECK_EQ(a, 4);
                CHECK_EQ(b, 2);
            } else if (b > a) {
                CHECK_EQ(b, 4);
                CHECK_EQ(a, 2);
            }
        }
    }
}
