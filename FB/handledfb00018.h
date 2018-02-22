/* ФБ "Алгебраическое возведение в степень" */

typedef struct {
  Register_type Value;
  Register_type Power;
} fb00018_IN_type;

typedef struct {
  Register_type Output;
  Register_type Overflow;
} fb00018_OUT_type;
u32 fb00018_var_size(u8 type);
