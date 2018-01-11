/* ФБ "Мультиплексор (до 32 входов)" */

#define Channels    64

typedef struct {
	Register_type Channel;
	Register_type Inputs[Channels];
} fb00022_IN_type;

typedef struct {
	Register_type Output;
} fb00022_OUT_type;
u32 fb00022_var_size(u8 type);
