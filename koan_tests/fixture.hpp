// #ifndef KOAN_FIXTURE_HPP
// #define KOAN_FIXTURE_HPP

// #endif KOAN_FIXTURE_HPP
#pragma once

#include <string>

#include "chibi/eval.h"
#include "gtest/gtest.h"

static constexpr char PROGRAM_ROOT[] =
    "/home/clint/projects/embedded_scheme/koans/";
static sexp ctx;

class KoanTest : public ::testing::Test {
public:
  KoanTest() { sexp_gc_preserve2(ctx, prog, prog_res); }

  ~KoanTest() { sexp_gc_release2(ctx); }

  static void SetUpTestCase() {
    ctx = sexp_make_eval_context(NULL, NULL, NULL, 0, 0);
    sexp_load_standard_env(ctx, NULL, SEXP_SEVEN);
    sexp_load_standard_ports(ctx, NULL, stdin, stdout, stderr, 0);
  }

  // static void TearDownTestCase() {
  //   sexp_destroy_context(ctx);
  // }

protected:
  void load_program(const std::string &prog_name) {
    std::string prog_path{PROGRAM_ROOT};
    prog_path += prog_name;
    prog = sexp_c_string(ctx, prog_path.c_str(), -1);
    sexp_load(ctx, prog, NULL);
  }

  sexp_gc_var2(prog, prog_res);
};
