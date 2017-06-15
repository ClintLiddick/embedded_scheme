#include "gtest/gtest.h"

#include "fixture.hpp"

// sexp_debug(ctx, "result: ", prog_res);
// sexp_print_exception(ctx, prog_res, sexp_current_error_port(ctx));

class Conditional : public KoanTest {
public:
  // using KoanTest::KoanTest;
  Conditional() { load_program("conditional.scm"); }
};

TEST_F(Conditional, if) {
  prog = sexp_intern(ctx, "if-koan", -1);
  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_TRUE), NULL);
  EXPECT_EQ(prog_res, SEXP_ONE);

  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_FALSE), NULL);
  EXPECT_EQ(prog_res, SEXP_ZERO);
}
