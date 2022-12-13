#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Object {
  char * name;
  char * key;
  int value; 
} Object;

int chars() {
  size_t length = 4;
  char * characters = malloc(length);
  printf("length %li \n", length);
  for (size_t i = 0; i < length; i++) {
    characters[i] = 'x';
  }
  printf("chars %s", characters);
  free(characters);
  return 0;
}

int printStruct(Object * obj) {
  printf("obj name %s\n", obj->name);
  printf("obj key %s\n", obj->key);
  printf("obj value %i\n", obj->value);
  return 0;
}

void makeObj(Object * obj, char* name, char* key, int value) {
    obj->name = (char *) malloc(sizeof(char*)); // max length is 8 chars
    obj->key = (char *) malloc(sizeof(char*));
    strcpy(obj->name, name);
    strcpy(obj->key, key);
    obj->value = value;
}

int structing() {
  size_t length = 10;
  Object * objs = calloc(length, sizeof(Object));
  for (size_t i = 0; i < length; i++) {
    makeObj(&objs[i], "me", "you", i);
  }
  for (size_t i = 0; i < length; i++) {
    printStruct(&objs[i]);
  }
  free(objs);
}

int main() {
 chars();
 structing();
}
