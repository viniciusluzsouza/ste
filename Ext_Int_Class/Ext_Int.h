#include <avr/io.h>
#include "Singleton.h"

#ifndef EXT_INT_H_
#define EXT_INT_H_

#define EICR(_x) _SFR_MEM8((0x69 + (_x)))
#define IHV(_y) _VECTOR((_y + 1))
#define MSK(_int) (1 << (_int))
#define EICR_mode(_i,_z) ((_z) << (2*(_i)))

namespace EXT_INT{
  typedef void(*CALLBACK_t)(void);

  class Ext_Int : public Singleton<Ext_Int> {

    public:
      static Ext_Int * ExtInt_Singletons[8];
      enum ISC_t {
        LOW = 0,
        ANY = 1,
        FALLING = 2,
        RISING = 3,
      };

      enum Intx_t {
        Int0 = 0,
        Int1 = 1,
        Int2 = 2,
        Int3 = 3,
        Int4 = 4,
        Int5 = 5,
        Int6 = 6,
        Int7 = 7,

      };

      Ext_Int(Intx_t ID, ISC_t int_config, CALLBACK_t pcallback);
      ~Ext_Int(){};
      void enable();
      void disable();
      void callback(){(*_pcallback)();};
      uint8_t get_id(){return _id;};

    private:
      uint8_t _id;
      CALLBACK_t _pcallback;
      bool _AB;

  };

};
#endif /* EXT_INT_H_ */
