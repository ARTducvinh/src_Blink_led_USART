// filepath: c:\Users\ducvi\OneDrive\Máy tính\Code_Usart\src\syscalls.c
#include <sys/types.h>
#include <errno.h>

typedef char *caddr_t;

extern char _end;
static char *heap_end;

caddr_t _sbrk(int incr) {
    if (heap_end == 0) {
        heap_end = &_end;
    }
    char *prev_heap_end = heap_end;
    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

// Định nghĩa _write để tránh lỗi liên kết
int _write(int file, char *ptr, int len) {
    // Nếu muốn xuất ra UART, có thể gửi từng ký tự ở đây
    // for (int i = 0; i < len; i++) {
    //     USART2_SendChar(ptr[i]);
    // }
    return len;
}

int _read(int file, char *ptr, int len) {
    // Nếu muốn nhận dữ liệu từ UART, có thể đọc từng ký tự ở đây
    // for (int i = 0; i < len; i++) {
    //     ptr[i] = USART2_ReceiveChar(); // Bạn cần tự viết hàm này nếu muốn
    // }
    // Ở đây trả về 0 để báo không có dữ liệu
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    // Không hỗ trợ seek, trả về -1 (lỗi)
    return -1;
}

int _close(int file) {
    // Không hỗ trợ đóng file, trả về -1 (lỗi)
    return -1;
}

int _fstat(int file, void *st) {
    // Giả lập thiết bị character (terminal)
    return 0;
}

int _isatty(int file) {
    // Luôn là thiết bị terminal
    return 1;
}