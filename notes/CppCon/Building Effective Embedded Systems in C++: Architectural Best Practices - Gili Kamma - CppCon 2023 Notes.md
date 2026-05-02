Original Source: https://www.youtube.com/watch?v=xv7jf2jQezI
# Notes:
- For hard real-time constraints, in the order of micro-seconds or below, it is easier to meet deadlines when there is no operating system or if you bypass the operating system via custom kernel modules.
- Keep the number of threads in your application to the minimum, to avoid complexity and execution order issues. Lesser threads is better.
- The execution order of almost all embedded systems looks like this:
```
while(true) {
   GetSensorInputs();
   ReceiveAllMsgs();
   DoLogic();
   SendAllMsgs();
   SetOutputs();
   sleep(time_period);
};
```
- Separate the logic layer from the hardware layer
  - the application/logic layer should only return the desired HW state, but not control the HW directly
  - the application layer must be unit testable, without any HW mocking
  - more HW mocking implies tighter coupling, which is not a good thing
  - the HW interface should strive for minimalism:
```
class UartInterface {
   public:
     bool Init(int32_t baudrate);
     bool Write(char* buffer, size_t size);
     size_t Read(char* buffer, size_t maxSize);
   };
 ```
  - Disconnect the logic from the network
    - Thread #1 -> logic
    - Thread #2 -> Rx/Tx from the network
  - Logging:
    - add timestamps w/ milli-sec resolution
  - add metadata- log level, thread ID, etc
    - use the same log configuration
    - log with numerical data, not just text
