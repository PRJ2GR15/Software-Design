#ifndef COMMINTERFACE_H
#define COMMINTERFACE_H


class CommInterface
{
public:
    CommInterface() {
        int a = 0;
    }

    //Placeholder
    bool getUnitStatus(unsigned char ID) {
        return true;
    }
private:
    int a;
};

#endif // COMMINTERFACE_H
