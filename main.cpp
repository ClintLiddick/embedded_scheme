#include "chibi/eval.h"

#include <iostream>

int main(int argc, char **argv) {

  sexp ctx;

  // printf("Hello from C!\n");
  std::cout << "Hello from C!\n" << std::endl;

  // Setup scheme environment
  ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
  sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
  sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 0);

  // Declare two scheme objects with macro
  sexp_gc_var2(prog, prog_res);

  // Preserve two scheme objects in context
  sexp_gc_preserve2(ctx, prog, prog_res);

  // Load program
  prog =
      sexp_c_string(ctx, "/home/clint/projects/embedded_scheme/prog.scm", -1);
  sexp_load(ctx, prog, NULL);

  // Create symbol we want to call from a string
  prog = sexp_intern(ctx, "my-prog", -1);

  // Convert to call form `(my-prog)`
  prog = sexp_list1(ctx, prog);

  // Evaluate program
  prog_res = sexp_eval(ctx, prog, NULL);

  // Could also directly evalute a string
  // prog_res = sexp_eval_string(ctx, "(my-prog)", -1, NULL);

  // Print result
  sexp_debug(ctx, "result: ", prog_res);

  // Free (garbage collect) scheme objects
  sexp_gc_release2(ctx);

  std::cout << "main exiting" << std::endl;

  // Destroy environment and exit
  sexp_destroy_context(ctx);
}
