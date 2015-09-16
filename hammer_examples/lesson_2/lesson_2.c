#include <hammer/hammer.h>
#include <hammer/glue.h>

int main() {
  H_RULE(on, h_sequence(h_ch('O'), h_ch('n'), NULL));
  H_RULE(off, h_sequence(h_ch('O'), h_ch('f'), h_ch('f'), NULL));

  H_RULE(lightswitch_message, h_choice(on, off, NULL));

  // On
  // (On, Off,)
  // (On, Off,) On
  // (On, Off,) (On, Off)
  // (On, Off,) (On, Off,) On
  // (On, Off,) (On, Off,) (On, Off)
  // (On, Off,) (On, Off,) (On, Off,) On

  H_RULE(on_off, h_sequence(on, off, NULL));

  H_RULE(just_on, h_sequence(on, h_end_p(), NULL));

  H_RULE(valid_message, h_choice(just_on, h_sequence(h_many1(on_off), h_optional(on), h_end_p(), NULL), NULL));

  // Messy testing of our parser!
  HParseResult *res = h_parse(valid_message, (const uint8_t*)"On", 2);
  printf("%s: On\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOff", 5);
  printf("%s: OnOff\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOn", 7);
  printf("%s: OnOffOn\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOnOff", 10);
  printf("%s: OnOffOnOff\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOnOffOn", 12);
  printf("%s: OnOffOnOffOn\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOnOffOnOff", 15);
  printf("%s: OnOffOnOffOnOff\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOnOffOnOffOn", 17);
  printf("%s: OnOffOnOffOnOffOn\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOffOnOffOnOffOnOff", 20);
  printf("%s: OnOffOnOffOnOffOnOff\n", res == NULL ? "Fail" : "Pass");

  // Test some failure cases, too...
  printf("\nTesting some failure cases now:\n");

  res = h_parse(valid_message, (const uint8_t*)"Off", 3);
  printf("%s: Off\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OffOn", 5);
  printf("%s: OffOn\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OffOff", 6);
  printf("%s: OffOff\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"OnOn", 4);
  printf("%s: OffOn\n", res == NULL ? "Fail" : "Pass");

  res = h_parse(valid_message, (const uint8_t*)"", 0);
  printf("%s: [empty_string]\n", res == NULL ? "Fail" : "Pass");
  
  return 0;
}
