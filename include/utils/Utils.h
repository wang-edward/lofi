// The helper function used to visualize which keys pressed or released on a virtual piano.
int asciiToKeyLabelIndex(int asciiKey) {
  switch (asciiKey) {
  case '2':
    return 30;
  case '3':
    return 31;
  case '5':
    return 33;
  case '6':
    return 34;
  case '7':
    return 35;
  case '9':
    return 37;
  case '0':
    return 38;

  case 'q':
    return 10;
  case 'w':
    return 11;
  case 'e':
    return 12;
  case 'r':
    return 13;
  case 't':
    return 14;
  case 'y':
    return 15;
  case 'u':
    return 16;
  case 'i':
    return 17;
  case 'o':
    return 18;
  case 'p':
    return 19;

  case 's':
    return 20;
  case 'd':
    return 21;
  case 'g':
    return 23;
  case 'h':
    return 24;
  case 'j':
    return 25;
  case 'l':
    return 27;
  case ';':
    return 28;

  case 'z':
    return 0;
  case 'x':
    return 1;
  case 'c':
    return 2;
  case 'v':
    return 3;
  case 'b':
    return 4;
  case 'n':
    return 5;
  case 'm':
    return 6;
  case ',':
    return 7;
  case '.':
    return 8;
  case '/':
    return 9;
  }
  return 0;
}