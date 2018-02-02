char parse_json_fb_file(const char *path);
char parse_json_fb_array_file(const char *path);
uint32_t parse_fb32_file(const char *path,char* pFB);
uint32_t first_cycle(void);
struct fb_data{
  unsigned int ordinal_fb_number;
  unsigned short type_fb_number;
  Register_type* input;
  Register_type* var;
  Register_type* output;
  unsigned short input_number;
  unsigned short var_number;
  unsigned short output_number;
  struct fb_data* prev;
  struct fb_data* next;
};
