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
  EXPECT_EQ(prog_res, SEXP_TRUE);

  prog_res = sexp_eval(ctx, sexp_list2(ctx, prog, SEXP_FALSE), NULL);
  EXPECT_EQ(prog_res, SEXP_FALSE);
}

TEST_F(Conditional, and) {
  prog = sexp_intern(ctx, "and-koan", -1);
  sexp_gc_var1(args);
  sexp_gc_preserve1(ctx, args);

  args = sexp_list2(ctx, SEXP_TRUE, SEXP_TRUE);
  prog_res = sexp_eval(ctx, sexp_cons(ctx, prog, args), NULL);
  EXPECT_EQ(prog_res, SEXP_TRUE);

  args = sexp_list2(ctx, SEXP_TRUE, SEXP_FALSE);
  prog_res = sexp_eval(ctx, sexp_cons(ctx, prog, args), NULL);
  EXPECT_EQ(prog_res, SEXP_FALSE);

  args = sexp_list2(ctx, SEXP_FALSE, SEXP_TRUE);
  prog_res = sexp_eval(ctx, sexp_cons(ctx, prog, args), NULL);
  EXPECT_EQ(prog_res, SEXP_FALSE);

  args = sexp_list2(ctx, SEXP_FALSE, SEXP_FALSE);
  prog_res = sexp_eval(ctx, sexp_cons(ctx, prog, args), NULL);
  EXPECT_EQ(prog_res, SEXP_FALSE);

  sexp_gc_release1(ctx);
}
