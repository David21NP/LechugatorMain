#include <Arduino.h>
#include <vector>

// #define SerialLogger Serial

namespace Lechugator
{
  class SerialObj
  {
  private:
    unsigned long baud = 0;

  public:
    HardwareSerial serialHardware = Serial;
    SerialObj(const HardwareSerial &_serialHardware, const unsigned long &_baud) : serialHardware(_serialHardware),
                                                                                   baud(_baud)
    {
    }
    SerialObj(const HardwareSerial &_serialHardware) : SerialObj(_serialHardware, 115200)
    {
    }
    SerialObj(const unsigned long &_baud) : SerialObj(Serial, _baud)
    {
    }
    SerialObj() : SerialObj(115200)
    {
    }
    void begin()
    {
      serialHardware.begin(baud);
    }
  };

  class SerialLogger
  {
  private:
    std::vector<SerialObj> serialObjs;

  public:
    SerialLogger();
    ~SerialLogger();
    SerialLogger(const unsigned long &_baud);

    void initLoggers();

    void addLogger(const HardwareSerial &_serialHardware, const unsigned long &_baud);
    void addLogger(const HardwareSerial &_serialHardware);
    void addLogger(const unsigned long &_baud);
    void addLogger();

    void print(auto x);
    void println(auto x);
  };

  SerialLogger::SerialLogger()
  {
    serialObjs.push_back(SerialObj());
  }
  SerialLogger::SerialLogger(const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_baud));
  }

  void SerialLogger::addLogger(const HardwareSerial &_serialHardware, const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_serialHardware, _baud));
  }
  void SerialLogger::addLogger(const HardwareSerial &_serialHardware)
  {
    serialObjs.push_back(SerialObj(_serialHardware));
  }
  void SerialLogger::addLogger(const unsigned long &_baud)
  {
    serialObjs.push_back(SerialObj(_baud));
  }
  void SerialLogger::addLogger()
  {
    serialObjs.push_back(SerialObj());
  }

  void SerialLogger::print(auto x)
  {
    for (SerialObj &serialObj : serialObjs)
    {
      serialObj.serialHardware.print(x);
    }
  }
  void SerialLogger::println(auto x)
  {
    for (SerialObj &serialObj : serialObjs)
    {
      serialObj.serialHardware.println(x);
    }
  }

  void SerialLogger::initLoggers()
  {
    for (SerialObj &serialObj : serialObjs)
    {
      serialObj.begin();
    }
  }

  SerialLogger::~SerialLogger()
  {
    serialObjs.clear();
  }

} // namespace Lechugator
