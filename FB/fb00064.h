/* ФБ "Вычислитель Кнап" */

#define MaxLenDNM   200   // Максимальное кол-во точек ДНМ
#define NCorr	    201   // Кол-во точек ДНМ
#define nF          9     // Кол-во коэффициентов ряда Фурье (?)

// Входы
typedef struct {
	Register_type Start;              // bit      // Начать рассчёт ДНМ
	Register_type LenDNM_in;          // uint8-16 // кол-во элементов в массиве ДНМ
	Register_type DNM_in[MaxLenDNM];  // uint8-16 // Массив ДНМ
} fb00064_IN_type;

// Внутренние переменные
typedef struct {
	Register_type P2_idx;           // uint8 // индекс второй "опорной" точки
	Register_type P4_idx;           // uint8 // индекс четвертой "опорной" точки
	Register_type LenDNM;           // Кол-во точек в ДНМ
  
	Register_type BufCor[NCorr];    // Массив uint8
	Register_type BufCor_F[NCorr];  // Массив uint8
  
	Register_type aFourier[nF];     // float32
	Register_type bFourier[nF];     // float32
	Register_type omega;            // float32
	Register_type da1;              // float32
	Register_type da2;              // float32
	Register_type x;                // float32
	Register_type cos_nx;           // float32
	Register_type sin_nx;           // float32
	Register_type cos_x;            // float32
	Register_type sin_x;            // float32
	Register_type roo;              // float32
	Register_type d1;               // float32
	Register_type d2;               // float32
	Register_type cond1;            // float32
} fb00064_VAR_type;

// Выходы
typedef struct {
	Register_type Stage;            // uint8  // Стадия вычислений
	Register_type Knap;             // uint8  // Коэффициент наполнения в % // Эффективный ход плунжера в %
	Register_type KnapOK;           // bit    // 1 когда на выходе Knap - рассчитанный коэффициент
} fb00064_OUT_type;

float aro_cos_1(float x, float epsilon);
float aro_sin_1(float x, float epsilon);
float aro_sin(float x);
float aro_cos(float x);
float aro_sqrt_1(float x, float epsilon);
float aro_sqrt(float x);
unsigned char get_P_idx(short cside, unsigned char i_start, unsigned char i_end, Register_type y_1[]);
float aro_eml_sub2norm(float x[], int istart, int iend);
float get_beta(float alphr, float xnorm);
void aro_polyfit1(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2);
void aro_polyfit2(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2, float *c3);
void aro_polyfit3(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2, float *c3, float *c4);

u32 fb00064_var_size(u8 type);
