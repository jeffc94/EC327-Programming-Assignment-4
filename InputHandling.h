#ifndef __InputHandling__
#define __InputHandling__

class InvalidInput
{
public:
    InvalidInput(char* in_ptr): msg_ptr(in_ptr) {}
    const char* const msg_ptr;
private:
    InvalidInput();
};

#endif //
