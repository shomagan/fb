#include "kernel.h"
struct fb_branch{
  u32 output_fb_number;
  u16 output_gate_number;
  u32 input_fb_number;
  u16 input_gate_number;
  u16 address;
};
struct fb_visual{
	Register_type* in_out_reg;	//full buffer for data
	u32 reg_number;
	u32 order_number;
	u16 type;
};
