#ifndef _INPUT_KEYBOARD_
#define _INPUT_KEYBOARD_

namespace Utils {
    namespace KeyBoard {
        //Arrow key made form = 224 + Arrow key
        enum ArrowKey{
            LEFT  = 75 ,
            RIGHT  = 77 ,
            UP  = 72 ,
            DOWN  = 80
        };

        enum key{
            TAB = 9 ,
            BACKSPACE = 8,
            ENTER  = 13 ,
            ARROWKEY = 224
        };
    }
}
#endif