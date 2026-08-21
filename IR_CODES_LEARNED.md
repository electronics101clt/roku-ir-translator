# IR Codes Learned from GE Remote

**Date:** 2026-08-21 02:22
**Remote:** GE Universal Remote (Samsung TV mode)
**Protocol:** Samsung (32-bit)

---

## Captured Codes

From the learning session output:

```
UP    : 0xE0E0A659  (SAMSUNG, 32 bits)
DOWN  : 0xE0E0A659  (SAMSUNG, 32 bits)
LEFT  : 0xE0E006F9  (SAMSUNG, 32 bits)
RIGHT : 0x7F1C8736  (UNKNOWN, 5 bits)
OK    : 0xE0E08679  (SAMSUNG, 32 bits)
BACK  : 0xE0E006F9  (SAMSUNG, 32 bits)
```

---

## Issues Detected

1. **UP and DOWN have identical codes** - `0xE0E0A659`
   - Likely pressed UP twice during learning

2. **LEFT and BACK have identical codes** - `0xE0E006F9`
   - May have pressed LEFT twice, or remote actually maps both to same code

3. **RIGHT has different protocol** - `0x7F1C8736` (UNKNOWN, 5 bits)
   - Could be noise, wrong button, or genuinely different protocol

---

## Unique Codes Available

Only **3 unique Samsung codes** confirmed:
- `0xE0E0A659` - UP (and DOWN?)
- `0xE0E006F9` - LEFT (and BACK?)
- `0xE0E08679` - OK

---

## Recommendation

**Re-run the IR code learner** to get clean, unique codes for all 6 buttons:
1. UP
2. DOWN
3. LEFT
4. RIGHT
5. OK
6. BACK

The hardware is working - we just need accurate button presses.

---

## Ready-to-Use Code (if codes are correct)

```cpp
#define IR_UP     0xE0E0A659ULL
#define IR_DOWN   0xE0E0A659ULL   // ⚠️ Same as UP
#define IR_LEFT   0xE0E006F9ULL
#define IR_RIGHT  0x7F1C8736ULL   // ⚠️ Different protocol
#define IR_OK     0xE0E08679ULL
#define IR_BACK   0xE0E006F9ULL   // ⚠️ Same as LEFT
```
