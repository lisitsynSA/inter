enum MSG_CODE {
    PING = 0,
    ECHO = 1,
    STATUS = 2,
    RUN = 3,
    FILENAME = 4,
    FILEDATA = 5,
    IO = 6
};

// SEND = TransmitBuffer
// RECEIVE = ReceiveBuffer
// Buffer[0] - HID CODE
// Buffer[1] - MSG CODE
// Buffer[2] - SIZE
// Buffer[4..63] - MSG
