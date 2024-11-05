#include "stdio.h"
#include "stdlib.h"

#include "hw01.h"

// this line was determined by platform libc.
#define _USE_GETOPT

#ifdef USE_GETOPT
#include <getopt.h>

void usage(char *argv) {
  printf("Usage: %s <Args>\n", argv);
  puts("Args:");
  puts("\t--year, -Y <year>");
  puts("\t--func, -F <x>");
  puts("\t--prof, -P <p>");
  puts("");
  puts("\t--prof-demand=<p>");
  puts("\t--prof-fixed=<p>");
  puts("\t--prof-fixed-twice=<p>");
  puts("");
  puts("\t--help, -h");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage(argv[0]);
    return 1;
  } else {
    int opt;
    const struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"year", required_argument, NULL, 'Y'},
        {"func", required_argument, NULL, 'F'},
        {"prof", required_argument, NULL, 'P'},
        {"prof-demand", required_argument, NULL, 1},
        {"prof-fixed", required_argument, NULL, 2},
        {"prof-fixed-twice", required_argument, NULL, 3},
        {NULL, 0, NULL, 0}};
    double prof_demand = 0.01;
    double prof_fixed = 0.03;
    double prof_fixed_twice = 0.02;
    while ((opt = getopt_long(argc, argv, "hF:Y:P:", longopts, NULL)) != -1) {

      switch (opt) {
      case 'F':
        printf("calc_func(%.2f) = %.2f\n", atof(optarg),
               calc_func(atof(optarg)));
        break;
      case 'Y':
        printf("%d %s a leap year\n", atoi(optarg),
               is_leap(atoi(optarg)) ? "is" : "is not");
        break;
      case 'P': {
        double initial = atof(optarg);
        printf("prof of initial %.2f:\n", initial);
        printf("\tdemand        %.2f\n", calc_prof_once(initial, prof_demand));
        printf("\tfixed         %.2f\n", calc_prof_once(initial, prof_fixed));
        printf("\tfixed_twice   %.2f\n",
               calc_prof_once(initial, prof_fixed_twice));
      } break;

      case 1:
        prof_demand = atof(optarg);
        break;
      case 2:
        prof_fixed = atof(optarg);
        break;
      case 3:
        prof_fixed_twice = atof(optarg);
        break;

      case 'h':
      case '?':
      default:
        usage(argv[0]);
        return 1;
      }
    }
  }
}

#else

#include "hw02.h"

void usage(void) { puts("operations: F Y P d f t 0 1 u g q"); }

int main(void) {
  char opt = 0;
  char optarg[100];
  double prof_demand = 0.01;
  double prof_fixed = 0.03;
  double prof_fixed_twice = 0.02;

  while (opt != EOF) {
    printf("> ");
    opt = getchar();
    fgets(optarg, sizeof(optarg), stdin);

    switch (opt) {
    case 'F':
      printf("calc_func(%.2f) = %10f\n", atof(optarg), calc_func(atof(optarg)));
      break;
    case 'Y':
      printf("%d %s a leap year\n", atoi(optarg),
             is_leap(atoi(optarg)) ? "is" : "is not");
      break;
    case 'P': {
      double initial = atof(optarg);
      printf("prof of initial %.2f:\n", initial);
      printf("\tdemand        %.2f\n", calc_prof_once(initial, prof_demand));
      printf("\tfixed         %.2f\n", calc_prof_once(initial, prof_fixed));
      printf("\tfixed_twice   %.2f\n",
             calc_prof_once(initial, prof_fixed_twice));
    } break;

    case 'd':
      prof_demand = atof(optarg);
      break;
    case 'f':
      prof_fixed = atof(optarg);
      break;
    case 't':
      prof_fixed_twice = atof(optarg);
      break;

    case 'q':
      opt = EOF;
      break;

    case '0': {
      char *estr = encrypt(optarg);
      printf("encrypted: %s\n", estr);
      free(estr);
    } break;

    case '1': {
      char *dstr = decrypt(optarg);
      printf("decrypted: %s\n", dstr);
      free(dstr);
    } break;

    case 'u': {
      int *p = calc_prime_under(200);
      for (int i = 1; i < p[0]; i++) {
        if (p[i] > 100) {
          printf("%d\n", p[i]);
        }
      }
      free(p);
    } break;

    case 'g':
      guess_number_game();
      break;

    default:
      printf("unknown operation %c\n", opt);
      break;
    case 'h':
    case '?':
    case '\n':
      usage();
    }
  }
}

#endif
