#include "clickChuot.hpp"

// Hàm kiểm tra xem tọa độ chuột có nằm trong hình chữ nhật không
bool isMouseInsideRect(int mouseX, int mouseY, int x, int y, int w, int h) {
    return mouseX >= x && mouseX < x + w &&
           mouseY >= y && mouseY < y + h;
}
