#include "gtest/gtest.h"

#include "fixture.hpp"

class Phone : public KoanTest {
public:
  Phone() {
    load_program("phone.scm");
    prog = sexp_intern(ctx, "cleanup-phone", -1);
  }
};

TEST_F(Phone, identity) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_c_string(ctx, "2223334444", -1)), NULL);
  // ASSERT_FALSE(sexp_exceptionp(prog_res));
  // EXPECT_STREQ(sexp_string_data(prog_res), "2223334444");
  EXPECT_STREQ_SEXP(prog_res, "2223334444");
}

// TODO legit
TEST_F(Phone, remove_leading_ones) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_c_string(ctx, "12223334444", -1)), NULL);
  EXPECT_STREQ_SEXP(prog_res, "2223334444");
}

// TODO legit
TEST_F(Phone, remove_punctuation) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog,
                      sexp_c_string(ctx, "2~!2@#2$%2^&2*(2)-2_[2]{2}.2", -1)),
      NULL);
  EXPECT_STREQ_SEXP(prog_res, "2222222222");
}

TEST_F(Phone, remove_trailing_digits) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_c_string(ctx, "22233344445", -1)), NULL);
  EXPECT_STREQ_SEXP(prog_res, "2223334444");
}
