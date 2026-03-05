int counter = 10;

int multiply(int x, int y) {
    int result = x * y;
    static int calls = 0;
    ++calls;
    return result + counter + calls;
}

int square(int value) {
    int temp = value * value;
    return temp;
}

/*
Ожидаемый вывод после плагина:

int global_counter = 10;

int multiply(int param_x, int param_y) {
    int local_result = param_x * param_y;
    static int static_calls = 0;
    ++static_calls;
    return local_result + global_counter + static_calls;
}

int square(int param_value) {
    int local_temp = param_value * param_value;
    return local_temp;
}
*/