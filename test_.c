uint64_t* power_of_two_table;

uint64_t twoToThePowerOf(uint64_t p) {
  // assert: 0 <= p < CPUBITWIDTH
  return *(power_of_two_table + p);
}

uint64_t leftShift(uint64_t n, uint64_t b) {
  // assert: 0 <= b < CPUBITWIDTH
  return n * twoToThePowerOf(b); //*(power_of_two_table + b);
}

uint64_t rightShift(uint64_t n, uint64_t b) {
  // assert: 0 <= b < CPUBITWIDTH
  return n / twoToThePowerOf(b); // *(power_of_two_table + b);
}

uint64_t encodeRFormat(uint64_t opcode, uint64_t rs, uint64_t rt, uint64_t rd, uint64_t function) {
  // assert: 0 <= opcode < 2^6
  // assert: 0 <= rs < 2^5
  // assert: 0 <= rt < 2^5
  // assert: 0 <= rd < 2^5
  // assert: 0 <= function < 2^6
  return leftShift(leftShift(leftShift(leftShift(opcode, 5) + rs, 5) + rt, 5) + rd, 11) + function;
}

uint64_t func () {
  uint64_t s;

  s = 12;
  return encodeRFormat(26, 21, 4, 5, 645);
}

uint64_t main () {
  uint64_t i;

  // powers of two table with CPUBITWIDTH entries for 2^0 to 2^(CPUBITWIDTH - 1)
  power_of_two_table = malloc(64 * 8);

  *power_of_two_table = 1; // 2^0 == 1

  i = 1;

  while (i < 64) {
    // compute powers of two incrementally using this recurrence relation
    *(power_of_two_table + i) = *(power_of_two_table + (i - 1)) * 2;

    i = i + 1;
  }

  i = func();

  return i;
}