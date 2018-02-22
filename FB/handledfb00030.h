/* ФБ "Архиватор R7 универсальный (тип 18)" */

typedef struct {
	Register_type Enable;      // bit
	Register_type R7Data[R7_BodySize];
} fb00030_IN_type;

typedef struct {
	Register_type Ok;
} fb00030_OUT_type;
u32 fb00030_var_size(u8 type);
