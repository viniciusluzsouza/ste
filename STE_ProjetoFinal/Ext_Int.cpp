#include "Ext_Int.h"
#include <avr/io.h>
#include <avr/interrupt.h>

using namespace EXT_INT;

    Ext_Int * Ext_Int::ExtInt_Singletons[8];

    ISR(INT0_vect){Ext_Int::ExtInt_Singletons[0]->callback();}

    ISR(INT1_vect){Ext_Int::ExtInt_Singletons[1]->callback();}

    ISR(INT2_vect){Ext_Int::ExtInt_Singletons[2]->callback();}

    ISR(INT3_vect){Ext_Int::ExtInt_Singletons[3]->callback();}

    ISR(INT4_vect){Ext_Int::ExtInt_Singletons[4]->callback();}

    ISR(INT5_vect){Ext_Int::ExtInt_Singletons[5]->callback();}

    ISR(INT6_vect){Ext_Int::ExtInt_Singletons[6]->callback();}

    ISR(INT7_vect){Ext_Int::ExtInt_Singletons[7]->callback();}


    Ext_Int::Ext_Int(Intx_t ID, ISC_t int_config, CALLBACK_t pcallback){
            uint8_t msk = ( (ID % 4 )*2);
            disable();
            if(ID & 16){
                _AB = true;
                //EICRB = (EICRB & ~(3 << msk)) | (int_config << msk);
            }else{
                _AB = false;
                //EICRA = (EICRA & ~(3 << msk)) | (int_config << msk);
            }
            EICR(_AB) &= ~(EICR_mode((ID & ~(4)), 3));
            EICR(_AB) |= EICR_mode((ID & ~(4)), int_config);
            EIFR |= MSK(ID);

            _pcallback = pcallback;
            _id = ID;
            ExtInt_Singletons[_id] = this;
    }

    void Ext_Int::enable(){EIMSK  |= MSK(_id);}
    void Ext_Int::disable(){EIMSK  &= ~(MSK(_id));}
