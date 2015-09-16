#include <hammer/hammer.h>

int main() {
  // Parsers for characters 'h' and 'i'
  HParser *h = h_ch('h');
  HParser *i = h_ch('i');
  
  // A parser that takes a sequence of 'h' and 'i'
  HParser *hi = h_sequence(h,i,NULL);
  
  // Test our sequence
  HParseResult *res = h_parse(hi, (const uint8_t*)"hi", 2);
  
  // Is res is NULL, the parse failed.
  if (NULL == res) {
    printf("Oh no, parse failed!\n");
  } else {
    printf("Yay, parse successful!\n");
  } 

  // What if we parse a hippo?
  res = h_parse(hi, (const uint8_t*)"hippo", 5);
  if (NULL == res) {
    printf("Good! We shouldn't be parsing hippos.\n");
  } else {
    printf("Oh no! It parsed a hippo! We should think about how to prevent hippos from being parsed.\n");
  } 

  // Let's use that h_end_p() parser!
  HParser *just_hi = h_sequence(h, i, h_end_p(), NULL);
  // And test it out...
  res = h_parse(just_hi, (const uint8_t*)"hippo", 5);
  if (NULL == res) {
    printf("We failed gracefully, yay!\n");
  } else {
    printf("Uh-oh! Something went wrong, we shouldn't be here.\n");
  }
  return 0;
}
