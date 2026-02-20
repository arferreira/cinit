// This is a tool created to start C projects like cargo new or smith for C++
// Author: Antonio Souza
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cinit.h"

static const char *cinit_color_to_ansi(cinit_color_t color)
{
    switch (color)
    {
        case CINIT_COLOR_RED:     return "\033[1;31m";
        case CINIT_COLOR_GREEN:   return "\033[1;32m";
        case CINIT_COLOR_YELLOW:  return "\033[1;33m";
        case CINIT_COLOR_BLUE:    return "\033[1;34m";
        case CINIT_COLOR_MAGENTA: return "\033[1;35m";
        case CINIT_COLOR_CYAN:    return "\033[1;36m";
        case CINIT_COLOR_WHITE:   return "\033[1;37m";
        default:
            return "\033[1;37m";
    }
}

void cinit_put_str_color(const char *str, cinit_color_t color)
{
    printf("%s%s\033[0m", cinit_color_to_ansi(color), str);
}

#define CINIT_VERSION "0.1.0"

int main_file(const char *project_name) {
  char main_path[256];
  snprintf(main_path, sizeof(main_path), "%s/src/main.c", project_name);
  FILE *f = fopen(main_path, "w");

  if (f == NULL) {
    cinit_put_str_color("Error creating main.c\n", CINIT_COLOR_RED);
    return 1;
  }

  fprintf(f, "#include <stdio.h>\n\n");
  fprintf(f, "int main(void) {\n");
  fprintf(f, "    printf(\"Hello, World!\\n\");\n");
  fprintf(f, "    return 0;\n");
  fprintf(f, "}\n");
  fclose(f);
  return 0;
}

int readme(const char *project_name) {

  char readme_path[256];
  snprintf(readme_path, sizeof(readme_path), "%s/README.md", project_name);
  FILE *f = fopen(readme_path, "w");

  if (f == NULL) {
    cinit_put_str_color("Error creating README.md\n", CINIT_COLOR_RED);
    return 1;
  }

  fprintf(f, "# %s\n\n", project_name);
  fprintf(f, "## Start developing your program");
  fclose(f);
  return 0;
}

int gitignore(const char *project_name) {

  char ignore_path[256];
  snprintf(ignore_path, sizeof(ignore_path), "%s/.gitignore", project_name);
  FILE *f = fopen(ignore_path, "w");

  if (f == NULL) {
    cinit_put_str_color("Error creating gitignore\n", CINIT_COLOR_RED);
    return 1;
  }

  fprintf(f, "*.o");
  fclose(f);
  return 0;
}

int makefile(const char *project_name) {

  char make_path[256];
  snprintf(make_path, sizeof(make_path), "%s/Makefile", project_name);
  FILE *f = fopen(make_path, "w");

  if (f == NULL) {
    cinit_put_str_color("Error creating Makefile\n", CINIT_COLOR_RED);
    return 1;
  }

  fprintf(f, "build:\n");
  fprintf(f, "\tgcc -o %s src/main.c\n", project_name);
  fprintf(f, "\n");
  fprintf(f, "clean:\n");
  fprintf(f, "\trm -f %s\n", project_name);

  fclose(f);
  return 0;
}

void print_help_cmd(void){
  printf("Usage:\n");
  printf("  cinit <command> [arguments] \n");
  printf("  cinit [options] \n\n");
  printf("Commands:\n");
  printf("  new <project_name> Initialize a new project with the specified name. \n\n");
  printf("Options:\n");
  printf("  --help             Show this help message and exit.\n");
  printf("  --version          Print the current version of cinit.\n");
}

int main(int argc, char *argv[]) {

  if (argc >= 3) {
    // cmd has args
    if (strcmp(argv[1], "new") == 0) {
      size_t length = strlen(argv[2]);
      if (length <= 3) {
        cinit_put_str_color("Your project name needs to be longer than 3\n", CINIT_COLOR_RED);
        return 1;
      }

      // creating dir
      int dir = mkdir(argv[2], 0755);
      if (dir != 0) {
        cinit_put_str_color("An error occurs creating your project\n", CINIT_COLOR_RED);
        return 1;
      }
      char src_path[256];
      snprintf(src_path, sizeof(src_path), "%s/src", argv[2]);
      mkdir(src_path, 0755);

      // creating main
      int mf = main_file(argv[2]);
      if (mf != 0) {
        cinit_put_str_color("An error occurs creating your main file\n", CINIT_COLOR_RED);
        return 1;
      }
      // creating readme
      int rm = readme(argv[2]);
      if (rm != 0) {
        cinit_put_str_color("An error occurs creating your Readme\n", CINIT_COLOR_RED);
        return 1;
      }

      // creating ignore
      int ig = gitignore(argv[2]);
      if (ig != 0) {
        cinit_put_str_color("An error occurs creating gitignore\n", CINIT_COLOR_RED);
        return 1;
      }

      // creating makefile
      int mk = makefile(argv[2]);
      if (mk != 0) {
        cinit_put_str_color("An error occurs creating makefile\n", CINIT_COLOR_RED);
        return 1;
      }

      char git_cmd[512];
      snprintf(git_cmd, sizeof(git_cmd), "git -C %s init -b main", argv[2]);
      system(git_cmd);
    }
    char success_msg[256];
    snprintf(success_msg, sizeof(success_msg), "%s was created!\n", argv[2]);
    cinit_put_str_color(success_msg, CINIT_COLOR_GREEN);
    return 0;
  } else {
    cinit_put_str_color("Arguments are required for creating a new project\n", CINIT_COLOR_RED);
    cinit_put_str_color("Try: cinit new project_name\n", CINIT_COLOR_RED);
  } else if (argc == 2){
    if(strcmp(argv[1], "--version") == 0){
      printf("cinit version %s\n", CINIT_VERSION);
      return 0;
    } else if (strcmp(argv[1], "--help") == 0){
      print_help_cmd();
      return 0;
    } else {
      printf("Error: unrecognized subcommand '%s'\n\n", argv[1]);
      printf("Usage: cinit <command> [arguments]\n\n");
      printf("For more information, try '--help'.\n");
    }
  }
  else {
    printf("Arguments are required for creating a new project\n");
    printf("Try: cinit new project_name\n");
    return 1;
  }
}
