int cursor = 0;

void clear_screen() {
        char* video = (char*)0xb8000;

        for(int i = 0; i < 80 * 25; i++) {
                video[i * 2] = ' ';
                video[i * 2 + 1] = 0x0F;
        }

        cursor = 0;

}

void print(char* str) {
        char* video = (char*)0xb8000;

        int i = 0;

        while(str[i] != '\0') {

                if(str[i] == '\n') {
                        cursor += 80 - (cursor % 80);
                }
                else {
                        video[cursor * 2] = str[i];
                        video[cursor *2 + 1] = 0x0F;

                        cursor++;
                }

                i++;
        }
}

void print_char(char c) {
        char* video = (char*)0xb8000;

        video[cursor * 2] = c;
        video[cursor *2 +1] = 0x0F;

        cursor++;
}


unsigned char inb(unsigned short port) {
        unsigned char result;

        __asm__ volatile(
                "inb %1, %0"
                : "+a"(result)
                : "Nd"(port)
        );

         return result;
}

char keyboard_map[128] = {
        0,
        27,
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=', '\b',
        '\t',

        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
        '[',']','\n',

        0,

        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
        ';',

        0,

        '`',

        0,

        '\\',

        'z', 'x', 'c', 'v', 'b', 'n', 'm',
        ',', '.', '/',

        0,
        '*',

        0,
        ' '

};

void kernel_main() {

        clear_screen();

        print("Welcome to StarkOS\n");
        print("Version Beta 0.3\n");
        print("Screen system initialized\n");
        print("Initialized keyboard test\n");
        print("Press keys... \n\n");
        print("userstarkos> ");

        void backspace() {
                if(cursor <= 78) return;

                char* video = (char*)0xb8000;

                cursor--;

                video[cursor * 2] = ' ';
                video[cursor * 2 + 1] = 0x0F;
        }

        unsigned char last_key = 0;

                while(1) {

                        if((inb(0x64) & 1) == 0)
                                continue;

                        unsigned char key = inb(0x60);

                        if(key & 0x80)
                                continue;




                        if(key == 0x0E) {
                                backspace();
                                continue;
                        }



                        if(key < 128) {

                                char c = keyboard_map[key];


                        if(c) {
                                print_char(c);
                        }
                }
        }}
