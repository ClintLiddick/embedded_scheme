#include "chibi/eval.h"

#include <stdio.h>

int main(int argc, char **argv) {
  sexp ctx;

  printf("hello\n");

  ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
  sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
  sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 0);

  sexp_gc_var3(prog_str, prog, prog_res);
  /* sexp_eval_string(ctx, "(display \"hello from scheme\n\")", -1, NULL); */
  prog_str = sexp_c_string(ctx, "/home/clint/projects/sk/prog.scm", -1);
  sexp_load(ctx, prog_str, NULL);
  /* sexp_eval_string(ctx, "(my-prog)", -1, NULL); */
  prog_str = sexp_intern(ctx, "my-prog", -1);
  /* Convert to call form */
  prog = sexp_list1(ctx, prog_str);
  prog_res = sexp_eval(ctx, prog, NULL);
  sexp_debug(ctx, "result: ", prog_res);

  sexp_gc_release3(ctx);

  sexp_destroy_context(ctx);
  return 0;
}
