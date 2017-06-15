#include "chibi/eval.h"

#include <stdio.h>

int main(int argc, char **argv) {

  sexp ctx;

  printf("Hello from C!\n");

  /* Setup scheme environment */
  ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
  sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
  sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 0);

  /* Declare two scheme objects with macro */
  sexp_gc_var2(prog, prog_res);

  /* Load program */
  prog = sexp_c_string(ctx, "/home/clint/projects/embedded_scheme/prog.scm", -1);
  sexp_load(ctx, prog, NULL);

  /* Create symbol we want to call from a string */
  prog = sexp_intern(ctx, "my-prog", -1);

  /* Convert to call form `(my-prog)` */
  prog = sexp_list1(ctx, prog);

  /* Evaluate program */
  prog_res = sexp_eval(ctx, prog, NULL);

  /* Could also directly evalute a string */
  /* prog_res = sexp_eval_string(ctx, "(my-prog)", -1, NULL); */

  /* Print result */
  sexp_debug(ctx, "result: ", prog_res);

  /* Free (garbage collect) scheme objects */
  sexp_gc_release2(ctx);

  /* Destroy environment */
  sexp_destroy_context(ctx);

  return 0;
}
