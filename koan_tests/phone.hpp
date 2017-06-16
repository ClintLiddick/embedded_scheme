#include "gtest/gtest.h"

#include "fixture.hpp"

class Phone : public KoanTest {
public:
  Phone() {
    load_program("phone.scm");
    prog = sexp_intern(ctx, "cleanup-phone", -1);
  }
};

TEST_F(Phone, one) {
  prog_res = sexp_eval(
      ctx, sexp_list2(ctx, prog, sexp_c_string(ctx, "2223334444", -1)), NULL);
  EXPECT_TRUE(sexp_equalp(ctx, prog_res, sexp_c_string(ctx, "2223334444", -1)));
}
