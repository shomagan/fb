/* ФБ "уставка" */
#include "../kernel.h"
typedef struct {
  Register_type Max;      // bit/uint8/uint16/uint32/float // 
  Register_type Min;      // bit/uint8/uint16/uint32/float // 
  Register_type Default;  // bit/uint8/uint16/uint32/float // 
	Register_type SetDefault;  // bit
} fb00102_IN_type;
typedef struct {
	Register_type Variable[256]; // bit/uint8/uint16/uint32/float // 
} fb00102_OUT_type;
void fb00102_exec(void);
u32 fb00102_var_size(u8 type);
