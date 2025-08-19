#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Exception {
     char *name;
     int code;
     char *reason;

     void (*_raise)(struct Exception *self, int lineno, char *filename);

     void (*_raise2)(struct Exception *self, char *reason, int lineno, char *filename);

     void (*rename)(struct Exception *self, char *name);
} Exception;


void Exception_raise(struct Exception *self, int lineno, char *filename)
{
     printf("%s(%d) -> %s: %s\n", self->name, lineno, filename, self->reason);
     exit(self->code);
}


void Exception_rename(struct Exception *self, char *name) {
     self->name = name;
}


void Exception_raise2(struct Exception *self, char *reason, int lineno, char *filename) {
     char *_reason = self->reason;
     self->reason = reason;
     self->_raise(self, lineno, filename);
     self->reason = _reason;
}


Exception Exception_init(char *reason) {
     Exception self;
     self.name = "Exception";
     self.code = 1;
     self.reason = reason;
     self._raise = Exception_raise;
     self._raise2 = Exception_raise2;
     self.rename = Exception_rename;
     return self;
}


Exception Error_init(char *name, char *reason, int code) {
     Exception self = Exception_init(reason);
     self.name = name;
     self.code = code;
     return self;
}

extern const inline void yeet(char *reason, int lineno, char *filename) {
     Exception error = Error_init("Exception", reason, 1);
     error._raise(&error, lineno, filename);
}


int copy_times(char out[], char *src, int times) {
     if (strlen(out) < strlen(src) * times) return 0;
     for (int i = 0; i <= (times - 1); i++) {
          out[i] = src[0];
     }
     return 1;
}

int fill(char out[], char *src) {
     if (strlen(src) != 0) return 0;
     for (int current = 0; current <= (strlen(out) - 1); current++) {
          out[current] = src[0];
     }
}