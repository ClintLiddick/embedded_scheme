#include "gtest/gtest.h"

#include "fixture.hpp"

#include <limits>

// sexp_debug(ctx, "result: ", prog_res);
// sexp_print_exception(ctx, prog_res, sexp_current_error_port(ctx));

class Grains : public KoanTest {
public:
  // using KoanTest::KoanTest;
  Grains() {
    load_program("grains.scm");
    prog = sexp_intern(ctx, "square", -1);
  }
};

TEST_F(Grains, one) {
  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_ONE), NULL);
  EXPECT_EQ(prog_res, SEXP_ONE);
}

TEST_F(Grains, two) {
  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_TWO), NULL);
  EXPECT_EQ(prog_res, SEXP_TWO);
}

TEST_F(Grains, three) {
  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_THREE), NULL);
  EXPECT_EQ(prog_res, SEXP_FOUR);
}

TEST_F(Grains, four) {
  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_FOUR), NULL);
  EXPECT_EQ(prog_res, SEXP_EIGHT);
}

TEST_F(Grains, 16) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_make_unsigned_integer(ctx, 16U)), NULL);
  EXPECT_EQ(prog_res, sexp_make_unsigned_integer(ctx, 32768U));
}

TEST_F(Grains, 32) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_make_unsigned_integer(ctx, 32U)), NULL);
  EXPECT_TRUE(sexp_equalp(
      ctx, prog_res,
      sexp_string_to_number(ctx, sexp_c_string(ctx, "2147483648U", -1),
                            SEXP_VOID)));
}

TEST_F(Grains, 64) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_make_unsigned_integer(ctx, 64U)), NULL);
  EXPECT_TRUE(sexp_equalp(
      ctx, prog_res,
      sexp_string_to_number(ctx, sexp_c_string(ctx, "9223372036854775808", -1),
                            SEXP_VOID)));
}
