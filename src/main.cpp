#include <stdio.h>

#include "SpriteEditor.hpp"

int main(int argc, char** argv) {
    if(argc != 6) {
        printf(" Args: ./sprite_editor, file_path, sprite_width, sprite_height, start_frame, end_frame\n");
        return -1;
    }

    SpriteEditor* editor = new SpriteEditor(argv[1], atol(argv[2]), atol(argv[3]), atol(argv[4]), atol(argv[5]));

    editor->Init();
    editor->Run();

    printf("Exiting main\n");
    delete editor;
    return 0;
}