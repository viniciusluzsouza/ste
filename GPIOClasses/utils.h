#ifndef UTILS_H_
#define UTILS_H_

// just a hack because avr-g++ do not suport new and delete operators...
void* operator new(size_t objsize) {
  return malloc(objsize);
}

// in IFSC the compiler want this
void operator delete(void* obj) {
  free(obj);
}
// in my home the compiler want this
void operator delete(void* obj, unsigned int unused) {
  free(obj);
}
// -----------------------------------------------------------------

#endif /* UTILS_H_ */
