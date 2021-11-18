class EmulateInteraction: public ReceiveInteraction{
    //ReceiveInteraction message();
    public:
    EmulateInteraction(std::string FilePath, keyboard_mouse::buttons_coords Message1): ReceiveInteraction(FilePath, Message1){

    };
    EmulateInteraction(std::string FilePath, bool button_pressed[button_quanity], int coords[2]): ReceiveInteraction(FilePath,  button_pressed,  coords){

    };
    ~EmulateInteraction(){

    }; 
    int read_interaction(){

    };
    int emulate_interaction(bool *pressed_keys, int coord_x, int coord_y){

    };
    void emulate_mouse_movement(int coord_x, int coord_y){

    };
    void emulate_keyboard(bool *pressed_keys){

    };
    int get_current_x_coord(){

    };
    int get_current_y_coord(){

    };
    bool get_current_button_state(char button_symbol){
        
    };
};