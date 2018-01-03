uint64_t* power_of_two_table;
uint64_t allocatedTemporaries;

uint64_t currentTemporary() {
  if (allocatedTemporaries > 0)
    return allocatedTemporaries + 1;
}

uint64_t nextTemporary() {
  if (allocatedTemporaries < 7 - 1)
    return currentTemporary() + 1;
}

uint64_t twoToThePowerOf(uint64_t p) {
  // assert: 0 <= p < CPUBITWIDTH
  return *(power_of_two_table + p);
}

uint64_t leftShift(uint64_t n, uint64_t b) {
  // assert: 0 <= b < CPUBITWIDTH
  return n * twoToThePowerOf(b);
}

uint64_t rightShift(uint64_t n, uint64_t b) {
  // assert: 0 <= b < CPUBITWIDTH
  return n / twoToThePowerOf(b);
}

uint64_t emitSFormat(uint64_t opcode, uint64_t rs, uint64_t rt, uint64_t immediate) {
  return immediate;
}

uint64_t emitIFormat(uint64_t opcode, uint64_t rs, uint64_t rt, uint64_t immediate) {
  uint64_t i;
  uint64_t value;
  uint64_t shifted;
  uint64_t reg;
  uint64_t ret;

  i = 3;
  value = 320;
  shifted = 5;
  reg = 0;
  while (i >= 2) {
    if (value >= twoToThePowerOf(i)) {
      ret = emitSFormat(25, reg, currentTemporary(), rightShift(leftShift(value, shifted), i));

      reg = currentTemporary();

      //emitLeftShiftBy(reg, 14);
    }

    shifted = shifted + 1;

    i = i - 1;
  }
  return ret;
}

uint64_t emitLeftShiftBy(uint64_t reg, uint64_t b) {
  // assert: 0 <= b < 15

  // load multiplication factor less than 2^15 to avoid sign extension
  return emitIFormat(25, 0, nextTemporary(), twoToThePowerOf(b));
}

uint64_t func () {
  uint64_t s;

  s = 12;
  return emitLeftShiftBy(s, 2);
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

  allocatedTemporaries = 1;

  i = func();

  return i;
}