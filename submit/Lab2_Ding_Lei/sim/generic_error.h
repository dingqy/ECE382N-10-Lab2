//
// generic_error.h
//   by Derek Chiou, while at Avici Systems
//  copyright Avici Systems

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.

#ifndef ERROR_H

#define ERROR_H

// requires terminate_on_error to be defined in the including program
extern void terminate_on_error();

#define ERROR(_str) { 						      \
  fprintf(stdout, "ERROR: %d: %s: ", cur_cycle, __func__);		      \
  fprintf(stdout, _str);					      \
  fprintf(stdout, "\n");					      \
  terminate_on_error();						      \
}

#define ERROR_ARGS(_str) {					      \
  fprintf(stdout, "ERROR: %d: %s: ", cur_cycle,  __func__);		      \
  printf _str;							      \
  printf("\n");					      		      \
  terminate_on_error();						      \
}

#define NOTE(_str) { 						      \
  if (args.verbose) { \
    fprintf(stdout, "NOTE: %d: %s: ", cur_cycle,  __func__);		      \
    fprintf(stdout, _str);					      \
    fprintf(stdout, "\n");					      \
  }\
}

#define NOTE_ARGS(_str) {					      \
  if (args.verbose) { \
    fprintf(stdout, "NOTE: %d: %s: ", cur_cycle, __func__);		      \
    printf _str;							      \
    printf("\n");					      		      \
  }\
}

#define ASSERT(_bool) 						      \
  if (!(_bool)) 						      \
    ERROR("assertion error");			      

#define FUNC_NAME(_func_name_arg) char *_func_name = _func_name_arg


#endif // ERROR_H
