             Binary
Value        Sample             Meaning
  x         00101100        the original x value
x & -x      00000100        extract lowest bit set
x | -x      11111100        create mask for lowest-set-bit & bits to its left
x ^ -x      11111000        create mask bits to left of lowest bit set
x & (x-1)   00101000        strip off lowest bit set
                            --> useful to process words in O(bits set)
                                instead of O(nbits in a word)
x | (x-1)   00101111        fill in all bits below lowest bit set
x ^ (x-1)   00000111        create mask for lowest-set-bit & bits to its right
~x & (x-1)  00000011        create mask for bits to right of lowest bit set
x | (x+1)   00101101        toggle lowest zero bit
x / (x&-x)  00001011        shift number right so lowest set bit is at bit 0